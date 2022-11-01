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

Node *lookup(Node *root, const char *word, size_t word_len)
{
    if (!root)
    {
        return NULL;
    }

    int length = strncmp(root->content, word, word_len);

    if (length == 0)
        return root;
    else if (length < 0)
        return lookup(root->left, word, word_len);
    else if (length > 0)
        return lookup(root->right, word, word_len);

    return NULL;
}
