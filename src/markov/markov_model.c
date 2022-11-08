#include <bst/analysis.h>
#include <macros.h>
#include <markov/model.h>
#include <markov/probability.h>
#include <time.h>
#include <utilities.h>

Tree* tree_from_file(FILE* file, char* search_string,
                     size_t input_length,
                     size_t* output_length) {

    Tree *tree = tree_new();

    size_t buffer_len = 1;
    size_t search_string_len = 0;
    size_t counter = 0;
    /* +2 bytes because: byte for extra character + null terminator) */
    char* buffer = calloc(input_length + 2, sizeof(char));
    Node* root = NULL;

    int c = getc(file);

    while(c != EOF) {
        strncat(buffer, (char*) &c, 1);

        if(search_string_len < input_length)
            search_string[search_string_len++] = (char) c;

        if(buffer_len == input_length+1) {
            root = node_insert(root, buffer, buffer_len, tree);
            shift_string(buffer, (int) buffer_len);
        } else {
            buffer_len++;
        }
        counter++;
        c = getc(file);
    }

    if(*output_length == 0)
        *output_length = counter;

    free(buffer);
    return tree;
}

MarkovModel* model_new(FILE* file, char* search_string,
                       size_t input_length,
                       size_t output_length) {

    Tree* tree = tree_from_file(file, search_string, input_length,
                                &output_length);
    if(!tree) {
        free(search_string);
        graceful_exit("Error: Unable to generate binary search tree");
    }

    calculate_probabilities(tree->root);

    MarkovModel* model = malloc(sizeof(MarkovModel));
    model->tree = tree;
    model->search_length = input_length;
    model->output_length = output_length;
    model->search_string = search_string;

    return model;
}

void model_destroy(MarkovModel* model) {
    tree_destroy(model->tree);
    free(model->search_string);
    free(model);
}

void shift_string(char *words, int len) {
    for (int i = 1; i < len; i++)
        words[i - 1] = words[i];

    words[len - 1] = '\0';
}

char next_letter(MarkovModel *state) {
    Node* n = lookup(state->tree->root, state->search_string,
                     state->search_length);
    if(!n) {
        model_destroy(state);
        fprintf(stderr,
                "Error: Unable to make prediction for search string '%s'",
                state->search_string);
        exit(EXIT_FAILURE);
    }
    return weighted_random(n->list_char->head)->character;
}

void generate_text(MarkovModel *model) {
    char last_letter;
    srand((unsigned int) time(NULL));

    printf("<%s>", model->search_string);

    for (int i = 0; i < (int) model->output_length; i++) {
        last_letter = next_letter(model);
        printf("%c", last_letter);
        shift_string(model->search_string, (int) model->search_length);
        model->search_string[model->search_length - 1] = last_letter;
    }
    printf("\n");
}
