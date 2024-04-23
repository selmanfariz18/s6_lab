#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 2020
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_size;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Fill server information
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("UDP Server listening on port %d...\n", PORT);

    addr_size = sizeof(clientAddr);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        // Receive message from client
        int len = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, 
                    MSG_WAITALL, (struct sockaddr *) &clientAddr, 
                    &addr_size);
        buffer[len] = '\0';
        printf("Client : %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) break;

        printf("Server : ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
        // Send response to client
        sendto(sockfd, (const char *)buffer, strlen(buffer), 
            MSG_CONFIRM, (const struct sockaddr *) &clientAddr,
            addr_size);

        if (strcmp(buffer, "exit") == 0) break;
    }

    close(sockfd);
    return 0;
}

