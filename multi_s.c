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
int clients[max_c],client_c=0;
pthread_mutex_t lock;
void broadcast(char *msg,int sock)
{
	int i;
	pthread_mutex_lock(&lock);
	for(i=0;i<client_c;i++)
	{
		if(clients[i]!=sock)
		{
			send(clients[i],msg,strlen(msg),0);
		}
	}
}
void *handleclient(void *arg)
{
	int i;
	int sock=*(int*)arg;
	free(arg);
	char buf[max];
	while(1)
	{
		bzero(buf,max);
		int b=recv(sock,buf,sizeof(buf)-1,0);
		if(b<=0)
		{
			printf("error");
			break;
		}
		buf[b]='\0';
		printf("msg from client : %s",buf);
		broadcast(buf,sock);
	}
	close(sock);
	pthread_mutex_lock(&lock);
	for(i=0;i<client_c;i++)
	{
		if(clients[i]==sock)
		{
			clients[i]=clients[client_c-1];
			client_c--;
			break;
		}
	}
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main()
{
	int sock_desc,temp_sock;
	socklen_t len;
	char buf[max];
	pthread_t tid;
	pthread_mutex_init(&lock,NULL);
	struct sockaddr_in server,client;
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(3004);
	len=sizeof(client);
	bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
	listen(sock_desc,10);
	printf("server_started....\n");
	while(1)
	{
		temp_sock=accept(sock_desc,(struct sockaddr*)&client,&len);
		printf("client 1 is accepted");
		pthread_mutex_lock(&lock);
		clients[client_c++]=temp_sock;
		printf("Client %d is connected\n", client_c);

		pthread_mutex_unlock(&lock);
		int *pclient=malloc(sizeof(int));
		*pclient=temp_sock;
		pthread_create(&tid,NULL,handleclient,pclient);
		pthread_detach(tid);
	}
	close(sock_desc);
}
