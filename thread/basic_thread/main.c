#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    char name[30];
    char msg[30];
} thr_data_t;

static void *thr_handle(void *args) 
{
    printf("Thread %ld: Hello from thread\n", pthread_self());

    // thread is exit.
    pthread_exit(NULL);
}

int main()
{
    int ret;
    int status;
    pthread_t thread_id1, thread_id2;

    if (ret = pthread_create(&thread_id1, NULL, &thr_handle, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }


    if (ret = pthread_create(&thread_id2, NULL, &thr_handle, NULL)) {
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    // Waiting for the created thread to terminate 
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    while(1);
    
    return 0;
}
