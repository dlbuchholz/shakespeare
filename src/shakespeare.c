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

void display_usage() {
    printf("Usage: shakespeare [options] [-i] file\n");
    printf("Options:\n");
    printf(" -c     Count characters of file\n");
    printf(" -w     Count words of file\n");
    printf(" -l     Count lines of file\n");
}

int main (int argc, char **argv) {
    char* file_name = "text.txt";
    int word_count = 1;
    int output_length = 0;
    Tree* tree = tree_from_file(file_name);
    Node* n = lookup(tree->nodes[tree->root], "Friedrich", strlen("Friedrich"));

    if(!n) {
        printf("String not found: %s", "Hello?");
    } else {
        printf("String found: %s", "Hello?");
    }

    print_tree(tree);
    debug_print_tree(tree);
    tree_destroy(tree);
}