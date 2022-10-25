#include <bst/analysis.h>
#include <markov.h>

void generate_text(Tree* tree, char* search_string, int search_length, int output_length) {
    Match matches[20] = {};
    int i = 0;
    find_matches(tree->nodes[tree->root], search_string, search_length, matches, &i);

    for(int j = 0; j < i; j++) {
        printf("%s", matches[j].node->content);
    }
}