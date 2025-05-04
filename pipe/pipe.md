# Pipe Programming in Linux

## Introduction
This folder contains a series of exercises designed to provide hands-on experience with pipe programming in Linux. Pipes are a fundamental mechanism for inter-process communication (IPC), allowing data to be passed between processes. These exercises focus on using unnamed and named pipes (FIFOs) to enable communication between processes.

## Objectives
- Understand the fundamentals of pipe programming in Linux.
- Learn how to use unnamed pipes for communication between parent and child processes.
- Explore named pipes (FIFOs) for communication between unrelated processes.
- Implement real-world examples of inter-process communication using pipes.

## Exercises Overview
The folder is organized into subdirectories, each focusing on a specific concept related to pipe programming:

### 1. `related_process`
- Demonstrates how to use pipes for communication between a parent process and its child.
- Covers reading and writing data through the pipe.

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
   ./program
   ```

## References
- [Linux Pipe Programming](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [Named Pipes (FIFOs)](https://man7.org/linux/man-pages/man7/fifo.7.html)
- [Inter-Process Communication](https://man7.org/linux/man-pages/man7/ipc.7.html)

