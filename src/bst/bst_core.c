////////////////////////////////////////////////////////////////////////////////
// linked_list.c                                                              //
//                                                                            //
// Dieser Quellcode beinhaltet die Implementation einer verketteten Liste,    //
// welche Namen enthält.                                                      //
//                                                                            //
// Erstellt am: 19.10.2022                                                    //
//       Autor: Dennis Lucas Buchholz                                         //
////////////////////////////////////////////////////////////////////////////////
#include <bst/core.h>
#include <macros.h>

Tree* tree_new (long max_tree_elements) {
    Tree* tree = (Tree *) malloc(sizeof(Tree));

    // Reserves memory for whole array of node adresses (Keeping track of all
    // node references is good practice to avoid orphan nodes)
    //
    // Note: Calloc initializes all memory after allocating it
    tree->nodes = calloc (max_tree_elements, sizeof(Node*));
    tree->root = 0;
    tree->node_len = 0;
    return tree;
}

Node* new_node(const char* content, size_t content_len) {
    Node* node = (Node *) malloc(sizeof(Node));
    node->content = strdup(content);
    node->content[content_len-1] = '\0';
    node->left = NULL;
    node->right = NULL;
    node->length = content_len;
    node->count = 1;
    node->next_state = calloc(52, sizeof(NextState));
    node->state_len = 0;
    return node;
}

Node* node_insert(Node* parent, const char* content, size_t content_len) {
    if(parent == NULL) {
        Node* n = new_node(content, content_len);
        append_state(n, content[content_len-1]);
        return n;
    }

    // Only compare the first 4 characters
    int length = strncmp(parent->content, content, content_len - 1);

    if (length == 0) {
        append_state(parent, content[content_len-1]);
        parent->count++;
        return parent;
    } else if(length < 0)
        parent->left = node_insert(parent->left, content, content_len);
    else if (length > 0)
        parent->right = node_insert(parent->right, content, content_len);

    return parent;
}

void append_state(Node* parent, char c) {
    int found = -1;
    for(int i = 1; i < parent->state_len; i++) {
        if(parent->next_state[i-1].character == c) {
            found = i-1;
        }
    }

    if(found == -1) {
        if(parent->state_len < 52) {
            NextState l;
            l.character = c;
            l.frequency = 1;
            l.probability = 0;
            parent->next_state[parent->state_len++] = l;
            parent->sum_of_frequencies++;
        }
    } else {
        parent->next_state[found].frequency++;
        parent->sum_of_frequencies++;
    }
}

void calculate_probabilities(Node* root) {
    for(int i = 0; i < root->state_len; i++) {
        root->next_state[i].probability = (float) root->next_state[i].frequency / root->sum_of_frequencies;
    }

    if(root->left)
        calculate_probabilities(root->left);
    if(root->right)
        calculate_probabilities(root->right);
}

////////////////////////////////////////////////////////////////////////////////
// Garbage collection                                                         //
////////////////////////////////////////////////////////////////////////////////

void node_destroy(Node* node) {
    if(node->left)
        node_destroy(node->left);
    if(node->right)
        node_destroy(node->right);
    free(node);
}

void tree_destroy(Tree* tree) {
    DEBUG_PRINT(("DEBUG: Destroying tree: %p\n", &tree));

    // Destroy all nodes recursively, starting from the root node
    node_destroy(tree->nodes[tree->root]);

    // Check for possible orphan nodes, destroy them if found
    for(int i = 0; i < tree->node_len - 1; i++) {
        if(tree->nodes[i]) {
            DEBUG_PRINT(("DEBUG: Destroying orphan node: %s\n", tree->nodes[i]->content));
            node_destroy(tree->nodes[i]);
        }
    }
    free(tree->nodes);
    free(tree);
}