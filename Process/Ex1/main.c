#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    pid_t p = fork();
    if(p >= 0)
    {
        if(p > 0) //parent process
        {
            printf("\nCreating process %d is parent of %d\n", getpid(), p);
            //while(1);
        }
        else //p > 0: child process
        {
            printf("\nCreating process %d\n", getpid());
        }
    }
    else
    {
        printf("fork fail\n");
        exit(1); //exit(1) if failure exit(0) if success
    }


    return 0;
}