#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void writefile(char *name)
{
	FILE *f;
	f=fopen(name,"w+");
	int i=0, j=0;
	for (i=0 ; i<10 ; i++)
	{
		for (j=0 ; j<10 ; j++)
		{
			fprintf(f,"%i ",j);
		}
		fprintf(f,"\n");
	}
	fclose(f);
}

int main(int argc, char **argv)
{
	int i=0;
	char name[9];
	for (i=0 ; i<100 ; i++)
	{
		if (i/10*10==i)
		{
			sprintf(name,"file%i.txt",i);
			writefile(name);
		}
	}
}
