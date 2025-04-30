
#ifndef FOURIER_SERIES_TYPES_H
#define FOURIER_SERIES_TYPES_H


#ifdef __cplusplus
extern "C" {
#endif

#include "fourier_series_const.h"

typedef struct {
    double a;/*coefficient for cos*/
    double b;/*coefficient for sin*/
}FourierSeriesCoefficient_t;

typedef struct{
	uint8_t num ;
	bool valid;
    char* file_name;
}FourierSeriesConfig_t;

typedef struct {
	uint8_t num ;
	int32_t line_cnt;
	bool valid;
	FourierSeriesCoefficient_t Coefficient[FS_MAX_ORDER];
	char line[500];
	char out_file_name[50];
	double delta_x;
	double* x;
	double* y;
	double* y_lp;
	double value;
	double value_x;
	double sampling_period_s;
}FourierSeriesHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* FOURIER_SERIES_TYPES_H */
