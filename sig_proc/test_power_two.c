#include <stdio.h>
#include <stdlib.h>

#include "signal_processing.h"

int main (int argc, char *argv[])
{
	int x=int_pow(2,0);
	printf("x = %i\n",x);
	int pow;
	int y=x;

	//y=int_pow(3,3);
	//printf("3^3 = %i\n",y);

	//printf("if condition: %i\n",power_two(x,&pow));
	//if (power_two(x,&pow)){y=int_pow(2,pow+1);}
	//printf("power : %i\n",pow);
	//printf("y = %i\n",y);

	int j=0;
	for (j=0 ; j<31 ; j++)
	{
		printf("j = %i\n",j);
		x=int_pow(2,j)+12;
		if (power_two(x,&pow)) {y=pow+1;}
		else {y=pow;}
		printf("power = %i\n",y);
	}

	return 0;
}
