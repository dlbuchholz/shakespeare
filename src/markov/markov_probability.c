#include <markov/probability.h>

/* Function: calculate_probabilities
 * ---------------------------------
 * Calculate the probability of every element in a set of characters following
 * each node.
 *
 * root | pointer to the the root node of the tree
 */
void calculate_probabilities(Node* root) {
    ListNode* list_node = root->list_char->head;

    while (list_node != NULL) {
        /* probability of this char =
         * frequency of this char / frequencies of all chars in this set  */
        list_node->probability = (double) list_node->frequency / root->list_char->sum_of_frequencies;
        list_node = list_node->next_element;
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
ListNode* weighted_random(ListNode* head) {
    double s = rand() / (RAND_MAX + 1.0);
    ListNode* list_node = head;
    while (list_node->next_element != NULL && ((s -= list_node->probability) >= 0))
        list_node = list_node->next_element;

    return list_node;
}
