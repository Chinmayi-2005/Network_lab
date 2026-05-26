#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<time.h>

#define MAXLINE 1000
#define PORT 5000

char* timefind()
{
    time_t T = time(NULL);
    struct tm tm = *localtime(&T);

    char *buf = malloc(80);

    sprintf(buf,"%02d:%02d:%02d",
            tm.tm_hour,tm.tm_min,tm.tm_sec);

    return buf;
}

int main()
{
    int sock_desc;
    char buf[100],buf1[100];
    struct sockaddr_in server,client;
    socklen_t len=sizeof(client);
    //socklen_t len=sizeof(client);
	sock_desc=socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(PORT);
	bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
	int n=recvfrom(sock_desc,buf,sizeof(buf)-1,0,(struct sockaddr*)&client,&len);
	buf[n]='\0';
	printf("the cmd is : %s",buf);
	strcpy(buf1,timefind());
	sendto(sock_desc,buf1,sizeof(buf1),0,(struct sockaddr*)&client,sizeof(client));
	close(sock_desc);
}
