#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>

#define PORT 2020

int main(){
	int sock_fd, clength;
	struct sockaddr_in server_addr, client_addr;
	char buffer[1024]={0};
	
	sock_fd=socket(AF_INET,SOCK_DGRAM, 0);
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(PORT);
	
	bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	
	printf("UDP server is listening on port %d...\n",PORT);
	
	clength=sizeof(client_addr);
	
	while(1){
		memset(buffer, 0, 1024);
		
		int len=recvfrom(sock_fd, (char *)buffer, 1024, MSG_WAITALL, (struct sockaddr *)&client_addr, &clength);
		
		buffer[len]='\0';
		printf("CLIENT: %s\n", buffer);
		
		if(strcmp(buffer,"exit")==0) break;
		
		printf("SERVER:");
		scanf("%s",&buffer);
		
		sendto(sock_fd, (char *)buffer, strlen(buffer), MSG_CONFIRM, (struct sockaddr *)&client_addr, clength);
		
		if(strcmp(buffer,"exit")==0) break;
	}
	close(sock_fd);
	return 0;
}
