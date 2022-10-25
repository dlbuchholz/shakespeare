#include <bst/analysis.h>
#include <markov.h>

void shift_string(char *words, int len)
{
    //printf("1: %s\n", words);
    int i;
    for(i = 1; i < len; i++)
    {
        words[i - 1] = words[i];
    }

    //printf("%s\n", words);
}

char next_letter(Tree* tree, char* search_string, int search_length) {
    Match matches[20] = {};
    int i = 0;
    char* temp = strdup(search_string);

    find_matches(tree->nodes[tree->root], search_string, search_length, matches, &i);
    /*for(int j = 0; j < i; j++) {
        printf("%s\n", matches[j].node->content);
    }*/
    srand(time(0));
    int random_match = (rand() % (i));

    if(matches[random_match].last_pos) {
        return ' ';
    } else {
        return matches[random_match].char_next;
    }
}

void generate_text(Tree* tree, char* search_string, int search_length, int output_length) {

    char* work_string = strdup(search_string);
    printf("<%s>", work_string);

    for(int i = 0; i < output_length; i++) {
        char c = next_letter(tree, work_string, search_length);
        printf("%c", c);
        shift_string(work_string, search_length);
        work_string[search_length-1] = c;
    }
}