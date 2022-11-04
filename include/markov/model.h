#ifndef MARKOV_MODEL_H_
#define MARKOV_MODEL_H_
#include <bst/core.h>
#include <stdio.h>

typedef struct MarkovModel MarkovModel;

struct MarkovModel {
    char* search_string;
    size_t search_length;
    size_t output_length;
    Tree* tree;
};

Tree* tree_from_file(FILE* file, char* search_string,
                     size_t input_length,
                     size_t* output_length);
MarkovModel* model_new(FILE* file, char* search_string,
                       size_t input_length,
                       size_t output_length);
void generate_text(MarkovModel *model);
char next_letter(MarkovModel *state);
void shift_string(char *words, int len);
void model_destroy(MarkovModel* model);

#endif
