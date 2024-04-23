#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 2020

int main() {
    int server_fd, client_fd, addr_len;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024] = {0};
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    // Bind the socket to the server address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for client connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    addr_len = sizeof(client_addr);
    if ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&addr_len)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    // Communication - receive message and send response
    while(1) {
        memset(buffer, 0, 1024);
        int valread = read(client_fd, buffer, 1024);
        if (valread == 0) {
            printf("Client disconnected.\n");
            break;
        }
        printf("Client: %s\n", buffer);
        printf("Server: ");
        fgets(buffer, 1024, stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
        send(client_fd, buffer, strlen(buffer), 0);
        if (strcmp(buffer, "exit") == 0) break;
    }

    close(client_fd);
    close(server_fd);
    return 0;
}

