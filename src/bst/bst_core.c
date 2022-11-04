#include <bst/core.h>
#include <macros.h>

/* Maximum amount of characters to store for a search string.
 * 52 is an arbitrary value choosen because the sum of
 * 26 (all lower-case letters) + 26 (all higher-case letters) is 52.
 */
#define MAX_TRANSITION_CHARS 52

/* Function: tree_new
 * ------------------
 * Declare a new tree, allocate memory for it on the heap and initialize it
 * according to the parameters, then return it.
 *
 */
Tree* tree_new() {
    Tree* tree = (Tree *) malloc(sizeof(Tree));
    /*                     ^^^^ gets freed in tree_destroy() */
    tree->root = NULL;
    tree->node_len = 0;
    return tree;
}

/* Function: new_node
 * ------------------
 * Declare a new node, allocate memory for it on the heap and initialize it
 * according to the parameters, then return it.
 *
 * content     | string to be saved in the node
 * content_len | length of the string
 */

Node* new_node(const char* content, size_t content_len) {
    Node* node = (Node *) malloc(sizeof(Node));
    /*                     ^^^^ gets freed in node_destroy */
    node->content = strdup(content);
    /*		         ^^^^ gets freed in node_destroy */
    node->content[content_len-1] = '\0';
    node->left = NULL;
    node->right = NULL;
    node->length = content_len;
    node->list_char = list_new();
    /*                  ^^^^ gets freed in line node_destroy */
    return node;
}

/* Function: node_insert
 * ---------------------
 * Inserts a node into a binary search tree. It's position is determined by a
 * lexicographic comparision with the existing nodes in the tree.
 *
 * parent      | pointer to a higher-level node
 * content     | string to be saved in the node
 * content_len | length of the string
 * tree	       | pointer to the binary search tree
 */
Node* node_insert(Node* parent, const char* content, size_t content_len, Tree* tree) {
    if(parent == NULL) {
        Node* n = new_node(content, content_len);
        append_transition_state(n, content[content_len-1]);
        if(tree->root == NULL)
            tree->root = n;
        tree->node_len++;
        return n;
    }

    /* Don't consider the last character for the comparison, since it's not
     * part of the node but already a following character. */
    int length = strncmp(parent->content, content, content_len - 1);

    if (length == 0) {
        /* Save the last char as a possible following char for this node */
        append_transition_state(parent, content[content_len-1]);
        return parent;
    } else if(length < 0)
        parent->left = node_insert(parent->left, content, content_len, tree);
    else if (length > 0)
        parent->right = node_insert(parent->right, content, content_len, tree);

    return parent;
}

/* Function: append_transition_state
 * ---------------------------------
 * Gets called each time a node is followed by a character. This character
 * shall get added to the node's set of next possible characters, if this
 * character is already included in the set, increase it's counter.
 *
 * parent | pointer to a node
 * c      | character that was found after the node
 */
void append_transition_state(Node* parent, char c) {

    ListNode* char_node = list_node_lookup(parent->list_char->head, c);

    if(!char_node) {
        parent->list_char->sum_of_frequencies++;
        list_node_append(parent->list_char, c);
    } else {
        char_node->frequency++;
        parent->list_char->sum_of_frequencies++;
    }
}

/* Function: node_destroy
 * ----------------------
 * Frees all of the memory allocated on the heap used for nodes. The nodes get
 * iterated recursively using post-order tree traversal.
 *
 * node | pointer to the the root node of the tree
 */
void node_destroy(Node* node) {
    if(node->left != NULL)
        node_destroy(node->left);
    if(node->right != NULL)
        node_destroy(node->right);
    if(node->list_char != NULL)
        list_destroy(node->list_char);
    if(node->content != NULL)
        free(node->content);
    free(node);
}

/* Function: tree_destroy
 * ----------------------
 * Frees all of the memory allocated on the heap used for nodes by calling
 * node_destroy() on the root node.
 *
 * tree | pointer to a tree
 */
void tree_destroy(Tree* tree) {
    DEBUG_PRINT(("DEBUG: Destroying tree: %p\n", (void*) tree));

    /* Destroy all nodes recursively */
    node_destroy(tree->root);

    free(tree);
}
