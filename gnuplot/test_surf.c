#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include "gnuplot_i.h"

#define Nx 64
#define Ny 128

int main (int argc, char *argv[])
{
	gnuplot_ctrl * h; //handler of gnuplot session

	int i, j;

	double *x = (double *)malloc(Nx*sizeof(double));
	double *y = (double *)malloc(Ny*sizeof(double));
	double **z = (double **)malloc(Nx*sizeof(double *));

	for (i=0 ; i<Ny ; i++)
	{
		z[i]=malloc(Ny*sizeof(double));
	}

	h=gnuplot_init();
	
	for (i=0 ; i<Nx ; i++)
	{
		for (j=0 ; j<Ny ; j++)
			{
				x[i]=(double)(i-Nx/2);
				y[j]=(double)(j-Ny/2);
				z[i][j]=x[i]*y[j];
				//printf("z[i][j]=%e\n",z[i][j]);
			}
	}

	gnuplot_surf_gray_IMP(h, x, y, z, Nx, Ny, "try surface plot");

	sleep(10);
	gnuplot_close(h);
	return 0;
}
