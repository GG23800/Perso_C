#include<stdio.h> //for printf
#include<stdlib.h> //for exit()
#include<sys/socket.h> //for socket
#include<sys/types.h> //utile?
#include<arpa/inet.h> //for inet_addr
#include<errno.h> //for error
#include<unistd.h> //for close()

#include<math.h>
#include"gnuplot_i.h"

#define Port 7538
#define BuffLength 1025 //size of the TCP buffer
#define Nline 64 //number of line of the scan

int main(int arg, char *argv[])
{
	//socket variable
	int sock;
	struct sockaddr_in sin;
	char buff[BuffLength]={0};
	const char *IP="192.168.128.3";

	//gnuplot variable
	gnuplot_ctrl * h; //handler of gnuplot session
	printf("gnuctrl done\n");
	int i, j, line;

	int **z = (int **)malloc(Nline*sizeof(int *));

	for (i=0 ; i<Nline ; i++)
	{
		z[i]=(int *)malloc((BuffLength-1)*sizeof(int));
	}
	printf("z init finish\n");

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

	printf("define socket\n");

	if (connect(sock, (struct sockaddr *) &sin, sizeof(sin))==-1)
	{
		perror("connect()");
		exit(errno);
	}

	printf("Connected\n");

	//gnuplot object
	h=gnuplot_init();
	gnuplot_cmd(h,"set pm3d map");
	gnuplot_cmd(h,"set palette gray");
	int k=0, l=1;;
	while(l)
	{	
		for (i=0 ; i<Nline ; i++)
		{
			if(recv(sock, buff, BuffLength, MSG_WAITALL)==0)
			{
				printf("Server closed\n");
				i=Nline+1;
				l=0;
				break;
			}

			if (i<Nline+2)
			{
				line=(int)(buff[0])-1;
				printf("line number %d\n",line);
				for (j=0 ; j<BuffLength-1 ; j++)
				{
					z[line][j]=(int)(buff[j+1]);
				}
			}
		}
		printf("image number %d\n",k);
		k++;
		gnuplot_matrix(h, z, BuffLength-1, Nline);
	}
	
	close(sock);
	gnuplot_close(h);
	free(z);

	return 0;
}
