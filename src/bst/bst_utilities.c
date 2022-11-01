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

void debug_print_node(Node* node, int level, const char* position) {
    printf("{value:\"%s\", level: %d, position: %s next_char: [ ", node->content, level, position);
    printf("%d", node->state_len);
    for(int i = 0; i < (int) node->state_len; i++) {
        printf("{'%c', frequency: %f},", node->next_state[i].character, node->next_state[i].probability);
    }
    printf("},\n");

    if(node->left) {
        debug_print_node(node->left, level +1, "left");
    }
    if(node->right) {
        debug_print_node(node->right, level +1, "right");
    }
}

void debug_print_tree(Tree* tree) {
    debug_print_node(tree->nodes[tree->root], 0, "root");
}
