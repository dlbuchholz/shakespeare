#ifndef MARKOV_PROBABILITY_H_
#define MARKOV_PROBABILITY_H_
#include <bst/core.h>
#include <stdio.h>

void calculate_probabilities(Node* root);
int weighted_random(NextState *p, int n);

#endif
