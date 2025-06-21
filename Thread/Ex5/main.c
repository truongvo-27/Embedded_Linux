#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_READ 5
#define NUM_WRITE 2

void* writer_thread_handle(void *arg);
void* reader_thread_handle(void *arg);

int shared_resource = 0;

pthread_rwlock_t lock_rw = PTHREAD_RWLOCK_INITIALIZER;

int main(int argc, char *argv[])
{
    pthread_t readers_thr[NUM_READ];
    pthread_t writers_thr[NUM_WRITE];

    // Initialize the read-write lock
    pthread_rwlock_init(&lock_rw, NULL);

    //Creating status
    // Create reader thread
    for (int i = 0; i < NUM_READ; i++)
    {
        pthread_create(&readers_thr[i], NULL, &reader_thread_handle, NULL);
    }

    // Create writer thread
    for (int i = 0; i < NUM_WRITE; i++)
    {
        pthread_create(&writers_thr[i], NULL, &writer_thread_handle, NULL);
    }

    // Waiting status
    // Waiting reader thread finish
    for (int i = 0; i < NUM_READ; i++)
    {
        pthread_join(readers_thr[i], NULL);
    }

    //Waiting writer thread finish
    for (int i = 0; i < NUM_WRITE; i++)
    {
        pthread_join(writers_thr[i], NULL);
    }

    // Destroy read-write lock
    pthread_rwlock_destroy(&lock_rw);
    
    exit(0);
}

void* writer_thread_handle(void *arg)
{
    pthread_t thr_id = pthread_self();

    pthread_rwlock_wrlock(&lock_rw);

    shared_resource++;
    printf("Write shared resource from thread %lu, value = %d\n", (unsigned long)thr_id, shared_resource);

    pthread_rwlock_unlock(&lock_rw);

    return NULL;
}

void* reader_thread_handle(void *arg)
{
    pthread_t thr_id = pthread_self();

    pthread_rwlock_rdlock(&lock_rw);

    printf("Read shared resource from thread %lu, value = %d\n", (unsigned long)thr_id, shared_resource);

    pthread_rwlock_unlock(&lock_rw);

    return NULL;
}