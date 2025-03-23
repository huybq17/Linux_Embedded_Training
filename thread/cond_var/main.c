#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_PRINT 10U
#define MAX_NUM_THREADS 2U

// Declaration of thread condition variable
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
// declaring mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int data = 0;
int data_ready = 0;

typedef struct {
    char msg[30];
} thread_info_t;

typedef struct {
    thread_info_t   data;
    pthread_t       thread;
} pthread_info_t;


int random_number() {
    return (rand() % 10) + 1;
}

void *producer_handler(void *args) 
{
    int i = 0;
    srand(time(NULL));

    for (i; i < MAX_PRINT; i++) {
        pthread_mutex_lock(&lock);
        data = random_number();
        data_ready = 1;
        printf("Producer: Transfering data %d\n", data);

        pthread_cond_signal(&cond1);
        pthread_mutex_unlock(&lock);

        // Waiting consumer is finish handled the data
        pthread_mutex_lock(&lock);
        while (data_ready == 1) {
            pthread_cond_wait(&cond1, &lock);
        }
        pthread_mutex_unlock(&lock);
    }

    // thread is exit.
    pthread_exit(NULL);
}

void *consumer_handler(void *args) 
{   
    int i = 0;

    for (i; i < MAX_PRINT; i++) {
        pthread_mutex_lock(&lock);

        while (data_ready == 0) {
            pthread_cond_wait(&cond1, &lock);
        }
        printf("Consumer: Received data is %d\n", data);
        data_ready = 0;

        // Inform producer that consumer is received the data
        pthread_cond_signal(&cond1);
        pthread_mutex_unlock(&lock);
    }

    // thread is exit.
    pthread_exit(NULL);
}

int main() {
    int ret;
    int i;
    pthread_info_t   threads[MAX_NUM_THREADS];

    for (i = 0; i < MAX_NUM_THREADS; i++) {
        memset( &threads[i].data, 0x00, sizeof(pthread_info_t));
    }
    
    // Creating new threads
    if ((ret = pthread_create(&threads[0].thread, NULL, &producer_handler, NULL)) != 0) {
        printf("pthread_create() error number=%d\n", ret);
        return (ret);
    }

    if ((ret = pthread_create(&threads[1].thread, NULL, &consumer_handler, NULL)) != 0) {
        printf("pthread_create() error number=%d\n", ret);
        return (ret);
    }

    // used to block for the end of a thread and release
    for (i = 0; i < MAX_NUM_THREADS; i++)
    {
        pthread_join(threads[i].thread, NULL);
    }

    while (1);
    
    return 0;
}