#ifndef CFFT_H_INCLUDED
#define CFFT_H_INCLUDED

typedef double complex cplx;

void _fft(cplx buf[], cplx out[], int n, int step) ; 

void fft(cplx buf[], int n) ;

void _ifft(cplx buf[], cplx out[], int n, int step) ; 

void ifft(cplx buf[], int n) ;

void filter(cplx buf[], int n , float fech , float f0 , float fm , int methode) ;

void ht(double sig[], int n, float fech, float f0, float fm, int methode) ;

#endif
