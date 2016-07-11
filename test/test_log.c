#include<stdio.h>
#include<stdlib.h>

int main(int arg, char * argv[])
{
	FILE *fr=NULL;
	char *line=NULL; //line read by getline
	size_t len=0; //give the length of the string array
	ssize_t read; //to check if we reach the end of the file

	int nline=0, nrow=0; //to determine the size of the 2D array
	int i=0, j=0; //loop variable

	fr=fopen("scan01.dat","r");
	if (fr==NULL)
	{
		printf("file not found\n");
		return(-1);
	}

	while((read=getline(&line, &len, fr))!=-1)
	{
		//printf("Line length = %zu\n",read);
		//printf("line: %s\n",line);
		if (read>1 && nrow==0){nline++;}
		if (read==1){nrow++;}
	}
	fclose(fr);
	printf("nline=%i\n",nline);
	printf("nrow=%i\n",nrow);

	double ** x=NULL;
	double ** y=NULL;
	double ** z=NULL;
	x=(double **)malloc(nline*sizeof(double *));
	y=(double **)malloc(nline*sizeof(double *));
	z=(double **)malloc(nline*sizeof(double *));

	for (i=0 ; i<nline ; i++)
	{
		x[i]=(double *)malloc(nrow*sizeof(double));
		y[i]=(double *)malloc(nrow*sizeof(double));
		z[i]=(double *)malloc(nrow*sizeof(double));
	}

	fr=fopen("scan01.dat","r");
	if (fr==NULL) 
	{
	printf"failed to open a second time the file\n");
	return 1;
	}

	//usage, double boucle avec fscanf
	//quand on arrive oà l'espage faire getline

	fclose(fr);
	/*
	now define the 2D double pointer x, y, z
	use fscanf, dont forget to cast z as a double
	*/

	free(x);
	free(y);
	free(z);
	return 0;
}
