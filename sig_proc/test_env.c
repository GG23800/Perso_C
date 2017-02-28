#include <stdio.h>
#include <stdlib.h>

#include "signal_processing.h"

void write_file (double *sig, int length, char *name)
{
	FILE *f;
	f=fopen(name, "w+");
	int i=0;
	
	for (i=0 ; i<length ; i++)
	{
		fprintf(f, "%f ",sig[i]);
	}
	
	fclose(f);
}

void load_line(double *image, int row, char *name)
{
        FILE *h=NULL;
        int tmp=0;

        h=fopen(name,"r");
        if (h==NULL)
        {
                printf("file not found\n");
        }
        else
        {
                int i=0, j=0;
                for (i=0 ; i<1 ; i++)
                {
                        for (j=0 ; j<row ; j++)
                        {
                                fscanf(h, "%i", &tmp);
                                image[j]=(double)tmp;
                        }
                }
                fclose(h);
        }
}


int main (int argc, char *argv[])
{
	int len=8445, pad_len=0;
        int powd;
        double *sig=NULL, *pad=NULL, *env=NULL;
        int i=0;

        sig=(double *)malloc(len*sizeof(double));

        if (power_two(len,&powd)){powd++;}
        pad_len=int_pow(2,powd);
        printf("pad_len = %i\n",pad_len);
        pad=(double *)malloc(pad_len*sizeof(double));
	env=(double *)malloc(pad_len*sizeof(double));

	/*double f=3500000.0;
	double om=2*PI*f;
	double tech=0.1/f;

	double *t=NULL;
	t=(double *)malloc(len*sizeof(double));

	t[0]=0.0;
	for (i=1 ; i<len ; i++) {t[i]=t[i-1]+tech;}
	for (i=0 ; i<len ; i++)
	{sig[i]=cos(om*t[i])*exp(-pow(2000000.0*(t[i]-200.0*tech),2.0));}*/

	double f=125000000.0;

	load_line(sig, len, "line.txt");

        zero_padding(sig, pad, len, pad_len, 1);
	write_file(pad, pad_len, "zero_pad.txt");

	envelope(pad, env, pad_len, f, 500000.0, 5500000.0, 0);

	write_file(env, pad_len, "env.txt");

	return 0;
}
