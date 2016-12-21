#include<stdio.h>
#include<stdlib.h>

int main(int arg, char * argv[])
{
	FILE *f=NULL;
	int Nline=64, buffl=1024;
	char *ligne=NULL;
	size_t longueur=0;
	ssize_t luts=0;

	double **x = NULL;
	double **y = NULL;

	int **z = (int **)malloc(Nline*sizeof(int *));
	x = malloc(Nline*sizeof(double *));
	y = malloc(Nline*sizeof(double *));

	for (i=0 ; i<Nline ; i++)
	{
		x[i]=malloc((BuffLength-1)*sizeof(double));
		y[i]=malloc((BuffLength-1)*sizeof(double));
		z[i]=malloc((BuffLength-1)*sizeof(int));
	}

	f=fopen("scan.dat","r");
	for (i=0 ; i<Nline ; i++)
	{
		for 
	}
}
