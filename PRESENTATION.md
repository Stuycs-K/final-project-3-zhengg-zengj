# MD5

## Background of MD5
MD5, known as Message-Digest 5, is a hash algorithm created in 1991 by Ronald Rivest as an extension to its predecessor, MD4, which was known to be insecure.

Like the majority of hash function, MD5, is a one way encryption method used for authenticating digital signatures via checksums.
The generated hash cannot be reversed and a small change to the input would change the enter hash, but the same input would always result in the same hash. However, by 2005, cryptographers, researchers, and even Rivest himself concluded that MD5 was no longer consider a cryptographic hash as it is vulnerable to hash collisions -- where two inputs would output the same hash value.  

## What Makes MD5 so vulnerable?
The main contributing factor is the design of the algorithm. MD5 produces a 128-bit hash, which means there's approximately 2^128 (3.4 × 10^38) different hashes that can be generated; a birthday attack can brute force a collision in approximately 2^64 attempts, where the probability of finding a hash collision increases as the number of hashes generated also increases (assuming that all hashes have the same probability to be generated).
![Probability of Collision Using Birthday Attack](https://github.com/Stuycs-K/final-project-3-zhengg-zengj/blob/main/IMAGES/BirthdayAttackProbability.jpg?raw=true)


We can demonstrate these attacks using a tool called HashClash
### Identical-prefix Collision Attack/ Classical Condition Attack

### Chosen-prefix Collision Attack


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
