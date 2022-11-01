#include <file_io.h>
#include <stdlib.h>

void file_into_buffer(size_t n, FILE* file, char* buffer) {
    int c = getc(file);
    for(int i = 0; i < (int) n; i++) {
        buffer[i] = (char) c;
        c = getc(file);
    }
    fseek(file, 0, SEEK_SET);
}

size_t get_file_size(FILE* file) {
    size_t file_size = 0;

        fseek(file, 0, SEEK_END);
        file_size = (size_t) ftell(file);
        fseek(file, 0, SEEK_SET);
    
    if(file_size == 0) {
        fprintf(stderr, "Error: Unable to calculate file size!");
        exit(EXIT_FAILURE);
    }
        
    return file_size;
}
