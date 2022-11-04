#ifndef ARGPARSING_H_
#define ARGPARSING_H_

#include <stddef.h>

void parse_arguments(int argc, char **argv, char* file_name,
                     size_t *input_length, size_t *output_length);

#endif
