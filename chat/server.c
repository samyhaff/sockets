#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define PORT 9002
#define MAX_CONNECTIONS 5
#define MAX_MESSAGE_LENGTH 256

int main(int argc, char *argv[])
{
    char server_message[MAX_MESSAGE_LENGTH] = "Welcome to the chat room";
    char message[MAX_MESSAGE_LENGTH];

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        printf("There was an error creating the socket\n");
        return -1;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1)
    {
        printf("There was an error binding the socket\n");
        return -1;
    }

    listen(server_socket, MAX_CONNECTIONS);
    int client_socket;
    /* send(client_socket, server_message, MAX_MESSAGE_LENGTH, 0); */

    while (client_socket = accept(server_socket, NULL, NULL))
    {
        int pid;
        // child process
        if ((pid = fork()) == 0)
        {
            while (recv(client_socket, message, MAX_MESSAGE_LENGTH, 0) > 0)
                printf("user: %s", message);
        }
    }

    close(server_socket);

    return 0;
}
