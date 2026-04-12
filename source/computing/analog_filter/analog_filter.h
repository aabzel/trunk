#ifndef ANALOG_FILTER_H
#define ANALOG_FILTER_H

#include <stdbool.h>

#include "analog_filter_dep.h"

double filter_lc_calc_resonant_frequency_hz(const double incuctance_henri, const  double capasity_farad);
bool analog_filter_cap_calc(char *const text, double *const capacity);
double filter_lc_calc_f_cut_hz(double incuctance_henri, double capasity_farad);
double filter_rc_calc_f_cut_hz(double resistance_om, double capasity_farad);
double capasity_serial_connection_calc(const double capasity1_farad, const double capasity2_farad);
double colpitts_oscillator_calc(double capasity1_farad,
                                double incuctance_henri,
                                double capasity2_farad);

#endif /* ANALOG_FILTER_H */
