#ifndef BST_CORE_H_
#define BST_CORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;
typedef struct NextState NextState;
typedef struct Tree Tree;

struct NextState {
    char character;
    int frequency;
    double probability;
};

struct Node {
    char* content;
    Node* left;
    Node* right;
    size_t length;
    int sum_of_frequencies;
    NextState* next_state;
    size_t state_len;
};

struct Tree {
    Node* root;
    size_t node_len;
};

Tree* tree_new (void);
Node* new_node(const char* content, size_t content_len);
Node* node_insert(Node* parent, const char* content, size_t content_len, Tree* tree);
void node_destroy(Node* node);
void tree_destroy(Tree* tree);
void append_transition_state(Node* parent, char c);
void realloc_node(Node* root);

#endif
