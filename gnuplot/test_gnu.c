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
	int i;

	h=gnuplot_init();
	
	for (i=0; i<BufferLength; i++)
	{
		x[i]=(double)(0.01*i);
		y[i]=sin(x[i]);
	}

	gnuplot_setstyle(h, "lines");
	gnuplot_plot_xy(h, x, y, BufferLength, "try to plot sin(x)");

	sleep(10);
	gnuplot_close(h);
	return 0;
}
