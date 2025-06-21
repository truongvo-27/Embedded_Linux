#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_t thread_id[3];
int counter;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* thread_handle(void* arg);

int main(int argc, char* argv[])
{
    int i = 0;
    int error;

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n Mutex init has failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= 3; i++)
    {
        error = pthread_create(&thread_id[i], NULL, &thread_handle, NULL);
        if (error)
        {
            fprintf(stderr, "Cannot create thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 1; i <= 3; i++)
    {
        pthread_join(thread_id[i], NULL);
    }

    printf("counter = %d\n", counter);
    
    exit(0);
}

void* thread_handle(void* arg)
{
    pthread_mutex_lock(&lock);

    for (int i = 0; i < 1000000; i++)
    {
        counter++;
    }

    pthread_mutex_unlock(&lock);

    return NULL;
}
