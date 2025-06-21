#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MSGSIZE 20

char *msg = "Hello children\n";

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

    pid_t cpid = fork();
    if (cpid >= 0)
    {
        if (cpid > 0) 
        {
            printf("Parent is writing to child\n");
            sleep(2);
            write(p[1], msg, MSGSIZE);
        }
        else
        {
            read(p[0], buf, MSGSIZE);
            printf("Read succesfully\nData: %s", buf);
        }
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE); 
    }

    return 0;
}