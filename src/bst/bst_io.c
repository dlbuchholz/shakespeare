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

Tree* tree_from_file(const char* fname) {
    FILE* file = fopen(fname, "r");
    if(!file) {
        fprintf(stderr, "Error: Unable to open file!");
        exit(EXIT_FAILURE);
    }
    Tree *tree = tree_new(get_file_size(NULL, file));

    int c = getc(file);
    int found_word = 0;
    int carry_over_char = 0;

    // Save length of each word while reading the file to avoid using
    // strlen() for the rest of the program.
    int len = 0;
    char buffer[100] = "";
    Node* root = NULL;

    while(c != EOF) {
        if(c == ' ' || c == '\n') {
            found_word = 1;
        } else {
            if(found_word) {
                root = node_insert(root, buffer, len, (char) c);
                tree->nodes[tree->node_len++] = root;
                memset(buffer, 0, 100);
                len = 0;
                found_word = 0;
            }
            strncat(buffer, &c, 1);
            len++;
        }

        c = getc(file);
    }

    fclose(file);

    tree->nodes = realloc(tree->nodes, tree->node_len * sizeof(Node*));

    return tree;
}