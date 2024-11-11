#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 2020

int main(){
	int sock_fd;
	struct sockaddr_in server_addr;
	char buffer[1024];
	
	sock_fd=socket(AF_INET,SOCK_DGRAM,0);
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(PORT);
	
	int len,n;
	while(1){
		printf("Client:");
		scanf("%s",&buffer);
		sendto(sock_fd, (char *)buffer, strlen(buffer), MSG_CONFIRM, (struct sockaddr *)&server_addr, sizeof(server_addr));
		
		if (strcmp(buffer, "exit") == 0) break;
		
		n=recvfrom(sock_fd, (char *)buffer, 1024,MSG_WAITALL, (struct sockaddr *)&server_addr, &len);
		buffer[n]='\0';
		printf("SERVER: %s\n", buffer);
		if (strcmp(buffer, "exit") == 0) break;
	}
	close(sock_fd);
	return 0;
}
