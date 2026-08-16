#ifndef GNSS_DRV_H
#define GNSS_DRV_H

/*GNSS receiver invariant component*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#include "gnss_types.h"
#include "gnss_config.h"
#include "gnss_utils.h"
#include "timer_utils.h"

#ifdef HAS_GNSS_DIAG
#include "gnss_diag.h"
#endif

#ifdef HAS_PC
#include "local_oscillator_config.h"
#endif

#define GNSS_PERIOD_US SEC_2_US(0.9)

GnssHandle_t* GnssGetNode(uint8_t num);
const GnssConfig_t* GnssGetConfig(uint8_t num);

bool gnss_init_one(uint8_t num) ;
bool gnss_mcal_init(void);
bool gnss_doppler_freq_calc(double velocity_mps, double freq_tx_hz, double* freq_rx_hz);
bool gnss_proc(void);

#ifdef HAS_PC
bool gnss_correlation_i8_iq(const int8_t* const signal, const int8_t* const SignalI, const int8_t* const SignalQ,
                            size_t size, SdrCorrRes_t* const CorrRes);
LocalOscillatorHandle_t* LocalOscillatorGetNode(uint8_t num);
const LocalOscillatorConfig_t* LocalOscillatorGetConfig(uint8_t num);

bool local_oscillator_mcal_init(void);
bool local_oscillator_init_one(uint8_t num);
#endif

/*setter*/
bool gnss_true_location_set(const   GnssCoordinate_t * const  coordinate);

/*getter*/

bool sdr_generate_local_oscilator_signals(LocalOscillatorHandle_t* const Node);

double calc_carrier_phase_err_deg(int32_t i_val, int32_t q_val);
double calc_carrier_phase_err_rad(int32_t i_val, int32_t q_val);
double sdr_calc_noncoherent(const SdrCorrRes_t* const Early, const SdrCorrRes_t* const Late);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*GNSS_DRV_H*/
