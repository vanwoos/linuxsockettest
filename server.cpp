#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define MAXLINE 4096

int main()
{
	int listenfd,connfd;
	struct sockaddr_in servaddr;
	char buff[4096+1];
	int n;

	printf("start run socket\n");
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	if(listenfd==-1)
		printf("run socket failed\n");
	else
		printf("run socket succeed\n");

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(8080);

	printf("start run bind\n");
	if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1)
		printf("run bind failed\n");
	else
		printf("run bind succeed\n");

	printf("start run listen\n");
	if(listen(listenfd,10)==-1)
		printf("run listen failed\n");
	else
		printf("run listen succeed\n");

	printf("start run accept\n");
	connfd=accept(listenfd,(struct sockaddr *)NULL,NULL);
	if(connfd==-1)
		printf("run accept faild\n");
	else
		printf("run accept succeed\n");

	while(1)
	{
		n=recv(connfd,buff,MAXLINE,0);
		if(n==0) break;
		buff[n]='\0';
		printf("recv msg from client:%s\n",buff);
	}
	close(connfd);
	close(listenfd);
}
