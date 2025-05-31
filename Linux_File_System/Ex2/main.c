#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd;
    
    if(argc != 5)
    {
        printf("Wrong Arguments!!!\n");
        return 0;
    }

    fd = open(argv[1], O_CREAT | O_RDWR | O_APPEND, 0766);

    if(fd < 0)
    {
        printf("File creation failed!\n");
    }

    if(argv[3][0] == 'r')
    {
        int num = atoi(argv[2]);
        char buf[100];
        int sz = 0;
        sz = read(fd, buf, num - 1);
        printf("%d bytes are read: %s", sz, buf);
    }

    else if(argv[3][0] == 'w')
    {
        int sz;
        sz = write(fd, argv[4], strlen(argv[4]));
        printf("%d bytes are written!!\n", sz);
    }

    close(fd);

    return 0;
}