#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
	char buf[100];
	int k,sock_desc;
	struct sockaddr_in client;
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=INADDR_ANY;
	client.sin_port=3004;
	k=connect(sock_desc,(struct sockaddr*)&client,sizeof(client));
	printf(" enter the msg : ");
	fgets(buf,100,stdin);
	send(sock_desc,buf,100,0);
	close(sock_desc);
}
