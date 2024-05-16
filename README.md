# MERGED INTO [allib](https://github.com/alex-s168/allib)

# Kollektions & Kallok
Collection and memory allocator framework written in C.
Tested on Linux and Windows.

## Features (Kollektions)
- Fixed List:
  fixed-length mutable list. Is the base for most other collections.
- Dynamic List:
  dynamically-allocated mutable list.
- Doubly Linked List:
  dynamically-allocated mutable list with O(1) remove, add and insert

## Features (Kallok)
- Common interface for all allocators. `Ally` type.
- Page allocator
- LibC allocator
- Basic fixed & dynamic allocators:
  big allocation split into chunks. one allocation consists of multiple chunks.
- Disk-based allocator:
  virtual maps a file into memory.

## Building
This repository currently contains two libraries: `kallok` and `kollektions`.
To build them, you need to first compile the independent `build.c` file.
(The project uses [Build.C](https://github.com/alex-s168/build.c))
But first you should configure some options that can be found in the top of the `build.c` file.
Then run: `./build.exe kallok.a` and `./build.exe kollektions.a`. The output static-libraries will be located in the `build/` directory.
It is also recommended to run `./build.exe tests` afterwards.
