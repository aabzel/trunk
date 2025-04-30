#include "gnss_commands.h"

#include <stdbool.h>
#include <stdint.h>

#include "array_diag.h"
#include "convert.h"
#include "gnss_diag.h"
#include "gnss_drv.h"
#include "gnss_types.h"
#include "log.h"
#include "time_diag.h"
#ifdef HAS_PARAM
#include "param_drv.h"
#endif

bool gnss_data_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = print_time_date("GNSS:", &Gnss.time_date, true);
        res = print_coordinate("GNSS:", Gnss.coordinate_cur, true);
        LOG_INFO(GNSS, "height %f m", Gnss.height_m);
    } else {
        LOG_ERROR(GNSS, "Usage: gnss");
    }
    return res;
}

bool gnss_set_location_command(int32_t argc, char* argv[]) {
    bool res = false;
    GnssCoordinate_t Coordinate = {0.0, 0.0};
    if(1 <= argc) {
        res = try_str2double(argv[0], &Coordinate.phi);
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &Coordinate.lambda);
    }

    if(res) {
        LOG_INFO(GNSS, "Set [%s]", coordinate2str(&Coordinate));
        res = false;
#ifdef HAS_PARAM
        res = param_set(PAR_ID_TRUE_LOCATION, (uint8_t*)&Coordinate);
#endif
        if(res) {
            LOG_INFO(GNSS, "Set [%s] Ok", coordinate2str(&Coordinate));
        } else {
            LOG_ERROR(GNSS, "Set [%s] Err", coordinate2str(&Coordinate));
        }
    }
    return res;
}

bool gnss_doppler_command(int32_t argc, char* argv[]) {
    bool res = false;
    double velocity_mps = 0.0;
    double freq_tx_hz = FREQ_L1_HZ;
    double freq_rx_hz = 0.0;
    if(1 <= argc) {
        res = try_str2number(argv[0], &freq_tx_hz);
    }

    if(2 <= argc) {
        res = try_str2number(argv[1], &velocity_mps);
    }

    if(res) {
        LOG_INFO(GNSS, "Freq:%f Hz,Volocity:%f m/s", freq_tx_hz, velocity_mps);
        res = false;
        res = gnss_doppler_freq_calc(velocity_mps, freq_tx_hz, &freq_rx_hz);
        if(res) {
            double freq_err_hz = freq_rx_hz - freq_tx_hz;
            LOG_INFO(GNSS, "FreqRx:%f Hz,Diff:%f Hz", freq_rx_hz, freq_err_hz);
        } else {
            LOG_ERROR(GNSS, "CalcErr");
        }
    }
    return res;
}

/*
 * glo 9.548M 38.192M 1
 * glo 4092000 0 16368000 1
 * glo 4092000 90 16368000 1
 * glo 4092000 -90 16368000 1
 *
 * glo 4092000 180 16368000 1
 * glo -10000  16368000 2
 * 0,1,0,-1,0,1,0,-1,0,1,0,-1,0,1,0,-1,0,1,0,-1,0
 * */
bool gnss_generate_lo_command(int32_t argc, char* argv[]) {
    bool res = false;
    int32_t lo_freq_hz = 0;

    int32_t phase_deg = 0;
    SignalType_t signal_type = SIGNAL_SIN;
    uint32_t adc_freq_hz = 0.0;

    if(1 <= argc) {
        res = try_str2int32(argv[0], &lo_freq_hz);
        if(false == res) {
            LOG_ERROR(GNSS, "Arg1 FreqErr %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], &phase_deg);
        if(false == res) {
            LOG_ERROR(GNSS, "Arg1 PhaseDeg %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2int32(argv[2], &adc_freq_hz);
    }

    if(4 <= argc) {
        res = try_str2uint8(argv[3], &signal_type);
    }

    if(res) {
        set_log_level(GNSS, LOG_LEVEL_DEBUG);
        int8_t samples[512] = {0};

        LOG_INFO(GNSS, "GenerateSignal Freq:%d Hz,Phase:%d Deg,ADCfreq:%u Hz", lo_freq_hz, phase_deg, adc_freq_hz);
        res =
            generate_local_oscilator_signal(lo_freq_hz, phase_deg, samples, sizeof(samples), adc_freq_hz, signal_type);
        if(res) {
            array_i8_print(samples, sizeof(samples));
            cli_printf(CRLF);
        } else {
            LOG_ERROR(GNSS, "GenerateErr");
        }
        set_log_level(GNSS, LOG_LEVEL_INFO);
    } else {
        LOG_ERROR(GNSS, "Usage: glo LoFreq ADCsampleRate Signal");
    }
    return res;
}

bool gnss_carr_pahse_err_command(int32_t argc, char* argv[]) {
    bool res = false;
    int32_t i_val = 0;
    int32_t q_val = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2int32(argv[0], &i_val);
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], &q_val);
    }

    if(res) {
        LOG_INFO(GNSS, "I:%d,Q:%d", i_val, q_val);
        float phase_err_deg = calc_carrier_phase_err_deg(i_val, q_val);
        LOG_INFO(GNSS, "PhaseErr:%f Deg", phase_err_deg);
    }

    return res;
}
