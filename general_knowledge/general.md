# Static and Shared Libraries

## Introduction
This document provides an overview of **static libraries** and **shared libraries**, their differences, and how they are used in software development.

## Objectives
- Understand the fundamentals of static and shared libraries.
- Learn how to create and use static libraries (`.a`) and shared libraries (`.so`) in Linux.
- Explore the advantages and disadvantages of each type of library.
- Gain hands-on experience with compiling and linking programs using libraries.

### 1. Static Libraries
- A **static library** is a collection of object files linked into the program at compile time.
- Characteristics:
  - File extension: `.a` (on Linux).
  - Embedded into the executable during the linking phase.
  - Larger executable size but no runtime dependency.
- Advantages:
  - No runtime dependency on external files.
  - Easier to distribute as a standalone executable.
- Disadvantages:
  - Larger executable size.
  - Requires recompilation if the library is updated.

### 2. Shared Libraries
- A **shared library** is a collection of object files loaded into memory and linked at runtime.
- Characteristics:
  - File extension: `.so` (on Linux).
  - Dynamically linked at runtime, reducing executable size.
  - Requires the library to be present on the system at runtime.
- Advantages:
  - Smaller executable size.
  - Easier to update: Updating the library updates all dependent programs.
  - Shared memory usage across multiple programs.
- Disadvantages:
  - Dependency on external files at runtime.
  - Potential compatibility issues if the library is updated improperly.

## Running the Programs
1. Navigate to the desired subdirectory:
   ```sh
   cd <subdirectory_name>
   ```
2. Compile the program:
   ```sh
   make
   ```
3. Run the program:
   ```sh
   ./program
   ```

## References
- [Static Libraries in Linux](https://tldp.org/HOWTO/Program-Library-HOWTO/static-libraries.html)
- [Shared Libraries in Linux](https://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html)
- [GCC Documentation](https://gcc.gnu.org/onlinedocs/)
- [Linux Programmer's Manual](https://man7.org/linux/man-pages/)
