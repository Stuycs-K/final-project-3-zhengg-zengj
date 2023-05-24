#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define left_rotate(x, c) (((x) << (c)) | ((x) >> (32 - (c)))) //found this left rotate after googling :)

int printBits(size_t const size, void const *const ptr); //for debugging purposes; prints any data type in bits (assumes little endian)
char** splitMessage(char *curr_chunk); //splits chunk into 32-bit words
char* add_padding(char *chunk); //adds padding to chunks such that its divisible by 512
char** make_chunks(char *initial_message); //splits message into 512-bit chunks
int find_length(char **chunks); //finds amount of chunks for loops