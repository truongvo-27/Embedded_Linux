#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SV_SOCK_PATH "./mySocket"
#define BUFF_SIZE 1024

void func_chat(int socket_fd, struct sockaddr_un *server_addr);

int main(int argc, char *argv[]) 
{
    int client_socket;
    struct sockaddr_un server_addr;

    // Create client socket
    client_socket = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Config server
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SV_SOCK_PATH, sizeof(server_addr.sun_path) - 1);

    // 
    int optval = 1;
    setsockopt(client_socket, SOL_SOCKET, SO_PASSCRED, &optval, sizeof(optval));

    func_chat(client_socket, &server_addr);

    close(client_socket);
    return 0;
}

void func_chat(int socket_fd, struct sockaddr_un *server_addr)
{
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];
    socklen_t len = sizeof(struct sockaddr_un);

    while (1) {
        // memset(sendbuff, 0, BUFF_SIZE);
        // memset(recvbuff, 0, BUFF_SIZE);

        // Gửi
        printf("Type the message: ");
        fgets(sendbuff, BUFF_SIZE, stdin);
        sendto(socket_fd, sendbuff, strlen(sendbuff), 0,
               (struct sockaddr *) server_addr, len);

        if (strncmp("exit", sendbuff, 4) == 0) {
            system("clear");
            break;
        }

        // Nhận
        recvfrom(socket_fd, recvbuff, BUFF_SIZE, 0, (struct sockaddr *) server_addr, &len);
        printf("Message from server: %s", recvbuff);

        if (strncmp("exit", recvbuff, 4) == 0) {
            system("clear");
            break;
        }
    }
}
