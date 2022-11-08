#include <bst/analysis.h>

/* Function: lookup
 * ----------------
 * Search for a word match in the binary search tree using preorder traversal,
 * return the corresponding node if found.
 *
 * root     | pointer to the root node
 * word     | string to be searched within the tree
 * word_len | length of the search string
 */
Node *lookup(Node *root, const char *word, size_t word_len) {
    if (!root) {
        return NULL;
    }

    int length = strncmp(root->content, word, word_len);

    if (length == 0)
        return root;
    else if (length > 0)
        return lookup(root->left, word, word_len);
    else if (length < 0)
        return lookup(root->right, word, word_len);

    return NULL;
}
