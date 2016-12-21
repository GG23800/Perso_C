#include<stdio.h> //for printf
#include<stdlib.h> //for exit()

#include"gnuplot_i.h"
#include"TCP_API.h"

#define Port 7538
#define Ymax 150 //maximum boundary of the y axis

int int_converter(char set)
{
	int tmp;
	tmp=(int)set;
	tmp+=256;
	tmp=tmp%256;
	return tmp;
}

int main(int arg, char *argv[])
{
	int Npoint, dec, line, Nline, sector;
	double x0, xf;

	//socket variable
	SOCKET sock;
	const char *IP="192.168.128.3";
	init_TCP_client(&sock, IP, Port);

	int Nset=5;
	char settings[Nset];
	receive_TCP_client(&sock, settings, Nset);
	x0=(double)int_converter(settings[0]);
	xf=(double)int_converter(settings[1]);
	dec=int_converter(settings[2]);
	line=int_converter(settings[3]);
	Nline=line/2;
	sector=int_converter(settings[4]);
	Npoint=(int)(2.0*(xf-x0)*125.0/1.48/((double)dec));
	char *buff=(char *)malloc((Npoint+1)*sizeof(char));

	//gnuplot variable
	gnuplot_ctrl * h;
	double *y= (double *)malloc(Npoint*sizeof(double));
	int i,j;

	//gnuplot object
	h=gnuplot_init();
	gnuplot_setstyle(h,"lines");
	gnuplot_set_xlabel(h,"time (us)");
	gnuplot_set_ylabel(h,"signal");
	gnuplot_cmd(h,"set yrange [1:%d]",Ymax);
	gnuplot_cmd(h,"set xrange [0:%d]",Npoint-1);

	while(1)
	{
		if (receive_TCP_client(&sock, buff, Npoint+1)==1)
		{
			break;
		}	
			
		if ((int)(buff[0])==Nline)
		{
			for (i=1; i<Npoint+1 ; i++)
			{
				y[i-1]=(double)(buff[i]);
			}
			gnuplot_resetplot(h);
			gnuplot_plot_x(h, y, Npoint, "RP");
		}
	}

	usleep(30);
	close(sock);
	free(y);
	return 0;
}
