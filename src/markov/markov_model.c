#include <bst/analysis.h>
#include <file_io.h>
#include <macros.h>
#include <markov/model.h>
#include <markov/probability.h>
#include <time.h>

Tree* tree_from_file(FILE* file, size_t input_length, size_t* output_length) {
    
    size_t file_size = get_file_size(file);
    Tree *tree = tree_new(file_size);

    if(*output_length == 0) {
        *output_length = file_size;
    }

    int c = getc(file);
    
    size_t len = 1;
    char buffer[5] = "";
    Node* root = NULL;

    while(c != EOF) {
        strncat(buffer, (char*) &c, 1);

        if(len == input_length+1) {
            root = node_insert(root, buffer, len);
            tree->nodes[tree->node_len++] = root;
            shift_string(buffer, (int) len);
        } else {
            len++;
        }

         c = getc(file);
    }
    fseek(file, 0, SEEK_SET);
    return tree;
}

MarkovModel* model_new(FILE* file, size_t input_length, size_t output_length) {

    Tree* tree = tree_from_file(file, input_length, &output_length);
    if(!tree) {
        fprintf(stderr, "Error: Unable to generate binary search tree");
        exit(EXIT_FAILURE);
    }
    
    calculate_probabilities(tree->nodes[tree->root]);
    // Shrink allocated memory space for the binary search tree to the size
    // that the nodes actually use
    tree->nodes = realloc(tree->nodes, tree->node_len * sizeof(Node*));
    realloc_node(tree->nodes[tree->root]);

    MarkovModel* model = malloc(sizeof(MarkovModel));
    model->tree = tree;
    model->search_length = input_length;
    model->output_length = output_length;

    return model;
}

void shift_string(char *words, int len)
{
    for (int i = 1; i < len; i++)
        words[i - 1] = words[i];

    words[len - 1] = '\0';
}

char next_letter(MarkovModel *state)
{
    Node* n = lookup(state->tree->nodes[state->tree->root], state->search_string, state->search_length);
    if(!n) {
        fprintf(stderr, "Error: Unable to predict '%s'", state->search_string);
        exit(EXIT_FAILURE);
    }

    srand((unsigned int) time(0));
    return n->next_state[weighted_random(n->next_state, (int) n->state_len)].character;
}

void generate_text(MarkovModel *model, char *search_string)
{
    model->search_string = search_string;
    char last_letter;

    printf("<%s>", model->search_string);

    for (int i = 0; i < (int) model->output_length; i++)
    {
        last_letter = next_letter(model);
        printf("%c", last_letter);
        shift_string(model->search_string, (int) model->search_length);
        model->search_string[model->search_length - 1] = last_letter;
    }
    printf("\n");
}
