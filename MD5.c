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
            printf("%x", byte);
            ctr++;
        }
        printf(" ");
    }
    puts("");
    return ctr;
}

char* add_padding(char* message)
{
  int new_len = ((((strlen(message) + 8) / 64) + 1) * 64) - 8;
  uint8_t *new_message;
  new_message = calloc(new_len+64, 1);                   // zeroes
  memcpy(new_message, message, strlen(message)); // copying over initial message
  new_message[strlen(message)] = 128;            // add one 1 (10000000)
  uint32_t bits_len = 8 * strlen(message);       // last 64 bits is for original length
  memcpy(new_message + new_len, &bits_len, 4);        // append length of message in bits to end
  return new_message;
}

char** make_chunks(char* initial_message)
{
  // memcpy(new_message + new_len, &bits_len, 4);
  int chunks_length;
  char **chunks;
  if (strlen(initial_message) * 8 > 512)
  {
    int offset = 0;
    chunks_length = (strlen(initial_message) / 64) + 1;
    if (strlen(initial_message)%64 >= 56) {
      chunks_length++;
    }
    chunks = malloc(chunks_length * sizeof(char *));
    for (int i = 0; i < chunks_length; i++)
    {
      char *temp = calloc(64, sizeof(char));
      memcpy(temp, initial_message+offset, 64);
      *(chunks + i) = temp;
      offset += 64;
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

int find_length(char* initial_message)
{
  int length = (strlen(initial_message) / 64) + 1;
  if (strlen(initial_message)%64 >= 56) length++;
  return length;
}

void md5(char* initial_message) {
  //s specifies per-round shift amounts
  uint32_t s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
             5, 9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5, 9, 14, 20,
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
  uint32_t a0 = 0x67452301;   // A
  uint32_t b0 = 0xefcdab89;  // B
  uint32_t c0 = 0x98badcfe;   // C
  uint32_t d0 = 0x10325476;   // D

  //padding 448 mod 512 long
  // uint8_t* message = chunks[chunks_length-1];
  uint8_t* new_message = add_padding(initial_message);
  int new_len = ((((strlen(new_message) + 8) / 64) + 1) * 64) - 8;

  //splitting message into 512-bit chunks
  char** chunks = make_chunks(new_message);
  int chunks_length = find_length(new_message);
  // for (int i = 0; i < chunks_length; i++) printf("%s\n", chunks[i]);

  //looping time: going through each chunk
  for (int c = 0; c < chunks_length; c++) {
    //start spltting chunks into smaller, 32-bit chunks
    char* curr_chunk = chunks[c];
    uint32_t *w = (uint32_t *) (curr_chunk);
    //initialize hash values for this chunk
    uint32_t A = a0;
    uint32_t B = b0;
    uint32_t C = c0;
    uint32_t D = d0;
    //main loop
    for (int i = 0; i < 64; i++) {
      uint32_t F, g;
      //four different rounds
      if (i < 16) {
        F = (B & C) | ((~B) & D);
        g = i;
      }
      else if (i < 32) {
        F = (D & B) | ((~D) & C);
        g = ((5*i) + 1) % 16;
      }
      else if (i < 48) {
        F = B ^ C ^ D;
        g = ((3 * i) + 5) % 16;
      }
      else {
        F = C ^ (B | (~D));
        g = (7*i) % 16;
      }
      int temp = D;
      D = C;
      C = B;
      // printf("rotateLeft(%x + %x + %x + %x, %d) %d\n", A, F, k[i], w[g], s[i], i); //for debugging
      // printf("curr(A: %x, B:%x, C:%x, D:%x) %d\n", A, B, C, D, i);
      B = B + left_rotate((A + F + k[i] + w[g]), s[i]);
      A = temp;
    }

    a0+=A;
    b0+=B;
    c0+=C;
    d0+=D;
  }
  uint8_t *digest_p;
  digest_p=(uint8_t *)&a0;
  printf("%2.2x%2.2x%2.2x%2.2x", digest_p[0], digest_p[1], digest_p[2], digest_p[3]);
  digest_p=(uint8_t *)&b0;
  printf("%2.2x%2.2x%2.2x%2.2x", digest_p[0], digest_p[1], digest_p[2], digest_p[3]);
  digest_p=(uint8_t *)&c0;
  printf("%2.2x%2.2x%2.2x%2.2x", digest_p[0], digest_p[1], digest_p[2], digest_p[3]);
  digest_p=(uint8_t *)&d0;
  printf("%2.2x%2.2x%2.2x%2.2x", digest_p[0], digest_p[1], digest_p[2], digest_p[3]);
  puts("");
}


int main(int argc, char** argv) {

  if (argc < 2) {
      printf("Please include a message (%s |text here!|)\n", argv[0]);
      return 1;
  }

  char* message = argv[1];
  printf("Original message: %s\n", message);
  printf("MD5 Encrypted: ");
  md5(message);

  return 0;
}
