#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main()
{
    int fd; 

    fd = open("text.txt", O_CREAT | O_APPEND | O_WRONLY, 0766);

    if(fd == -1)
    {
        printf("File creation failed!");
    }

    write(fd, "TruongVo", strlen("TruongVo"));

    lseek(fd, 20, SEEK_SET);

    write(fd, "ZZZZZZZZZZZZ", strlen("ZZZZZZZZZZZZ"));

    close(fd);
    
    return 0;
}

//Co O_APPEND làm cho hàm write() luôn được ghi vào cuối file bất kể con trỏ đang ở đâu, bỏ qua mọi vị trí lseek() thiết lập