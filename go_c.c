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
	int sock_desc,base=0,next_seq=0,ack;
	struct sockaddr_in client;
	struct timeval tv;
	
	
	int recv_len;
	sock_desc=socket(AF_INET,SOCK_DGRAM,0);
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	client.sin_port=htons(PORT);
	client.sin_family=AF_INET;
	tv.tv_sec=TIMEOUT_SEC;
	tv.tv_usec=0;
	setsockopt(sock_desc,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
	socklen_t len=sizeof(client);
	printf("[sender] starting gobackn protocol\n");
	while(base<TOTAL)
	{
		while(next_seq<WINDOW+base&&next_seq<TOTAL)
		{
		
			printf("[sender] sending packet %d\n",next_seq);
			sendto(sock_desc,&next_seq,sizeof(next_seq),0,(struct sockaddr*)&client,sizeof(client));
			next_seq++;
		}
		if(recvfrom(sock_desc,&ack,sizeof(ack),0,(struct sockaddr*)&client,&len)<0)
		{
			printf("Timeout occur retransmitting pkt fom %d\n",base);
			next_seq=base;
		}
		else
		{
			if(ack>=base)
			{
				printf("[sender] recieved cumulative ack for %d\n",ack);
				base=ack+1;
			}
		}
		
		
	}
	printf("[sender] all packets are sent and ack\n");
	close(sock_desc);
	
}
