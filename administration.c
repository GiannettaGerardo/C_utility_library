/// Include the header file for this .c:
#include "administration.h"

/// Include util libraries:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/// Procedure/function implementation:


/**
 * A function that uses the input_string procedure to take a string as input 
 * and the check_interface function to convert it to an integer, checking its validity.
 * Protects the code from inserting characters / strings instead of integers.
 *
 * @pre integer_length > 1
 *
 * @post integer == 0
 *       integer != null
 */
int input_integer(short integer_length) {

    /** Check the minimum acceptable length for the integer, if 
     * the value is less than 2, it returns the error value -99. */
    if (integer_length < MIN_INTEGER_LENGTH) {
        fprintf(stderr, "\nERROR: The minimum length of the integer cannot be accepted. The return value is 0.\n");
        return 0;
    }

    int integer = 0;
    int flag = 0;						       /// it serves to repeat the cycle
    char main_string[MAX_STRING] = {0}; 	   /// the string that I will pass in input to the procedure input_string

    do {
    	/// I call the procedure to take the string as input (which should be a numeric value)
	input_string(main_string, integer_length);

	/** I call the function that checks if the string taken in input is a number or not, if 
	 * it returns 1, the flag is set to 1 and exits, otherwise the cycle is repeated. */
	if (check_integer(&integer, main_string) == 1) {
		flag = 1;
	}
	else {
		fprintf(stderr, "ERROR: Enter a value that is numeric.\n");
	}

	/** if flag is still set to 0, repeat the input, if flag is 1, exit. */
     } while (flag == 0);

     return integer;
}


/**
 * Function that checks if the string passed as a parameter is an integer or not.
 *
 * @pre stringa_principale != null
 *      intero != null
 *
 * @post the function returns 1 or 0.
 */
int check_integer(int * integer, char * main_string) {

    char * remaining_string = 0;       /// here the remaining string is stored after separation from numeric values

    /// remove a null string bug
    if (isdigit(main_string[0]) == 0) {
        return 0;
    }
  
    /** the strtol () function returns a long int to the integer variable
     * if there is a number as string passed (string variable),
     * all symbols not recognized as numbers are separated and put in the remaining_string.
     * Casting is also done in int. */
    *integer = (int) strtol(main_string, &remaining_string, 0);

    /// if the remaining string is empty, it returns 1, otherwise 0.
    if (strcmp(remaining_string, "") == 0) {
        return 1;
    }

    return 0;
}



/**
 * Function that checks a general string. Check that the length does not exceed
 * maximum or not less than minimum, the string is not empty. Check in base
 * to a flag the presence of spaces and based on another flag it checks the presence of
 * numbers and special characters. Finally, using another procedure, print all errors.
 *
 * @pre string (the variable must have already been filled)
 *      flag_space (can be set to any integer)
 *      flag_numeri_and_car_speciali (can be set to any integer)
 *      max_length (the maximum length of the string must be 2 characters more than what you 
 *                  want to obtain, so that you can perform an effective check on the length)
 *      min_length > 0
 *      flag_space == (YES_SPACES (0) or NO_SPACES (1))
 *      flag_digits_special_char == (YES_DIGITS_SPECIAL_CHAR (0) or NO_DIGITS_SPECIAL_CHAR (1))
 * 
 * @post the returned value will be 0 (error) or 1 (no error)
 */
int check_string(char * string, unsigned short max_length, unsigned short min_length, short flag_space, short flag_digits_special_char) {

    short error_spaces = 0;
    short error_initial_space = 0;
    short error_special_char = 0;
    short error_digits = 0;
    short error_empty_string = 0;
    short error_min_length = 0;
    short error_max_length = 0;
    short error_graphic_char = 0;

    short general_error = 0;      /// reports that there is at least one (or none) error in the string

    /**
     * if the flag has been set to 1 between the parameters, check that the inserted string has no spaces.
     * If the parameter is a value other than 1 (for convenience I'll use 0) it will only check that
     * the string does not start with a space.
     */
     if (flag_space == 1) {
         /// I call the function that checks that there are no spaces in the string
         if (check_spaces(string) == 0) {
	     error_spaces = 1;
         }
         else if (check_spaces(string) == 2) {
	     error_empty_string = 1;
         }
     }
     else {
     	/// I check that the string doesn't start with a space
     	if (string[0] == ' ') {
     		error_initial_space = 1;
     	}
     }

    /**
     * if the flag is set to 1 among the parameters, check that the inserted string has no numbers
     * and special characters by calling 2 specific functions.
     */
    if (flag_digits_special_char == 1) {

        /// I call the function that checks that there are no numbers inside the inserted string
        if (check_numeric_string(string) == 0) {
            error_digits = 1;
        }
        else if (check_numeric_string(string) == 2) {
            error_empty_string = 1;
        }

        /// I call the function that checks that there are no special characters
        if (check_special_characters(string) == 0) {
            error_special_char = 1;
        }
    }

    /// check that the string does not contain unrepresentable characters
    if (check_graphic_characters(string) == 0) {
    	error_graphic_char = 1;
    }

    /// check that the maximum length has not been exceeded
    if (strlen(string) > max_length - ADDITION) {
        error_max_length = 1;
    }

    /// check that the string respects a minimum length
    if (strlen(string) < min_length) {
	    error_min_length = 1;
    }

    /**
     * sum all flags into a general one, if the flags are all set to 0, the general flag will be 0,
     * no errors will be reported and 1 will be returned, otherwise if only one of the flags is set to 1,
     * the sum of the general flag will be greater than 0 and the function that prints all errors will be called
     * appropriate, finally returns 0.
     */
    general_error = error_spaces + error_initial_space + error_special_char + error_digits + error_empty_string + error_min_length + error_max_length + error_graphic_char;

    if (general_error > 0) {
        string_control_errors(error_spaces, error_initial_space, error_special_char, error_digits, error_empty_string, error_min_length, error_max_length, error_graphic_char);
        return 0;
    }

    return 1;
}



/**
 * Procedure that prints error messages (on string checking)
 * based on the value of the error flags passed as parameters.
 *
 * @pre error_spaces (it can be any integer, but to have an effect it must be set to 1)
 * @pre initial_space_error ( ... )
 * @pre error_car_speciali ( ... )
 * @pre error_numbers ( ... )
 * @pre error_string_empty ( ... )
 * @pre error_lun_minima ( ... )
 * @pre error_lun_massima ( ... )
 */
void string_control_errors(short error_spaces, short error_initial_space, short error_special_char, short error_digits, short error_empty_string, short error_min_length, short error_max_length, short error_graphic_char) {

    /// check all flags and print all appropriate error messages
    if (error_spaces == 1) {
        fprintf(stderr, "ERROR: The space character is not allowed.\n");
    }
    if (error_initial_space == 1) {
        fprintf(stderr, "ERROR: Initial space not allowed.\n");
    }
    if (error_special_char == 1) {
        fprintf(stderr, "ERROR: It is forbidden to enter special characters.\n");
    }
    if (error_digits == 1) {
        fprintf(stderr, "ERROR: It is forbidden to enter numbers.\n");
    }
    if (error_empty_string == 1) {
        fprintf(stderr, "ERROR: Null entry.\n");
    }
    if (error_min_length == 1) {
        fprintf(stderr, "ERROR: Minimum length not reached.\n");
    }
    if (error_max_length == 1) {
        fprintf(stderr, "ERROR: Maximum length exceeded.\n");
    }
    if (error_graphic_char == 1) {
    	fprintf(stderr, "ERROR: It is forbidden to enter no graphic characters.\n");
    }
}


/**
 * Function that checks if the inserted string contains characters that cannot be represented graphically or not.
 * The space character is not counted.
 *
 * @pre string != null
 *
 * @post the returned value will be 0, 1
 */
int check_graphic_characters(char * string) {

	short i = 0;
	while (string[i] != '\0') {

		if (isgraph(string[i]) == 0) {
			if (string[i] != ' ') {
				return 0;
			}
		}
		i++;
	}

	return 1;
}



/**
 * Function that checks whether or not special characters exist within the string passed as a parameter.
 * All special characters in C: ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~
 *
 * @pre string != null
 *
 * @post the returned value will be 0, 1
 */
int check_special_characters(char * string) {

    short i = 0;
    while (string[i] != '\0') {
        if (ispunct(string[i]) != 0) {
            return 0;
        }
        i++;
    }

    return 1;
}



/**
 * Function that checks whether or not there are spaces within the string passed as a parameter.
 *
 * @pre string != null
 *
 * @post the returned value will be 0, 1
 */
int check_spaces(char * string) {

    short i = 0;
    while (string[i] != '\0') {
        if (string[i] == ' ') {
            return 0;
        }
        i++;
    }
    return 1;
}


/**
 * Function that checks that the string passed as a parameter does not contain numbers.
 *
 * @pre string != null
 *
 * @post the function returns 0, 1
 */
int check_numeric_string(char * string) {

    short i = 0;
    while (string[i] != '\0') {
        if (isdigit(string[i]) > 0) {
            return 0;
        }
        i++;
    }

    return 1;
}



/**
 * @authors: Gerardo Giannetta - Francesco Catignano ( https://github.com/catignanof )
 *
 * Procedure that takes as input a string of maximum length passed as a parameter,
 * accepts spaces and clears the buffer of remaining characters.
 * (simulates the operation of fgets and fixes the bug with the buffer).
 *
 * @pre string (the variable, if already written, will be overwritten).
 */
void input_string(char * string, unsigned short int max_length) {

    char empty_buffer;		          /// support variable to empty the buffer
    unsigned short int i = 0;         /// cycle index
    unsigned short int found = 0;     /// flag to signal the presence of a newline character
    unsigned short int length = 0;    /// it is used to memorize the length of the input string

    printf("%s", ">>> ");

    /// take a string as input until you hit enter
    while ((i < max_length) && (string[i - 1] != '\n')) {

        string[i] = getchar();
        i++;

    }

    /** checks the length of the string just taken as input.
     * If a newline character is found, exit the loop.
     * If the newline character is not found in the bounds
     * of the length of the string, it means that this will be
     * longer than necessary. 
     */
    while ((string[length] != '\n') && (length < max_length) && (found == 0)) {

        length++;

        if(string[length] == '\n'){
          found = 1;
        }
    }

    /** if the length is acceptable based on the passed input parameter,
     * add the end-of-string character at the end.
     * Otherwise, if the length goes beyond the maximum allowed,
     * add the end of string character in the last acceptable position
     * (actually cutting the string) and clear the buffer.
     */
    if (length < max_length) {
        string[i - 1] = '\0';
    }
    else {
        string[max_length - 1] = '\0';
        while ((empty_buffer = getchar()) != '\n' && empty_buffer != EOF);
    }
}



/**
 * Function that checks if a number is inside or outside a certain numeric range.
 * It also prints an accurate error message based on the error.
 *
 * @pre number != null
 *      limite_minimo != limite_massimo
 *
 * @post The function returns 0 or 1.
 */
int check_numeric_limits(int number, int min_limit, int max_limit) {

    if (number < min_limit) {
        fprintf(stderr, "The number entered is less than the minimum limit [%d].\n", min_limit);
        return 0;
    }
    if (number > max_limit) {
        fprintf(stderr, "The number entered is greater than the maximum limit [%d].\n", max_limit);
        return 0;
    }
    return 1;
}
