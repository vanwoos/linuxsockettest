#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAXLINE 4096

int main()
{
	int clientfd;
	char recvline[4096],sendline[4096]="hellokdjsgksljdkgjkrgjksjghkfjk";
	struct sockaddr_in servaddr;
	while(1)
	{
		printf("start run socket\n");
		clientfd=socket(AF_INET,SOCK_STREAM,0);
		if(clientfd==-1)
			printf("run socket failed\n");
		else
			printf("run socket succeed\n");

		servaddr.sin_family=AF_INET;
		servaddr.sin_port=htons(21);
		if(inet_pton(AF_INET,"192.168.41.43",&servaddr.sin_addr)<=0)
		{
			printf("run inet_pton failed\n");
			exit(0);
		}

		printf("start run connect\n");
		if(connect(clientfd,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
			printf("run connect failed\n");
		else{
			printf("run connect succeed\n");
		}
		printf("start run send\n");
		if(send(clientfd,sendline,strlen(sendline),0)<0)
			printf("run send failed\n");
		else
			printf("run send succeed\n");
		close(clientfd);
		//fgets(recvline,4096,stdin);
		usleep(1);
	}
	while(1)
	{
		printf("send msg to server:");
		fgets(sendline,4096,stdin);
		//gets(sendline);
		printf("start run send\n");
		if(send(clientfd,sendline,strlen(sendline),0)<0)
			printf("run send failed\n");
		else
			printf("run send succeed\n");
		//fgets(recvline,4096,stdin);
	}
	close(clientfd);
	return 0;
}
