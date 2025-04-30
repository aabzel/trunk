#ifndef GPS_CONFIG_H
#define GPS_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "gps_types.h"

#if 0
#define CRYSTAL_OSCILLATOR_FREQ_HZ (24553500.0)
#define GNSS_FRONT_END_FREQ_HZ (41.0 * ADC_SAMPLE_RATE_HZ)
#define ADC_SAMPLE_RATE_HZ (7.0 * CRYSTAL_OSCILLATOR_FREQ_HZ * 2.0 / 9.0)

#define GNSS_FRONT_END_FREQ_HZ 1571328000.0
#define CRYSTAL_OSCILLATOR_FREQ_HZ (16368000.0)
#define ADC_SAMPLE_RATE_HZ CRYSTAL_OSCILLATOR_FREQ_HZ
#define IF_FREQ_HZ (FREQ_L1_HZ - GNSS_FRONT_END_FREQ_HZ)

#endif

#define GNSS_FRONT_END_FREQ_HZ 1571328000.0
#define ADC_SAMPLE_RATE_HZ 16368000.0
//#define CRYSTAL_OSCILLATOR_FREQ_HZ (16368000.0)
#define IF_FREQ_HZ (FREQ_L1_HZ - GNSS_FRONT_END_FREQ_HZ)

/*
 *  41.0*7.0*24553500.0*2.0/9.0   =1`565`967`666.6666667
 *  ADC sample rate:  7.0*24553500.0*2.0/9.0 =  38194333.333333336
 * */
extern const GpsConfig_t GpsConfig[];
extern GpsHandle_t GpsInstance[];

uint32_t gps_get_cnt(void);

#endif /* GPS_CONFIG_H */
