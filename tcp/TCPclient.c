#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9002

int main(int argc, char *argv[])
{
    int network_soket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(network_soket, (struct sockaddr *) &server_address, sizeof(server_address));
    if (connection_status == -1)
        printf("There was an error making a connection to the remote socket");

    char server_response[256];
    recv(network_soket, &server_response, sizeof(server_response), 0);
    printf("The server sent the data %s", server_response);

    close(network_soket);

    return 0;
}
