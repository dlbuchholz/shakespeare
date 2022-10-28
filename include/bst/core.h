#ifndef BST_CORE_H_
#define BST_CORE_H_

#include <fileio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;
typedef struct NextState NextState;

struct NextState {
    char character;
    int frequency;
    float probability;
};

struct Node {
    char* content;
    Node* left;
    Node* right;
    int length;
    int count;
    int sum_of_frequencies;
    NextState* next_state;
    int state_len;
};

struct Tree {
    Node** nodes;
    long root;
    size_t node_len;
} typedef Tree;

Tree* tree_new (long max_tree_elements);
Node* new_node(const char* content, size_t content_len);
Node* node_insert(Node* parent, const char* content, size_t content_len);
void node_destroy(Node* node);
void tree_destroy(Tree* tree);
void append_state(Node* parent, char c);
void calculate_probabilites(Node* root);

#endif