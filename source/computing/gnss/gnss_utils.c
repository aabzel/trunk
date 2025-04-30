#include "gnss_utils.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#ifdef HAS_PARAM
#include "param_types.h"
#endif

#include "log.h"

#ifdef HAS_FLASH_FS
#include "flash_fs.h"
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "time_mcal.h"
#include "utils_math.h"

double gnss_calc_distance_m(GnssCoordinate_t dot1, GnssCoordinate_t dot2) {
    double distance = 0.0f;
    double dlong = (dot2.lambda - dot1.lambda) * D2R;
    double dlat = (dot2.phi - dot1.phi) * D2R;
    double a = pow(sin(dlat / 2.0), 2) + cos(dot1.phi * D2R) * cos(dot2.phi * D2R) * pow(sin(dlong / 2.0), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    distance = 6367 * c * 1000.0;
    return distance;
}

bool is_valid_phi(double phi_deg) {
    bool res = false;
    if((-90.0 <= phi_deg) && (phi_deg <= 90.0)) {
        res = true;
    }
    return res;
}

bool gnss_is_valid_lambda(double lambda_deg) {
    bool res = false;
    if(-180.0  <= lambda_deg) {
        if(lambda_deg <= 180.0){
            res = true;
        }
    }
    return res;
}

bool is_valid_gnss_coordinates(GnssCoordinate_t dot) {
    bool res = false;
    res = is_valid_phi(dot.phi);
    if(res) {
        res = gnss_is_valid_lambda(  dot.lambda) ;
        GnssCoordinate_t valid_dot = {55.750964, 37.617135};
        double distance = gnss_calc_distance_m(dot, valid_dot);
        if(distance < 5057696.0) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

double gnss_encoding_2_degrees(double in_ddmm_mmmmm) {
    double ddmm_mmmmm = in_ddmm_mmmmm;
    double mm_mmmmm = 0.0;
    double dd_dddd = 0.0;
    double degrees = ((int32_t)ddmm_mmmmm) / 100;
    mm_mmmmm = ddmm_mmmmm - degrees * 100.0;
    dd_dddd = degrees + (mm_mmmmm / 60.0);
    return dd_dddd;
}

GnssCoordinate_t encode_gnss_coordinates(GnssCoordinate_t dot_ddmm) {
    GnssCoordinate_t dot_dd = {0};
    dot_dd.phi = gnss_encoding_2_degrees(dot_ddmm.phi);
    dot_dd.lambda = gnss_encoding_2_degrees(dot_ddmm.lambda);
    return dot_dd;
}

#define ONE_DEG_OF_EQUATOR (40000000.0 / 360.0)
GnssCoordinate_t gnss_encode_deg2mm(GnssCoordinate_t dot_dd) {
    GnssCoordinate_t ret_dot_mm = {0.0, 0.0};
    ret_dot_mm.lambda = dot_dd.lambda * cos(dot_dd.phi * D2R) * ONE_DEG_OF_EQUATOR; //долгота
    ret_dot_mm.phi = ONE_DEG_OF_EQUATOR * dot_dd.phi;                               //широта

    return ret_dot_mm;
}
/*
check here:
https://www.sunearthtools.com/tools/distance.php
*/
static double gnss_calc_azimuth_rad(GnssCoordinate_t dot1, GnssCoordinate_t dot2) {
    double teta1 = DEG_2_RAD(dot1.phi);
    double teta2 = DEG_2_RAD(dot2.phi);
    /*double delta1 = DEG_2_RAD(dot2.phi-dot1.phi);*/
    double delta2 = DEG_2_RAD(dot2.lambda - dot1.lambda);

    double y = sin(delta2) * cos(teta2);
    double x = cos(teta1) * sin(teta2) - sin(teta1) * cos(teta2) * cos(delta2);
    double azimuth = atan2(y, x);

    LOG_DEBUG(GNSS, "Az:%f Rad", azimuth);
    return azimuth;
}

/*
check here:
https://www.sunearthtools.com/tools/distance.php
*/

double gnss_calc_azimuth_deg(GnssCoordinate_t rover, GnssCoordinate_t point_of_interest) {
    double azimuth_deg = RAD_2_DEG(gnss_calc_azimuth_rad(rover, point_of_interest));
    LOG_INFO(GNSS, "Az:%f Deg", azimuth_deg);
    return azimuth_deg;
}

#ifdef HAS_SX1262
uint16_t param_calc_modulation_id(BandWidth_t band_width, SpreadingFactor_t spreading_factor,
                                  LoRaCodingRate_t coding_rate) {
    ModeInfoId_t LinkInfoId;
    LinkInfoId.spreading_factor = spreading_factor;
    LinkInfoId.band_width = band_width;
    LinkInfoId.coding_rate = coding_rate;
    LinkInfoId.type = ID_TYPE_LINK_INFO;

    return LinkInfoId.id;
}
#endif

bool is_valid_height(double height) {
    bool res = false;
    if(0.0 < height) {
        if(height < 10000.0) {
            res = true;
        }
    }
    return res;
}

#ifdef HAS_PARAM
bool gnss_update_link_info(GnssCoordinate_t coordinate_local, GnssCoordinate_t coordinate_remote) {
    bool res = false;
    double dist_cur = 0.0;
    double dist_prev = 0.0;
    dist_cur = gnss_calc_distance_m(coordinate_local, coordinate_remote);

    uint16_t id_modulation = 0;
#ifdef HAS_SX1262
    id_modulation = param_calc_modulation_id(Sx1262Instance.lora_mod_params.band_width,
                                             Sx1262Instance.lora_mod_params.spreading_factor,
                                             Sx1262Instance.lora_mod_params.coding_rate);
#endif

    LinkInfoPayload_t LinkInfoPayloadRead;
    uint16_t file_len = 0;
    res = flash_fs_get(id_modulation, (uint8_t*)&LinkInfoPayloadRead, sizeof(LinkInfoPayload_t), &file_len);
    if(res && (sizeof(LinkInfoPayload_t) == file_len)) {
        dist_prev = gnss_calc_distance_m(LinkInfoPayloadRead.coordinate_local, LinkInfoPayloadRead.coordinate_remote);
    }

    if(dist_prev < dist_cur) {
        LinkInfoPayload_t LinkInfoPayload;
        LinkInfoPayload.coordinate_local = coordinate_local;
        LinkInfoPayload.coordinate_remote = coordinate_remote;
        res = flash_fs_set(id_modulation, (uint8_t*)&LinkInfoPayload, sizeof(LinkInfoPayload_t));
        if(false == res) {
            FlashFs.err_set_cnt++;
        }
    }

    return res;
}
#endif

int8_t sign(double value) {
    int8_t sign_val = 0;
    if(0.0 <= value) {
        sign_val = 1;
    } else if(value < 0.0) {
        sign_val = -1;
    } else {
    }

    return sign_val;
}


#ifdef HAS_SDR
/*
    freq_hz - lo_freq [] +/- 10kHz
    samples - samples in time domain
    size - The size of sample array
    sample_time_s- sample_time
*/
bool generate_local_oscilator_signal(double freq_hz, double phase_deg, int8_t* const samples, uint32_t size,
                                     int32_t sample_freq_hz, SignalType_t sig_type) {
    bool res = false;

    double sample_time_s = 1.0 / ((double)sample_freq_hz);
    double duration_s = sample_time_s * ((double)size);
    LOG_DEBUG(GNSS, "LoSig:F_lo:%f Hz,Phase:%f Deg,Sz:%u Sample,Sample:%f ns,%s,Dur:%f s", freq_hz, phase_deg, size,
              SEC_2_NSEC(sample_time_s), SignalTypeToStr(sig_type), duration_s);
    if(samples) {
        if(size) {
            if(sample_freq_hz) {
                if(freq_hz < sample_freq_hz) {
                    // double sample_time_s = 1.0/ ((double)sample_freq_hz);
                    double phase_s = 0.0;
                    double step = 0.0;
                    double phase_rad;

                    phase_rad = deg_to_rad((double)phase_deg);

                    step = (2.0 * freq_hz * M_PI) / ((double)sample_freq_hz);
                    LOG_DEBUG(GNSS, "step:%f,Phase:%f Rad", step, phase_rad);

                    int32_t s = 0;
                    for(s = 0; s < size; s++) {
                        phase_s = step * ((double)s) + phase_rad;

                        switch(sig_type) {
                        case SIGNAL_SIN: {
                            samples[s] = sign(sin(phase_s));
                            res = true;
                        } break;
                        case SIGNAL_COS: {
                            // cli_printf("%f,",phase_s);
                            samples[s] = sign(cos(phase_s));
                            res = true;
                        } break;
                        default: {
                            LOG_ERROR(GNSS, "UndefSignalErr");
                        } break;
                        } // switch
                    }

                } else {
                    LOG_ERROR(GNSS, "SamplingLowRate SamFreq:%u Hz,SigFreq:%d Hz", sample_freq_hz, freq_hz);
                }

            } else {
                LOG_ERROR(GNSS, "SampleFreqErr");
            }
        } else {
            LOG_ERROR(GNSS, "SizeErr");
        }
    } else {
        LOG_ERROR(GNSS, "SamplesErr");
    }
    return res;
}
#endif

/*odd means not divided by 2*/
bool is_odd(uint32_t i) {
    bool res = false;
    if(i & 1) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

int32_t zigzag_traversal(uint32_t i, uint32_t step) {
    int32_t value = 0;
    int32_t sign = 1;
    bool res = is_odd(i);
    if(res) {
        sign = 1;
    } else {
        sign = -1;
    }

    value = sign * ceil(((double)i * step) / 2.0);
    return value;
}
