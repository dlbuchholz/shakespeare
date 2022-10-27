#include <bst/analysis.h>
#include <markov.h>

void shift_string(char *words, int len)
{
    // printf("1: %s\n", words);
    int i;
    for (i = 1; i < len; i++)
    {
        words[i - 1] = words[i];
    }

    //printf("((%s))\n", words);
}

void find_matches(Node *root, Match matches[], int *index, MarkovState *state)
{
    char *char_found = strchr(root->content, state->last_letter);

    if (char_found)
    {
        char node_letter_before = root->content[(char_found - root->content) - 1];
        char node_letter_after = root->content[(char_found - root->content) + 1];
        Match m;
        m.count = root->count;
        m.node = root;
        m.last_pos = 0;

       //printf("[[%c %c %c]]", node_letter_before, state->last_letter, state->search_string[state->search_length - 2]);

        if (state->is_first_letter)
        {
            m.char_next = node_letter_after;
            matches[(*index)++] = m;
        }
        else if (node_letter_before == state->search_string[state->search_length - 2])
        {
            if (state->search_string[state->search_length - 1] == root->content[root->length - 1])
            {
                m.char_next = root->next_char;
                m.last_pos = 1;
                matches[(*index)++] = m;
            } else
            {
                m.char_next = node_letter_after;
                matches[(*index)++] = m;
            }
        }
            
    }

    if (root->left)
        find_matches(root->left, matches, index, state);
    if (root->right)
        find_matches(root->right, matches, index, state);
}

char next_letter(MarkovState *state)
{
    Match matches[20] = {};
    int i = 0;

    // int j = 1;
    // while(i == 0) {
    find_exact_matches(state->tree->nodes[state->tree->root], state->search_string, state->search_length, matches, &i);
    //    shift_string(temp, search_length);
    //      temp[search_length - j++] = '\0';
    // }

    if (i == 0)
    {
        find_matches(state->tree->nodes[state->tree->root], matches, &i, state);
    }

    //printf("((%d))", i);

    if(state->is_first_letter)
        state->is_first_letter=0;
    

    /* for(int j = 0; j < i; j++) {
         printf("[[%s]]%d", matches[j].node->content, i);
     }*/

    srand(time(0));
    int random_match = (rand() % (i));

    if (matches[random_match].last_pos)
    {
        printf(" ");
        state->is_first_letter=1;
    }
    return matches[random_match].char_next;
}

void generate_text(Tree *tree, char *search_string, int search_length, int output_length)
{

    MarkovState state;
    state.tree = tree;
    state.search_string = strdup(search_string);
    state.search_length = search_length;
    state.is_first_letter = 0;

    printf("<%s>", state.search_string);

    for (int i = 0; i < output_length; i++)
    {
        state.last_letter = next_letter(&state);
        printf("%c", state.last_letter);
        shift_string(state.search_string, search_length);
        state.search_string[search_length - 1] = state.last_letter;
    }
}