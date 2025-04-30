#ifndef GNSS_UTILS_H
#define GNSS_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <std_includes.h>
#include <time.h>

#include "gnss_types.h"

#define METER_TO_MM(METER) ((METER)*1000)
#define MM_TO_METER(MM) ((MM) / 1000.0)

bool gnss_is_valid_lambda(double lambda_deg) ;
int8_t sign(double value);
int32_t zigzag_traversal(uint32_t i, uint32_t step);

bool generate_local_oscilator_signal(double freq_hz, double phase_deg, int8_t* const samples, uint32_t size,
                                     int32_t sample_freq_hz, SignalType_t sig_type);

bool is_valid_phi(double phi_deg);
bool is_valid_height(double height);
bool gnss_update_link_info(GnssCoordinate_t coordinate_local, GnssCoordinate_t coordinate_remote);
bool is_valid_gnss_coordinates(GnssCoordinate_t dot);
GnssCoordinate_t gnss_encode_deg2mm(GnssCoordinate_t dot_dd);
double gnss_calc_distance_m(GnssCoordinate_t dot1, GnssCoordinate_t dot2);
double gnss_encoding_2_degrees(double in_ddmm_mmmmm);
GnssCoordinate_t encode_gnss_coordinates(GnssCoordinate_t dot_ddmm);
double gnss_calc_azimuth_deg(GnssCoordinate_t rover, GnssCoordinate_t beacon);
#ifdef HAS_SX1262
uint16_t param_calc_modulation_id(BandWidth_t band_width, SpreadingFactor_t spreading_factor,
                                  LoRaCodingRate_t coding_rate);
#endif
#ifdef __cplusplus
}
#endif

#endif /* GNSS_UTILS_H */
