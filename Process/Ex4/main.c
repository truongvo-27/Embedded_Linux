#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    pid_t p = fork();
    int status, w;

    if (p >= 0)
    {
        if (p > 0) 
        {
            printf("I'm Parents process with PID = %d\n", getpid());
            w = wait(&status);

            if (w < 0)
            {
                printf("wait() unsuccesfully\n");
                exit(1);
            }

            if (WIFEXITED(status)) 
            {
                printf("Normally termination, status = %d\n", WEXITSTATUS(status));
            } 
        }
        else
        {
            printf("I'm Child process with exiting status 100 and PID = %d\n", getpid());
            exit(100);
        }
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}
