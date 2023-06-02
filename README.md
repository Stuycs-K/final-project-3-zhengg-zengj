# MD5 Implementation
Gil Zheng, Jaylen Zeng
Hashbrowns
Period 3 Cybersecurity

## Compilation
To run the MD5 Hash Generator:
```
gcc -o MD5.out MD5.c
./MD5.out (text)
```
## HashClash Installation

To use [HashClash](https://github.com/cr-marcstevens/hashclash)
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

```
[*] checking for system tool: autoconf: found
[*] checking for system tool: automake: found
[*] checking for system tool: libtool: found
[*] checking for system library: zlib1g-dev: found
[*] checking for system library: libbz2-dev: found
[*] Checking for local boost (version 1.72.0): found
[*] Run: autoreconf --install

````


## About

This project serves to recreate the MD5 hash algorithm in C. Not only will we implement our own version of MD5, but we also aim to fully understand and share the inner workings of the hashing algorithm. We also dive into the vulnerabilities of MD5 and explain how to generate hash collisions using the tool, HashClash.

## Links
- [Presentation](./PRESENTATION.md)
- [Homework](./HOMEWORK.md)
