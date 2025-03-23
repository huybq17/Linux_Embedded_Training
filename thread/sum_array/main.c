#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


#define MAX_NUM_THREADS           4U
#define MAX_SIZE            1000000U

unsigned int sum_array = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    char    *array;
    char    order;
} thread_info_t;

typedef struct {
    thread_info_t   data;
    pthread_t       thread;
} pthread_info_t;

char random_number(void) {
    return (rand() % 10) + 1;
}

void *sum_handler(void *arg) {
    int i;
    thread_info_t *data = (thread_info_t*)arg;  
    
    pthread_mutex_lock(&lock);
    for (i = 0; i < MAX_NUM_THREADS; i++) {
        if (i == data->order) {
            for (i*(MAX_SIZE/MAX_NUM_THREADS); i < i*(MAX_SIZE/MAX_NUM_THREADS) + MAX_SIZE/MAX_NUM_THREADS; i++) {
                sum_array += *(data->array+i);
            }
            printf("Sum of array %d is: %u\n", data->order, sum_array);
        }
    }
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main() {
    pthread_info_t threads[MAX_NUM_THREADS];
    int i, ret;
    char temp[MAX_SIZE] = {0};

    for (i = 0; i < MAX_SIZE; i++) {
        temp[i] = random_number();
    }
    
    // Creating new threads
    for (i = 0; i < MAX_NUM_THREADS; i++) {
        if ((ret = pthread_create(&threads[i].thread, NULL, sum_handler, &threads[i].data)) != 0) {
            return (ret);
        }

        threads[i].data.order = i;
        threads[i].data.array = temp;
    }
    
    // Waiting the return value
    for (i = 0; i < MAX_NUM_THREADS; i++) {
        pthread_join(threads[i].thread, NULL);
    }

    printf("Sum of array is: %u\n", sum_array);

    return 0;
}
