#ifndef GPS_1BIT_CONFIG_H
#define GPS_1BIT_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "gps_1bit_types.h"

#if 0

#endif

#define PRN_LENGTH              1023 //in chips
#define IF_NCO_STEP_HZ          (0.003810972f)
#define SPI_BAUDRATE_HZ         (int)(16368000)
#define PRN_SPEED_HZ            1000 //1ms period
#define BITS_IN_PRN             (SPI_BAUDRATE_HZ / PRN_SPEED_HZ) //16Kbit
#define PRN_SPI_WORDS_CNT       (BITS_IN_PRN / 16)
#define GPS_DATA_WORDS_CNT      (PRN_SPI_WORDS_CNT + 1)
#define PRN_SPEED_HZ            1000 //1ms period
#define SPI_BAUDRATE_HZ         (int)(16368000)
#define PRN_SPI_WORDS_CNT       (BITS_IN_PRN / 16) //1023 16bit words

#define TRACKING_CH_LENGTH 4

#define FREQ_L1_HZ             1575420000.0 //ok 1575.42ÌHz è 1227.6
#define GNSS_FRONT_END_FREQ_HZ 1571328000.0  //
#define ADC_SAMPLE_RATE_HZ 16368000.0
//#define CRYSTAL_OSCILLATOR_FREQ_HZ (16368000.0)
//#define IF_FREQ_HZ (FREQ_L1_HZ - GNSS_FRONT_END_FREQ_HZ)
#define IF_FREQ_HZ              ((int)(4092000))


/*
 *  41.0*7.0*24553500.0*2.0/9.0   =1`565`967`666.6666667
 *  ADC sample rate:  7.0*24553500.0*2.0/9.0 =  38194333.333333336
 * */
extern const Gps1BitConfig_t Gps1BitConfig[];
extern Gps1BitHandle_t Gps1BitInstance[];

uint32_t gps_1bit_get_cnt(void);

#endif /* GPS_1BIT_CONFIG_H */
