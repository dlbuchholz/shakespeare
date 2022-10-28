////////////////////////////////////////////////////////////////////////////////
// linked_list.c                                                              //
//                                                                            //
// Dieser Quellcode beinhaltet die Implementation einer verketteten Liste,    //
// welche Namen enthält.                                                      //
//                                                                            //
// Erstellt am: 19.10.2022                                                    //
//       Autor: Dennis Lucas Buchholz                                         //
////////////////////////////////////////////////////////////////////////////////
#include <bst/io.h>
#include <macros.h>
#include <markov.h>

Tree* tree_from_file(const char* fname, int input_length) {
    FILE* file = fopen(fname, "r");
    if(!file) {
        fprintf(stderr, "Error: Unable to open file!");
        exit(EXIT_FAILURE);
    }
    Tree *tree = tree_new(get_file_size(NULL, file));

    int c = getc(file);
    int found_word = 0;

    // Save length of each word while reading the file to avoid using
    // strlen() for the rest of the program.
    int len = 1;
    char buffer[5] = "";
    Node* root = NULL;

    while(c != EOF) {
        strncat(buffer, &c, 1);

        if(len == input_length+1) {
            root = node_insert(root, buffer, len);
            tree->nodes[tree->node_len++] = root;
            shift_string(buffer, len);
        } else {
            len++;
        }

         c = getc(file);
    }

    fclose(file);
    calculate_probabilities(tree->nodes[tree->root]);
    tree->nodes = realloc(tree->nodes, tree->node_len * sizeof(Node*));

    return tree;
}