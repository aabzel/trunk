#include "voltage_divider.h"

#include "log.h"

#define VAL_2_MVAL(VAL) ((VAL)*1000.0)

double volt_div_calc_u_out(double r_vcc_om, double r_gnd_om, double u_in_v) {
    LOG_INFO(VOLTAGE_DIVIDER, "U_in %f V, R_gnd %f Om, R_vcc %f Om", u_in_v, r_gnd_om, r_vcc_om);
    double i_through = 0.0;
    double u_out = 100.0;
    double r_total = r_vcc_om + r_gnd_om;
    if(0.0 < r_total) {
        i_through = u_in_v / r_total;
        double power = i_through * u_in_v;
        LOG_INFO(VOLTAGE_DIVIDER, "Current %f mA, Power %f mW", VAL_2_MVAL(i_through), VAL_2_MVAL(power));
        u_out = i_through * r_gnd_om;
    } else {
        LOG_ERROR(VOLTAGE_DIVIDER, "ArgErr %f Om", r_total);
    }
    return u_out;
}

double volt_div_calc_r_gnd(double r_vcc_om, double u_in_v, double u_out_v) {
    double r_gnd = 0.0;
    LOG_INFO(VOLTAGE_DIVIDER, "R_vcc %f Om U_in:%f V U_out:%f V", r_vcc_om, u_in_v, u_out_v);
    if(u_out_v < u_in_v) {
        r_gnd = u_out_v * r_vcc_om / (u_in_v - u_out_v);
    } else {
        LOG_ERROR(VOLTAGE_DIVIDER, "U_in> U_out U_in %f U_out %f", u_in_v, u_out_v);
    }
    return r_gnd;
}

double volt_div_calc_r_vcc(double r_gnd_om, double u_in_v, double u_out_v) {
    double r_vcc = 0.0;
    if(0.0 < u_out_v) {
        r_vcc = r_gnd_om * (u_in_v - u_out_v) / u_out_v;
    } else {
        LOG_ERROR(VOLTAGE_DIVIDER, "U_out %f Err", u_out_v);
    }
    return r_vcc;
}
