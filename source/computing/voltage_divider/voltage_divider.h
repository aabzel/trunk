
#ifndef VOLTAGE_DIVIDER_H
#define VOLTAGE_DIVIDER_H

#include "voltage_divider_dep.h"

double volt_div_calc_u_out(double r_vcc_om, double r_gnd_om, double u_in_v);

double volt_div_calc_r_gnd(double r_vcc_om, double u_in_v, double u_out_v);
double volt_div_calc_r_vcc(double r_gnd_om, double u_in_v, double u_out_v);

#define VOLT_DIV_CALC_R_GND(R_VCC_OM, U_IN_V, U_OUT_V) (((U_OUT_V) * (R_VCC_OM)) / ((U_IN_V) - (U_OUT_V)))

#endif /* VOLTAGE_DIVIDER_H */
