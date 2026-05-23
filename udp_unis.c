#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

int main()
{
	int k,sock_desc;
	char buf[100];
	struct sockaddr_in server,client;
	sock_desc=socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=3004;
	bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
	socklen_t len=sizeof(client);
	recvfrom(sock_desc,buf,100,0,(struct sockaddr*)&client,&len);
	printf("msg from client : %s",buf);
	close(sock_desc);
}
