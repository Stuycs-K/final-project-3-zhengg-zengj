#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
        printf(" ");
    }
    puts("");
}

void printBinary(unsigned char* string, int length) {
  for (int i = 0; i < length; i++) {
    //toBinary(string[i]);
  }
  printf("\n");
}

//uint8_t* == unsigned char
int main(int argc, char const *argv[]) {
  uint8_t* message = "test";
  int size = strlen(message) * 8;
  printBits(strlen(message), message);
  //padding 448 mod 512 long
  int padding = 448 - size; //# of zeros were adding
  uint8_t* new_message;
  new_message = calloc(448, 1);
  for (int i = 0; i < strlen(message); i++) {
    new_message[i] = message[i];
  }
  //memcpy(new_message, message, size);
  new_message[strlen(message)] = 128;
  printBits(448, new_message);
  return 0;
}
