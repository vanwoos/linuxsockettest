#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAXLINE 4096

void * handleConn(void * connfd)
{
	char buff[MAXLINE+1];
	int n;
	while(1)
	{
		n=recv(*(int *)connfd,buff,MAXLINE,0);
		if(n==0) break;
		buff[n]='\0';
		//send(connfd,buff,n,0);
		printf("recv msg from client:%s\n",buff);
	}
	close(*(int *)connfd);
	return (void *)0;
}

int main()
{
	int serverfd,connfd;
	pthread_t tid;
	pthread_attr_t attr;
	struct sockaddr_in servaddr;
	char buff[MAXLINE+1];
	int n;
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
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
		pthread_create(&tid,&attr,handleConn,(void *)&connfd);
		//pthread_join(th1,NULL);
		//close(connfd);
	}
	close(serverfd);
	pthread_attr_destroy(&attr);
}
