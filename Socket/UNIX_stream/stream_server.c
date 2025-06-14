#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SV_SOCK_PATH "./mySocket"
#define BACKLOG 50
#define BUFF_SIZE 1024

void chat_func(int new_socket_fd);

int main(int argc, char *argv[])
{
    int server_socket;
    int client_socket;
    struct sockaddr_un server_addr;

    // Create socket
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
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

    // Listen
    if (listen(server_socket, BACKLOG) == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        printf("Wating for client\n....\n");
        // Block until have the connection
        client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == -1)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        printf("Connect successfully\n");
        chat_func(client_socket);
    }
    close(server_socket);
    return 0;
}

void chat_func(int new_socket_fd)
{       
    int numb_read, numb_write;
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];
	
    while (1) {        
        // clear all data in buffer
        memset(sendbuff, '0', BUFF_SIZE);
        memset(recvbuff, '0', BUFF_SIZE);

        /* Đọc dữ liệu từ socket */
        /* Hàm read sẽ block cho đến khi đọc được dữ liệu */
        numb_read = read(new_socket_fd, recvbuff, BUFF_SIZE);
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
        printf("\nMessage from Client: %s\n", recvbuff);

        /* Nhập phản hồi từ bàn phím */
        printf("Please type the message: ");
        fgets(sendbuff, BUFF_SIZE, stdin);

        /* Ghi dữ liệu tới client thông qua hàm write */
        numb_write = write(new_socket_fd, sendbuff, sizeof(sendbuff));
        if (numb_write == -1)
        {
            perror("write failed");
            exit(EXIT_FAILURE);
        }
        
        if (strncmp("exit", sendbuff, 4) == 0) {
            system("clear");
            break;
        }

        sleep(1);
    }
    close(new_socket_fd);
}