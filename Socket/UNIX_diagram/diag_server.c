#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SV_SOCK_PATH "./mySocket"
#define BUFF_SIZE 1024

void func_chat(int socket_fd);

int main(int argc, char const* argv[])
{
    int server_socket;
    struct sockaddr_un server_addr;

    // Create socket
    server_socket = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (server_socket == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Config socket server
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SV_SOCK_PATH, sizeof(server_addr.sun_path) - 1);

    // Bind Socket
    if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_un)) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    printf("Start the conversation\n");
    func_chat(server_socket);

    return 0;
}

void func_chat(int socket_fd)
{
    int numb_read, numb_write;
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];

    struct sockaddr_un cliaddr;
    while(1)
    {
        memset(sendbuff, 0, BUFF_SIZE);
        memset(recvbuff, 0, BUFF_SIZE);

        int len = sizeof(cliaddr);
        // Receive message
        if (recvfrom(socket_fd, recvbuff, BUFF_SIZE, 0, (struct sockaddr*)&cliaddr, &len) == -1)
        {
            perror("recvfrom");
            exit(EXIT_FAILURE);    
        }
        printf("Message from client: %s", recvbuff);
        // Client type "exit" to end the conversation
        if (strncmp("exit", recvbuff, 4) == 0) 
        {
            system("clear"); // clear all content on terminal
            break;
        }
        
        // Send message
        printf("Type the message: ");
        fgets(sendbuff, BUFF_SIZE, stdin);
        if (sendto(socket_fd, sendbuff, BUFF_SIZE, 0, (struct sockaddr*)&cliaddr, len) == -1)
        {
            perror("sendto");
            exit(EXIT_FAILURE);
        }
        // Server type "exit" to end the conversation
        if (strncmp("exit", sendbuff, 4) == 0) 
        {
            system("clear");
            break;
        }
    }
}