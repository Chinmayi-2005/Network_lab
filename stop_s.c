#include<stdio.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#define PORT 4004

struct pkt
{
	int seq_no;
	int ack;
	char data[25];
}packet,recv_packet;

int main()
{
	srand(time(NULL));
	int sock_desc,err;
	struct sockaddr_in server,client;
	socklen_t len=sizeof(client);
	sock_desc=socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(PORT);
	bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
	while(1)
	{
		err=recvfrom(sock_desc,&recv_packet,sizeof(recv_packet),0,(struct sockaddr*)&client,&len);
		if(err>0)
		{
			int drop=rand()%10;
			if(drop<2)
			{
				printf("packet %s of seq_num %d is drpped due to noise\n",recv_packet.data,recv_packet.seq_no);
				continue;
			}
			
			printf("Recieved packet %s of seq_num %d\n",recv_packet.data,recv_packet.seq_no);
			packet.ack=recv_packet.seq_no;
			sendto(sock_desc,&packet,sizeof(packet),0,(struct sockaddr*)&client,len);
			printf("Acknowledgement is send for seq %d\n",packet.ack);
				
		}
	}
	close(sock_desc);
}
