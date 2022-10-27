#ifndef MARKOV_H_
#define MARKOV_H_
#include <bst/core.h>
#include <stdio.h>

struct MarkovState {
    char* search_string;
    int search_length;
    Tree* tree;
    int is_first_letter;
    char last_letter;
} typedef MarkovState;

void generate_text(Tree* tree, char* search_string,
                   int search_length, int output_length);
#endif

