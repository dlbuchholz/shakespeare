#include <file_io.h>
#include <stdlib.h>

/* Function: file_into_buffer
 * --------------------------
 * Reads n amount characters from the beginning of a file into a buffer.
 * 
 * n      | amount of characters
 * file   | pointer to file
 * buffer | pointer to memory location of string
 */
void file_into_buffer(size_t n, FILE* file, char* buffer) {
    int c = getc(file);
    for(int i = 0; i < (int) n; i++) {
        buffer[i] = (char) c;
        c = getc(file);
    }

    /* Insert null-terminator */
    buffer[n] = '\0';

    fseek(file, 0, SEEK_SET);
}

/* Function: get_file_size
 * -----------------------
 * Determines the size of a file (in bytes)
 * 
 * file | pointer to a file
 */
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
