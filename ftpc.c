#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define max 1024
#define DATA_PORT 2031
#define CONTROL_PORT 2132

int main()
{
	int data_sock,control_sock,n,control_cli,data_cli;
	struct sockaddr_in control_server,data_server,client;
	socklen_t len1,len2;
	char filename[100],buf[max];
	FILE *fp;
	control_sock=socket(AF_INET,SOCK_STREAM,0);
	memset(&control_server,0,sizeof(control_server));
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	client.sin_port=htons(CONTROL_PORT);
	connect(control_sock,(struct sockaddr*)&client,sizeof(client));
	while(1)
	{
		printf("enter the filename : ");
		scanf("%s",filename);
		write(control_sock,filename,strlen(filename)+1);
		if(strcmp(filename,"exit")==0)
		{
			break;
		}
		data_sock=socket(AF_INET,SOCK_STREAM,0);
		client.sin_port=htons(DATA_PORT);
		connect(data_sock,(struct sockaddr*)&client,sizeof(client));
		printf("\nfilecontent of %s : \n",filename);
		while(n=read(data_sock,buf,sizeof(buf)-1))
		{
			buf[n]='\0';
			printf("%s",buf);
			
		}printf("\n");
		close(data_sock);
	}close(control_sock);
	
}
