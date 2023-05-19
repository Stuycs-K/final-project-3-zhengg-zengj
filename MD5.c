#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void toBinary(int n) {
  int a[10];
  int i;
  for(i=0; n>0; i++) {
    a[i]=n%2;
    n=n/2;
  }
  printf("\nBinary of Given Number is=");
  for(i=i-1; i>=0 ;i--) {
    printf("%d",a[i]);
  }
  printf("\n");

}

char* bitwise_concat(char* input) {

  
}

int main(int argc, char const *argv[]) {
  char* message = "test";
  int size = strlen(message) * 8;
  //padding

  return 0;
}
