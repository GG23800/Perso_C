#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

#include "gnuplot_i.h"

#define BufferLength 1024

int main (int argc, char *argv[])
{
	gnuplot_ctrl * h; //handler of gnuplot session
	double x[BufferLength];
	double y[BufferLength];
	int i,j;

	h=gnuplot_init();
	gnuplot_setstyle(h,"lines");
	
	for (j=0; j<10; j++)
	{ 
		for (i=0; i<BufferLength; i++)
		{
			x[i]=(double)(0.01*i);
			y[i]=sin(x[i]+(double)(3.14/10*j));
		}
		gnuplot_resetplot(h);	
		gnuplot_plot_xy(h, x, y, BufferLength, "sin(x)");
		gnuplot_set_xlabel(h,"time (s)");
		gnuplot_set_ylabel(h,"signal (V)");
		sleep(1);
	}

	gnuplot_close(h);
	return 0;
}
