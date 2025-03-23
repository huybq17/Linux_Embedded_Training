#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_INCREMENTS 1000000U

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void *thr_handle(void *args) 
{
    int i = 0;

    pthread_mutex_lock(&lock);
    for (i; i < NUM_INCREMENTS; i++)
    {
        counter++;
    }
    pthread_mutex_unlock(&lock);

    // thread is exit.
    pthread_exit(NULL);
}

int main() {

    int ret;
    pthread_t thread_id1, thread_id2, thread_id3;

    if (ret = pthread_create(&thread_id1, NULL, &thr_handle, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        exit(1);
    }

    if (ret = pthread_create(&thread_id2, NULL, &thr_handle, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        exit(1);
    }

    if (ret = pthread_create(&thread_id3, NULL, &thr_handle, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        exit(1);
    }

    // used to block for the end of a thread and release
    pthread_join(thread_id1,NULL);  
    pthread_join(thread_id2,NULL);
    pthread_join(thread_id3,NULL);
    printf("Final counter is %d\n", counter);

    while(1);

    return 0;
}
