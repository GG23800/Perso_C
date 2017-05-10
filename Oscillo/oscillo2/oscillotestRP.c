#include<stdio.h> //for printf
#include<stdlib.h> //for exit()

#include"gnuplot_i.h"
#include"TCP_API.h"
#include"signal_processing.h"

#define Port 7538
//#define Ymax 1 //maximum boundary of the y axis

float x0=0.0;
float xf=0.0;
int dec=0;
int Nline=0;
double sector=0.0;
int mode_RP=0;
int step=1;


void writefile (double *z, int line, char *name)
{
	int i;
	FILE * f;
	f = fopen(name,"w+");
	for (i=0 ; i<line ; i++)
	{
		fprintf(f, "%f\n", z[i]);
	}
	fclose(f);
}

int main(int arg, char *argv[])
{
	int Npoint;

	//socket variable
	SOCKET sock;
	const char *IP="192.168.128.3";
	init_TCP_client(&sock, IP, Port);
	get_RP_settings(&sock);
	printf("x0=%f\n",x0);
        printf("xf=%f\n",xf);
        printf("dec=%i\n",dec);
        printf("Nline=%i\n",Nline);
        printf("sector=%f\n",sector);
	printf("mode_RP=%i\n",mode_RP);

	int l=0;

	Npoint=16384;

	//gnuplot variable
	gnuplot_ctrl * h;
	double *y= (double *)malloc(Npoint*sizeof(double));
	int i;

	int Ymax=1.5;

	//gnuplot object
	h=gnuplot_init();
	gnuplot_setstyle(h,"lines");
	gnuplot_set_xlabel(h,"time (us)");
	gnuplot_set_ylabel(h,"signal");
	//gnuplot_cmd(h,"set yrange [0:%d]", 2*Ymax);
	gnuplot_cmd(h,"set xrange [0:%d]",Npoint-1);

	char name[30];

	int16_t *buff=(int16_t *)malloc((Npoint+1)*sizeof(int16_t));
	while (1)
	{
		if(receive_int16_TCP_client(&sock, buff, Npoint+1)==1){break;}
		for (i=1 ; i<Npoint+1 ; i++){y[i-1]=(double)(buff[i])/409.6;} //divide by 409.6 to have voltage value
		gnuplot_resetplot(h);
                gnuplot_plot_x(h, y, Npoint, "Oscillo int16_t");

	}


	usleep(30);
	close(sock);
	free(y);

	return 0;
}
