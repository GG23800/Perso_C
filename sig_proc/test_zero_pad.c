#include <stdio.h>
#include <stdlib.h>

#include "signal_processing.h"

int main (int argc, char *argv[])
{
	int len=24, pad_len=0;
	int pow;
	double *sig=NULL, *pad=NULL;
	int i=0;

	sig=(double *)malloc(len*sizeof(double));

	if (power_two(len,&pow)){pow++;}
	pad_len=int_pow(2,pow);
	printf("pad_len = %i\n",pad_len);
	pad=(double *)malloc(int_pow(2,pow)*sizeof(double));

	for (i=0 ; i<len ; i++){sig[i]=1;}

	zero_padding(sig, pad, len, pad_len);

	printf ("sig pad = \n");
	for (i=0 ; i<pad_len ; i++){printf("%f ",pad[i]);}
	printf("\n");

	return 0;
}
