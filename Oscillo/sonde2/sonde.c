#include<stdio.h> //for printf
#include<stdlib.h> //for exit()
#include<time.h> //for timestamp

#include"gnuplot_i.h"
#include"TCP_API.h"
#include<math.h>

#define Port 7538

float x0=0.0, xf=0.0;
int Nline=0, dec=0, Npoint=0;
double sector=0.0;
int mode_RP;

void writefile (int **z, int line, int row, char *name)
{
	int i, j;
	FILE * f;
	f = fopen(name,"w+");
	fprintf(f, "#timestamp:%i\n",(int)time(NULL));
	fprintf(f, "#lines:%i\n",Nline);
	fprintf(f, "#length:%i\n",Npoint);
	fprintf(f, "#frequency:%f\n",125.0/((float)dec));
	fprintf(f, "#piezofrequency:3.5\n");
	fprintf(f, "#angle:%f\n",sector);
	fprintf(f, "#r0:%f\n",x0);
	fprintf(f, "#rf:%f\n",xf);
	for (i=0 ; i<line ; i++)
	{
		for (j=0 ; j<row ; j++)
		{
			fprintf(f, "%i ", z[i][j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
}

void writefileicsv (int **z, int line, int row, char *name)
{
        int i, j;
        FILE * f;
        f = fopen(name,"w+");
        fprintf(f, "#timestamp:%d\n",(int)time(NULL));
        fprintf(f, "#lines:%i\n",Nline);
        fprintf(f, "#length:%i\n",Npoint);
        fprintf(f, "#frequency:%f\n",125.0/((float)dec));
        fprintf(f, "#piezofrequency:3.5\n");
        fprintf(f, "#angle:%f\n",sector);
        fprintf(f, "#r0:%f\n",x0);
        fprintf(f, "#rf:%f\n",xf);
        for (i=0 ; i<line ; i++)
        {
                for (j=0 ; j<row ; j++)
                {
                        fprintf(f, "%i,", z[i][j]);
                }
                fprintf(f,"\n");
        }
        fclose(f);
}

int init_xy (double **x, double **y)
{
        int i, j;
        double deltar, deltatheta, anglerad, anglemin;
        double *r = (double *)malloc(Npoint*sizeof(double));
        double *theta = (double *)malloc(Nline*sizeof(double));

        deltar = (double)(xf-x0)/(double)(Npoint-1);
        anglerad = sector*M_PI/180.0;
        deltatheta = anglerad/(double)(Nline-1);
        anglemin = -anglerad/2.0;

        for (i=0 ; i<Npoint ; i++)
        {
                r[i] = (double)(x0)+(double)(i)*deltar;
        }
        for (i=0 ; i<Nline ; i++)
        {
		theta[i]=anglemin+(double)(i)*deltatheta;
                for (j=0 ; j<Npoint ; j++)
                {
                        x[i][j]=r[j]*cos(theta[i]);
                        y[i][j]=r[j]*sin(theta[i]);
                }
        }

        free(r);
        free(theta);
        return 0;
}

int main(int arg, char *argv[])
{
	//socket variable
	SOCKET sock;
	const char *IP="192.168.128.3";
	init_TCP_client(&sock, IP, Port);
        get_RP_settings(&sock);
        printf("x0=%f\n",x0);
        printf("xf=%f\n",xf);
        printf("dec=%i\n",dec);
        printf("Nline=%i\n",Nline);
        printf("sector=%f\n",sector);
	printf("mode_RP=%i\n",mode_RP);

	char name[50];

	Npoint=(int)(2.0*(xf-x0)*125.0/1.48/((double)dec));
	if (Npoint>16384){Npoint=16384;}
	printf("Npoint = %i\n",Npoint);

	//gnuplot variable
	gnuplot_ctrl * h;
	int i, j;

	double **x = NULL;
        double **y = NULL;
        int **z = (int **)malloc(Nline*sizeof(int *));
        x = malloc(Nline*sizeof(double *));
        y = malloc(Nline*sizeof(double *));

        for (i=0 ; i<Nline ; i++)
        {
                x[i]=malloc((Npoint)*sizeof(double));
                y[i]=malloc((Npoint)*sizeof(double));
                z[i]=malloc((Npoint)*sizeof(int));
        }

        init_xy(x,y);

	//gnuplot object
	h=gnuplot_init();
	gnuplot_cmd(h, "set pm3d map");
	gnuplot_cmd(h, "set palette gray");

	int k=1, line=0, l=0;

	if (mode_RP==0)
	{
		int16_t *buff=(int16_t *)malloc((Npoint+1)*sizeof(int16_t));
		while(k)
		{
			for (i=0 ; i<Nline ; i++)
			{
				if (receive_int16_TCP_client(&sock, buff, Npoint+1)==1)
				{
					i=Nline+2;
					k=0;
					break;
				}
	
				if(i<Nline+2)
				{
					line=(int)buff[0]-1;
					for (j=0 ; j<Npoint ; j++) {z[line][j]=(int)buff[j+1];}
				}
			}
			gnuplot_matrix(h, z, Npoint, Nline);
			//sprintf(name, "toto%i.txt", l);
			//writefile(z, Nline, Npoint, name);
			l++;
		}
		free(buff);
	}

	else if (mode_RP==1)
	{
		char *buff=(char *)malloc((Npoint+1)*sizeof(char));
		while(k)
		{
			for (i=0 ; i<Nline ; i++)
			{
				if (receive_TCP_client(&sock, buff, Npoint+1)==1)
				{
					i=Nline+2;
					k=0;
					break;
				}
	
				if(i<Nline+2)
				{
					line=int_converter(buff[0])-1;
					for (j=0 ; j<Npoint ; j++) {z[line][j]=int_converter(buff[j+1]);}
				}
			}
			gnuplot_matrix(h, z, Npoint, Nline);
			//sprintf(name, "toto%i.txt", l);
			//writefile(z, Nline, Npoint, name);
			l++;
		}
		free(buff);
	}

	else {printf("problem with RP settings\n");}


	/*int k=1, line=0, l=0;
	while(k)
	{
		for (i=0 ; i<Nline ; i++)
		{
			if (receive_TCP_client(&sock, buff, Npoint+1)==1)
			{
				i=Nline+2;
				k=0;
				break;
			}
			
			if (i<Nline+2)
			{
				line=int_converter(buff[0])-1;
				for (j=0 ; j<Npoint-1 ; j++)
				{
					//z[line][j]=(int)buff[j+1];
					z[line][j]=int_converter(buff[j+1]);
				}
			}
		}
		gnuplot_matrix(h, z, Npoint, Nline);	
		//sprintf(name, "main%i.txt",l);
		//writefile(z, Nline, Npoint, name);
		l++;
	}*/

	usleep(30);
	close(sock);
	free(x);
	free(y);
	free(z);
	return 0;
}
