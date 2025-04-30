#include "analog_filter.h"

#include <math.h>
#include <stdio.h>

#include "convert.h"
#include "log.h"
#include "num_to_str.h"
#include "utils_math.h"

// https://tel-spb.ru/rc.html
double filter_rc_calc_f_cut_hz(double resistance_om, double capasity_farad) {
    double f_cut_hz = 0.0;
    double tau_s = resistance_om * capasity_farad;
    double denominator = 2.0 * M_PI * resistance_om * capasity_farad;
    f_cut_hz = 1.0 / denominator;
    char lText[200] = {0};
    snprintf(lText, sizeof(lText), "%sR:%s Om,", lText, DoubleToStr(resistance_om));
    snprintf(lText, sizeof(lText), "%sC:%s F,", lText, DoubleToStr(capasity_farad));
    snprintf(lText, sizeof(lText), "%sFcut:%s Hz,", lText, DoubleToStr(f_cut_hz));
    snprintf(lText, sizeof(lText), "%sTau:%s s,", lText, DoubleToStr(tau_s));
    snprintf(lText, sizeof(lText), "%s 1/Tau:%s Hz,", lText, DoubleToStr(1.0 / tau_s));
    LOG_INFO(ANALOG_FILTER, "%s", lText);
    return f_cut_hz;
}

double filter_lc_calc_f_cut_hz(double incuctance_henri, double capasity_farad) {
    double f_cut_hz = 0.0;
    LOG_INFO(ANALOG_FILTER, "L:%f H,C:%f F, Fcut:%f Hz", incuctance_henri, capasity_farad, f_cut_hz);
    return f_cut_hz;
}

bool analog_filter_cap_calc(char* const in_text, double* const capacity) {
    bool res = false;
    if(in_text) {
        if(capacity) {

            size_t len = strlen(in_text);
            if(3 == len) {
                res = is_dec_str(in_text, len);
                if(res) {
                    uint8_t mantissa = 0;
                    res = try_strl2uint8(in_text, 2, &mantissa);
                    if(res) {
                        uint8_t exp = 0;
                        res = try_strl2uint8(&in_text[2], 1, &exp);
                        if(res) {
                            double exponent = pow(10.0, (double)exp);
                            double real_value = ((double)mantissa) * exponent * pow(10.0, -12.0);
                            *capacity = real_value;
                            LOG_INFO(ANALOG_FILTER, "Cap:%f=%sF", real_value, DoubleToStr(real_value));
                            res = true;
                        } else {
                            LOG_ERROR(ANALOG_FILTER, "ExpErr");
                            res = false;
                        }
                    } else {
                        LOG_ERROR(ANALOG_FILTER, "MantissaErr");
                        res = false;
                    }
                } else {
                    LOG_ERROR(ANALOG_FILTER, "DecErr");
                    res = false;
                }
            } else {
                LOG_ERROR(ANALOG_FILTER, "LenErr");
                res = false;
            }
        }
    } else {
        res = false;
    }
    return res;
}
