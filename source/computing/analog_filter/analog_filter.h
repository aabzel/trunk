#ifndef ANALOG_FILTER_H
#define ANALOG_FILTER_H

#include <stdbool.h>

#include "analog_filter_dep.h"

bool analog_filter_cap_calc(char *const text, double *const capacity);
double filter_lc_calc_f_cut_hz(double incuctance_henri, double capasity_farad);
double filter_rc_calc_f_cut_hz(double resistance_om, double capasity_farad);

#endif /* ANALOG_FILTER_H */
