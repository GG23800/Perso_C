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
#define Rmin 25 //minimum distance (mm) of the scan
#define Rmax 150 //maximum distance (mm) of the scan
#define angle 60 //angle in degree of the scan
#define Nline 64 //number of line of the scan

int init_xy (double **x, double **y)
{
	int i, j;
	double deltar, deltatheta, anglerad, anglemin;
	double r = (double)malloc((BufferLength-1)*sizeof(double));
	double theta = (double)malloc(Nline*sizeof(double)); 
	x = malloc(Nline*sizeof(double *);
	y = malloc(Nline*sizeof(double *);

	for (i=0 ; i<Nline ; i++)
	{
		x[i]=malloc((BuffLength-1)*sizeof(double));
		y[i]=malloc((BuffLength-1)*sizeof(double));
	}

	deltar = (double)(Rmax-Rmin)/(double)(BuffLength-2);
	anglerad = (double)(angle)*M_PI/180.0;
	deltatheta = anglerad/(double)(Nline-1);
	anglemin = -anglerad/2.0;

	for (i=0 ; i<Nline ; i++)
	{
		theta[i]=anglemin+(double)(i)*deltatheta;
	}
	for (i=0 ; i<BufferLength-1 ; i++)
	{
		r[i] = (double)(Rmin)+(double)(i)*deltar;
		for (j=0 ; j<Nline ; j++)
		{
			x[i][j]=r[i]*cos(theta[j]);
			y[i][j]=r[i]*sin(theta[j]);
		}
	}

}

int main(int arg, char *argv[])
{
	//socket variable
	int sock, line;
	struct sockaddr_in sin;
	char buff[BuffLength];
	const char *IP="192.168.128.3";

	//gnuplot variable
	gnuplot_ctrl * h;
	double *y= (double *)malloc((BuffLength-1)*sizeof(double));
	int i,j;

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

	//gnuplot object
	h=gnuplot_init();
	gnuplot_setstyle(h,"lines");
	gnuplot_set_xlabel(h,"time (us)");
	gnuplot_set_ylabel(h,"signal");
	gnuplot_cmd(h,"set yrange [1:%d]",Ymax);
	gnuplot_cmd(h,"set xrange [0:1024]");

	j=0;
	while(1)
	{	
		if(recv(sock, buff, BuffLength, MSG_WAITALL)==0)
			{
				printf("Server closed\n");
				break;
			}
		if ((int)(buff[0])==LineNumber)
		{
			for (i=1; i<BuffLength; i++)
			{
				y[i-1]=(double)(buff[i]);
			}
			gnuplot_resetplot(h);
			gnuplot_plot_x(h, y, BuffLength-1, "RP");
			printf("Image numéro %i\n",j);
			j++;
		}
	}

	sleep(30);
	close(sock);
	free(y);
	return 0;
}
