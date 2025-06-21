#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int sum = 0;
int arr[1000000];

pthread_t thread_id[4];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void create_arr();

void* thread_handle1(void* arg);
void* thread_handle2(void* arg);
void* thread_handle3(void* arg);
void* thread_handle4(void* arg);

// Create a array function poiter to manager the thread handle function
void* (*thread_handle[4])(void* arg) = {
    thread_handle1,
    thread_handle2,
    thread_handle3,
    thread_handle4
};


int main(int argc, char* argv[])
{
    int i = 0;
    int error;
    create_arr();

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n Mutex init has failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 4; i++)
    {
        error = pthread_create(&thread_id[i], NULL, thread_handle[i], NULL);
        if (error)
        {
            fprintf(stderr, "Cannot create thread %d\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        pthread_join(thread_id[i], NULL);
    }

    printf("Sum expectation: 1000000\n");
    printf("Sum reality: %d\n", sum);
    
    exit(0);
}

void* thread_handle1(void* arg)
{
    pthread_mutex_lock(&lock);
    for (int i = 0; i < 250000; i++)
    {
        sum += arr[i];
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

void* thread_handle2(void* arg)
{
    pthread_mutex_lock(&lock);
    for (int i = 250000; i < 500000; i++)
    {
        sum += arr[i];
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

void* thread_handle3(void* arg)
{
    pthread_mutex_lock(&lock);
    for (int i = 500000; i < 750000; i++)
    {
        sum += arr[i];
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

void* thread_handle4(void* arg)
{
    pthread_mutex_lock(&lock);
    for (int i = 750000; i < 1000000; i++)
    {
        sum += arr[i];
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

void create_arr()
{
    for (int i = 0; i < 1000000; i++)
    {
        arr[i] = 1;
    }
}