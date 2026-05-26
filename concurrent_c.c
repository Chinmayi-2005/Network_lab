#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define MAXLINE 1000
#define PORT 5000

int main()
{
	int sockdesc;
	struct sockaddr_in client;
	socklen_t len=sizeof(client);
	sockdesc=socket(AF_INET,SOCK_DGRAM,0);
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	client.sin_port=htons(PORT);
	printf("enter the cmd : ");
	
	char str[100],buf[100];
	scanf("%s",str);
	sendto(sockdesc,str,strlen(str),0,(struct sockaddr*)&client,sizeof(client));
	int n=recvfrom(sockdesc,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);
	buf[n]='\0';
	printf("%s",buf);
	close(sockdesc);
}
