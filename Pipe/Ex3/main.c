#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MSGSIZE 30

char *msg = "Hello World";

int main(int argc, char *argv[])
{
    char buf[MSGSIZE];
    memset(buf, 0, MSGSIZE);

    int p[2];
    if (pipe(p) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int cpid;
    cpid = fork();
    if (cpid >= 0)
    {
        if (cpid == 0) // child
        {
            read(p[0], buf, MSGSIZE);
            int length = strlen(buf);
            printf("Data: %s\nlength: %d\n", buf, length);
        }
        else // parent
        {
            write(p[1], msg, MSGSIZE);
            printf("Parent write data to child\n....\n");
        }
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);    
    }

    return 0;
}