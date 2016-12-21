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
	double *r = (double *)malloc((BuffLength-1)*sizeof(double));
	double *theta = (double *)malloc(Nline*sizeof(double)); 

	deltar = (double)(Rmax-Rmin)/(double)(BuffLength-2);
	anglerad = (double)(angle)*M_PI/180.0;
	deltatheta = anglerad/(double)(Nline-1);
	anglemin = -anglerad/2.0;

	for (i=0 ; i<BuffLength-1 ; i++)
	{
		r[i] = (double)(Rmin)+(double)(i)*deltar;
	}
	for (i=0 ; i<Nline ; i++)
	{
		theta[i]=anglemin+(double)(i)*deltatheta;
		for (j=0 ; j<BuffLength-1 ; j++)
		{
			x[i][j]=r[j]*cos(theta[i]);
			y[i][j]=r[j]*sin(theta[i]);
		}
	}
	
	free(r);
	free(theta);
	return 0;
}

void writefile (double **x, double **y, double **z, int line, int row)
{
	int i, j;
	FILE * f;
	f = fopen("data.dat", "w+");
	for (i=0 ; i<line ; i++)
	{
		for (j=0 ; j<row ; j++)
		{
			fprintf(f, "%f %f %f\n", x[i][j], y[i][j], z[i][j]);
		}
	}
	fclose(f);
}

int main(int arg, char *argv[])
{
	//socket variable
	int sock;
	struct sockaddr_in sin;
	char buff[BuffLength];
	const char *IP="192.168.128.3";

	//gnuplot variable
	gnuplot_ctrl * h; //handler of gnuplot session

	int i, j, line;

	double **x = NULL;
	double **y = NULL;
	double **z = (double **)malloc(Nline*sizeof(double *));
	x = malloc(Nline*sizeof(double *));
	y = malloc(Nline*sizeof(double *));

	for (i=0 ; i<Nline ; i++)
	{
		x[i]=malloc((BuffLength-1)*sizeof(double));
		y[i]=malloc((BuffLength-1)*sizeof(double));
		z[i]=malloc((BuffLength-1)*sizeof(double));
	}

	init_xy(x,y);

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
	gnuplot_cmd(h, "set pm3d map");
	gnuplot_cmd(h, "set palette gray");
	//gnuplot_angle_gray_IMP(h, x, y, z, BuffLength-1, Nline);

	while(1)
	{	
		for (i=0 ; i<Nline ; i++)
		{
			if(recv(sock, buff, BuffLength, MSG_WAITALL)==0)
			{
				printf("Server closed\n");
				break;
			}

			line=(int)(buff[0])-1;
			printf("%d\n",line);
			for (j=0 ; j<BuffLength-1 ; j++)
			{
				z[line][j]=(double)(buff[j+1]);
			}
		}

		gnuplot_angle_gray_IMP(h, x, y, z, BuffLength-1, Nline);
	}
	writefile(x,y,z,Nline,BuffLength-1);

	close(sock);
	gnuplot_close(h);
	free(x);
	free(y);
	free(z);
	return 0;
}
