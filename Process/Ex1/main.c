#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    pid_t p = fork();
    if (p >= 0)
    {
        if (p > 0) 
        {
            printf("\nCreating process %d is parent of %d\n", getpid(), p);
            //while(1);
        }
        else 
        {
            printf("\nCreating process %d\n", getpid());
        }
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}