#include <stdio.h>
#include <math.h>
#include <complex.h>
#include "Cfft.h"

/*-----------------------------------------
C scrit for calculating fft
source from https://rosettacode.org/wiki/Fast_Fourier_transform
-----------------------------------------*/
 
const double PI = 3.141592653589793238460;
typedef double complex cplx;

void _fft(cplx buf[], cplx out[], int n, int step)
{
	if (step < n) {
		_fft(out, buf, n, step * 2);
		_fft(out + step, buf + step, n, step * 2);
 
		for (int i = 0; i < n; i += 2 * step) {
			cplx t = cexp(-I * PI * i / n) * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
		}
	}
}
 
void fft(cplx buf[], int n)
{
	cplx out[n];
	for (int i = 0; i < n; i++) out[i] = buf[i];
 
	_fft(buf, out, n, 1);
}

void _ifft(cplx buf[], cplx out[], int n, int step)
{
	if (step < n) {
		_ifft(out, buf, n, step * 2);
		_ifft(out + step, buf + step, n, step * 2);
 
		for (int i = 0; i < n; i += 2 * step) {
			cplx t = cexp(I * PI * i / n) * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
		}
	}
}
 
void ifft(cplx buf[], int n)
{
	cplx out[n];
	for (int i = 0; i < n; i++) out[i] = buf[i];
 
	_ifft(buf, out, n, 1);
	for (int i = 0 ; i < n ; i++){buf[i] /= n;}
}

void filter(cplx buf[], int n , float fech , float f0 , float fm , int methode)
{
	int n0 , n1 , N;
	n0=(int)(f0*n/fech);
	n1=(int)(fm*n/fech);
	N=n1-n0+1;
	printf("%i %i %i\n", n0 , n1 , N);

	for (int i=0 ; i<n0 ; i++){buf[i]=(complex) 0;}
	for (int i=n1 ; i<n ; i++){buf[i]=(complex) 0;}

	switch(methode) {

		case 0 : //door
			break; // optional

		case 1 : //Hanning: 0.5*(1-cos(2*pi*t/T))
			for (int i=0 ; i<N ; i++){buf[i+n0]*=(complex)(0.5*(1.0-cos(2.0*PI*i/N)));}
			break;

		case 2 : //Blackmann: 0.42-0.5*cos(2*pi*t/T)+0.08*cos(4*pi*t/T)
			for (int i=0 ; i<N ; i++){buf[i+n0]*=(complex)(0.42-0.5*cos(2.0*PI*i/N)+0.08*cos(4.0*PI*i/N));}
			break; 

	}
}

void ht(double sig[], int n, float fech, float f0, float fm, int methode) 
{
	cplx buf[n];

	for (int i=0 ; i<n ; i++) {buf[i] = (complex) sig[i];}
	fft(buf,n);
	filter(buf, n , fech , f0 , fm , methode);
	ifft(buf,n);

	for (int i=0 ; i<n ; i++){sig[i]=cabs(buf[i])*2.0;}
}
