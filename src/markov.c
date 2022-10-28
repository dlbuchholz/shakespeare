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

    words[len - 1] = '\0';

    //printf("((%s))\n", words);
}

char next_letter(MarkovState *state)
{
    Node* n = lookup(state->tree->nodes[state->tree->root], state->search_string, state->search_length);
    if(!n) {
        fprintf(stderr, "Error: Unable to predict '%s'", state->search_string);
        exit(EXIT_FAILURE);
    }

    srand(time(0));
    
    int random_match = (rand() % n->state_len);

    return n->next_state[random_match].character;
}

void generate_text(Tree *tree, char *search_string, int search_length, int output_length)
{

    MarkovState state;
    state.tree = tree;
    state.search_string = strdup(search_string);
    state.search_length = search_length;
    char last_letter;

    printf("<%s>", state.search_string);

    for (int i = 0; i < output_length; i++)
    {
        char last_letter = next_letter(&state);
        printf("%c", last_letter);
        shift_string(state.search_string, search_length);
        state.search_string[search_length - 1] = last_letter;
    }
    printf("\n");
}