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

Tree* tree_new (long max_tree_elements) {
    Tree* tree = (Tree *) malloc(sizeof(Tree));
    // Reserves memory for the whole array of nodes
    // Note: Calloc initializes all memory after allocating it
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

Node* lookup(Node* root, const char* word, size_t word_len) {
    if(!root) {
        return NULL;
    }

    int length = root->length > word_len;

    if(strcmp(root->content, word) == 0)
        return root;
    else if(length) 
        return lookup(root->left, word, word_len);
    else if (!length)
        return lookup(root->right, word, word_len);

    return NULL;
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
    node_destroy(node->left);
    node_destroy(node->right);
    free(node);
}

void tree_destroy(Tree* tree) {
    node_destroy(tree->nodes[tree->root]);
    free(tree->nodes);
    free(tree);
}