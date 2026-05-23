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
	struct sockaddr_in client;
	sock_desc=socket(AF_INET,SOCK_DGRAM,0);
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=INADDR_ANY;
	client.sin_port=3004;
	//bind(sockdesc,(struct sockaddr*)&server,sizeof(server));
	
	printf("enter the msg : ");
	fgets(buf,100,stdin);
	sendto(sock_desc,buf,sizeof(buf),0,(struct sockaddr*)&client,sizeof(client));
	//printf("msg form client : %s",buf);
	close(sock_desc);
}
