#include<stdio.h> //for printf
#include<stdlib.h> //for exit()
#include<sys/socket.h> //for socket
#include<sys/types.h> //utile?
#include<arpa/inet.h> //for inet_addr
#include<errno.h> //for error
#include<unistd.h> //for close()

#define Port 7538
#define BuffLength 1025

int main(int arg, char *argv[])
{
	int sock, line;
	struct sockaddr_in sin;
	char buff[BuffLength];
	const char *IP="192.168.128.3";

	//Create socket
	sock=socket(AF_INET, SOCK_STREAM, 0);
	if (sock==-1)
	{
		perror("socket()");
		exit(errno);
	}

	sin.sin_addr.s_addr=inet_addr(IP);
	sin.sin_family=AF_INET;
	sin.sin_port=htons(Port);

	if (connect(sock, (struct sockaddr *) &sin, sizeof(sin))==-1)

	{
		perror("connect()");
		exit(errno);
	}

	printf("Connected\n");

	while(1)
	{	
		if(recv(sock, buff, BuffLength, MSG_WAITALL)==0) //flag MSG_WAITALL is used to be sure that the wall buffer is taken, if flag 0 is put we don't allwais have the complete buffer...
			{
				printf("Server closed\n");
				break;
			}
		line=(int)(buff[0]);
		printf("line number: %i\n",line);
	}

	close(sock);
	return 0;
}
