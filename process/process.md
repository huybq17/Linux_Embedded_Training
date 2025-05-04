# Process Programming in Linux

## Introduction
This folder contains a series of exercises designed to provide hands-on experience with process programming in Linux. Process programming is essential for understanding how programs execute and interact with the operating system. These exercises cover process creation, execution and process status management.

## Objectives
- Understand the fundamentals of process creation and management in Linux.
- Learn how to use `fork` to create child processes.
- Explore the `exec` family of functions to execute new programs.
- Manage and monitor process statuses.

## Exercises Overview
The folder is organized into subdirectories, each focusing on a specific concept related to process programming:

### 1. `fork`
- Demonstrates how to create child processes using the `fork` system call.
- Explores parent-child process relationships and process IDs.

### 2. `exec`
- Shows how to replace the current process image with a new program using the `exec` family of functions.
- Includes examples of running commands like `ls`, `date`, `time`, and `ps` using arguments.

### 3. `signal process`
- Explains how to send and handle signals between processes.
- Covers signal handling using `signal` or `sigaction`.

### 4. `status process`
- Demonstrates how to retrieve and manage process statuses.
- Uses system calls like `wait` and `waitpid` to monitor child processes.

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
- [Linux Process Management](https://man7.org/linux/man-pages/man2/fork.2.html)
- [exec Family of Functions](https://man7.org/linux/man-pages/man3/exec.3.html)
- [Signal Handling in Linux](https://man7.org/linux/man-pages/man7/signal.7.html)
- [Process Status and Monitoring](https://man7.org/linux/man-pages/man2/wait.2.html)

