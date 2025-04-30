#include "gnss_drv.h"

#include <complex.h>
#include <string.h>
#include <math.h>

/*GNSS receiver invariant component*/
#include "gnss_utils.h"
#ifdef HAS_CALENDAR
#include "calendar.h"
#endif

#ifdef HAS_NMEA
#include "nmea_protocol.h"
#endif

#ifdef HAS_UBLOX
#include "ublox_driver.h"
#endif
#include "log.h"
#ifdef HAS_PARAM
#include "param_drv.h"
#endif
#include "array.h"
#include "code_generator.h"
#include "time_diag.h"
#include "time_mcal.h"
#include "utils_math.h"

COMPONENT_GET_NODE(Gnss, gnss)
COMPONENT_GET_CONFIG(Gnss, gnss)




#ifdef HAS_SDR
COMPONENT_GET_NODE(LocalOscillator, local_oscillator)
COMPONENT_GET_CONFIG(LocalOscillator, local_oscillator)
#endif

#ifndef HAS_GNSS
#error "It is needed to add HAS_GNSS option"
#endif

#ifdef HAS_NMEA
static bool gnss_update_from_nmea(uint8_t num) {
    bool res = true;
    GnssHandle_t* Node=GnssGetNode(  num);
    if(Node){

      bool res_time = false;
       bool res_dot = false;

    NmeaHandle_t* Nmea=NmeaGetNode(Node->nmea_num);
    if(Nmea) {
        res = is_valid_time_date(&Nmea->time_date);
        if(res) {
            if(Node->first_time) {
                LOG_INFO(GNSS, "SpotValidTimeInNmea!");
                print_time_date("NMEA:", &Nmea->time_date, true);
#ifdef HAS_CALENDAR
                calendar_settime(&Nmea->time_date);
#endif /*HAS_CALENDAR*/
                Node->first_time = false;
            }
            memcpy(&Node->time_date, &Nmea->time_date, sizeof(struct tm));
            res_time = true;
        } else {
            res_time = false;
#ifdef HAS_LOG
            LOG_DEBUG(GNSS, "InvalNmeaTimeDate");
#endif
        }

        if((0.0 < Nmea->height) && (Nmea->height < 15000.0)) {
            Node->height_m = Nmea->height;
        }

        res = is_valid_gnss_coordinates(Nmea->coordinate_dd);
        if(res) {
            if(Node->first_gnss) {
                LOG_INFO(GNSS, "SpotValidGNSSDotInNmea!");
#ifdef HAS_GNSS_DIAG
                print_coordinate("NMEA:", Nmea->coordinate_dd, true);
#endif
                Node->first_gnss = false;
            }
            Node->coordinate_cur = Nmea->coordinate_dd;
            res_dot = true;
        } else {
            res_dot = false;
#ifdef HAS_LOG
            LOG_DEBUG(GNSS, "InvalNmeaGNSSDot");
#endif
        }

        if(res_dot && res_time) {
            res = true;
        } else {
            res = false;
        }
    }
    }
    return res;
}
#endif /*HAS_NMEA*/

#ifdef HAS_UBLOX
static bool gnss_update_from_ubx(uint8_t num) {
        bool res_time = false;
        GnssHandle_t *Node = GnssGetNode(num);
        if(Node){



        bool res_dot = false;
        bool res = true;
        res = is_valid_time_date(&NavInfo.date_time);
        if(res) {
            if(Node->first_time) {
                LOG_INFO(GNSS, "SpotValidTimeInUbx");
                print_time_date("UBX:", &NavInfo.date_time, true);
#ifdef HAS_CALENDAR
                calendar_settime(&NavInfo.date_time);
#endif /*HAS_CALENDAR*/
                Node->first_time = false;
            }
            Node->time_date = NavInfo.date_time;
            res_time = true;
        } else {
            res_time = false;
            LOG_DEBUG(GNSS, "InvalUbxTimeDateInUbx");
        }
        res = is_valid_gnss_coordinates(NavInfo.coordinate);
        if(res) {
            if(Node->first_gnss) {
                LOG_INFO(GNSS, "SpotValidGNSSDataInUbx!");
                print_coordinate("UBX:", NavInfo.coordinate, true);
                Node->first_gnss = false;
            }
            Node->coordinate_cur = NavInfo.coordinate;
            res_dot = true;
        } else {
            res_dot = false;
            LOG_DEBUG(GNSS, "InvalUbxGNSSDotInUbx");
        }

        res = is_valid_height(NavInfo.height_m);
        if(res) {
            Node->height_m = NavInfo.height_m;
        }

        if(res_dot && res_time) {
            res = true;
        } else {
            res = false;
        }
    } //if(Node)
    return res;
}
#endif

bool gnss_proc_one(uint8_t num) {
    bool res = false;
    GnssHandle_t *Node = GnssGetNode(num);
    if (Node) {
        res = true;
        res = is_valid_time(&Node->time_date);
        if (false == res) {
            LOG_DEBUG(GNSS, "InvalCurTime");
        }

        res = is_valid_gnss_coordinates(Node->coordinate_cur);
        if (res) {
            Node->coordinate_last = Node->coordinate_cur;
        } else {
            LOG_DEBUG(GNSS, "InvalGnssCurCoordinate");
        }

#ifdef HAS_NMEA
    res = gnss_update_from_nmea(num);
#endif

#ifdef HAS_UBLOX
    if(false == res) {
        res = gnss_update_from_ubx(num);
        if(false == res) {
            LOG_DEBUG(GNSS, "LackGnssData");
        }
    }
#endif
    }

    return res;
}

bool gnss_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(GNSS, "Init:%u", num);
    const GnssConfig_t *Config = GnssGetConfig(num);
    if (Config) {
        GnssHandle_t* Node=GnssGetNode( num);
        if (Node) {
            Node->height_m = 0.0;
            Node->first_gnss = true;
            Node->first_time = true;
            Node->coordinate_cur.phi = 0.0;
            Node->coordinate_cur.lambda = 0.0;

#ifdef HAS_PARAM
            bool out_res = true;
            (void) out_res;
            GnssCoordinate_t dflt_coordinate_base = { 0, 0 };
            LOAD_PARAM(GNSS, PAR_ID_TRUE_LOCATION, Node->coordinate_cur, dflt_coordinate_base);
#endif
            res = true;
        }
    }
    return res;
}

#ifdef HAS_SDR
bool gnss_doppler_freq_calc(double velocity_mps, double freq_tx_hz, double* const freq_rx_hz_out) {
    bool res = false;
    if(freq_rx_hz_out) {
        double freq_rx_hz = 0.0;
        freq_rx_hz = freq_tx_hz / (1.0 - (velocity_mps / SPEED_OF_LIGHT_MPS));
        LOG_INFO(GNSS, "CalcDoppler FreqTx:%f Hz,SpeedOfSv:%f m/s,FreqRx:%f Hz", freq_tx_hz, velocity_mps, freq_rx_hz);
        *freq_rx_hz_out = freq_rx_hz;
        res = true;
    }
    return res;
}

double sdr_calc_noncoherent(const SdrCorrRes_t* const Early, const SdrCorrRes_t* const Late) {
    int32_t IE2 = Early->correlation_i * Early->correlation_i;
    int32_t QE2 = Early->correlation_q * Early->correlation_q;

    int32_t IL2 = Late->correlation_i * Late->correlation_i;
    int32_t QL2 = Late->correlation_q * Late->correlation_q;

    int32_t numerator = (IE2 + QE2) - (IL2 + QL2);
    int32_t denominator = (IE2 + QE2) + (IL2 + QL2);
    double code_err = (double)numerator / (double)denominator;

    return code_err;
}

bool gnss_correlation_i8_iq(const int8_t* const signal, const int8_t* const SignalI, const int8_t* const SignalQ,
                            size_t size, SdrCorrRes_t* const CorrRes) {
    bool res = false;

    LOG_DEBUG(GNSS, "size:%d", size);
    if(signal) {
        if(SignalI) {
            if(SignalQ) {
                if(size) {
                    res = true;
                }
            }
        }
    }

    if(res) {
        int32_t mult_summ_cur_i = 0;
        int32_t mult_summ_cur_q = 0;
        mult_summ_cur_i = array_i8_mult_sum(signal, SignalI, size);
        mult_summ_cur_q = array_i8_mult_sum(signal, SignalQ, size);

        LOG_DEBUG(GNSS, "mult_summ_cur_i:%d", mult_summ_cur_i);
        LOG_DEBUG(GNSS, "mult_summ_cur_q:%d", mult_summ_cur_q);

        CorrRes->correlation_i = mult_summ_cur_i;
        CorrRes->correlation_q = mult_summ_cur_q;

        // double i2=(double)(CorrRes->correlation_i*CorrRes->correlation_i);
        // double q2=(double)(CorrRes->correlation_q*CorrRes->correlation_q);

        double complex z2 = ((double)mult_summ_cur_i) - ((double)mult_summ_cur_q) * I;
        CorrRes->arg = carg(z2);
        CorrRes->abs = (int32_t)cabs(z2);
        // CorrRes->abs =(int32_t) sqrt(i2+q2);
    } else {
        LOG_ERROR(GNSS, "InErr");
    }
    return res;
}

/*
 *           Q
 *           ^
 *           |
 *   --------|++++++++
 *   --------|++++++++
 * __--------|++++++++_______\I
 *   ++++++++|--------       /
 *   ++++++++|--------
 *   ++++++++|--------
 */

double calc_carrier_phase_err_rad(int32_t i_val, int32_t q_val) {
    double carr_phase_err_rad = 0.0;
    /* PLL discriminator */
    if(0 < i_val) {
        carr_phase_err_rad = atan2((double)q_val, (double)i_val);
    } else {
        carr_phase_err_rad = atan2((double)-q_val, (double)-i_val);
    }
    LOG_DEBUG(GNSS, "carr_phase_err:%f Rad", carr_phase_err_rad);
    return carr_phase_err_rad;
}

double calc_carrier_phase_err_deg(int32_t i_val, int32_t q_val) {
    double phase_err_deg = 0.0;
    double phase_err_rad = calc_carrier_phase_err_rad(i_val, q_val);
    LOG_INFO(GNSS, "Phase:%f Rad", phase_err_rad);
    phase_err_deg = rad_2_deg(phase_err_rad);
    LOG_INFO(GNSS, "Phase:%f deg", phase_err_deg);
    return phase_err_deg;
}

bool sdr_generate_local_oscilator_signals(LocalOscillatorHandle_t* const Node) {
    bool res = false;
    if(Node) {
        if(0 < Node->frequency_hz) {
            uint32_t size = sizeof(Node->if_lo_Q);
            if(size) {
#if 0
                res = generate_local_oscilator_signal(Node->frequency_hz, Node->phase_deg, Node->if_lo_Q, size,
                                                      (int32_t)Node->adc_sample_rate_hz, SIGNAL_COS);
                res = generate_local_oscilator_signal(Node->frequency_hz, Node->phase_deg, Node->if_lo_I, size,
                                                      (int32_t)Node->adc_sample_rate_hz, SIGNAL_SIN ) &&
                      res;
#endif
#if 1
                res = generate_local_oscilator_signal(Node->frequency_hz, Node->phase_deg, Node->if_lo_Q, size,
                                                      (int32_t)Node->adc_sample_rate_hz, SIGNAL_SIN);
                res = generate_local_oscilator_signal(Node->frequency_hz, Node->phase_deg, Node->if_lo_I, size,
                                                      (int32_t)Node->adc_sample_rate_hz, SIGNAL_COS) &&
                      res;
#endif
                if(res) {

                } else {
                    LOG_ERROR(GPS, "SignalErr");
                }
            } else {
                LOG_ERROR(GPS, "SizeErr");
            }
        } else {
            LOG_ERROR(GPS, "FreqErr %d Hz", Node->frequency_hz);
        }
    } else {
        LOG_ERROR(GPS, "NodeErr");
    }
    return res;
}


bool local_oscillator_init_one(uint8_t num) {
    LOG_INFO(SDR, "INIT:%u", num);
    bool res = false;
    const LocalOscillatorConfig_t* Config = LocalOscillatorGetConfig(num);
    if(Config) {
        LocalOscillatorHandle_t* Node = LocalOscillatorGetNode(num);
        if(Node) {
            Node->frequency_hz = Config->frequency_hz;
            Node->phase_deg = Config->phase_deg;
            Node->adc_sample_rate_hz = Config->adc_sample_rate_hz;
            Node->num = Config->num;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

bool local_oscillator_init_custom(void) { return true; }

COMPONENT_INIT_PATTERT_CNT(SDR, SDR, local_oscillator, 32)


#endif

bool gnss_init_custom(void){
	return true;
}

COMPONENT_INIT_PATTERT(GNSS, GNSS, gnss)
COMPONENT_PROC_PATTERT(GNSS, GNSS, gnss)
