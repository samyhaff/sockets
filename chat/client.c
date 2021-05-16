#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define PORT 9002
#define MAX_MESSAGE_LENGTH 256

int main(int argc, char *argv[])
{
    char server_response[MAX_MESSAGE_LENGTH];
    char message[MAX_MESSAGE_LENGTH];

    int network_soket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    if (connect(network_soket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1)
    {
        printf("There was an error making a connection to the remote socket\n");
        return -1;
    }

    /* recv(network_soket, server_response, MAX_MESSAGE_LENGTH, 0); */
    /* printf("%s\n", server_response); */

    while (1)
    {
        fgets(message, MAX_MESSAGE_LENGTH, stdin);
        send(network_soket, message, MAX_MESSAGE_LENGTH, 0);
    }

    close(network_soket);

    return 0;
}
