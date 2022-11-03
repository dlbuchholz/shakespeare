#include <markov/probability.h>

/* Function: calculate_probabilities
 * ---------------------------------
 * Calculate the probability of every element in a set of characters following
 * each node. 
 *
 * root | pointer to the the root node of the tree
 */
void calculate_probabilities(Node* root) {
    for(int i = 0; i < (int) root->state_len; i++) {
	/* probability of this char =
	 * frequency of this char / frequencies of all chars in this set  */
        root->next_state[i].probability = (double) root->next_state[i].frequency / root->sum_of_frequencies;
    }

    if(root->left)
        calculate_probabilities(root->left);
    if(root->right)
        calculate_probabilities(root->right);
}


/* Function: weighted_random
 * -------------------------
 * Pick and return a random index of a character in the set (from 0 to n-1).
 * This index is chosen randomly but based on the weight of a character's
 * probability (p[i].probability). The probability values of *p are assumed to
 * have a sum of 1, thus the the probability values matter up to the point
 * where the sum exceeds 1.
 *
 * p | pointer to an array of NextState (next possible character)
 * n | length of the array 
 */
int weighted_random(NextState *p, int n) {
    double s = rand() / (RAND_MAX + 1.0);
    int i;
    for (i = 0; i < n - 1 && ((s -= p[i].probability) >= 0); i++);
    return i;
}
