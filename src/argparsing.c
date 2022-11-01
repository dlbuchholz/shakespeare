#include <argparsing.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void parse_arguments(int argc, char **argv, char* file_name, size_t *input_length, size_t *output_length) {
    int option;
    unsigned int i_len = 1;
    unsigned int o_len = 0;
    while((option = getopt(argc, argv, "f:l:s:h")) != -1 ) {
        switch (option) {
            case 'l':
            if(sscanf(optarg, "%u", &o_len) != 1) {
                fprintf(stderr, "Error: Invalid output length");
                exit(EXIT_FAILURE);
            }
            break;
            case 's':
            if(sscanf(optarg, "%u", &i_len) != 1) {
                fprintf(stderr, "Error: Invalid input length");
                exit(EXIT_FAILURE);
            }
            break;
            case 'f':
            if (access(optarg, F_OK) == 0 && (file_name != NULL))
                strcpy(file_name, optarg);
            else {
                fprintf(stderr, "Error: Unable to access file!");
                exit(EXIT_FAILURE);
            }
            break;
        }
    }
    *input_length = (size_t) i_len;
    *output_length = (size_t) o_len;
}
