#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

// #define EXIT_SUCCESS  0
// #define EXIT_FAILURE  /* nonzero */
#define SIGALRM 14

int count = 0;

void signal_handle(int sig);

int main(int argc, char *argv[])
{
    if (signal(SIGALRM, signal_handle) == SIG_ERR) {
		fprintf(stderr, "Cannot handle SIGINT\n");
		exit(EXIT_FAILURE);
	}

    while(1)
    {
        alarm(1);
        sleep(1); // Wait for sending signal SIGALRM
        if(count == 10)
            break;
    }

    printf("The program is terminated\n");

    exit(0);
}

void signal_handle(int sig)
{
    if(sig == SIGALRM)
    {
        count++;
        printf("Timer: %d seconds\n", count);
    }
}