# Signal Programming in Linux

## Introduction
This folder contains a series of exercises designed to provide hands-on experience with signal programming in Linux. Signals are a mechanism for inter-process communication and asynchronous event handling. These exercises focus on catching, handling, and generating signals, as well as using signals for process control and timers.

## Objectives
- Understand the fundamentals of signal programming in Linux.
- Learn how to catch and handle signals using `signal` and `sigaction`.
- Explore the use of signals for process control and communication.
- Implement timers using signals like `SIGALRM`.

## Exercises Overview
The folder is organized into subdirectories, each focusing on a specific concept related to signal programming:

### 1. Catching the Signal `SIGINT`
- Demonstrates how to handle the `SIGINT` signal (triggered by pressing `Ctrl+C`).
- Prevents the program from terminating immediately by catching and handling the signal.

### 2. Creating a Timer Using `SIGALRM`
- Shows how to use the `SIGALRM` signal to create a timer.
- Demonstrates setting up an alarm and handling the signal when the timer expires.


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
- [Linux Signal Programming](https://man7.org/linux/man-pages/man7/signal.7.html)
- [Signal Handling with sigaction](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [Using SIGALRM for Timers](https://man7.org/linux/man-pages/man2/alarm.2.html)
- [Inter-Process Communication with Signals](https://man7.org/linux/man-pages/man2/kill.2.html)
