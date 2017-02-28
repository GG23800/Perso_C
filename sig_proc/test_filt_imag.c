#include <stdio.h>
#include <stdlib.h>

#include "signal_processing.h"

int main (int argc, char *argv[])
{
	int line=3;
	int row=8;

	double **im=NULL, **im2=NULL;
	im=(double **)malloc(line*sizeof(double *));
	im2=(double **)malloc(line*sizeof(double *));
	
	int i=0, j=0;

	for (i=0 ; i<line ; i++)
	{
		im[i]=(double *)malloc(row*sizeof(double));
		im2[i]=(double *)malloc(row*sizeof(double));
	}

	/*for (i=0 ; i<line ; i++)
	{
		for (j=0 ; j<row ; j++)
		{
			im[i][j]=(double)(3*i+j+1);
		}
	}*/

	int k=0;
	for (i=0 ; i<line ; i++)
	{
		k=1;
		for (j=0 ; j<row ; j++)
		{
			if (k>4){k=1;}
			im[i][j]=(double)(2*k);
			k++;
		}
	}

	filter_image (im, im2, line, row);

	for (i=0 ; i<line ; i++)
	{
		for (j=0 ; j<row ; j++)
		{
			printf("%f ",im[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (i=0 ; i<line ; i++)
	{
		for (j=0 ; j<row ; j++)
		{
			printf("%f ",im2[i][j]);
		}
		printf("\n");
	}

	free(im);
	free(im2);

	return 0;
}
