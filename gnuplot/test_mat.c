#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include "gnuplot_i.h"
#include "math.h"

#define Nx 64
#define Ny 1024

int main (int argc, char *argv[])
{
	gnuplot_ctrl * h; //handler of gnuplot session

	int i, j, k;

	int **z =(int **)malloc(Nx*sizeof(*z));
	if (z==NULL)
	{
		printf("malloc ** problem");
	}

	for (i=0 ; i<Nx ; i++)
	{
		z[i]=(int *)malloc(Ny*sizeof(int *));
		if(z[i]==NULL)
		{
			printf("malloc * problem");
		}
	}
	
	h=gnuplot_init();
	gnuplot_cmd(h,"set pm3d map");
	gnuplot_cmd(h,"set palette gray");
	
	for (k=0 ; k<10 ; k++)
	{
		for (i=0 ; i<Nx ; i++)
		{
			for (j=0 ; j<Ny ; j++)
				{
					z[i][j]=pow(-1,k)*j;//pow(-1,i);//*pow(-1,j);//*pow(-1,k)*i*j/1000;
				}
		}
	gnuplot_matrix(h, z, Ny, Nx);
	printf("image %d\n",k);
	sleep(1);
	}

	sleep(10);
	gnuplot_close(h);

	free(z);
	//printf("z[%d][%d]= %d\n",i-1,j-1,z[i-1][j-1]);
	return 0;
}
