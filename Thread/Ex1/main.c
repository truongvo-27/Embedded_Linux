#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t thread_id1, thread_id2;

static void *thr_handle1(void *args);
static void *thr_handle2(void *args);

int main(int argc, char *argv[])
{
    int ret_val;

    if (ret_val = pthread_create(&thread_id1, NULL, &thr_handle1, NULL)) {
        printf("pthread_create() error number=%d\n", ret_val);
        exit(EXIT_FAILURE);
    }

    if (ret_val = pthread_create(&thread_id2, NULL, &thr_handle2, NULL)) {
        printf("pthread_create() error number=%d\n", ret_val);
        exit(EXIT_FAILURE);
    }
    sleep(3);

    pthread_join(thread_id1, NULL);
    printf("Thread 1 was terminated\n");

    pthread_join(thread_id2, NULL);
    printf("Thread 2 was terminated\n");

    exit(0);
}

static void *thr_handle1(void *args) 
{
    pthread_t tid = pthread_self();

    if(pthread_equal(tid, thread_id1))
    {
        printf("Thread 1, ID = %lu\n", (unsigned long)pthread_self());
    }
    return NULL;
}

static void *thr_handle2(void *args) 
{
    pthread_t tid = pthread_self();

    if(pthread_equal(tid, thread_id2))
    {
        printf("Thread 2, ID = %lu\n", (unsigned long)pthread_self());
    }
    return NULL;
}