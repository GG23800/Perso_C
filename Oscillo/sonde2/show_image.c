#include<stdio.h> //for printf
#include<stdlib.h> //for exit()
#include<unistd.h> //for usleep()

#include"gnuplot_i.h"

int main(int arg, char *argv[])
{
	int Npoint=2111;
	int Nline=128;
	int i=0, j=0;
	int **z;
	z=(int **)malloc(Nline*sizeof(int *));
	for (i=0 ; i<Nline ; i++){z[i]=(int *)malloc(Npoint*sizeof(int));}

	int k=0, image=64;
	gnuplot_ctrl * h;
	h=gnuplot_init();
        gnuplot_cmd(h, "set pm3d map");
        gnuplot_cmd(h, "set palette gray");

	FILE *f;
	char name[50];
	int tmp=0;

	for (k=17 ; k<=image ; k++)
	{
		printf("k=%i\n",k);
		sprintf(name, "support%i.txt",k);
		f=fopen(name, "r");
		for (i=0 ; i<Nline ; i++)
		{
			for (j=0 ; j<Npoint ; j++)
			{
				fscanf(f,"%i",&tmp);
				z[i][j]=tmp;
			}
		}
		fclose(f);
		gnuplot_matrix(h, z, Npoint, Nline);
		usleep(500000);
	}
	gnuplot_close(h);
	free(z);
	return 0;
}
