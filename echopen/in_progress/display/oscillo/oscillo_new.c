#include<stdio.h> //for printf
#include<stdlib.h> //for exit()

#include"gnuplot_i.h"
#include"TCP_API.h"

#define Port 7538

float r0=0.0;
float rf=0.0;
int dec=0;
int Nline=0;
double sector=0.0;
int mode_RP=0;
int step=1;


int main(int arg, char *argv[])
{
	int Npoint;

	//socket variable
	SOCKET sock;
	const char *IP="192.168.128.3";
	init_TCP_client(&sock, IP, Port);
	get_RP_settings(&sock);
	printf("r0=%f\n",r0);
        printf("rf=%f\n",rf);
        printf("dec=%i\n",dec);
        printf("Nline=%i\n",Nline);
        printf("sector=%f\n",sector);
	printf("mode_RP=%i\n",mode_RP);

	int i=0;

	Npoint=(int)(2.0*(rf-r0)*125.0/1.48/((double)dec));
        if (Npoint>16384) {Npoint=16384;}
	printf("Npoint = %i\n",Npoint);

	float fech=125.0/((float)dec);

	double *x=(double *)malloc((int)Npoint*sizeof(double));
	for (i=0 ; i<Npoint ; i++)
	{
		x[i]=((double)i)/fech;
	}

	//gnuplot variable
	gnuplot_ctrl * h;
	double *y1= (double *)malloc(Npoint*sizeof(double));
	double *y2= (double *)malloc(Npoint*sizeof(double));

	for (i=0 ; i<Npoint ; i++)
	{
		y1[i]=0.0;
		y2[i]=0.0;
	}

	//gnuplot object
	h=gnuplot_init();
	gnuplot_setstyle(h,"lines");
	gnuplot_set_xlabel(h,"time (us)");
	gnuplot_set_ylabel(h,"signal");
	//gnuplot_cmd(h,"set yrange [0:%d]", 2*Ymax);
	//gnuplot_cmd(h,"set xrange [0:%.18e]",x[Npoint-1]);

	if (mode_RP==0)
	{

		int16_t *buff=(int16_t *)malloc((Npoint+1)*sizeof(int16_t));
		int voie=0;
		while(1)
		{
			if(receive_int16_TCP_client(&sock, buff, Npoint+1)==1){break;}
			voie = (int)buff[0];
			switch (voie)
			{
				case 1 :
				for (i=0 ; i<Npoint ; i++) {y1[i]=((double)buff[i+1])/409.6;}
				break;

				case 2 :
				for (i=0 ; i<Npoint ; i++) {y2[i]=((double)buff[i+1])/409.6;}
			}
			gnuplot_resetplot(h);
			gnuplot_double_plot(h, (int)Npoint, x, y1, y2);
		}
		free(buff);
	}

	usleep(30);
	close(sock);
	free(x);
	free(y1);
	free(y2);

	return 0;
}
