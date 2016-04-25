#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAXLINE 4096

void handleConn(int connfd)
{
	char buff[MAXLINE+1];
	int n;
	while(1)
	{
		n=recv(connfd,buff,MAXLINE,0);
		if(n==0) return;
		buff[n]='\0';
		//send(connfd,buff,n,0);
		printf("recv msg from client:%s\n",buff);
	}
}

int main()
{
	int pid;
	int serverfd,connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE+1];
	int n;

	printf("start run socket\n");
	serverfd=socket(AF_INET,SOCK_STREAM,0);
	if(serverfd==-1)
		printf("run socket failed\n");
	else
		printf("run socket succeed\n");

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(8080);
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	printf("start run bind\n");
	if(bind(serverfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1)
		printf("run bind failed\n");
	else
		printf("run bind succeed\n");

	printf("start run listen\n");
	if(listen(serverfd,10)==-1)
		printf("run listen failed\n");
	else
		printf("run listen succeed\n");

	while(1)
	{
		printf("start run accept\n");
		connfd=accept(serverfd,(struct sockaddr *)NULL,NULL);
		if(connfd==-1)
			printf("run accept faild\n");
		else
			printf("run accept succeed\n");
		pid=fork();
		if(pid==0)
		{
			handleConn(connfd);
			close(connfd);
			exit(0);
		}
		else{
		}
	}
	close(serverfd);
}
