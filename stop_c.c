#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define PORT 4004

struct pkt
{
	int seq_no;
	int ack;
	char data[25];
}packet,recv_packet;
int main()
{
	int sock_desc,counter=1;
	struct sockaddr_in client;
	char input[25];
	struct timeval timeout={2,0};
	sock_desc=socket(AF_INET,SOCK_DGRAM,0);
	client.sin_family=AF_INET;
	int recv_len;
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	client.sin_port=htons(PORT);
	socklen_t len=sizeof(client);
	printf("enter the sequance\n");
	while(1)
	{
		scanf("%s",input);
		if(strcmp(input,"q")==0)
		{
			break;
		}
		strcpy(packet.data,input);
		packet.seq_no=counter;
		sendto(sock_desc,&packet,sizeof(packet),0,(struct sockaddr*)&client,len);
		printf("packet %s is sending of %d seq_num\n",packet.data,packet.seq_no);
		setsockopt(sock_desc,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(timeout));
		while(1)
		{
			recv_len=recvfrom(sock_desc,&recv_packet,sizeof(recv_packet),0,(struct sockaddr*)&client,&len);
			if(recv_len>0)
			{
				if(recv_packet.ack==packet.seq_no)
				{
					printf("acknowledged %d\n",packet.seq_no);
					counter++;
					break;
				}
				else
				{
					printf("packet is retransmitted %s",packet.data);
					sendto(sock_desc,&packet,sizeof(packet),0,(struct sockaddr*)&client,len);
				}
				
			}
		}
	}close(sock_desc);
}
