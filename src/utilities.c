#include <stdio.h>
#include <stdlib.h>
#include <utilities.h>

/* Function: display_usage
 * -------------------------
 * Show the program's help page
 */
void display_usage(void) {
    printf("Usage: shakespeare [-h] [-s <n>] [-l <m>] [-f <file>]\n");
    printf("Options:\n");
    printf(" -f     Input file\n");
    printf(" -l     Output length\n");
    printf(" -s     Length of input string\n");
    printf(" -h     Print help page\n");
}

/* Function: graceful_exit
 * -------------------------
 * End the program while either printing an error message into stderr, or
 * display the program's help page.
 * 
 * error_message | pointer to a string that contains an error message
 */
void graceful_exit(const char* error_message) {
    if(error_message)
        fprintf(stderr, error_message);
    else
        display_usage();

    exit(EXIT_FAILURE);
}