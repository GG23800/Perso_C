#include "test_client_web.h"

#include<signal.h>
#include<math.h>

#define Port 9000 
#define Nset 8
static int sock;

void ctrlc(int signum)
{
	printf("oquin\n");
	close(sock);
	exit(signum);
}

int main(int arg, char *argv[])
{
	signal(SIGINT,ctrlc);

	int Nline, Nsample, i, j;
	SOCKADDR_IN sin={0};
	struct hostent *hostinfo=NULL;
	const char *IP="92.243.29.92";

	//buffers parameters
	char buff[Nset];	
	int *intbuff=(int *)malloc(Nset*sizeof(int));

	//Create socket
	sock=socket(AF_INET, SOCK_STREAM, 0);
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

	sin.sin_addr.s_addr=inet_addr(IP);
	sin.sin_family=AF_INET;
	sin.sin_port=htons(Port);

	if (connect(sock, (SOCKADDR *) &sin, sizeof(SOCKADDR))==SOCKET_ERROR)

	{
		perror("connect()");
		exit(errno);
	}

	printf("Connected\n");

	int tmp=0;
	while(1)
	{
		if(recv(sock, buff, Nset+1, MSG_WAITALL)==0)
		{
			printf("Server closed\n");
			break;
		}
		printf("%s\n",buff);

		for (i=0 ; i<Nset ; i++)
		{
			intbuff[i]=(int)(buff[i]);
			intbuff[i]=(intbuff[i]+256)%256;
		}
		Nline=intbuff[6];
		Nsample=(int)(2.0*(double)(intbuff[2]-intbuff[1])*125.0/1.48/(double)(intbuff[0]));
		printf("number of points : %i\n",Nsample);
		send(sock,buff,Nset,0);
			
		char ** tmpbuff=(char **)malloc(Nline*sizeof(char *));
		for (i=0 ; i<Nline ; i++)
		{
			tmpbuff[i]=(char *)malloc(Nsample*sizeof(char));
		}
		for (j=0 ; j<Nline ; j++)
		{
			for (i=0 ; i<Nsample ; i++)
			{
				tmp=(j+1)*(i+1)%256;
				tmpbuff[j][i]=(char)(tmp);
				//printf("tmpbuff[%i][%i]=:%i\n",j,i,tmp);
			}
		}
	
		for (j=0 ; j<intbuff[7] ; j++)
		{
			for (i=0 ; i<Nline ; i++)
			{
				send(sock,tmpbuff[i],intbuff[7],0);
			}
		}
		free(tmpbuff);
	}

	close(sock);
	free(intbuff);
	return 0;
}
