#include "test_client_web6.h"

#define Port 8080
#define Nset 5
#define setL 5

int main(int arg, char *argv[])
{
	int line, i, j;
	SOCKET sock=0;
	SOCKADDR_IN6 sin6={0};
	struct hostent *hostinfo=NULL;
	//const char *hostname="www.xxx";
	const char *IP="92.243.29.92";

	char buff[Nset*setL];	
	char **charbuff=NULL;
	int *intbuff=(int *)malloc(Nset*sizeof(int));
	charbuff=(char **)malloc(Nset*sizeof(char *));
	for (i=0 ; i<Nset ; i++)
	{
		charbuff[i]=(char*)malloc(setL*sizeof(char));
	}

	//Create socket
	sock=socket(AF_INET6, SOCK_STREAM, 0);
	if (sock==INVALID_SOCKET)
	{
		perror("socket()");
		exit(errno);
	}

/*
	hostinfo=gethostbyname(hostname);
	if (hostinfo==NULL)
	{
		printf("Unknown host %s.\n", hostname);
		exit(EXIT_FAILURE);
	}*/

	//sin.sin_addr=*(IN_ADDR *) hostinfo->h_addr;
	sin6.sin6_addr.s6_addr=inet_addr(IP);
	sin6.sin6_family=AF_INET6;
	sin6.sin6_port=htons(Port);

	if (connect(sock, (SOCKADDR *) &sin6, sizeof(SOCKADDR))==SOCKET_ERROR)

	{
		perror("connect()");
		exit(errno);
	}

	printf("Connected\n");


	if(recv(sock, buff, Nset*setL, MSG_WAITALL)==0)
	{
		printf("Server closed\n");
		//break;
	}

	for (i=0 ; i<Nset*setL ; i++)
	{
		printf("%s\n",buff);
	}

	for (i=0 ; i<Nset ; i++)
	{
		for (j=0 ; j<setL ; j++)
		{
			charbuff[i][j]=buff[i*setL+j];
		}
		intbuff[i]=atoi(charbuff[i]);
		printf("intbuff[%d]=%d\n",i,intbuff[i]);
	}

	close(sock);
	return 0;
}
