#ifndef BST_UTILITIES_H_
#define BST_UTILITIES_H_
#include <bst/core.h>
#include <stdio.h>

void print_node(Node* node, int indentation);
void print_tree(Tree* tree);
void debug_print_tree(Tree* tree);
void debug_print_node(Node* root, size_t node_len);
void debug_print_node_2(Node* node, int level, char* position);
#endif