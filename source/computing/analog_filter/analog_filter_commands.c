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
bool analog_filter_rc_f_cut_calc_command(int32_t argc, char* argv[]) {
    bool res = false;
    double resistance_om = 100000.0;
    double capasity_farad = 100000.0;

    if(1 <= argc) {
        res = try_str2number(argv[0], &resistance_om);
        log_info_res(ANALOG_FILTER,res,"R");
    }

    if(2 <= argc) {
        res = try_str2number(argv[1], &capasity_farad);
        log_info_res(ANALOG_FILTER,res,"C");
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
        log_info_res(ANALOG_FILTER,res,"L");
    }

    if(2 <= argc) {
        res = try_str2number(argv[1], &capasity_farad);
        log_info_res(ANALOG_FILTER,res,"C");
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
    char lText[10] = "";
    double capacity = 0.0;
    if(1 <= argc) {
        res = strcpy(lText, argv[0]);
        log_info_res(ANALOG_FILTER,res,"Text");
    }

    if(res) {
        res = analog_filter_cap_calc(lText, &capacity);
        if(res) {
            LOG_INFO(ANALOG_FILTER, "Capacity:[%s]->%sF", lText, DoubleToStr(capacity));
        } else {
            LOG_ERROR(ANALOG_FILTER, "ProcErr[%s]", lText);
        }
    } else {
        LOG_ERROR(ANALOG_FILTER, "Usage: cc xxx");
    }
    return res;
}


bool filter_lc_calc_resonant_frequency_hz_command(int32_t argc, char* argv[]){
    bool res = false;
    double capasity_farad = 0.000;

    double incuctance_henri = 0.000650;
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
        double f_cut_hz = filter_lc_calc_resonant_frequency_hz(incuctance_henri, capasity_farad);
        LOG_INFO(ANALOG_FILTER, "Fcut:%f Hz", f_cut_hz);
    } else {
        LOG_ERROR(ANALOG_FILTER, "Usage: lcf0c L C");
    }
    return res;
}

bool analog_capasity_serial_connection_calc_command(int32_t argc, char* argv[]){
    bool res = false;
    double capasity1_farad = 0.000;
    double capasity2_farad = 0.000;

    if(1 <= argc) {
        res = try_str2number(argv[0], &capasity1_farad);
        if(false == res) {
        }
    }

    if(2 <= argc) {
        res = try_str2number(argv[1], &capasity2_farad);
        if(false == res) {
        }
    }

    if(res) {
        double capasity_farad = capasity_serial_connection_calc(capasity1_farad, capasity2_farad);
        LOG_INFO(ANALOG_FILTER, "C1:%f F,C2:%f F,Cap:%f F",capasity1_farad,capasity2_farad, capasity_farad);
    } else {
        LOG_ERROR(ANALOG_FILTER, "Usage: sccc C1 C2");
    }
    return res;
}


bool filter_colpitts_oscillator_command(int32_t argc, char* argv[]){
    bool res = false;
    double capasity1_farad = 0.0001;
    double incuctance_henri = 0.000650;
    double capasity2_farad = 0.0001;

    if(1 <= argc) {
        res = try_str2number(argv[0], &capasity1_farad);
        if(false == res) {
        }
    }

    if(2 <= argc) {
        res = try_str2number(argv[1], &incuctance_henri);
        if(false == res) {
        }
    }

    if(3 <= argc) {
        res = try_str2number(argv[2], &capasity2_farad);
        if(false == res) {
        }
    }

    if(res) {
        double freq_hz = colpitts_oscillator_calc(capasity1_farad, incuctance_henri, capasity2_farad);
        LOG_INFO(ANALOG_FILTER, "Freq:%f Hz", freq_hz);
    } else {
        LOG_ERROR(ANALOG_FILTER, "Usage: co C1 L C2");
    }
    return res;
}
