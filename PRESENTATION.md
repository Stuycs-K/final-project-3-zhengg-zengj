# MD5
Jaylen Zeng, Gil Zheng
Period 3

## Review on Hashing Algorithms
Hashing algorithms aim to take a specified string/input and convert it into a unique, fixed-length string.

Many websites make use of powerful hashing algorithms in order to protect their user's passwords by converting them from plaintext into something much less readable. Hashing can also be used on files in order to "label" them with a unique identifier. This way, people can confirm if a received file is legitimate by matching it with what was expected.

In class, we already learned how to brute force hashes using tools like John the Ripper and hashcat. However, certain hashes are vulnerable to hash collisions, which is when two inputs return the same hash. Attackers can exploit these collisions to perform something known as a collision attack.

## Background of MD5
MD5, known as Message-Digest 5, is a hash algorithm created in 1991 by Ronald Rivest as an extension to its predecessor, MD4, which was known to be insecure.

Like the majority of hash function, MD5, is a one way encryption method used for authenticating digital signatures via checksums.
The generated hash cannot be reversed and a small change to the input would change the enter hash, but the same input would always result in the same hash. However, by 2005, cryptographers, researchers, and even Rivest himself concluded that MD5 was no longer consider a cryptographic hash as it is vulnerable to hash collisions -- where two inputs would output the same hash value.  

## What makes MD5 so vulnerable?
The main contributing factor is the design of the algorithm. MD5 produces a 128-bit hash, which means there's approximately 2^128 (3.4 × 10^38) different hashes that can be generated; a birthday attack can brute force a collision in approximately 2^64 attempts, where the probability of finding a hash collision increases as the number of hashes generated also increases (assuming that all hashes have the same probability to be generated).

![Probability of Collision Using Birthday Attack](https://github.com/Stuycs-K/final-project-3-zhengg-zengj/blob/main/IMAGES/BirthdayAttackProbability.jpg?raw=true)

MD5, like many other popular hash algorithms, follows the Merkle–Damgård construction for is padding and compression steps. The inputs of MD5 are padded to 512-bits because the Merkle–Damgård compression function cannot handle arbitrary sizes. This function is also the reason why MD5 has the length of the initial input appended to the end of the padding: making the construction more secure.

![Merkle-Damgård Construction Process](https://github.com/Stuycs-K/final-project-3-zhengg-zengj/blob/main/IMAGES/MerkleDamg%C3%A5rd.jpg?raw=true)

However, this block construction is what allows MD5 to be vulnerable to prefix collisions. There are two main prefix collisions: identical and chosen. We'll use [HashClash](https://
github.com/cr-marcstevens/hashclash), a tool used to generate both prefix collisions, to demonstrate each one.

### How to download/use HashClash (from the GitHub Page)

- Have C++11 compiler (e.g. g++) and make

- Install autoconf & automake & libtool:
`sudo apt-get install autoconf automake libtool` | *MAC:* `brew install autoconf automake libtool`  

- Install zlib & bzip2 libraries:
`sudo apt-get install zlib1g-dev libbz2-dev` | *MAC:* `brew install zlib-ng libzdb`

- **Not needed** Only download CUDA if you have a NVIDIA graphics card -- allows computer to generate collision blocks/hashes faster.

- Clone the repository: `git clone https://github.com/cr-marcstevens/hashclash.git`

- cd into the repository and `nano install_boost.sh` and change the BOOST_VERSION to 1.72.0. Should look like `${BOOST_VERSION:=1.72.0}`.
Now run the shell script:  `./install_boost.sh`

- Run the automatic build script `./build.sh`
If everything is correctly downloaded it would output the following:

`
[*] checking for system tool: autoconf: found
[*] checking for system tool: automake: found
[*] checking for system tool: libtool: found
[*] checking for system library: zlib1g-dev: found
[*] checking for system library: libbz2-dev: found
[*] Checking for local boost (version 1.72.0): found
[*] Run: autoreconf --install
`

### Identical-prefix Collision Attack/ Classical Condition Attack:

1. Define an arbitrary prefix (content and length do not matter)
2. Prefix is padded to the next 64-byte block
3. Collision block(s) are then computed depending on the prefix and 
appended. 
  - Both sides are very random
  - Differences are predetermined by the attack.
4. Afterwards, the hash value is the same despite the file differences.
5. Finally, any arbitrary identical suffix can be added

![It will look something like this](https://github.com/Stuycs-K/final-project-3-zhengg-zengj/blob/main/IMAGES/identical.png)




### Chosen-prefix Collision Attack
Unique to Merkle–Damgård hash functions. Take two different files and then 
append two calculated values resulting in the whole document having the 
same hash. Here are the basic steps:

1. Take two arbitrary prefixes and pad the shorter one so that it is as 
long as the other.
2. Pad both to the next block of memory minus 12 bytes
3. X near-collision blocks will then be computed and appended.

This type of collision is very powerful but generally takes longer than 
other variations. 
