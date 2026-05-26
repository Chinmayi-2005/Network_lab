#include<stdio.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define max 1000
#define max_c 1000
int sock_desc;
pthread_mutex_t lock;
void *recievemsg(void * arg)
{
	char msg[max];
	while(1)
	{
		int b=recv(sock_desc,msg,sizeof(msg)-1,0);
		if(b<=0)
		{
			printf("error");
			break;
			
		}
		msg[b]='\0';
		printf("msg from client : %s\n",msg);
	}
	return NULL;
}
int main()
{
	pthread_t tid;
	char buf[max];
	struct sockaddr_in client;
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	pthread_mutex_init(&lock,NULL);
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	client.sin_port=htons(3004);
	connect(sock_desc,(struct sockaddr*)&client,sizeof(client));
	pthread_create(&tid,NULL,recievemsg,NULL);
	while(1)
	{
		fgets(buf,max,stdin);
		send(sock_desc,buf,strlen(buf),0);
	}close(sock_desc);
}
