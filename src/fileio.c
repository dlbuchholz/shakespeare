#include <fileio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

long get_file_size(const char *fname, FILE* file) {
    long file_size = 0;

        fseek(file, 0, SEEK_END);
        file_size = ftell(file);
        fseek(file, 0, SEEK_SET);
    
    if(file_size == 0) {
        fprintf(stderr, "Error: Unable to calculate file size!");
        exit(EXIT_FAILURE);
    }
        
    return file_size;
}