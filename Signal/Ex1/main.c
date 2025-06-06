#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

// #define EXIT_SUCCESS  0
// #define EXIT_FAILURE  /* nonzero */

int count = 0;

void signal_handle(int flag);

int main(int argc, char *argv[])
{
    if (signal(SIGINT, signal_handle) == SIG_ERR) {
		fprintf(stderr, "Cannot handle SIGINT\n");
		exit(EXIT_FAILURE);
	}

    while(1)
    {
        if(count == 3) 
            break;
    }

    return 0;
}

void signal_handle(int flag)
{
    if(flag == SIGINT)
    {
        count++;
        printf("SIGINT received\n");
        // exit(EXIT_SUCCESS);
    }
}

//if ignore the SIGINT signal the program will end immediately