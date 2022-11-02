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
 * max_tree_elements | maximum amount of elements to be allocated on the heap
 */
Tree* tree_new (size_t max_tree_elements) {
    Tree* tree = (Tree *) malloc(sizeof(Tree));
    /*                     ^^^^ gets freed in tree_destroy() */

    /* Reserves memory for whole array of node adresses (Keeping track of all
     * node references is good practice to avoid orphan nodes and thus memory
     * leaks).
     *
     * Calloc instead of malloc used here because calloc initializes all memory
     * after allocating it (i.e. fills it with zeroes). */
    tree->nodes = calloc (max_tree_elements, sizeof(Node*));
    /*             ^^^^ gets freed in tree_destroy() */
    tree->root = 0;
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
    node->next_state = calloc(MAX_TRANSITION_CHARS, sizeof(NextState));
    /*                  ^^^^ gets reallocated model_new (markov_model.c),
     *                       gets freed in line node_destroy */
    node->state_len = 0;
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
        tree->nodes[tree->node_len++] = n;
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

/* Function: realloc_node
 * ----------------------
 * Shrink the allocated memory for the set of all characters following a node
 * to the size it actually uses, thus freeing memory that isn't necessary.
 *
 * root | pointer to the the root node of the tree
 */
void realloc_node(Node* root) {
    if(root)
        root->next_state = realloc(root->next_state, root->state_len * sizeof(NextState));

    if(root->left)
        realloc_node(root->left);

    if(root->right)
        realloc_node(root->right);
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

    /* If character gets found in set: found = id of element in array 
     * If character is not found in set: found = -1 */
    int found = -1;
    
    for(int i = 1; i < (int) parent->state_len; i++) {
        if(parent->next_state[i-1].character == c) {
            found = i-1;
        }
    }

    if(found == -1) {
	/* Only save character if the array has enough space left. */
        if(parent->state_len < MAX_TRANSITION_CHARS) {
            NextState l = {
            .character = c,
            .frequency = 1,
            .probability = 0 };
            parent->next_state[parent->state_len++] = l;
            parent->sum_of_frequencies++;
        }
    } else {
        parent->next_state[found].frequency++;
        parent->sum_of_frequencies++;
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
    if(node->next_state != NULL)
        free(node->next_state);
    if(node->content != NULL)
	    free(node->content);
    free(node);
}

/* Function: tree_destroy
 * ----------------------
 * Frees all of the memory allocated on the heap used for nodes by calling
 * node_destroy() on the root node. The internal nodes array get iterated as
 * well to free any orphan nodes that did not get freed by node_destroy()
 *
 * tree | pointer to a tree
 */
void tree_destroy(Tree* tree) {
    DEBUG_PRINT(("DEBUG: Destroying tree: %p\n", (void*) tree));

    /* Destroy all nodes recursively */
    node_destroy(tree->nodes[tree->root]);

    /* Check for possible orphan nodes, destroy them if found */ 
    for(int i = 0; i < (int) tree->node_len - 1; i++) {
        if(tree->nodes[i] != NULL) {
            DEBUG_PRINT(("DEBUG: Destroying orphan node: %s\n", tree->nodes[i]->content));
            node_destroy(tree->nodes[i]);
        }
    }

    free(tree->nodes);
    free(tree);
}
