# File System in Linux with C

## 1. What is a File System?

A File System is a method of organizing and storing data on storage devices such as hard drives, SSDs, or USB drives. It provides an interface for users and programs to access, read, write, and manage data.

In Linux, everything is treated as a file, including hardware devices, directories, and regular files.

---

## 2. Types of Files in Linux

Linux categorizes files into the following types:
- **Regular file**: Standard files (e.g., text files, binary files).
- **Directory**: Folders containing files or subdirectories.
- **Special file**: Device files (e.g., `/dev/sda`).
- **Symbolic link**: Shortcut files (symlinks).
- **Socket**: Files used for inter-process communication.
- **FIFO (Named Pipe)**: Files used for queue-based inter-process communication.

---

## 3. How File System Works in Linux

### 3.1. File System Structure
The Linux File System is organized as a tree structure, with the root directory `/`. Subdirectories and files are arranged hierarchically.

### 3.2. Mounting
- **Mounting** is the process of attaching a file system to a directory in the system.
- Example: Mounting a USB drive to `/mnt/usb`:
  ```bash
  mount /dev/sdb1 /mnt/usb
  ```

### 3.3. Inode
- Every file in Linux is represented by an **inode**.
- **Inode** contains metadata about the file, such as:
  - File size.
  - Access permissions.
  - Creation and modification timestamps.
  - Storage location on the disk.

---

## 4. Assignments on File Systems

### 4.1. Practical Tasks
- Write a C program to create a new file and write some text into it.
- Implement a program to read the contents of a directory and display all file names.
- Create a symbolic link to an existing file and verify its functionality.

---

## 5. Other Important Functions

- **`stat()`**: Retrieve file information.
- **`mkdir()`**: Create a directory.
- **`rmdir()`**: Remove a directory.
- **`unlink()`**: Delete a file.
- **`opendir()` and `readdir()`**: Read directory contents.

---

## 6. Common File Systems in Linux

- **ext4**: Default file system for many Linux distributions.
- **xfs**: High-performance file system for large systems.
- **btrfs**: Supports snapshots and flexible storage management.
- **vfat**: Used for USB drives or devices compatible with Windows.

---

## 7. Summary

The File System is a critical component in Linux, providing an efficient way to organize and manage data. Understanding and using File System-related functions in C allows developers to manipulate files and directories flexibly and effectively.