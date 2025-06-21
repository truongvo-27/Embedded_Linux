#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BUFF_SIZE 1024
#define SV_SOCK_PATH "./mySocket"

void chat_func(int client_fd);

int main(int argc, char *argv[])
{
    int client_socket;
    struct sockaddr_un server_addr;

    client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SV_SOCK_PATH, sizeof(server_addr.sun_path) - 1);

    if (connect(client_socket, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_un)) == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    chat_func(client_socket);
    return 0;
}

void chat_func(int client_fd)
{       
    int numb_read, numb_write;
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];
	
    while (1)
    {        
        // clear all data in buffer
        memset(sendbuff, '0', BUFF_SIZE);
        memset(recvbuff, '0', BUFF_SIZE);

        /* Type message from keyboard */
        printf("Please type the message: ");
        fgets(sendbuff, BUFF_SIZE, stdin);

        /* Write data to server */
        numb_write = write(client_fd, sendbuff, sizeof(sendbuff));
        if (numb_write == -1)
        {
            perror("write failed");
            exit(EXIT_FAILURE);
        }

        // Type "exit" to end chat
        if (strncmp("exit", recvbuff, 4) == 0) 
        {
            system("clear"); // clear all content on terminal
            break;
        }

        /* Read function will be locked until be read data in buffer*/
        numb_read = read(client_fd, recvbuff, BUFF_SIZE);
        if(numb_read == -1)
        {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
        
        if (strncmp("exit", recvbuff, 4) == 0) 
        {
            system("clear"); // clear all content on terminal
            break;
        }
        printf("\nMessage from Server: %s\n", recvbuff);

        sleep(1);
    }

    close(client_fd);
}