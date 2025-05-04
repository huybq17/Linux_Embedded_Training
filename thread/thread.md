# Thread Programming in Linux

## Introduction
This folder contains a series of exercises designed to provide hands-on experience with thread programming in Linux. Thread programming is a key concept in concurrent programming, enabling multiple threads to execute within the same process. These exercises focus on creating, managing, and synchronizing threads using the `pthread` library, as well as exploring advanced concepts like thread pools and scheduling.

## Objectives
- Understand the fundamentals of thread programming in Linux.
- Learn how to create and manage threads using the `pthread` library.
- Explore thread synchronization techniques such as mutexes and semaphores.
- Implement real-world applications using multi-threading to improve performance and efficiency.

## Exercises Overview
The folder is organized into subdirectories, each focusing on a specific threading concept or application:

### 1. `basic_threading`
- Demonstrates how to create and join threads using the `pthread` library.
- Covers basic thread lifecycle management.

### 2. `thread_synchronization`
- Explores synchronization techniques like mutexes.
- Prevents race conditions when accessing shared resources.

### 3. `thread_pool`
- Implements a thread pool to handle multiple tasks efficiently.
- Demonstrates resource allocation and task scheduling.

### 4. `real_time_processing`
- Processes real-time data streams using concurrent threads.
- Uses mutexes for controlled access to shared data.

## How to Run the Exercises
Each subdirectory contains a Makefile for the exercises. Follow these steps to compile and run the programs:

1. Navigate to the desired subdirectory:
   ```sh
   > cd <subdirectory_name>
   ```
2. Compile the program:
   ```sh
   > make
   ```
3. Run the program:
   ```sh
   > ./program
   ```

## References
- [pthread Library Documentation](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [Linux Thread Programming](https://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)

