#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define SIGUSR1 10

int count = 0; //count variable is used for child process

void signal_handle(int sig);

int main(int argc, char *argv[])
{
    pid_t p = fork();
    int status;

    if (p >= 0)
    {
        if (p > 0)
        {
            sleep(1); //sleep to wait child process register the signal

            for (int i = 0; i < 5; i++)
            {
                kill(p, SIGUSR1);
                sleep(2);
            }

            waitpid(p, &status, 0);
        }
        else
        {
            if (signal(SIGUSR1, signal_handle) == SIG_ERR)
            {
                fprintf(stderr, "Cannot handle SIGINT\n");
                exit(EXIT_FAILURE);
	        }
            
            while(count < 5);
            exit(100);
        }
    }

    else
    {
        printf("fork fail\n");
        exit(EXIT_FAILURE); //exit(1) if failure exit(0) if success
    }

    if (WIFEXITED(status))
    {
        printf("Child %d terminated with status: %d\n", p, WEXITSTATUS(status));
    }

    printf("The program is terminated\n");

    exit(0);
}

void signal_handle(int sig)
{
    if (sig == SIGUSR1)
    {
        printf("Received signal from parent\n"); 
        count++;   
    }
}
