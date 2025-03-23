#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_NUM_THREADS 2U
#define MAX_NUMBERS     100U

typedef struct {
    char *msg;
    int   sum;
} thread_info_t;

typedef struct {
    thread_info_t   data;
    pthread_t       thread;
} pthread_info_t;

void *even_count (void *arg) {
    int i;
    thread_info_t *data = (thread_info_t*)arg;

    for (i = 0; i < MAX_NUMBERS; i++) {
        if ((*(data->msg+i) % 2) == 0) {
            data->sum++;
        }
    }
    
    printf("sum of even numbers: %d\n", data->sum);
    pthread_exit(NULL);
}

void *odd_count (void *arg) {
    int i;
    thread_info_t *data = (thread_info_t*)arg;

    for (i = 0; i < MAX_NUMBERS; i++) {
        if ((*(data->msg+i) % 2) == 0) {
            data->sum++;
        }
    }
    
    printf("sum of odd numbers: %d\n", data->sum);
    pthread_exit(NULL);
}


int main() {
    int i, ret;
    pthread_info_t threads[MAX_NUM_THREADS];
    char num[MAX_NUMBERS] = {0};

    // Initialize values ​​for array
    for (i = 0; i < MAX_NUMBERS; i++) {
        num[i] = i+1;
    }

    // Initialize values ​​for thread data
    for (i = 0; i < MAX_NUM_THREADS; i++)
    {
        threads[i].data.msg = num;
        threads[i].data.sum = 0;
    }
    
    // Create new threads
    if ((ret = pthread_create(&threads[0].thread, NULL, even_count, &threads[0].data)) != 0) {
        return (ret);
    }

    if ((ret = pthread_create(&threads[1].thread, NULL, odd_count, &threads[1].data)) != 0) {
        return (ret);
    }

    // Waiting the return value
    for (i = 0; i < MAX_NUM_THREADS; i++) {
        pthread_join(threads[i].thread, NULL);
    }
    
    while(1);
    
    return 0;
}
