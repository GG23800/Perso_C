#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "Cfft.h"
#include <time.h>
 
typedef double complex cplx;
 
time_t top_chrono;
 
void demarrer_chrono() {
        top_chrono = clock();
}
 
void stop_chrono() {
        time_t arret_chrono = clock();
        printf("Le calcul a pris %f secondes.\n",
                (float)(arret_chrono - top_chrono) / CLOCKS_PER_SEC);
}

 
int main()
{
	float fe=1.25e+08 , f0=1.0e+06 , fm=6.0e+06;
	int n=16384;
	double buf0[n];
	cplx buf[n];

	FILE *ft;
	ft = fopen ("sig_test.txt","r");
	for (int i = 0 ; i<n ; i++) {
	fscanf(ft , "%lf" , &buf0[i]);
	buf[i] = (complex) buf0[i];
	}
	fclose (ft);

	FILE *ff;
	ff = fopen ("sig_fft.txt" , "w+");
 
	demarrer_chrono();
	fft (buf,n);
	stop_chrono();
	for (int i = 0 ; i < n ; i++){fprintf(ff , "%e %e\n", creal(buf[i]) , cimag(buf[i]) );}
	fclose(ff);

	FILE *fs;
	fs=fopen("sig_ifft.txt" , "w+");

	demarrer_chrono();
	ifft(buf,n);
	stop_chrono();
	for (int i = 0 ; i < n ; i++){fprintf(fs , "%e\n" , creal(buf[i]) );}
	fclose(fs);

	FILE *fht;
	fht=fopen("sig_ht0.txt" , "w+");
	demarrer_chrono();
	ht(buf0, n , fe , f0 , fm , 0);
	stop_chrono();
	for (int i = 0 ; i < n ; i++){fprintf(fht , "%e\n" , buf0[i] );}
	fclose(fht);

	cplx test0[n];
	cplx test1[n];
	cplx test2[n];

	for (int i=0 ; i<n ; i++){
	test0[i]=(complex)1.0;
	test1[i]=(complex)1.0;
	test2[i]=(complex)1.0;
	}

	filter(test1, n , fe , f0 , fm , 1);
	filter(test2, n , fe , f0 , fm , 2);
	FILE *ff1;
	ff1=fopen("sig_ham.txt" , "w+");
	FILE *ff2;
	ff2=fopen("sig_bla.txt" , "w+");
	for (int i = 0 ; i < n ; i++){
	fprintf(ff1 , "%e\n" , creal(test1[i]));
	fprintf(ff2 , "%e\n" , creal(test2[i]));
	}
	fclose(ff1);
	fclose(ff2);

	return 0;
}
