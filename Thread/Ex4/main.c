#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_t thread_id1, thread_id2;

int data[100] = {0};
// int data_odd[100] = {0};
// int data_even[100] = {0};

int sum_odd = 0, sum_even = 0;
// int counter_odd = 0, counter_even = 0;

static void *handle_countEven(void *args);
static void *handle_countOdd(void *args);
static void Create_Arr();

int main(int argc, char *argv[])
{
    Create_Arr();
    //Count odd
    if (pthread_create(&thread_id1, NULL, &handle_countEven, NULL))
    {
        printf("Thread 1 can't be created\n");
        exit(EXIT_FAILURE);
    }

    //Count even
    if (pthread_create(&thread_id2, NULL, &handle_countOdd, NULL))
    {
        printf("Thread 2 can't be created\n");
        exit(EXIT_FAILURE);
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    // List all even numbers
    // printf("All of %d even numbers: ", counter_even);
    // for (int i = 0; i < counter_even; i++)
    // {
    //     printf("%d ", data_even[i]);
    // }
    // printf("\n");

    // List all odd numbers
    // printf("All of %d odd numbers: ", counter_odd);
    // for (int i = 0; i < counter_odd; i++)
    // {
    //     printf("%d ", data_odd[i]);
    // }
    // printf("\n");

    printf("Sum of even numbers: %d\n", sum_even);
    printf("Sum of odd numbers: %d\n", sum_odd);

    exit(0);
}

static void *handle_countEven(void *args)
{
    int counter = 0;
    while (counter < 100)
    {
        if (data[counter] % 2 == 0)
        {
            sum_even += data[counter];

            // data_even[counter_even] = data[counter];
            // counter_even++;
        }
        counter++;
    }

    pthread_exit(NULL); // exit or return;
}

static void *handle_countOdd(void *args)
{
    int counter = 0;
    while (counter < 100)
    {
        if (data[counter] % 2 != 0)
        {
            sum_odd += data[counter];

            // data_odd[counter_odd] = data[counter];
            // counter_odd++;
        }
        counter++;
    }

    pthread_exit(NULL); // exit or return;              
}

static void Create_Arr()
{
    for (int i = 0; i < 100; i++)
    {
        int upper_bound = 100;
        // Set the lower bound for random numbers
        int lower_bound = 1;
        // Generate a random number
        int value = rand() % (upper_bound - lower_bound + 1) + lower_bound;
        data[i] = value;
    }
}