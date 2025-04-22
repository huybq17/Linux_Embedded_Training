# Static and Shared Libraries

This document provides an overview of **static libraries** and **shared libraries**, their differences, and how they are used in software development.

---

## 1. Static Libraries

### What is a Static Library?
A **static library** is a collection of object files that are linked into the program at compile time. Once linked, the library becomes part of the executable, and the program does not require the library at runtime.

### Characteristics:
- File extension: `.a` (on Linux).
- The library is embedded into the executable during the linking phase.
- The resulting executable is self-contained and does not depend on the library at runtime.
- Larger executable size since the library code is included in the binary.
- Faster execution because no runtime linking is required.

### Advantages:
- No dependency on external files at runtime.
- Easier to distribute as a standalone executable.

### Disadvantages:
- Larger executable size.
- If the library is updated, the program must be recompiled to include the changes.

---

## 2. Shared Libraries

### What is a Shared Library?
A **shared library** is a collection of object files that are loaded into memory and linked to the program at runtime. The library code is shared among multiple programs, reducing memory usage and disk space.

### Characteristics:
- File extension: `.so` (on Linux).
- The library is not embedded into the executable; instead, it is dynamically linked at runtime.
- Smaller executable size since the library code is not included in the binary.
- Requires the library to be present on the system at runtime.

### Advantages:
- Smaller executable size.
- Easier to update: Updating the library automatically updates all programs that use it.
- Shared memory usage: Multiple programs can use the same library in memory.

### Disadvantages:
- Dependency on external files at runtime.
- Potential compatibility issues if the library is updated improperly.

---

## 3. Key Differences Between Static and Shared Libraries

| Feature                | Static Library (`.a`)       | Shared Library (`.so`)       |
|------------------------|-----------------------------|------------------------------|
| Linking Time           | Compile time               | Runtime                      |
| Executable Size        | Larger                     | Smaller                      |
| Runtime Dependency     | None                       | Requires library at runtime  |
| Update Process         | Requires recompilation     | No recompilation needed      |
| Memory Usage           | Separate copy for each app | Shared across apps           |

---

## 4. How to Create and Use Libraries

### Creating a Static Library
1. Compile source files into object files:
   ```bash
   gcc -c file1.c file2.c