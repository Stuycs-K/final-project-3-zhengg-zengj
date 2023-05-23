# MD5

## Background of MD5
MD5, known as Message-Digest 5, is a hash algorithm created in 1991 by Ronald Rivest to replace its predecessor, MD4.  

Like the majority of hash function, MD5, is a one way encryption method used for authenticating digital signatures via checksums. The hash cannot be reversed, but the same input would always result in the same hash. However, MD5 is no longer consider a cryptographic hash as it is vulnerable to hash collisions -- where two strings have the same hash value.  


##How it works
MD5 uses a mathematical algorithm to process the string.

###Padding
The message is first broken up into 512-bit chunks which the algorithm makes sure that it is divisible by 512. It accomplishes this by appending a singular 1 bit to the chunk and fills the rest with 0s until the chunk is 448 bits long. Then, it appends a 64 bit
