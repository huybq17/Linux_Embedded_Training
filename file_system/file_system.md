# File System Programming in Linux

## Introduction
This folder contains a series of exercises designed to provide hands-on experience with file system programming in Linux. The file system is a critical component of any operating system, providing a structured way to store, organize, and access data. In Linux, everything is treated as a file, including hardware devices, directories, and regular files. These exercises focus on understanding file system concepts and implementing file and directory operations using C.

## Objectives
- Understand the fundamentals of file systems in Linux.
- Learn how to create, read, write, and delete files using C.
- Explore directory operations such as listing contents and creating directories.
- Work with symbolic links, inodes, and file metadata.
- Gain familiarity with common Linux file systems like `ext4`, `xfs`, and `btrfs`.

## Exercises Overview
The folder is organized into subdirectories, each focusing on a specific concept related to file system programming:

### 1. `file_system`
- Demonstrates how to create, write to, and read from files using C.
- Covers basic file I/O operations such as `open`, `read`, `write`, and `close`.

### 2. `check`
- Explores how to check the operations like write, read a file.

### 3. `file_metadata`
- Explains how to retrieve file metadata using the `stat` function.
- Covers file size, permissions, timestamps, and inode information.

### Running the Programs
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
   ./program_name
   ```

## References
- [Linux File System Overview](https://man7.org/linux/man-pages/man7/filesystem.7.html)
- [File I/O in Linux](https://man7.org/linux/man-pages/man2/open.2.html)
- [Directory Operations](https://man7.org/linux/man-pages/man3/opendir.3.html)
- [File Metadata with `stat`](https://man7.org/linux/man-pages/man2/stat.2.html)
- [Common Linux File Systems](https://wiki.archlinux.org/title/File_systems)

---