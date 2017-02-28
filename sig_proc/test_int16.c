#include <stdio.h>
#include <stdlib.h>

#include "signal_processing.h"

/*void write_file (double *sig, int length, char *name)
{
	FILE *f;
	f=fopen(name, "w+");
	int i=0;
	
	for (i=0 ; i<length ; i++)
	{
		fprintf(f, "%f ",sig[i]);
	}
	
	fclose(f);
}*/

/*void load_line(double *image, int row, char *name)
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
}*/


int main (int argc, char *argv[])
{
	int len=8445, pad_len=0, line=128;;
        int powd;
        double **sig=NULL, **pad=NULL, **env=NULL, **env2=NULL;
        int i=0;


        if (power_two(len,&powd)){powd++;}
        pad_len=int_pow(2,powd);
        printf("pad_len = %i\n",pad_len);

        sig=(double **)malloc(len*sizeof(double *));
        pad=(double **)malloc(pad_len*sizeof(double *));
	env=(double **)malloc(pad_len*sizeof(double *));
	env2=(double **)malloc(pad_len*sizeof(double *));

	for (i=0 ; i<len ; i++)
	{
		sig[i]=(double *)malloc(line*sizeof(double));
		pad[i]=(double *)malloc(line*sizeof(double));
		env[i]=(double *)malloc(line*sizeof(double));
		env2[i]=(double *)malloc(line*sizeof(double));
	}
	for (i=len ; i<pad_len ; i++)
	{
		pad[i]=(double *)malloc(line*sizeof(double));
		env[i]=(double *)malloc(line*sizeof(double));
		env2[i]=(double *)malloc(line*sizeof(double));
	}

	double f=125000000.0;

	load_image(sig, len, line, "int10.txt");
	//write_image(sig, len, line, "im_pad.txt");

	zero_padding_matrix(sig, pad, len, line, pad_len, 1);
	write_image(pad, pad_len, line, "im_pad.txt");

	envelope_matrix(pad, env, pad_len, line, f, 500000.0, 5500000.0, 0);
	
	write_image(env, len, line, "im_env.txt");

	gray_log(env, env2, len, line);

	write_image(env2, len, line, "im_log.txt");

	filter_image(env, env2, len, line);
	write_image(env2, len, line, "im2_env.txt");

	free(sig);
	free(pad);
	free(env);
	free(env2);
	
	return 0;
}
