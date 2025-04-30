#include "analog_filter_commands.h"

#include "analog_filter.h"
#include "convert.h"
#include "log.h"
#include "num_to_str.h"

/*
 * rc 10 10n
 * rc 10 10*10**(-9)
 * rc 10    1**(-8)
 * rc 10.0 0.00000001
 *   10**(-8)
 * */
bool analog_filter_rc_calc_command(int32_t argc, char* argv[]) {
    bool res = false;
    double resistance_om = 100000.0;
    double capasity_farad = 100000.0;

    if(1 <= argc) {
        res = try_str2number(argv[0], &resistance_om);
        if(false == res) {
            LOG_ERROR(ANALOG_FILTER, "ParseErr [%s]", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2number(argv[1], &capasity_farad);
        if(false == res) {
            LOG_ERROR(ANALOG_FILTER, "ParseErr [%s]", argv[1]);
        }
    }

    if(res) {
        double f_cut_hz = filter_rc_calc_f_cut_hz(resistance_om, capasity_farad);
        LOG_INFO(ANALOG_FILTER, "Fcut:%f=%s Hz", f_cut_hz, DoubleToStr(f_cut_hz));
    } else {
        LOG_ERROR(ANALOG_FILTER, "Usage: rc R C");
    }
    return res;
}

bool analog_filter_lc_calc_command(int32_t argc, char* argv[]) {
    bool res = false;
    double incuctance_henri = 100000.0;
    double capasity_farad = 100000.0;

    if(1 <= argc) {
        res = try_str2number(argv[0], &incuctance_henri);
        if(false == res) {
        }
    }

    if(2 <= argc) {
        res = try_str2number(argv[1], &capasity_farad);
        if(false == res) {
        }
    }

    if(res) {
        double f_cut_hz = filter_lc_calc_f_cut_hz(incuctance_henri, capasity_farad);
        LOG_INFO(ANALOG_FILTER, "Fcut:%f Hz", f_cut_hz);
    } else {
        LOG_ERROR(ANALOG_FILTER, "Usage: lc L C");
    }
    return res;
}

bool analog_filter_cap_calc_command(int32_t argc, char* argv[]) {
    bool res = false;
    char text[10] = "";
    double capacity = 0.0;
    if(1 <= argc) {
        res = strcpy(text, argv[0]);
        if(false == res) {
        }
    }

    if(res) {
        res = analog_filter_cap_calc(text, &capacity);
        if(res) {
            LOG_INFO(ANALOG_FILTER, "Capacity:[%s]->%sF", text, DoubleToStr(capacity));
        } else {
            LOG_ERROR(ANALOG_FILTER, "ProcErr[%s]", text);
        }
    } else {
        LOG_ERROR(ANALOG_FILTER, "Usage: cc xxx");
    }
    return res;
}
