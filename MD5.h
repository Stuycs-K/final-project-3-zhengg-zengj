#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int printBits(size_t const size, void const *const ptr);
char** splitMessage(char *curr_chunk);
char* add_padding(char *chunk);
char** make_chunks(char *initial_message);
int find_length(char **chunks);