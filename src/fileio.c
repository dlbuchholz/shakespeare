#include <fileio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

long get_file_size(const char *fname, FILE* file) {
    long file_size = 0;
    if (!file) {
        FILE *f_new = fopen(fname, "r");
        fseek(f_new, 0, SEEK_END);
        file_size = ftell(f_new);
        fseek(f_new, 0, SEEK_SET);
        fclose(f_new);
    } else {
        fseek(file, 0, SEEK_END);
        file_size = ftell(file);
        fseek(file, 0, SEEK_SET);
    }

    if(file_size == 0) {
        exit(EXIT_FAILURE);
    }
        
    return file_size;
}