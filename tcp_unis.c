#include"sys/socket.h"
#include"netinet/in.h"
#include"stdio.h"
#include"string.h"
#include"stdlib.h"
#include"unistd.h"

int main()
{
	char buf[100];
	int k,sock_desc,temp_sock;
	socklen_t len;
	struct sockaddr_in server,client;
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=3004;
	k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
	len=sizeof(client);
	k=listen(sock_desc,1);
	temp_sock=accept(sock_desc,(struct sockaddr*)&client,&len);
	k=recv(temp_sock,buf,100,0);
	printf("msg from client : %s",buf);
	close(sock_desc);
}
