#include <markov/probability.h>

void calculate_probabilities(Node* root) {
    for(int i = 0; i < (int) root->state_len; i++) {
        root->next_state[i].probability = (double) root->next_state[i].frequency / root->sum_of_frequencies;
    }

    if(root->left)
        calculate_probabilities(root->left);
    if(root->right)
        calculate_probabilities(root->right);
}

int weighted_random(NextState *p, int n)
{
	double s = rand() / (RAND_MAX + 1.0);
	int i;
	for (i = 0; i < n - 1 && (s -= p[i].probability) >= 0; i++);
	return i;
}
