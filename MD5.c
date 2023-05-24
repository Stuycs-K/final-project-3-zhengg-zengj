#include "MD5.h"
//Check header file for function descriptions
int printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    int ctr = 0;

    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
            ctr++;
        }
        printf(" ");
    }
    puts("");
    return ctr;
}

char** splitMessage(char* curr_chunk)
{
  int curr2 = 0;
  int num_words = (strlen(curr_chunk)/4);
  char** words = malloc(num_words * sizeof(char*)); //we're splitting our message into 32 bit words
  for (int i = 0; i < num_words; i++) {
    char* temp = malloc(64 * sizeof(char));
    for (int j = 0; j < 4; j++) {
      temp[j] = curr_chunk[curr2+j];
      if (j+1 >= 4) curr2 = curr2 + j + 1; //update curr when loop is about to term
    }
    *(words + i) = temp;
  }
  return words;
}

char* add_padding(char* chunk) 
{
  uint8_t *message = chunk;
  printf("%s\n", message);
  int new_len = ((((strlen(message) + 8) / 64) + 1) * 64) - 8;
  uint8_t *new_message;
  new_message = calloc(64, 1);                   // zeroes
  memcpy(new_message, message, strlen(message)); // copying over initial message
  new_message[strlen(message)] = 128;            // add one 1 (10000000)
  uint32_t bits_len = 8 * strlen(message);       // last 64 bits is for original length
  memcpy(new_message + 63, &bits_len, 4);        // append length of message in bits to end
  return new_message;
}

char** make_chunks(char* initial_message) 
{
  int chunks_length;
  char **chunks;
  if (strlen(initial_message) * 8 > 512)
  {
    int curr = 0;
    chunks_length = (strlen(initial_message) / 64) + 1;
    chunks = malloc(chunks_length * sizeof(char *));
    for (int i = 0; i < chunks_length; i++)
    {
      char *temp = malloc(64 * sizeof(char));
      for (int j = 0; j < 64; j++)
      {
        temp[j] = initial_message[curr + j];
        if (j + 1 >= 64)
          curr = curr + j + 1; // update curr when loop is about to term
      }
      *(chunks + i) = temp;
    }
  }
  else
  {
    chunks_length = 1;
    chunks = malloc(chunks_length * sizeof(char *));
    *(chunks + 0) = initial_message;
  }
  return chunks;
}

int find_length(char** chunks) 
{
  int len = 0;
  while (chunks[len]) len++;
  return len;
}

int main(int argc, char const *argv[]) {
  uint8_t *initial_message = "testttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttestb";
  // uint8_t is unsigned char
  // uint32_t is unsigned int

  //splitting message into 512-bit chunks
  char** chunks = make_chunks(initial_message);
  int chunks_length = find_length(chunks);
  // for (int i = 0; i < chunks_length; i++) printf("%s\n\n", chunks[i]); //checking chunkss

  //s specifies per-round shift amounts
  uint32_t s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
             5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
             4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
             6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
  uint32_t k[] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
                   0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
                   0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
                   0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
                   0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
                   0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
                   0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                   0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
                   0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
                   0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
                   0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
                   0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
                   0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
                   0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                   0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
                   0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
  //initializing variables
  int a0 = 0x67452301;   // A
  int b0 = 0xefcdab89;  // B
  int c0 = 0x98badcfe;   // C
  int d0 = 0x10325476;   // D

  //padding 448 mod 512 long
  uint8_t* message = chunks[chunks_length-1];
  uint8_t* new_message = add_padding(message);
  chunks[chunks_length - 1] = new_message;
  printBits(64, chunks[chunks_length - 1]);

  //looping time: going through each chunk
  for (int c = 0; c < chunks_length; c++) {
    //start spltting chunks into smaller, 32-bit chunks
    char* curr_chunk = chunks[c];
    int num_words = (strlen(curr_chunk)/4);
    char** words = splitMessage(curr_chunk);
    //initialize hash values for this chunk
    int A = a0;
    int B = b0;
    int C = c0;
    int D = d0;
    //main loop
    for (int i = 0; i < 63; i++) {
      int F, g;
      //four different rounds
      if (i >= 0 && i <= 15) {
        F = (B & C) | ((~B) & D);
        g = i;
      }
      else if (i >= 16 && i <= 31) {
        F = (D & B) | ((~D) & C);
        g = ((5*i) + 1) % 16;
      }
      else if (i >= 32 && i <= 47) {
        F = B ^ C ^ D;
        g = ((3 * i) + 5) % 16;
      }
      else if (i >= 48 && i <= 63) {
        F = C ^ (B | (~D));
        g = (7*i) % 16;
      }

      F = F + A + k[i] + words[g];
      A = D;
      D = C;
      C = B;
      // B = B + left_rotate(F, s[i]);
    }
    a0+=A;
    b0+=B;
    c0+=C;
    d0+=D;

  }

  return 0;
}
