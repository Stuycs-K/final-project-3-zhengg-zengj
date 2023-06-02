# Homework
## Problem 1: Padding a MD5 input
Given the following phrase, **HASHBROWNS**, write out the 512-bit chunk with the padding.

SAMPLE RESPONSE WITH WORD: MCDONALDS

```
01001101 01000011 01000100 01001111 01001110 01000001 01001100 01000100 01010011 10000000
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
00000000 00000000 00000000 01001000
```

## Problem 2: Generate an hash collision!
Using HashClash, generate a identical pre-fix collision with the prefix: **POPEYES**

SAMPLE RESPONSE WITH PREFIX: KONSTANT
```
gilzheng@Gils-MacBook-Pro ipc_workdir % xxd collision1.bin
00000000: 4b4f 4e53 5441 4e54 b763 f622 d819 07e4  KONSTANT.c."....
00000010: 7156 6d21 1b49 d10a 26c8 4cb6 895f da68  qVm!.I..&.L.._.h
00000020: 3ae9 0bec 4e34 7588 b18f 282f 0c61 3188  :...N4u...(/.a1.
00000030: 04a8 dc7c 177d 047a af44 87bd 4abb bce2  ...|.}.z.D..J...
00000040: 737b 402e f85a 5f6b 8214 b250 03de 26fa  s{@..Z_k...P..&.
00000050: e2f3 1860 d9c3 16b7 24d1 bbc9 114f ab5d  ...`....$....O.]
00000060: daa8 875e 316b 562f 4287 66d2 66b8 e80b  ...^1kV/B.f.f...
00000070: f0dc 461a bba6 36f0 911d bbf1 3aee dcf1  ..F...6.....:...
gilzheng@Gils-MacBook-Pro ipc_workdir % xxd collision2.bin
00000000: 4b4f 4e53 5441 4e54 b764 f622 d819 07e4  KONSTANT.d."....
00000010: 7156 6d21 1b49 d10a 26c8 4cb6 895f da68  qVm!.I..&.L.._.h
00000020: 3ae9 0bec 4e34 7588 b18f 282f 0c61 3188  :...N4u...(/.a1.
00000030: 04a8 dc7c 177d 047a af44 87bd 4abb bce2  ...|.}.z.D..J...
00000040: 737b 402e f85a 5f6b 8213 b250 03de 26fa  s{@..Z_k...P..&.
00000050: e2f3 1860 d9c3 16b7 24d1 bbc9 114f ab5d  ...`....$....O.]
00000060: daa8 875e 316b 562f 4287 66d2 66b8 e80b  ...^1kV/B.f.f...
00000070: f0dc 461a bba6 36f0 911d bbf1 3aee dcf1  ..F...6.....:...
gilzheng@Gils-MacBook-Pro ipc_workdir % md5 collision1.bin
MD5 (collision1.bin) = 5f2822aafa35332334180ee2e71d54e4
gilzheng@Gils-MacBook-Pro ipc_workdir % md5 collision2.bin
MD5 (collision2.bin) = 5f2822aafa35332334180ee2e71d54e4
```
