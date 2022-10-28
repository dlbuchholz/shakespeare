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

#include <bst/io.h>
#include <bst/utilities.h>
#include <stdio.h>
#include <unistd.h>
#include <fileio.h>
#include <macros.h>
#include <markov.h>

void display_usage() {
    printf("Usage: shakespeare [options] [-f file]\n");
    printf("Options:\n");
    printf(" -f     Input file\n");
    printf(" -l     Output length\n");
    printf(" -s     Length of input string\n");
    printf(" -h     Print help page\n");
}

int main (int argc, char **argv) {
    char* file_name = "";
    int word_count = 1;
    int output_length = 6000;

    int option;
    while((option = getopt(argc, argv, "f:sl")) != -1 ) {
        switch (option) {
            break;
            case 'l':
            output_length = atoi(optarg);
            break;
            case 's':
            word_count = atoi(optarg);
            break;
            case 'f':
            if (access(optarg, F_OK) == 0 )
                file_name = optarg;
            else {
                fprintf(stderr, "Error: Unable to access file!");
                exit(EXIT_FAILURE);
            }
        }
    }

    Tree* tree = tree_from_file(file_name, strlen("Friedrich"));

    //print_tree(tree);
    #ifdef DEBUG
    //debug_print_tree(tree);
    #endif
    generate_text(tree, "Friedrich", strlen("Friedrich"), output_length);

    
    tree_destroy(tree);
}