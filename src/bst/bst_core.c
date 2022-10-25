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
    // Reserves memory for the whole pointerarray of nodes
    // Note: Calloc initializes all memory after allocating it
    // Keeping track of all node references is good practice to avoid orphan
    // nodes
    tree->nodes = calloc (max_tree_elements, sizeof(Node*));
    tree->root = 0;
    tree->node_len = 0;
    return tree;
}

Node* new_node(const char* content, size_t content_len) {
    Node* node = (Node *) malloc(sizeof(Node));
    node->content = strdup(content);
    node->left = NULL;
    node->right = NULL;
    node->length = content_len;
    node->count = 1;
    return node;
}

Node* node_insert(Node* parent, const char* content, size_t content_len) {
    if(parent == NULL)
        return new_node(content, content_len);

    int length = parent->length > content_len;

    if(strcmp(parent->content, content) == 0) {
        parent->count++;
        return parent;
    } else if(length)
        parent->left = node_insert(parent->left, content, content_len);
    else if (!length)
        parent->right = node_insert(parent->right, content, content_len);

    return parent;
}

void node_destroy(Node* node) {
    if(node->left)
        node_destroy(node->left);
    if(node->right)
        node_destroy(node->right);
    free(node);
}

void tree_destroy(Tree* tree) {
    DEBUG_PRINT(("DEBUG: Destroying tree: %p\n", &tree));
    node_destroy(tree->nodes[tree->root]);
    free(tree->nodes);
    free(tree);
}