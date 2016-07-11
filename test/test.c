#include<stdio.h>
#include<stdlib.h>

int main(int arg, char* argv[])
{
	int a=195;
	char c;
	int b,d,e;
	unsigned int f;
	c=(char)a;
	b=(int)c;
	d=(b+256)%256;
	e=c;
	f=c;

	printf("c=%i\n",c);
	printf("b=%i\n",b);
	printf("d=%i\n",d);
	printf("e=%i\n",e);
	printf("f=%i\n",f);
}
