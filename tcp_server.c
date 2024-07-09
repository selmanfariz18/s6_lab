#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define PORT 2020

int main(){
	int server_fd,client_fd,clength;
	struct sockaddr_in server_addr, client_addr;
	char buffer[1024]={0};
	
	server_fd=socket(AF_INET, SOCK_STREAM, 0);
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(PORT);
	
	bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	printf("\nBinded....\n");
	
	listen(server_fd,5);
	
	printf("Server is listening on PORT %d\n",PORT);
	
	clength=sizeof(client_addr);
	client_fd=accept(server_fd, (struct sockaddr *)&client_addr, &clength);
	
	printf("\nClient connected\n");
	
	while(1){
		memset(buffer,0,1024);
		int valread = read(client_fd, buffer,1024);
		if (valread==0){
			printf("Client disconnected");
			break;
		}
		printf("CLIENT: %s\n",buffer);
		printf("SERVER:");
		fgets(buffer, 1024, stdin);
		send(client_fd, buffer, strlen(buffer),0);
		if (strcmp(buffer,"exit")==0) break;
	}
	close(client_fd);
	close(server_fd);
	return 0;
}
