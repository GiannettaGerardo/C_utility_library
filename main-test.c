#include <stdio.h>
#include "administration.h"

int main(void) {
    
    // TEST INTEGER
    int max = 1000;
    int min = -1000;
    int integer = 0;

    printf("Enter a number between %d and %d. You can try to insert spaces, letters and strings:\n", min, max);
    do {

        // the number taken in input will be cut after exceeding the n digits allowed by the input parameter
        integer = input_integer(MAX_INTEGER);   // use the constant MAX_INTEGER = 8 of the administration.h to maximize safety

    } while (!check_numeric_limits(integer, min, max)); 

    printf("integer: %d\n", integer); // output

    // if you want to insert a short integer, you can use a manual cast + a specific constant, always defined in administration.h
    puts("Enter an integer, it will be changed to short securely:");
    short integer_short = (short)input_integer(MAX_INTEGER_SHORT); // MAX_INTEGER_SHORT = 5

    printf("short: %hd\n", integer_short); // output


    // TEST STRING
    char string[MAX_STRING] = {0};

    printf("Enter a string of max %d characters, min %d characters, with no numbers and no special characters:\n", REAL_MAX_STRING, MIN_STRING);
    // REAL_MAX_STRING is MAX_STRING - ADDITION = 22 - 2 = 20
    do {
        
        input_string(string, MAX_STRING);  // MAX_STRING = 20+2 to control the max length

     // use the constant of the administration.h to maximize safety
    } while (!check_string(string, MAX_STRING, MIN_STRING, YES_SPACES, NO_DIGITS_SPECIAL_CHAR));

    printf("string: %s\n", string); // output

    return 0;
}