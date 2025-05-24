#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/sysmacros.h>
#include <string.h>

int main()
{
    char *Filename = "text.txt";
    int fd = open(Filename, O_CREAT | O_RDWR, 0766);

    if(fd < 0)
    {
        printf("File creation failed");
        return 1;
    }

    int size = write(fd, "AAAAAwefwfwgfwersgwfqefwefgwrfgwAfefAA", strlen("AAAAAwefwfwgfwersgwfqefwefgwrfgwAfefAA"));
    if(size > 0)
    {
        printf("%d bytes are written!!!\n", size);
    }
    close(fd);

    struct stat buf;
    stat(Filename, &buf);

    printf("File name: %s\n", Filename);
    printf("File type: ");
    switch (buf.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
    }
    printf("Time of last data modification: %s", ctime(&buf.st_mtime));
    printf("File size: %jd bytes\n", buf.st_size);

    return 0;
}
