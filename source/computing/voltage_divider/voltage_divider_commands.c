#include "voltage_divider_commands.h"

#include "convert.h"
#include "log.h"
#include "voltage_divider.h"

bool voltage_divider_calc_command(int32_t argc, char* argv[]) {
    bool res = false;
    double r_gnd_om = 100000.0;
    double r_vcc_om = 100000.0;
    double u_in_v = 3.3;

    if(1 <= argc) {
        res = try_str2number(argv[0], &r_gnd_om);
        if(false == res) {
        }
    }

    if(2 <= argc) {
        res = try_str2number(argv[1], &r_vcc_om);
        if(false == res) {
        }
    }

    if(3 <= argc) {
        res = try_str2number(argv[2], &u_in_v);
        if(false == res) {
        }
    }

    if(res) {
        LOG_INFO(VOLTAGE_DIVIDER, "In:R_gnd:%f Om,R_vcc:%f Om", r_gnd_om, r_vcc_om);
        double u_out = volt_div_calc_u_out(r_vcc_om, r_gnd_om, u_in_v);
        double div = u_in_v / u_out;
        double scale = div;
        LOG_INFO(VOLTAGE_DIVIDER, "Uout:%f Volts,Div:1/%f,Scale:%f", u_out, div, scale);
    } else {
        LOG_ERROR(VOLTAGE_DIVIDER, "Usage: vc Rgnd Rvcc Vin");
    }
    return res;
}
