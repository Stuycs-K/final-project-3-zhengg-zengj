# MD5

## Background of MD5
MD5, known as Message-Digest 5, is a hash algorithm created in 1991 by Ronald Rivest as an extension to its predecessor, MD4.  

Like the majority of hash function, MD5, is a one way encryption method used for authenticating digital signatures via checksums. The hash cannot be reversed, but the same input would always result in the same hash. However, MD5 is no longer consider a cryptographic hash as it is vulnerable to hash collisions -- where two strings have the same hash value.  

## How it works
MD5 uses a mathematical algorithm to process the string.

### Padding/Appending Length
The hash algorithm first splits the message into 512-bit chunks -- it needs to make sure that each chunk is divisible by 512. If the message is already divisible by 512, the padding portion would be skipped. The padding operates by appending a singular 1 bit to the chunk and fills the rest with 0s until the chunk is 448 bits long. Then, it appends a 64 bit value with the size of the original message.

### Initialization/Splitting
The algorithm uses four buffer constants: A,B,C,D that are used to compute the digest Each of them are 32-bit and pre-initialized in hexadecimals:
```
  A = 0x67452301
  B = 0xEFCDAB89
  C = 0x98BADCFE
  D = 0x10325476
```
Each 512-bit chunk are further split into 16 words that are 32-bit each. In the processing step, there are four rounds with 16 steps each.
