#ifndef GNSS_SDR_TYPES_H
#define GNSS_SDR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

#include "std_includes.h"
#include "gnss_const.h"

typedef struct {
    double phi;    /* Latitude (degrees and minutes) широта*/
    double lambda;    /* Longitude (degrees and minutes) долгота*/
/*} __attribute__((packed)) GnssCoordinate_t; Cause Fault ISR*/
} GnssCoordinate_t;

#define GNSS_COMMON_VARIABLES  \
    uint8_t num;               \
    uint8_t nmea_num;          \
    bool valid;

typedef struct {
    GNSS_COMMON_VARIABLES
} GnssConfig_t;


typedef struct {
    GNSS_COMMON_VARIABLES
    struct tm time_date;
    GnssCoordinate_t coordinate_cur;
    GnssCoordinate_t coordinate_last;
    bool first_time;
    bool first_gnss;
    double height_m; /*Height above mean sea level*/
    int32_t adc_sample_rate_hz;
#ifdef HAS_PC
    int8_t SignalI[TWO_PRN_SAMPLE_CNT];
    int8_t SignalQ[TWO_PRN_SAMPLE_CNT];
#endif
} GnssHandle_t;


typedef struct {
    int32_t correlation_i;
    int32_t correlation_q;
    int32_t abs;
    double arg;
}SdrCorrRes_t;


typedef struct {
    SdrCorrRes_t Early;
    SdrCorrRes_t Present;
    SdrCorrRes_t Late;
    double lo_phase_deg ;
    double carr_phase_err_deg ;
}SdrEPL_t;

#define LOCAL_OSCULLATOR_COMMON_VARIABLES   \
    uint32_t size;  /*sample count*/        \
    double frequency_hz;                    \
    double phase_deg;                       \
    int32_t adc_sample_rate_hz; \
    uint8_t num;  /*num=prn*/ \
    char* name;   \
    bool valid;

typedef struct {
    LOCAL_OSCULLATOR_COMMON_VARIABLES
#ifdef HAS_PC
    int8_t if_lo_I[TWO_PRN_SAMPLE_CNT];
    int8_t if_lo_Q[TWO_PRN_SAMPLE_CNT];
#endif
}LocalOscillatorHandle_t;

typedef struct {
    LOCAL_OSCULLATOR_COMMON_VARIABLES
}LocalOscillatorConfig_t;


typedef struct {
    int prn;
    int32_t prn_phase_sample;
    int32_t correlation_value;
    int32_t prn_cnt;
    uint32_t time_sample;
    double doppler_offset_hz;
    double time_s ;
    double noncoherent ;
    double filt_noncoherent ;
    double adc_sample_rate_hz ;
} GnssEscortInfo_t;


typedef struct {
    int32_t x_cm;
    int32_t y_cm;
    int32_t z_cm;
    int32_t acc_cm;
} Wgs84Coordinate_t;

typedef struct {
    double velocity_north;
    double velocity_east;
    double velocity_down;
    double speed;
    double speed_ground;
    double heading;
    double accuracy_speed;
    double accuracy_course;
} GnssVelocity_t;

typedef struct  {
    GnssCoordinate_t coordinate_local;
    GnssCoordinate_t coordinate_remote;
} LinkInfoPayload_t;

#ifdef __cplusplus
}
#endif

#endif /* GNSS_SDR_TYPES_H */
