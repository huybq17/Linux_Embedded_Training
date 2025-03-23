# Assignment of Threads in Linux

## Introduction
This document provides an overview of thread assignment in Linux, covering the fundamental concepts, system calls, and best practices for working with threads in a Linux environment.

## What is a Thread?
A thread is a lightweight process that shares the same address space as its parent process. Threads enable parallel execution within a process, improving efficiency and performance.

## Creating Threads in Linux
In Linux, threads can be created using the `pthread` library. The following command ensures the necessary library is installed:

```sh
sudo apt-get install libpthread-stubs0-dev
```

### Example: Creating a Thread
The following C program demonstrates how to create a thread using `pthread_create`:

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg) {
    printf("Hello from thread!\n");
    return NULL;
}

int main() {
    pthread_t thread;
    if (pthread_create(&thread, NULL, thread_function, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    pthread_join(thread, NULL);
    return 0;
}
```

### Explanation
- `pthread_create()` initializes a new thread.
- `pthread_join()` ensures the main thread waits for the new thread to finish execution.

## Thread Synchronization
Synchronization is crucial to prevent race conditions when multiple threads access shared resources. Common techniques include:

### 1. Mutex (Mutual Exclusion)
```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_lock(&mutex);
// Critical section
pthread_mutex_unlock(&mutex);
```

### 2. Semaphores
```c
#include <semaphore.h>
sem_t sem;
sem_init(&sem, 0, 1);
sem_wait(&sem);
// Critical section
sem_post(&sem);
```

## Thread Scheduling
Linux uses different scheduling policies, which can be set using `pthread_setschedparam()`.
- `SCHED_FIFO`: First in, first out scheduling.
- `SCHED_RR`: Round-robin scheduling.
- `SCHED_OTHER`: Default time-sharing policy.

## Thread Termination
A thread can be terminated using:
```c
pthread_exit(NULL);
```
Or by returning from the thread function.

## User Projects on Threading
Below are some projects demonstrating the use of threads in Linux:

### 1. Multi-threaded File Processing
- Reads multiple files in parallel using separate threads.
- Uses mutex locks to prevent concurrent write conflicts.
- Improves file read and write efficiency.

### 2. Web Server with Thread Pool
- Implements a lightweight web server handling multiple requests simultaneously.
- Uses a thread pool to efficiently allocate resources for incoming requests.
- Demonstrates the use of thread synchronization to manage shared resources.

### 3. Parallel Matrix Multiplication
- Divides matrix multiplication tasks among multiple threads.
- Uses thread synchronization to merge computed results.
- Improves computational performance on large matrices.

### 4. Real-time Data Processing
- Processes streaming data using concurrent threads.
- Uses semaphores for controlled data access.
- Ensures real-time data processing without bottlenecks.

## Conclusion
Threading in Linux is a powerful tool for concurrent programming. By using `pthread`, developers can create, manage, and synchronize threads efficiently, improving performance in multi-threaded applications.

## References
- [pthread Library Documentation](https://man7.org/linux/man-pages/man7/pthreads.7.html)

