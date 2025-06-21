#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFF_SIZE 1024

void chat_func(int server_fd);

int main(int argc, char const* argv[])
{
    int port_no = 0;
    if (argc < 3) 
    {
        printf("command: ./client <server address> <port number>\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        port_no = atoi(argv[2]);
    }

    int status, valread, client_fd;
    struct sockaddr_in serv_addr;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) 
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (status < 0) 
    {
        printf("\nConnection Failed \n");
        return -1;
    }
  
    chat_func(client_fd);

    // closing the connected socket
    close(client_fd);

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

        /* Nhập nội dung tin nhắn từ bàn phím */
        printf("Please type the message: ");
        fgets(sendbuff, BUFF_SIZE, stdin);

        /* Ghi dữ liệu tới server thông qua hàm write */
        numb_write = write(client_fd, sendbuff, sizeof(sendbuff));
        if (numb_write == -1)
        {
            perror("write failed");
            exit(EXIT_FAILURE);
        }

        // Nhập "exit" để thoát đoạn chat
        if (strncmp("exit", recvbuff, 4) == 0) 
        {
            system("clear"); // clear all content on terminal
            break;
        }

        /* Đọc dữ liệu từ socket */
        /* Hàm read sẽ block cho đến khi đọc được dữ liệu */
        numb_read = read(client_fd, recvbuff, BUFF_SIZE);
        if (numb_read == -1)
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