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

Tree* tree_from_file(const char* fname) {
    FILE* file = fopen(fname, "r");
    Tree *tree = tree_new(get_file_size(NULL, file));
    if(!file) {
        exit(EXIT_FAILURE);
    }

    int c = getc(file);

    // Save length of each word while reading the file to avoid using
    // strlen() for the rest of the program.
    int len = 0;
    char buffer[100] = "";
    Node* root = NULL;

    while (c != EOF) {
        if(c == ' ' || c == '\n') {
            root = node_insert(root, buffer, len);
            if(root) {
                tree->nodes[tree->node_len++] = root;
            }
            strcpy(buffer, "");
            len = 0;
        } else {
            strncat(buffer, &c, 1);
            len++;
        }
        c = getc(file);
    }

    fclose(file);
    return tree;
}