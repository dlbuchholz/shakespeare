#include <bst/utilities.h>

void debug_print_node(Node* node, int level, const char* position) {
    printf("{value:\"%s\", level: %d, position: %s next_char: [ ", node->content, level, position);
    list_print(node->list_char);
    printf("},\n");

    if(node->left) {
        debug_print_node(node->left, level +1, "left");
    }
    if(node->right) {
        debug_print_node(node->right, level +1, "right");
    }
}

void debug_print_tree(Tree* tree) {
    debug_print_node(tree->root, 0, "root");
}
