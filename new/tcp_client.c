#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 2020

int main(){
	int client_fd;
	struct sockaddr_in server_addr;
	char buffer[1024]={0};
	
	client_fd=socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(PORT);
	
	connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	
	while(1){
		printf("CLIENT:");
		fgets(buffer,1024,stdin);
		send(client_fd, buffer, sizeof(buffer), 0);
		if(strcmp(buffer,"exit")==0) break;
		memset(buffer, 0,1024);
		read(client_fd,buffer,1024);
		printf("SERVER: %s\n",buffer);
		if(strcmp(buffer,"exit")==0) break;
	}
	close(client_fd);
	return 0;
}
	
