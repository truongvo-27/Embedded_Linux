#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>

#define BUFF_SIZE 1024

void func_chat(int socket_fd);

int main(int argc, char const* argv[])
{   
    int port_no = 0;
    if (argc < 3) 
    {
        printf("command: ./client <server address> <port number>\n");
        exit(EXIT_FAILURE);
    }
    else
        port_no = atoi(argv[2]);


    int client_fd, n;
    struct sockaddr_in servaddr;
    
    // clear servaddr
    bzero(&servaddr, sizeof(servaddr));
    
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    servaddr.sin_port = htons(port_no);
    servaddr.sin_family = AF_INET;
    
    // create datagram socket
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    
    // connect to server
    if(connect(client_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        return -1;
    }

    func_chat(client_fd);
    
    return 0;
}

void func_chat(int socket_fd)
{
    int numb_read, numb_write;
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];

    while(1)
    {
        memset(sendbuff, '0', BUFF_SIZE);
        memset(recvbuff, '0', BUFF_SIZE);

        // Send message
        printf("Type the message: ");
        fgets(sendbuff, BUFF_SIZE, stdin);
        sendto(socket_fd, sendbuff, BUFF_SIZE, 0, (struct sockaddr*)NULL, 0);
        // Server type "exit" to end the conversation
        if (strncmp("exit", sendbuff, 4) == 0) 
        {
            system("clear");
            break;
        }

        // Receive message
        int n = recvfrom(socket_fd, recvbuff, BUFF_SIZE, 0, (struct sockaddr*)NULL, 0);
        printf("Message from server: %s", recvbuff);
        // Client type "exit" to end the conversation
        if (strncmp("exit", recvbuff, 4) == 0) 
        {
            system("clear"); // clear all content on terminal
            break;
        }
    }

    // close the descriptor
    close(socket_fd);
}