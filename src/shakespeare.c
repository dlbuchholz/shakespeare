/* 
 * shakespeare.c
 *
 * Author: Dennis Lucas Buchholz
 * Date: 20.10.2022 - 01.11.2022
 * 
 */

#include <argparsing.h>
#include <bst/utilities.h>
#include <file_io.h>
#include <stdio.h>
#include <macros.h>
#include <markov/model.h>
#include <shakespeare.h>

/* Function: main
 * --------------
 * The program's entry point.
 * 
 * argc | amount of program arguments
 * argv | pointer to an array of program arguments
 */
int main (int argc, char **argv) {

    /* Maximum length of a filename is 255 characters
     * (+1 character for null-terminator) */
    char* file_name = malloc(sizeof(char) * 256);
    /*                 ^^^^ gets freed in line 38 */

    /* No need to initialize variables since they get initialized in
     *  parse_arguments() */
    size_t input_length, output_length;

    parse_arguments(argc, argv, file_name, &input_length, &output_length);

    FILE* file = fopen(file_name, "r");
    free(file_name);
    if(!file) {
        fprintf(stderr, "Error: Unable to open file!");
        exit(EXIT_FAILURE);
    }


    /* Reserve memory location for `search string`
     * It's size is the specificed input size + 1 (for null-terminator) */
    char* search_string = malloc(sizeof(char) * (input_length + 1));
    /*                     ^^^^ gets freed in model_destroy */

    file_into_buffer(input_length, file, search_string);

    MarkovModel* model = model_new(file, input_length, output_length);
    fclose(file);

    #ifdef DEBUG
    debug_print_tree(model->tree);
    #endif
    generate_text(model, search_string);
    model_destroy(model);
}

/* Function: display_usage
 * -------------------------
 * Show the program's help page
 */
void display_usage(void) {
    printf("Usage: shakespeare [options] [-f file]\n");
    printf("Options:\n");
    printf(" -f     Input file\n");
    printf(" -l     Output length\n");
    printf(" -s     Length of input string\n");
    printf(" -h     Print help page\n");
}