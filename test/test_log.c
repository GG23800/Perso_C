#include<stdio.h>
#include<stdlib.h>

#include<math.h>

void writefile (double **x, double **y, double **z, int line, int row)
{
	int i, j;
	FILE * f;
	f = fopen("scan05log.dat", "w+");
	for (i=0 ; i<row ; i++)
	{
		for (j=0 ; j<line ; j++)
		{
			fprintf(f, "%f %f %f\n", x[i][j], y[i][j], z[i][j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
}

int main(int arg, char * argv[])
{
	FILE *fr=NULL;
	char *line=NULL; //line read by getline
	size_t len=0; //give the length of the string array
	ssize_t read; //to check if we reach the end of the file

	int nline=0, nrow=0; //to determine the size of the 2D array
	int i=0, j=0; //loop variable

	fr=fopen("scan05.dat","r");
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
	x=(double **)malloc(nrow*sizeof(double *));
	y=(double **)malloc(nrow*sizeof(double *));
	z=(double **)malloc(nrow*sizeof(double *));
	int temp=0;
	float tempx=0.0, tempy=0.0;

	for (i=0 ; i<nrow ; i++)
	{
		x[i]=(double *)malloc(nline*sizeof(double));
		y[i]=(double *)malloc(nline*sizeof(double));
		z[i]=(double *)malloc(nline*sizeof(double));
	}

	fr=fopen("scan05.dat","r");
	if (fr==NULL) 
	{
	printf("failed to open a second time the file\n");
	return 1;
	}

	for (j=0 ; j<nrow ; j++)
	{
		for (i=0 ; i<nline ; i++)
		{
			fscanf(fr,"%f %f %i",&tempx,&tempy,&temp);
			temp=(temp+256)%256;
			x[j][i]=(double)tempx;
			y[j][i]=(double)tempy;
			z[j][i]=20.0*log10((double)temp);
		}
		read=getline(&line, &len, fr);
	}

	fclose(fr);
        
        writefile(x,y,z,nline,nrow);

	free(x);
	free(y);
	free(z);
	return 0;
}
