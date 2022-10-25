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

void inorder_traversal(Node *root, char **output, int *index)
{
    if (root != NULL)
    {
        inorder_traversal(root->left, output, index);
        output[(*index)++] = strdup(root->content);
        inorder_traversal(root->right, output, index);
    }
}

Node *lookup(Node *root, const char *word, size_t word_len)
{
    if (!root)
    {
        return NULL;
    }

    int length = root->length > word_len;

    if (strcmp(root->content, word) == 0)
        return root;
    else if (length)
        return lookup(root->left, word, word_len);
    else if (!length)
        return lookup(root->right, word, word_len);

    return NULL;
}

void find_matches(Node *root, const char *word, size_t word_len, Match matches[], int *index) {
    if (root->length >= word_len) {
        char* occurence = strstr(root->content, word);
        if (occurence) {
            Match m;
            m.count = root->count;
            m.node = root;

            if (root->length == word_len || ((occurence + word_len) - root->content == root->length))
            {
                m.char_next = root->next_char;
                m.last_pos = 1;
            }
            else
            {
                m.char_next = root->content[(occurence + word_len) - root->content];
            }

            matches[(*index)++] = m;
        }
    }

    if (root->left)
        find_matches(root->left, word, word_len, matches, index);
    if (root->right)
        find_matches(root->right, word, word_len, matches, index);
}