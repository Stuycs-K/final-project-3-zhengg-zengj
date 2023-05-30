#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define left_rotate(x, c) (((x) << (c)) | ((x) >> (32 - (c)))) //found this left rotate after googling --> see references in worklog

int printBits(size_t const size, void const *const ptr); //for debugging purposes; prints any data type in bits (assumes little endian)
char* add_padding(char *chunk, char *original_message); //adds padding to chunks such that its divisible by 512
char** make_chunks(char *initial_message); //splits message into 512-bit chunks
int find_length(char * msg); //finds amount of chunks for loops
