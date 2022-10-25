#ifndef MARKOV_H_
#define MARKOV_H_
#include <bst/core.h>
#include <stdio.h>

void generate_text(Tree* tree, char* search_string,
                   int search_length, int output_length);
#endif

