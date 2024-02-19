# Kollektions
Collection framework written in C with wrappers for the following programming languages:
- C++

## Features
- Fixed List
  fixed-length modifieable list. Is the base for most other collections.
- Static List
  fixed-capacity modifieable list. Based on Fixed List.
- Dynamic List
  dynamically-allocated modifieable list. Based on Static List.

## Building
This repository currently contains two libraries: `kallok` and `kollektions`.
To build them, you need to first compile the independent `build.c` file.
But first you should configure some options that can be found in the top of the `build.c` file.
Then run: `./build kallok.a` and `./build kollektions.a`. The output static-libraries will be located in the `build/` directory.
