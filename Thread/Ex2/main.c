#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t thread_id1, thread_id2, thread_id3;
int counter;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* thread_handle(void* arg);

int main(int argc, char* argv[])
{
    int i = 0;
    int error;

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n Mutex init has failed\n");
        exit(EXIT_FAILURE);
    }

    error = pthread_create(&thread_id1, NULL, &thread_handle, NULL);
    if(error)
    {
        fprintf(stderr, "Cannot create thread 1\n");
        exit(EXIT_FAILURE);
    }

    error = pthread_create(&thread_id2, NULL, &thread_handle, NULL);
    if(error)
    {
        fprintf(stderr, "Cannot create thread 2\n");
        exit(EXIT_FAILURE);
    }

    error = pthread_create(&thread_id3, NULL, &thread_handle, NULL);
    if(error)
    {
        fprintf(stderr, "Cannot create thread 3\n");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);

    printf("counter = %d\n", counter);
    
    exit(0);
}

void* thread_handle(void* arg)
{
    pthread_mutex_lock(&lock);

    for(int i = 0; i < 1000000; i++)
    {
        counter++;
    }

    pthread_mutex_unlock(&lock);

    return NULL;
}
