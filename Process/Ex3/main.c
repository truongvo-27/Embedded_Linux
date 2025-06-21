#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define SIGUSR1 10

void hanlder_signal(int signalNum);

int main(int argc, char **argv)
{
    pid_t p = fork();
    if (p >= 0)
    {
        if(p > 0) 
        {
            printf("Sending to child....\n");
            sleep(1); //sleep to wait child process register the signal
            kill(p, SIGUSR1);
            while(1);
        }
        else 
        {
            printf("Receiving the signal from parents....\n");
            signal(SIGUSR1, hanlder_signal);
            pause();
        }
    }

    else
    {
        printf("fork fail\n");
        exit(1); 
    }

    return 0;
}

void hanlder_signal(int signalNum)
{
    if (signalNum == SIGUSR1)
    {
        for (int i = 1; i < 6; i++)
        {
            printf("%d\n", i);
            sleep(1);
        }
        printf("Received successfully from parents after 5 seconds!\n");
    }
}