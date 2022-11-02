#include <argparsing.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


/* Function: parse_arguments
 * -------------------------
 * Parse the program's arguments using getopt()
 * 
 * INPUT:
 * argc          | amount of program arguments
 * argv          | pointer to an array of program arguments
 * file_name     | pointer to memory location of string
 * 
 * OUTPUT:
 * input_length  | pointer of input size 
 * output_length | pointer of output size
 */
void parse_arguments(int argc, char **argv, char* file_name,
                     size_t *input_length, size_t *output_length) {
    /* Declaring and initializing unsigned integers to read the program's
     * arguments into.
     *
     * Note: This is a workaround. Reading directly into input_length and
     * output_length would make more sense, but the format specifier `%zu`
     * for size_t is not supported by MinGW's gcc (despite size_t being
     * standardized since C89 and `%zu` being standardized since C99).
     */
    unsigned int i_len = 1;
    unsigned int o_len = 0;
    
    int option;
    while((option = getopt(argc, argv, "f:l:s:h")) != -1 ) {
        switch (option) {
            case 'l':
            if(sscanf(optarg, "%u", &o_len) != 1) {
                fprintf(stderr, "Error: Invalid output length");
                exit(EXIT_FAILURE);
            }
            break;

            case 's':
            if(sscanf(optarg, "%u", &i_len) != 1) {
                fprintf(stderr, "Error: Invalid input length");
                exit(EXIT_FAILURE);
            }
            break;
            
            case 'f':
            if (access(optarg, F_OK) == 0 && (file_name != NULL))
                strcpy(file_name, optarg);
            else {
                fprintf(stderr, "Error: Unable to access file!");
                exit(EXIT_FAILURE);
            }
            break;
        }
    }

    /* Explicit type casts to make the compiler happy :) */
    *input_length = (size_t) i_len;
    *output_length = (size_t) o_len;
}
