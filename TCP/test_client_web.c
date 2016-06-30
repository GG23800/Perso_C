#include "test_client_web.h"

#include<signal.h>
#include<math.h>

#define Port 9000 
#define Nset 5
#define setL 5

static int sock;

void ctrlc(int signum)
{
	printf("coquin\n");
	close(sock);
	exit(signum);
}

int main(int arg, char *argv[])
{
	signal(SIGINT,ctrlc);

	int line, i, j;
	//SOCKET sock=0;
	SOCKADDR_IN sin={0};
	struct hostent *hostinfo=NULL;
	//const char *hostname="www.xxx";
	const char *IP="92.243.29.92";
	const char *rep="baziga!!";

	//buffers parameters
	char buff[Nset*setL+1];	
	char **charbuff=NULL;
	int *intbuff=(int *)malloc(Nset*sizeof(int));
	charbuff=(char **)malloc(Nset*sizeof(char *));
	for (i=0 ; i<Nset ; i++)
	{
		charbuff[i]=(char*)malloc(setL*sizeof(char));
	}

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
		if(recv(sock, buff, Nset*setL+1, MSG_WAITALL)==0)
		{
			printf("Server closed\n");
			break;
		}
		buff[Nset*setL+1]=(char)0;
		printf("%s\n",buff);

		for (i=0 ; i<Nset ; i++)
		{
			for (j=0 ; j<setL ; j++)
			{
				charbuff[i][j]=buff[i*setL+j];
			}
			intbuff[i]=atoi(charbuff[i]);
			printf("intbuff[%d]=%d\n",i,intbuff[i]);
		}

		send(sock,rep,8,0);
			
		char ** tmpbuff=(char **)malloc(64*sizeof(char *));
		for (i=0 ; i<64 ; i++)
		{
			tmpbuff[i]=(char *)malloc(intbuff[3]*sizeof(char));
		}
		FILE *fmat=NULL;
		fmat=fopen("mat.dat","r");
		for (j=0 ; j<64 ; j++)
		{
			for (i=0 ; i<intbuff[3] ; i++)
			{
				//fscanf(fmat,"%c ",&tmpbuff[j][i]);
				tmp=(j+1)*(i+1)%255;
				tmpbuff[j][i]=(char)(tmp);
				printf("sent:%i\n",tmp);
			}
		}
		fclose(fmat);
		for (i=0 ; i<64 ; i++)
		{
			send(sock,tmpbuff[i],intbuff[3],0);
		}
		free(tmpbuff);
	}

	close(sock);
	return 0;
}
