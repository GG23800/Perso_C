#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>


char * convert_point(int *tempi , int length)
{
	int16_t temp16[length];
	int i=0;

	for (i=0 ; i<length ; i++)
	{
		temp16[i]=(int16_t)tempi[i];
		printf("temp16[%i] = %i\n",i,temp16[i]);
	}

	char * tmp=(char *)temp16;	
	return tmp;
}

void inv_conv(char *tempc , int length, int *tempi)
{
	int16_t *temp16=(int16_t *)tempc;
	int i=0;

	for (i=0 ; i<length ; i++)
	{
		tempi[i]=(int)temp16[i];
	}
}

int main (int agrc, char **argv)
{
	int *tempi=NULL;

	int Nb=16, i=0;

	tempi=(int *)malloc(Nb*sizeof(int));
	//char *tempc=(char *)tempi;
	//int *pointi=(int *)tempc;

	for (i=0 ; i<Nb ; i++)
	{tempi[i]=-61*i;}

	char *tempc=convert_point(tempi , Nb);

	for (i=0 ; i<Nb ; i++){printf("tempi[%i] = %i\n",i,tempi[i]);}
	for (i=0 ; i<2*Nb ; i++){printf("tempc[%i] = %i\n",i,(int)tempc[i]);}

	inv_conv(tempc, Nb, tempi);
	for (i=0 ; i<Nb ; i++){printf("pointi[%i] = %i\n",i,tempi[i]);}

	printf("timestamp: %i\n",(int)time(NULL));
	printf("sizeof(tempi) = %lu\n",sizeof(tempc));

	free(tempi);
	return 0;
}
