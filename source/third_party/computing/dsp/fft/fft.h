#ifndef __FFT_H__
#define __FFT_H__


#include <complex.h>
#include <math.h>
#include <stdbool.h>

//https://github.com/eugeneyuchunlin/fft-C
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif



//void FFT2N(complex double in[], complex double out[], int size);
/**
 * FFT() - A general FFT for 2^q elements of data
 */
void FFT_CALC(complex double in[], complex double out[], int size);
void IFFT_CALC(complex double in[], complex double out[], int size);



#endif
