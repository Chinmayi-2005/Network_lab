#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

int main()
{
	int k,sock_desc,temp_sock;
	char buf[100];
	struct sockaddr_in server,client;
	socklen_t len;
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=3004;
	k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
	k=listen(sock_desc,1);
	len=sizeof(client);
	temp_sock=accept(sock_desc,(struct sockaddr*)&client,&len);
	recv(temp_sock,buf,100,0);
	int n=(int)buf-'0';
	
	int m=n*n;
	printf("square of %d is %d",n,sm);
	for(i=1;i<=n;i++)
	{
		
	}
	close(sock_desc);
	
	
}
