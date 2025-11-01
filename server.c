#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_len = sizeof(client_addr);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Bind socket to address
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // Listen for connection
    listen(server_fd, 1);
    printf("Server listening on port 8080...\n");

    // Accept client connection
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
    printf("Client connected!\n");

    // Communication
    recv(client_fd, buffer, sizeof(buffer), 0);
    printf("Received from client: %s\n", buffer);

    char reply[] = "Hello from server!";
    send(client_fd, reply, strlen(reply), 0);
    printf("Reply sent to client.\n");

    close(client_fd);
    close(server_fd);
    return 0;
}
