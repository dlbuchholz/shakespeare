#ifndef FILE_IO_H_
#define FILE_IO_H_
#include <stdio.h>

void file_into_buffer(size_t n, FILE* file, char* buffer);
size_t get_file_size(FILE* file);

#endif
