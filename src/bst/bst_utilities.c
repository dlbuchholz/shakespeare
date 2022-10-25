////////////////////////////////////////////////////////////////////////////////
// linked_list.c                                                              //
//                                                                            //
// Dieser Quellcode beinhaltet die Implementation einer verketteten Liste,    //
// welche Namen enthält.                                                      //
//                                                                            //
// Erstellt am: 19.10.2022                                                    //
//       Autor: Dennis Lucas Buchholz                                         //
////////////////////////////////////////////////////////////////////////////////
#include <bst/utilities.h>

void print_node(Node* node, int indentation) {
    for(int i = 0; i < indentation; i++)
        printf(i == indentation - 1 ? "|-" : "  ");
    printf("%s\n", node->content);
    if(node->left) {
        print_node(node->left, indentation -1);
    }
    if(node->right) {
        print_node(node->right, indentation +1);
    }
}

void debug_print_node(Node* root, size_t node_len) {
    char **words = calloc(node_len, sizeof(char*));
    int index = 0;
    inorder_traversal(root, words, &index);
    printf("DEBUG: Constructed tree:\n[");
    for(int i = 0; i < node_len; i++)
        printf("%s, ", words[i]);
    printf("]\n");
    free(words);
}

void debug_print_node_2(Node* node, int level, char* position) {
    printf("{value:\"%s\", level: %d, position: %s}\n", node->content, level, position);
    if(node->left) {
        debug_print_node_2(node->left, level +1, "left");
    }
    if(node->right) {
        debug_print_node_2(node->right, level +1, "right");
    }
}

void debug_print_tree(Tree* tree) {
    debug_print_node(tree->nodes[tree->root], tree->node_len);
   // debug_print_node_2(tree->nodes[tree->root], 0, "root");
}

void print_tree(Tree* tree) {
    //print_node(tree->nodes[tree->root], 10);
}