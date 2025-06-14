#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MSGSIZE 30

char *msg = "Hello child 1";

int main(int argc, char *argv[])
{
    char buf[MSGSIZE];
    memset(buf, 0, MSGSIZE);
    
    int p[2][2]; // pipe[0] for child 1, pipe[1] for child 2 

    if ((pipe(p[0]) == -1) || (pipe(p[1]) == -1))
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int cpid1, cpid2;

    cpid1 = fork();
    if (cpid1 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid1 == 0)
    {
        read(p[0][0], buf, MSGSIZE);
        printf("Message chilld 1 receive from parent: %s\n", buf);
        msg = "Hello child 2";
        write(p[1][1], msg, MSGSIZE);
    }
    else if (cpid1 > 0)
    {
        write(p[0][1], msg, MSGSIZE);
        printf("Message from parent to child 1: %s\n", msg);
    }

    cpid2 = fork();
    if (cpid2 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid1 == 0)
    {
        read(p[1][0], buf, MSGSIZE);
        printf("Message from child 1 to child 2: %s\n", buf);
    }

    return 0;
}