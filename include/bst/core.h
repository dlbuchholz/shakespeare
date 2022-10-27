#ifndef BST_CORE_H_
#define BST_CORE_H_

#include <fileio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;
typedef struct LinkedState LinkedState;

struct Node {
    char* content;
    Node* left;
    Node* right;
    int length;
    int count;
    char next_char;
  //  LinkedState** next_state;
//    int state_len;
};
/*
struct LinkedState {
    Node* node;
    int count;
    int probability;
};
*/
struct Tree {
    Node** nodes;
    long root;
    size_t node_len;
} typedef Tree;

Tree* tree_new (long max_tree_elements);
Node* new_node(const char* content, size_t content_len, char next_chart);
Node* node_insert(Node* parent, const char* content, size_t content_len, char next_char);
void node_destroy(Node* node);
void tree_destroy(Tree* tree);

#endif