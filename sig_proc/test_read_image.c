#include <stdio.h>
#include <stdlib.h>

#include "signal_processing.h"

int main (int argc, char *argv[])
{
	int line=3, row=3;
	int i=0, j=0;
	double **image=NULL;
	image=(double **)malloc(line*sizeof(double *));
	for (i=0 ; i<line ; i++)
	{
		image[i]=(double *)malloc(row*sizeof(double));
	}

	load_image(image, line, row, "test_im.txt");

	for (i=0 ; i<line ; i++)
	{
		for (j=0 ; j<row ; j++)
		{
			printf("%f ",image[i][j]);
		}
		printf("\n");
	}

	free(image);
	return 0;
}
