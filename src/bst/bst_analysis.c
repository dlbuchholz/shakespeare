////////////////////////////////////////////////////////////////////////////////
// linked_list.c                                                              //
//                                                                            //
// Dieser Quellcode beinhaltet die Implementation einer verketteten Liste,    //
// welche Namen enthält.                                                      //
//                                                                            //
// Erstellt am: 19.10.2022                                                    //
//       Autor: Dennis Lucas Buchholz                                         //
////////////////////////////////////////////////////////////////////////////////
#include <bst/analysis.h>

void inorder_traversal(Node* root, char** output, int *index) {
    if(root != NULL) {
        inorder_traversal(root->left, output, index);
        //printf("%s,", root->content);
        output[(*index)++] = strdup(root->content);
        inorder_traversal(root->right, output, index);
    }
}