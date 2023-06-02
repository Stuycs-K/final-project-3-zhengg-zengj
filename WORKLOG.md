# Work Log

## Jaylen Zeng

### 5-17-23
- Wrote initial project description in README

### 5-18-23
- More preliminary research on hash collision attacks. Looked at MD5/SHA-1 variations.
- Consider covering hash collisions for less powerful hash algorithms (less bits)

### 5-19-23
- Switch from hash collisions to MD5 algorithm
- Began researching on MD5 algorithm --> found examples and implementations online

### 5-20-23 : 5-21-23
- Began programming MD5 message padding

### 5-22-23
- Finished message padding

### 5-23-23
- Finished splitting longer messages into 512 bit chunks
- Started main loop

### 5-24-23
- Basically finish main loop
  - ~~Just need to implement left_rotate~~ finished
  - Not sure if works

### 5-25-23
- Updated README.md
- Added references/sources

### 5-26-23 : 5-29-23
- Fixed bug in MD5 with padding
- Algo now works with any message length
- Fully functional MD5 hash

### 5-30-23
- Worked on presentation
- Discussed with other group how to split MD5 presentation
  -We will talk about its background and collisions | they will talk about algo itself

### 5-31-23 & 6-1-23
- More presentation work

## Gil Zheng

### 5-18-23
- Research on hash collisions in order to create a viable project.
- Found different methods such as HashClash, but unsure of practicability

### 5-19-23
- Researching MD5 algorithm; changed proj README

### 5-22-23 & 5-23-23
- Worked on the presentation aspect of the project  

### 5-24-23 & 5-25-23
- Finished the padding portion of the presentation
- Did the compression/concatenation of the MD5 program

### 5-26-23 to 5-29-23
- Continued working on presentation, and started further researching on HashClash

### 5-30-23
- Created homework questions and started experimenting on HashClash

### 5-31-23 to 6-2-23
- Scrapped presentation on MD5 algorithm and switched focus to prefix collisions
- Updated the readme and homework


## Resources
https://en.wikipedia.org/wiki/MD5#Algorithm (Psuedocode found here)
https://fthb321.github.io/MD5-Hash/MD5OurVersion2.html (Visualization of padding)
https://stackoverflow.com/questions/32933254/which-type-of-leftrotation-is-used-by-the-md5-hash-algorithm (leftrotate found here)
https://github.com/corkami/collisions (explanation of prefix collisions/ borrowed images)
https://en.wikipedia.org/wiki/Birthday_attack (birthday attack section/ borrowed images)
