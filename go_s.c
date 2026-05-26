#include<stdio.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#define PORT 4004
#define TOTAL 10
#define WINDOW 4
#define TIMEOUT_SEC 2

int main()
{
	int sock_desc,recv_seq,exp_seq=0;
	struct sockaddr_in server,client;
	socklen_t len=sizeof(client);
	sock_desc=socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(PORT);
	srand(time(NULL));
	bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
	while(1)
	{
		recvfrom(sock_desc,&recv_seq,sizeof(recv_seq),0,(struct sockaddr*)&client,&len);
		if(rand()%10<2)
		{
			printf("packet is %d is droped dueto noise\n",recv_seq);
			continue;
		}
		if(recv_seq==exp_seq)
		{
			printf("[reciever]correct pkt recieved : %d",recv_seq);
			sendto(sock_desc,&exp_seq,sizeof(exp_seq),0,(struct sockaddr*)&client,len);
			exp_seq++;
		}
		else
		{
			printf("[reciever] out of order got %d expected %d",recv_seq,exp_seq);
			int last_ack=exp_seq-1;
			sendto(sock_desc,&last_ack,sizeof(last_ack),0,(struct sockaddr*)&client,len);
		}
		if(exp_seq==TOTAL)
		{
			break;
		}
		
	}
	printf("[reciver]transfer complete\n");
	close(sock_desc);
}
