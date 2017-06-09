#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

void load_image(int line, int row, int16_t** data, char* name)
{
        FILE *h=NULL;
        int tmp=0;
	int err=0;
        
        h=fopen(name,"r");
        if (h==NULL)
        {       
                printf("file not found\n");
        }
        else
        {       
                int i=0, j=0;
                for (i=0 ; i<row ; i++)
                {       
                        for (j=1 ; j<=line ; j++)
                        {       
                                err=fscanf(h, "%i", &tmp);
				if (err==42){printf("err=1...\n");}
                        	data[i][j]=(int16_t)tmp;
                        }
                }       
                fclose(h);
        }
}

int main (int agrc, char **argv)
{
	FILE *h;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
 
	h = fopen("test.txt", "r");
	if (h == NULL)
		exit(EXIT_FAILURE);

	int i=0;
	for (i=0 ; i<9 ; i++)
	{
		if ((read = getline( &line, &len, h)) != 1)
		{
			printf("line number %i\n",i);
			printf("line red: %s\n",line);
		}
		else {printf("error while getline\n");}
	}

	int err=0, tmp=0;

	for (i=0 ; i<9 ; i++)
	{
		if ((err=fscanf(h,"%i",&tmp))!=2)
		{
			printf("data[x][%i] = %i\n",i,tmp);
		}
		else 
		{
			printf("err=%i\n",err);
			printf("error while fscanf\n");
		}
	}
 
	/*
	while ((read = getline(&line, &len, h)) != -1) {
		printf("Retrieved line of length %zu :\n", read);
		printf("%s", line);
	}//from rosetta code getline: https://www.rosettacode.org/wiki/Read_a_file_line_by_line#C
	*/
 
	free(line);
	fclose(h);
	exit(EXIT_SUCCESS);
}
