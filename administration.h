/**
 *  @file administration
 *
 *  Description:
 *  This library contains functions and/or procedures to perform 'general' checks
 *  (not for specific problems of a project) or carry out general actions
 *  (for example take an integer as input).
 *
 *  @version 4.1
 *
 *  @date  10/06/2020
 *
 *  @author Gerardo Giannetta
 *
 */

/// Guard:
#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H

/// Definition of constants:


#define ADDITION 2                  /// indicates the additional value to add and subtract from the maximum length of a string

/** indicates the maximum accepted for a general string
 * (+1 for the terminator and +1 for checking the maximum string length) */
#define MAX_STRING 20+ADDITION

/// indicates the real length to use for string controls
#define REAL_MAX_STRING MAX_STRING-ADDITION

#define MIN_STRING 4                /// indicates the minimum accepted for a general string
#define MAX_INTEGER 8               /// indicates the accepted maximum of the string to be converted to integer
#define MAX_INTEGER_SHORT 5         /// indicates the maximum accepted by the string to be converted into short int
#define MIN_INTEGER_LENGTH 2        /// indicates the minimum length of an integer to be accepted
#define YES_SPACES 0                /// indicates that spaces can be entered in the string control
#define NO_SPACES 1                 /// indicates that no spaces can be entered in the string control

/// indicates that numbers and special characters can be entered in the string control
#define YES_DIGITS_SPECIAL_CHAR 0
/// indicates that numbers and special characters cannot be entered in the string check
#define NO_DIGITS_SPECIAL_CHAR 1


/// Definition of function prototypes:

/**
 * Function that protects the code from inserting characters / strings instead of integers.
 *
 * @param integer_length (indicates the maximum length of the number to be taken as input
 * (used to cut the number when it will be taken as a string as input)).
 *
 * @return integer derived from the inserted string.
 */
int input_integer(short integer_length);


/**
 * Function that checks if the string passed as a parameter is an integer or not.
 *
 * @param integer (empty integer variable to fill, passed as pointer).
 * @param main_string (string filled to perform the check).
 *
 * @return 1 (if the string passed by parameter is an integer),
 *         0 (if the string passed as a parameter is not completely an integer),
 *         *integer (integer value)
 */
int check_integer(int * integer, char * main_string);


/**
 * Function that checks a general string. Check that the length does not exceed
 * maximum or not less than minimum, the string is not empty. Check in base
 * to a flag the presence of spaces and based on another flag it checks the presence of
 * numbers and special characters. Finally, using another procedure, print all errors.
 *
 * @param string (string to check).
 * @param max_length (maximum of acceptable length).
 * @param min_length (minimum of acceptable length).
 * @param flag_space (flag that if set to 1 checks the presence of spaces in the string,
 *        otherwise avoid this check).
 * @param flag_digits_special_char (flag that if set to 1 checks the presence of numbers and
 *       special characters in the string, otherwise avoid this check).
 *
 * @return 0 (if the controls report an error), 1 (if the controls do not report an error).
 */
int check_string(char * string, unsigned short max_length, unsigned short min_length, short flag_space, short flag_digits_special_char);


/**
 * Procedure that prints error messages (on string checking)
 * based on the value of the error flags passed as parameters.
 *
 * @param error_spaces (signals the presence of spaces).
 * @param error_initial_space (signals the presence of a leading space).
 * @param error_special_char (signals the presence of special characters).
 * @param error_digits (indicates the presence of numbers).
 * @param error_empty_string (signals that the string is empty).
 * @param error_min_length (indicates that the length is less than the minimum).
 * @param error_max_length (signals that the length is greater than the maximum).
 * @param error_graphic_char (signals that the presence of non-graphic characters).
 */
void string_control_errors(short error_spaces, short error_initial_space, short error_special_char, short error_digits, short error_empty_string, short error_min_length, short error_max_length, short error_graphic_char);


/**
 * Function that checks if the inserted string contains characters that cannot be represented graphically or not.
 * The space character is not counted.
 *
 * @param string (string to check).
 *
 * @return 1 (if the string contains no invalid characters), 0 (if the string contains invalid characters).
 */
int check_graphic_characters(char * string);


/**
 * Function that checks whether or not special characters exist within the string passed as a parameter.
 *
 * @param string (string to check).
 *
 * @return 1 (if the string contains no invalid characters), 0 (if the string contains invalid characters).
 */
int check_special_characters(char * string);


/**
 * Function that checks whether or not there are spaces within the string passed as a parameter.
 *
 * @param string (string to check).
 *
 * @return 0 (if a space is found in the string), 1 (if no space is found in the string),
 */
int check_spaces(char * string);


/**
 * Function that checks that the string passed as a parameter does not contain numbers.
 *
 * @param string (string to check).
 *
 * @return 0 (if a number is found in the string), 1 (if no number is found in the string),
 */
int check_numeric_string(char * string);


/**
 * Procedure that takes as input a string of maximum length passed as a parameter,
 * accepts spaces and clears the buffer of remaining characters.
 *
 * @param string (empty char variable to fill).
 * @param max_length (maximum length allowed for the string).
 *
 * @return the same variable but filled in input.
 */
void input_string(char * string, unsigned short int max_length);



/**
 * Function that checks if a number is integer or outside a certain numeric range.
 *
 * @param number (number to check).
 * @param min_limit (represents the minimum value that the number can take).
 * @param max_limit (represents the maximum value that the number can take).
 *
 * @return 1 (if the number is inside the range), 0 (if the number is outside the range).
 */
int check_numeric_limits(int number, int min_limit, int max_limit);


#endif
