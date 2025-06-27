#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>      
#include <sys/stat.h>
#include <mqueue.h>  
#include <errno.h>  

char *message = "Hello Child";
  
int main(int argc, char *argv[])  
{  
    struct mq_attr attrp;
    
    printf("Create mqueu\n");  
    mqd_t mqid = mq_open("/mqueue", O_RDWR | O_CREAT | O_NONBLOCK, 0666, NULL);  
    if (mqid == -1) {  
        printf("mq_open() error %d: %s\n", errno, strerror(errno));  
        return -2;  
    }

    if (mq_getattr(mqid, &attrp) != 0) {  
        printf("mq_open() error %d: %s\n", errno, strerror(errno));  
        return -3;  
    }

    char *revbuf = malloc(attrp.mq_msgsize);

    pid_t cpid = fork();
    if (cpid >= 0)
    {
        if (cpid > 0) 
        {
            if (mq_send(mqid, message, strlen(message) + 1, 0) == -1)
            {
                perror("mq_send");
                exit(EXIT_FAILURE);
            }
            printf("Parent send message to child, message: %s\n", message);
        }
        else 
        {
            memset(revbuf, 0, attrp.mq_msgsize);
            if (mq_receive(mqid, revbuf, attrp.mq_msgsize, 0) == -1)
            {
                perror("mq_receive");
                exit(EXIT_FAILURE);
            }   
            printf("Child receive message from parent succesfully, message: %s\n", revbuf);
        }
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    free(revbuf);
    mq_unlink("/mqueue");

    return 0;  
}