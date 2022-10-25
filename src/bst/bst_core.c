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

Node* new_node(const char* content, size_t content_len, char next_char) {
    Node* node = (Node *) malloc(sizeof(Node));
    node->content = strdup(content);
    node->left = NULL;
    node->right = NULL;
    node->length = content_len;
    node->count = 1;
    node->next_char = next_char;
    return node;
}

Node* node_insert(Node* parent, const char* content, size_t content_len, char next_char) {
    if(parent == NULL)
        return new_node(content, content_len, next_char);

    int length = parent->length > content_len;

    if(strcmp(parent->content, content) == 0) {
        parent->count++;
        return parent;
    } else if(length)
        parent->left = node_insert(parent->left, content, content_len, next_char);
    else if (!length)
        parent->right = node_insert(parent->right, content, content_len, next_char);

    return parent;
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
    for(int i = 0; i < tree->node_len; i++) {
        if(tree->nodes[i]) {
            DEBUG_PRINT(("DEBUG: Destroying orphan node: %s\n", tree->nodes[i]->content));
            node_destroy(tree->nodes[i]);
        }
    }
    free(tree->nodes);
    free(tree);
}