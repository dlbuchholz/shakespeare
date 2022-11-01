////////////////////////////////////////////////////////////////////////////////
// shakespeare.c                                                              //
//                                                                            //
// Dieser Quellcode beinhaltet die Implementation                             //
// eines Filters in der Programmiersprache C, welcher es                      //
// ermöglicht Wörter, Zeichen und Zeilen einer                                //
// Datei zu zählen.                                                           //
//                                                                            //
// Erstellt am: 20. - X.10.2022                                               //
//       Autor: Dennis Lucas Buchholz                                         //
////////////////////////////////////////////////////////////////////////////////

#include <argparsing.h>
#include <bst/utilities.h>
#include <file_io.h>
#include <stdio.h>
#include <macros.h>
#include <markov/model.h>
#include <shakespeare.h>

void display_usage(void) {
    printf("Usage: shakespeare [options] [-f file]\n");
    printf("Options:\n");
    printf(" -f     Input file\n");
    printf(" -l     Output length\n");
    printf(" -s     Length of input string\n");
    printf(" -h     Print help page\n");
}

int main (int argc, char **argv) {
    char* file_name = malloc(sizeof(char) * 256);
    size_t output_length = 0;
    size_t input_length = 1;
    parse_arguments(argc, argv, file_name, &input_length, &output_length);

    FILE* file = fopen(file_name, "r");
    if(!file) {
        fprintf(stderr, "Error: Unable to open file!");
        exit(EXIT_FAILURE);
    }

    char* first_chars = malloc(sizeof(char) * (input_length+1));
    file_into_buffer(input_length, file, first_chars);
    first_chars[input_length] = '\0';

    MarkovModel* model = model_new(file, input_length, output_length);
    fclose(file);
    free(file_name);

    //print_tree(tree);
    #ifdef DEBUG
    //debug_print_tree(tree);
    #endif
    generate_text(model, first_chars);

    tree_destroy(model->tree);
    free(first_chars);
    free(model);
}