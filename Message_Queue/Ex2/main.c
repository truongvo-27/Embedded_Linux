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
    struct mq_attr attrp1, attrp2;
    
    printf("Create mqueu1\n");  
    mqd_t mqid1 = mq_open("/mqueue1", O_RDWR | O_CREAT | O_NONBLOCK, 0666, NULL);  
    if (mqid1 == -1) {  
        printf("mq_open() error %d: %s\n", errno, strerror(errno));  
        return -2;  
    }

    if (mq_getattr(mqid1, &attrp1) != 0) {  
        printf("mq_open() error %d: %s\n", errno, strerror(errno));  
        return -3;  
    }

    printf("Create mqueu2\n");  
    mqd_t mqid2 = mq_open("/mqueue2", O_RDWR | O_CREAT | O_NONBLOCK, 0666, NULL);  
    if (mqid2 == -1) {  
        printf("mq_open() error %d: %s\n", errno, strerror(errno));  
        return -2;  
    }

    if (mq_getattr(mqid2, &attrp2) != 0) {  
        printf("mq_open() error %d: %s\n", errno, strerror(errno));  
        return -3;  
    }

    char *revbuf1 = malloc(attrp1.mq_msgsize);
    char *revbuf2 = malloc(attrp2.mq_msgsize);

    pid_t cpid = fork();
    if (cpid >= 0)
    {
        if (cpid > 0) 
        {
            if (mq_send(mqid1, message, strlen(message) + 1, 0) == -1)
            {
                perror("mq_send");
                exit(EXIT_FAILURE);
            }
            printf("Parent send message to child, message: %s\n", message);

            memset(revbuf2, 0, attrp2.mq_msgsize);

            sleep(2);
            if (mq_receive(mqid2, revbuf2, attrp1.mq_msgsize, 0) == -1)
            {
                perror("mq_receive");
                exit(EXIT_FAILURE);
            } 
            printf("Parent receive the length of message successfully, length: %s\n", revbuf2);
        }
        else 
        {
            sleep(1);
            memset(revbuf1, 0, attrp1.mq_msgsize);
            if (mq_receive(mqid1, revbuf1, attrp1.mq_msgsize, 0) == -1)
            {
                perror("mq_receive");
                exit(EXIT_FAILURE); 
            }   
            printf("Child receive message from parent succesfully, message: %s\n", revbuf1);

            sprintf(revbuf2, "%ld", strlen(revbuf1));
            if (mq_send(mqid2, revbuf2, strlen(revbuf1) + 1, 0) == -1)
            {
                perror("mq_send");
                exit(EXIT_FAILURE);
            }
            printf("Child send the length of message to parent, length: %s\n", revbuf2);

        }
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    free(revbuf1);
    free(revbuf2);
    mq_unlink("/mqueue1");
    mq_unlink("/mqueue2");

    return 0;  
}