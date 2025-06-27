#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>      
#include <sys/stat.h>
#include <mqueue.h>  
#include <errno.h>  
#include <ctype.h>
#include <sys/wait.h>

char message[20];
  
char *strupr(char *str) {
    char *p = str;
    while (*p) {
        *p = toupper((unsigned char)*p);
        p++;
    }
    return str;
}

int main(int argc, char *argv[])  
{  
    strcpy(message, "Hello Child1");
    struct mq_attr attrp;
    int status;
    
    printf("Create mqueu\n");  
    mqd_t mqid = mq_open("/mqueue", O_RDWR | O_CREAT, 0666, NULL);  
    if (mqid == -1) {  
        printf("mq_open() error %d: %s\n", errno, strerror(errno));  
        return -2;  
    }

    if (mq_getattr(mqid, &attrp) != 0) {  
        printf("mq_open() error %d: %s\n", errno, strerror(errno));  
        return -3;  
    }

    char *revbuf = malloc(attrp.mq_msgsize);

    pid_t cpid1 = fork();
    if (cpid1 >= 0)
    {
        if (cpid1 > 0) 
        {
            if (mq_send(mqid, message, strlen(message) + 1, 0) == -1)
            {
                perror("mq_send");
                exit(EXIT_FAILURE);
            }
            printf("Parent send message to child1, message: %s\n", message);
            wait(&status);
        }
        else 
        {
            memset(revbuf, 0, attrp.mq_msgsize);
            if (mq_receive(mqid, revbuf, attrp.mq_msgsize, 0) == -1)
            {
                perror("mq_receive");
                exit(EXIT_FAILURE);
            }   
            printf("Child1 receive message from parent succesfully, message: %s\n", revbuf);

            strcpy(message, strupr(revbuf));
            printf("Child1 change message from parent succesfully, message: %s\n", message);

            if (mq_send(mqid, message, strlen(message) + 1, 0) == -1)
            {
                perror("mq_send");
                exit(EXIT_FAILURE);
            }
            printf("Child1 send message to child2, message: %s\n", message);
            exit(100);
        }
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    pid_t cpid2 = fork();
    if (cpid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(cpid2 == 0) {
        sleep(1);
        if (mq_receive(mqid, revbuf, attrp.mq_msgsize, 0) == -1)
        {
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }   
        printf("Child2 receive message from child1 succesfully, message: %s\n", revbuf);
        exit(101);
    }

    if(cpid2 > 0)
    {
        wait(&status);
    }
    
    free(revbuf);
    mq_close(mqid);
    mq_unlink("/mqueue");

    return 0;  
}