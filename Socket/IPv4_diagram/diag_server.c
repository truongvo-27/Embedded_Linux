#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFF_SIZE 1024

void func_chat(int socket_fd);

int main(int argc, char const* argv[])
{   
    int port_no = 0;
    if (argc < 2) 
    {
        printf("No port provided\ncommand: ./server <port number>\n");
        exit(EXIT_FAILURE);
    }
    else
        port_no = atoi(argv[1]);

    int server_fd, len;
    struct sockaddr_in servaddr;

    // Clear all data of struct
    bzero(&servaddr, sizeof(servaddr));

    // Create a UDP Socket
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);        
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port_no);
    servaddr.sin_family = AF_INET; 
 
    // bind server address to socket descriptor
    len = sizeof(servaddr);
    if(bind(server_fd, (struct sockaddr*)&servaddr, len) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
     
    printf("Start the conversation\n");
    func_chat(server_fd);
    
    return 0;
}

void func_chat(int socket_fd)
{
    int numb_read, numb_write;
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];

    struct sockaddr_in cliaddr;
    while(1)
    {
        memset(sendbuff, '0', BUFF_SIZE);
        memset(recvbuff, '0', BUFF_SIZE);

        int len = sizeof(cliaddr);
        // Receive message
        int n = recvfrom(socket_fd, recvbuff, BUFF_SIZE, 0, (struct sockaddr*)&cliaddr, &len);
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
        sendto(socket_fd, sendbuff, BUFF_SIZE, 0, (struct sockaddr*)&cliaddr, len);
        // Server type "exit" to end the conversation
        if (strncmp("exit", sendbuff, 4) == 0) 
        {
            system("clear");
            break;
        }
    }
}