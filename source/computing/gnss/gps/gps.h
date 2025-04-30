#ifndef GPS_DRV_H
#define GPS_DRV_H

/*GPS receiver invariant component*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "gnss_types.h"
#include "gps_config.h"
#include "gps_diag.h"
#include "gps_misc.h"
#include "gps_types.h"

bool gps_escort_sat_epl(uint8_t num, int prn);
bool gps_prn_autocorrelation(uint8_t num, int prn);
bool gps_prn_convolution(uint8_t num, int prn);
bool gps_capture_prn(uint8_t num, int32_t prn, double time_s, uint32_t phase_offset_sample_start,
                     uint32_t phase_offset_sample_end, uint32_t* const phase_offset_sample,
                     int32_t doppler_freq_offset_hz);

bool gps_escort_sat(uint8_t num, int prn);

int32_t gps_correlation_i8(const int8_t* const signal, const int8_t* const SignalI, const int8_t* const SignalQ,
                           size_t size);

const GpsConfig_t* GpsGetConfig(uint8_t num);
GpsHandle_t* GpsGetNode(uint8_t num);
GpsSat_t* GpsGetSatConfig(const GpsSat_t* const SatS, uint32_t size, int32_t prn);
double fll_discriminator_deg(SdrCorrRes_t* const New, SdrCorrRes_t* const Old);
double pd_regulator(double in_value);
int32_t costas_loop(GpsHandle_t* const Node, uint32_t offset);

bool gps_tracking_pll(SdrCorrRes_t* const Present, int32_t cur_dopler_hz, int32_t* freq_tune_out);
bool gps_generate_prn_samples(int prn, int8_t* const sample, double sample_per_chip);

bool GpsProcTwoPrn(GpsHandle_t* Node, const int8_t* const sample_data, size_t size, int32_t prn,
                   int32_t doppler_freq_offset_hz, PrnInfo_t* const PrnInfo);
bool gps_proc_data(GpsHandle_t* Node, const int8_t* const sample_data, size_t size);
bool gps_init_custom(void);
bool gps_proc_one(uint8_t num);
bool gps_init_one(uint8_t num);
bool gps_unpack_u16(const char* const file_name);
bool gps_mcal_init(void);
// bool gps_generate_local_oscilator_signals(GpsHandle_t* const Node, int32_t fl_freq_hz, uint32_t size);

bool gps_mix_lo_signal(GpsHandle_t* const Node, int32_t prn, const int8_t* const sample_data, uint32_t size);
bool gps_seek_prn_phase_all(uint8_t num, const char* const file_name, int32_t prn, int32_t doppler_freq_offset_hz,
                            double percent, uint32_t seek_start_sample, uint32_t seek_end_sample

);

bool pll_loop(SdrCorrRes_t* const Present, double* const out_carr_phase_err_deg, double* const carr_phase_tune_deg_i);
bool gps_calc_best_lo_phase(GpsHandle_t* Node, int prn, LocalOscillatorHandle_t* Oscillator, int32_t fl_freq_hz,
                            int8_t* TwoPrnSampleSata, int32_t EplOfftestStep, int8_t* GeneratedPrnSample,
                            SdrEPL_t* CorrBest);
#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*GPS_DRV_H*/
