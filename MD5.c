#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void toBinary(int n) {
  int a[10];
  int i;
  for(i=0; n>0; i++) {
    a[i]=n%2;
    n=n/2;
  }
  //printf("\nBinary of Given Number is=");
  for(i=i-1; i>=0 ;i--) {
    printf("%d",a[i]);
  }
  printf(" ");

}

void printBinary(unsigned char* string) {
  for (int i = 0; i < strlen(string); i++) {
    toBinary(string[i]);
  }
  printf("\n");
}

//uint8_t* == unsigned char
int main(int argc, char const *argv[]) {
  uint8_t* message = "test";
  int size = strlen(message) * 8;
  printBinary(message);
  //padding 448 mod 512 long
  int padding = 448 - size; //# of zeros were adding
  uint8_t* new_message;
  new_message = calloc(448, 1);
  memcpy(new_message, message, size);
  new_message[size] = 128;
  printf("%02x\n", new_message);
  return 0;
}
