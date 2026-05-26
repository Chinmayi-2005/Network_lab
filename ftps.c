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
	struct sockaddr_in control_server,data_server,control_client,data_client;
	socklen_t len1,len2;
	char filename[100],buf[max];
	FILE *fp;
	control_sock=socket(AF_INET,SOCK_STREAM,0);
	memset(&control_server,0,sizeof(control_server));
	control_server.sin_family=AF_INET;
	control_server.sin_addr.s_addr=inet_addr("127.0.0.1");
	control_server.sin_port=htons(CONTROL_PORT);
	bind(control_sock,(struct sockaddr*)&control_server,sizeof(control_server));
	listen(control_sock,5);
	len1=sizeof(control_client);
	control_cli=accept(control_sock,(struct sockaddr*)&control_client,&len1);
	data_sock=socket(AF_INET,SOCK_STREAM,0);
	memset(&data_server,0,sizeof(data_server));
	data_server.sin_family=AF_INET;
	data_server.sin_addr.s_addr=inet_addr("127.0.0.1");
	data_server.sin_port=htons(DATA_PORT);
	bind(data_sock,(struct sockaddr*)&data_server,sizeof(data_server));
	listen(data_sock,5);
	while(1)
	{
		memset(filename,0,sizeof(filename));
		n=read(control_cli,filename,sizeof(filename)-1);
		if(n<=0)
		{
			break;
		}
		filename[n]='\0';
		if(strcmp(filename,"exit")==0)
		{
			printf("client_disconnected\n");
			break;
		}
		len2=sizeof(data_client);
		data_cli=accept(data_sock,(struct sockaddr*)&data_client,&len2);
		printf("filename is : %s\n",filename);
		fp=fopen(filename,"r");
		while(fgets(buf,sizeof(buf),fp)!=NULL)
				{
			write(data_cli,buf,sizeof(buf));
			
		}fclose(fp);
		close(data_cli);
	}close(data_sock);
	close(control_sock);
	close(control_cli);
}
