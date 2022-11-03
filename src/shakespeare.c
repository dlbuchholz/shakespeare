/*
 * shakespeare.c
 *
 * Author: Dennis Lucas Buchholz
 * Date: 20.10.2022 - 01.11.2022
 *
 */

#include <argparsing.h>
#include <bst/utilities.h>
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
    FILE* file = stdin;
    /* Maximum length of a filename is 255 characters
     * (+1 character for null-terminator) */
    char* file_name = malloc(sizeof(char) * 256);
    /*                 ^^^^ gets freed in line 38 */
    file_name[0] = '\0';

    /* No need to initialize variables since they get initialized in
     *  parse_arguments() */
    size_t input_length, output_length;

    parse_arguments(argc, argv, file_name, &input_length, &output_length);

    if(file_name[0] != '\0') {
        file = fopen(file_name, "r");
        FREE_IF_EXISTS(file_name);
        if(!file)
            graceful_exit("Error: Could not read file");
    }

    /* Reserve memory location for `search string`
     * It's size is the specificed input size + 1 (for null-terminator) */
    char* search_string = calloc((input_length + 1), sizeof(char));
    /*                     ^^^^ gets freed in model_destroy */
    search_string[input_length+1] = '\0';

    MarkovModel* model = model_new(file, search_string, input_length, output_length);
    fclose(file);

#ifdef DEBUG
    //debug_print_tree(model->tree);
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

void graceful_exit(const char* error_message) {
    if(error_message)
        fprintf(stderr, error_message);
    else
        display_usage();

    exit(EXIT_FAILURE);
}