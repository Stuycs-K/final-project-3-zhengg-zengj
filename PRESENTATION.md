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

### Identical-prefix Collision Attack/ Classical Condition Attack:
We take a single arbitrary prefix and append it to both files/inputs. Output files will be almost identical (few bits of difference at most)s

1. Define an arbitrary prefix (content and length do not matter)
2. Prefix is padded to the next 64-byte block
3. Collision block(s) are then computed depending on the prefix and
appended.
  - Both sides are very random
  - Differences are predetermined by the attack.
4. Afterwards, the hash value is the same despite the file differences.
5. Finally, any arbitrary identical suffix can be added

![It will look something like this](https://github.com/Stuycs-K/final-project-3-zhengg-zengj/blob/main/IMAGES/identical.png)

There's not much you can exploit with a identical-prefix collision since you know the differences in advance.


### Chosen-prefix Collision Attack
Unique to Merkle–Damgård hash functions. Take two different files and then
append two calculated values resulting in the whole document having the
same hash. Here are the basic steps:

1. Take two arbitrary prefixes and pad the shorter one so that it is as
long as the other.
2. Pad both to the next block of memory minus 12 bytes
3. X near-collision blocks will then be computed and appended.

This type of collision is very powerful but generally takes longer than
other variations. The Flame Malware (2012) took advantage of a MD5 chosen-prefix collision
to produce a counterfeit certificate to access Microsoft machines.

![It will look something like this](https://github.com/Stuycs-K/final-project-3-zhengg-zengj/blob/main/IMAGES/chosen.png)

### How to download/use HashClash (from the GitHub Page)

- Have C++11 compiler (e.g. g++) and make

- Install autoconf & automake & libtool:
`sudo apt-get install autoconf automake libtool` | **MAC:** `brew install autoconf automake libtool`  

- Install zlib & bzip2 libraries:
`sudo apt-get install zlib1g-dev libbz2-dev` | **MAC:** `brew install zlib-ng libzdb`

- Clone the repository: `git clone https://github.com/cr-marcstevens/hashclash.git`

- cd into the repository and `nano install_boost.sh` and change the BOOST_VERSION to 1.72.0. Should look like `${BOOST_VERSION:=1.72.0}`.
Now run the shell script:  `./install_boost.sh`

- Run the automatic build script `./build.sh`

***Generating collisions with HashClash***

*Identical Hash Collisions:*
- Make temp directory `mkdir ipc_workdir` and cd into it.  
- Create a file with your desired prefix: `echo -n "ANYSTRING" > prefix.txt`
- Run the script `../scripts/poc_no.sh prefix.txt`
- Running the program for the first time will take a while, but usually it would take a few seconds.
- When it finds a collision:
```
Block 1: ./data/coll1_481974632
4b 4f 4e 53 54 41 4e 54 b7 63 f6 22 d8 19 07 e4
71 56 6d 21 1b 49 d1 0a 26 c8 4c b6 89 5f da 68
3a e9 0b ec 4e 34 75 88 b1 8f 28 2f 0c 61 31 88
04 a8 dc 7c 17 7d 04 7a af 44 87 bd 4a bb bc e2
Block 2: ./data/coll2_481974632
4b 4f 4e 53 54 41 4e 54 b7 64 f6 22 d8 19 07 e4
71 56 6d 21 1b 49 d1 0a 26 c8 4c b6 89 5f da 68
3a e9 0b ec 4e 34 75 88 b1 8f 28 2f 0c 61 31 88
04 a8 dc 7c 17 7d 04 7a af 44 87 bd 4a bb bc e2
Found collision!
```
- The program will continue generating even when it finds a collision, so make sure to Ctrl+C to stop the program.
- The message is also easy to miss, so use Cmd+F or Ctrl+F to search for the collision message.
- When you ls, there will be two files: collision1.bin and collision2.bin that are each 128 bytes.
View the block with xxd:
```
xxd collision1.bin
00000000: 4b4f 4e53 5441 4e54 b763 f622 d819 07e4  KONSTANT.c."....
00000010: 7156 6d21 1b49 d10a 26c8 4cb6 895f da68  qVm!.I..&.L.._.h
00000020: 3ae9 0bec 4e34 7588 b18f 282f 0c61 3188  :...N4u...(/.a1.
00000030: 04a8 dc7c 177d 047a af44 87bd 4abb bce2  ...|.}.z.D..J...
00000040: 737b 402e f85a 5f6b 8214 b250 03de 26fa  s{@..Z_k...P..&.
00000050: e2f3 1860 d9c3 16b7 24d1 bbc9 114f ab5d  ...`....$....O.]
00000060: daa8 875e 316b 562f 4287 66d2 66b8 e80b  ...^1kV/B.f.f...
00000070: f0dc 461a bba6 36f0 911d bbf1 3aee dcf1  ..F...6.....:...

```
```
xxd collision2.bin
00000000: 4b4f 4e53 5441 4e54 b764 f622 d819 07e4  KONSTANT.d."....
00000010: 7156 6d21 1b49 d10a 26c8 4cb6 895f da68  qVm!.I..&.L.._.h
00000020: 3ae9 0bec 4e34 7588 b18f 282f 0c61 3188  :...N4u...(/.a1.
00000030: 04a8 dc7c 177d 047a af44 87bd 4abb bce2  ...|.}.z.D..J...
00000040: 737b 402e f85a 5f6b 8213 b250 03de 26fa  s{@..Z_k...P..&.
00000050: e2f3 1860 d9c3 16b7 24d1 bbc9 114f ab5d  ...`....$....O.]
00000060: daa8 875e 316b 562f 4287 66d2 66b8 e80b  ...^1kV/B.f.f...
00000070: f0dc 461a bba6 36f0 911d bbf1 3aee dcf1  ..F...6.....:...
```
The files have slight difference but will have the same hashes:
```
md5 collision1.bin
MD5 (collision1.bin) = 5f2822aafa35332334180ee2e71d54e4
md5 collision2.bin
MD5 (collision2.bin) = 5f2822aafa35332334180ee2e71d54e4
```
*Chosen-prefix Hash Collisions*
Depending on your hardware, a chosen-prefix hash collision can take hours to find one collision.
The fewer the blocks, the longer it will take to generate a collision.  (We didn't test this since it took too long).
- Create directory `mkdir cpc_workdir` and cd into it.
- Run the script `../scripts/cpc.sh <prefix.filename1> <prefix.filename2>`
