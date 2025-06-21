#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if ((argc != 2) | (strlen(argv[1]) > 1))
    {
        printf("Wrong arguments!\n");
        exit(1);
    }

    pid_t p = fork();
    if (p >= 0)
    {
        if (p > 0) 
        {
            printf("\nCreating process %d is parent of %d\n", getpid(), p);
        }
        else 
        {
            if (argv[1][0] == '1')
            {
                execlp("ls", "ls", "-l", "/", NULL);
                //printf("Hello\n");
            }
            else if (argv[1][0] == '2')
            {
                execlp("date", "date", NULL);
                //printf("Hello\n");
            }
        }
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}