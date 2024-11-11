#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 2020
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    
    // Server information
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    
    int n, len;

    while(1) {
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character

        // Send message to server
        sendto(sockfd, (const char *)buffer, strlen(buffer),
            MSG_CONFIRM, (const struct sockaddr *) &serverAddr, 
            sizeof(serverAddr));

        if (strcmp(buffer, "exit") == 0) break;

        // Receive response from server
        n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE,
                     MSG_WAITALL, (struct sockaddr *) &serverAddr,
                     &len);
        buffer[n] = '\0';
        printf("Server : %s\n", buffer);
        if (strcmp(buffer, "exit") == 0) break;
    }

    close(sockfd);
    return 0;
}

