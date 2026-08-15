#ifndef SONAR_DRV_H
#define SONAR_DRV_H

#include <complex.h>

#include "std_includes.h"
#include "sonar_config.h"
#include "sonar_types.h"
#include "sonar_diag.h"

extern double complex RecSpectrum[SONAR_MAX_SPEC] ;
extern double complex PulseSpectrum[SONAR_MAX_SPEC] ;

SonarHandle_t* SonarGetNode(uint8_t num);
const SonarConfig_t* SonarGetConfig(uint8_t num);

bool sonar_init_one(uint32_t num);
bool sonar_mcal_init(void);

bool sonar_proc(void);
bool sonar_proc_one(uint32_t num);

/* getter */
bool sonar_calc_correlation_max(uint32_t num, char* const file_name, SonarCorrelationInfo_t* const pBestCorrelation);
bool sonar_plot_convolution(uint8_t num, uint8_t x_col, uint8_t y_col) ;
bool sonar_chirp_calc_bandwith(float v_sound_mps,
                               float resolution_m,
                               float f_central_hz,
                               SonarChirpParam_t* ChirpParam);

/*setter*/
bool sonar_m_seq_calc_correlation_record(uint8_t num,
                                         uint8_t m_seq_num,
                                         float amplitude,
                                         float carrier_frequency_hz,
                                         uint32_t periods_per_chip,
                                         char *rec_file_name) ;

#ifdef HAS_BARKER_CODE
bool sonar_barker_calc_correlation_record( uint8_t num,
                                           float amplitude,
                                           float carrier_frequency_hz,
                                           uint32_t periods_per_chip,
                                           char* file_name);
#endif

bool sonar_chirp_correlation_record(uint32_t num,
                                    float chirp_duration_s,
                                    float amplitude,
                                    float frequency1,
                                    float frequency2,
                                    char* const file_name);

bool sonar_v_sound(uint32_t num, float v_sound);
bool sonar_zonding_signal(uint32_t num, char* rec_file_name);
bool sonar_correlation_ctrl(uint32_t num, bool on_off);
bool sonar_chirp_to_wav(uint32_t num);
#ifdef HAS_CORRELATOR_S16
bool sonar_calc_correlation(uint32_t num, char* const file_name);
#endif


bool sonar_calc_correlation_mono_record(uint8_t num, float carrier_frequency_hz, float amplitude, float signal_duration,
                                        char*  rec_file_name);
bool sonar_config_correlator_mono(uint32_t num, float duration_s, float amplitude,  float frequency) ;
bool sonar_config_correlator_chirp(uint32_t num, float chirp_duration_s, float amplitude,  float frequency1, float frequency2) ;
bool sonar_config_correlator_m_seq(uint8_t num, uint8_t m_seq_num,
                                   float amplitude, float carrier_frequency_hz, uint32_t periods_per_chip) ;
bool sonar_config_correlator_barker13(uint32_t num,
                                      float amplitude,
                                      float carrier_frequency_hz,
                                      uint32_t periods_per_chip);

bool sonar_signal_save(const char* const file_name, const double complex* const iSignal, uint32_t size, double scale_x);
bool sonar_dft_convolution(const char* const pulse_file_name, const char* const rec_file_name);


#endif /* SONAR_DRV_H */
