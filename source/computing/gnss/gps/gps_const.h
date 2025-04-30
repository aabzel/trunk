#ifndef GPS_CONST_H
#define GPS_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gps_dep.h"
#include "physics_const.h"

#define HONCOHERENT_ERROR 0.4
#define BITS_IN_PRN (1023 * 16)
#define PRN_DURATION_S (0.001)
/*
 * DLL (delay lock loop)
 */
#if 0
#define ONE_PRN_SAMPLE_CNT 38195
#define TWO_PRN_SAMPLE_CNT (76389)
#endif
//#define FREQ_STEP_HZ 1
//#define FREQ_STEP_HZ 5 // 1-
#define PRN_LENGTH 1023

// 38194.33333          0.001 /    (1.0/38194333.333333336)
// 38194.33333         38194333.333333336* 0.001
// 38194.33333         38194333.333333336/1000 =  38194.33
#define ONE_PRN_SAMPLE_CNT  16368
#define TWO_PRN_SAMPLE_CNT  (2*ONE_PRN_SAMPLE_CNT)

#define FREQ_L1_HZ 1575420000.0
#define L1_WAVE_LEN (SPEED_OF_LIGHT_MPS/FREQ_L1_HZ)

#define GNSS_DOPPLER_ERROR_HZ 5000
#define CRYSTAL_OSCILLATOR_ERROR_HZ 6000

#define GNSS_ERROR_HZ (GNSS_DOPPLER_ERROR_HZ+CRYSTAL_OSCILLATOR_ERROR_HZ)

#define PLL_TO_FLL (1.0/90.0)
#ifdef __cplusplus
}
#endif

#endif /* GPS_CONST_H */
