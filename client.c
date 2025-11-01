#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Server info
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }
    printf("Connected to server.\n");

    // Infinite message exchange
    while (1) {
        printf("Client: ");
        bzero(buffer, sizeof(buffer));
        fgets(buffer, sizeof(buffer), stdin);
        write(client_socket, buffer, strlen(buffer));

        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Client exiting...\n");
            break;
        }

        bzero(buffer, sizeof(buffer));
        read(client_socket, buffer, sizeof(buffer));
        printf("Server: %s\n", buffer);
    }

    close(client_socket);
    return 0;
}
