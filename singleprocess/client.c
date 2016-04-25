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
	int clientfd,connfd,n;
	char buff[MAXLINE+1];
	struct sockaddr_in servaddr;
	printf("start run socket\n");
	clientfd=socket(AF_INET,SOCK_STREAM,0);
	if(clientfd==-1)
		printf("run socket failed\n");
	else
		printf("run socket succeed\n");

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(8080);
	if(inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr)<=0)
	{
		printf("run inet_pton failed\n");
		exit(0);
	}

	printf("start run connect\n");
	if(connect(clientfd,(struct sockaddr *)&servaddr,sizeof(servaddr))!=0)
		printf("run connect failed\n");
	else{
		printf("run connect succeed\n");
	}
	//fgets(recvline,4096,stdin);
	while(1)
	{
		printf("send msg to server:");
		fgets(buff,MAXLINE,stdin);
		//gets(sendline);
		printf("start run send\n");
		if(send(clientfd,buff,strlen(buff),0)<0)
			printf("run send failed\n");
		else
			printf("run send succeed\n");
		/*sleep(3);
		n=recv(connfd,recvline,MAXLINE,0);
		if(n!=0)
		{
			recvline[n]='\0';
			printf("recv msg from server:%s\n",recvline);
		}*/
		//fgets(recvline,4096,stdin);
	}
	close(clientfd);
	return 0;
}
