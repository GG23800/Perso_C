#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<math.h>

#include "gnuplot_i.h"

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
}

int main (int argc, char *argv[])
{
	gnuplot_ctrl * h; //handler of gnuplot session

	int i, j;

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

	h=gnuplot_init();
	
	for (i=0 ; i<Nline ; i++)
	{
		for (j=0 ; j<BuffLength-1 ; j++)
			{
				z[i][j]=x[i][j]*y[i][j];
			}
	}

	gnuplot_angle_gray_IMP(h, x, y, z, BuffLength-1, Nline);

	sleep(10);
	gnuplot_close(h);
	free(x);
	free(y);
	free(z);
	return 0;
}
