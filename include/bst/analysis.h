#ifndef BST_ANALYSIS_H_
#define BST_ANALYSIS_H_
#include <bst/core.h>
#include <stdio.h>

struct Match {
    int count;
    Node* node;
    int last_pos;
    char char_next;
} typedef Match;

void inorder_traversal(Node* root, char** output, int *index);
Node* lookup(Node* root, const char* word, size_t word_len);
void find_exact_matches(Node* root, const char* word, size_t word_len, Match matches[], int *index);
//void find_matches(Node *root, const char *word, const char last_letter, size_t word_len, Match matches[], int *index, int is_first_letter);
#endif