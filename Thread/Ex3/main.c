#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t pthread_id;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int data[10] = {0};
int counter = 0;

static void *thread_handle(void *args);

int main(int argc, char *argv[])
{
    //Consumer
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n Mutex init has failed\n");
        exit(EXIT_FAILURE);
    }    

    if (pthread_create(&pthread_id, NULL, &thread_handle, NULL))
    {
        printf("Thread can't be created\n");
        exit(EXIT_FAILURE);
    }

    pthread_mutex_lock(&lock);
    while (1)
    {
        pthread_cond_wait(&cond, &lock);
        if (counter == 10)
        {
            break;
        }     
    }
    pthread_mutex_unlock(&lock);

    pthread_join(pthread_id,NULL); 

    printf("All of numbers: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", data[i]);
    }
    printf("\n");

    // pthread_join(pthread_id,NULL);

    exit(0);
}

static void *thread_handle(void *args)
{
    // Producer
    pthread_mutex_lock(&lock);

    while (counter < 10)
    {
        // Set the upper bound for random numbers
        int upper_bound = 10;
        // Set the lower bound for random numbers
        int lower_bound = 1;
        // Generate a random number
        int value = rand() % (upper_bound - lower_bound + 1) + lower_bound;

        data[counter] = value;
        printf("Random number %d is %d\n", counter + 1, value);
        sleep(1);
        counter++;     
    }

    pthread_cond_signal(&cond);
    
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL); // exit or return;
}
