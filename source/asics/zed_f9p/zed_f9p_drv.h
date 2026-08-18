#ifndef ZED_F9P_DRV_H
#define ZED_F9P_DRV_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "gnss_utils.h"
#include "system.h"

#define ZED_F9P_PERIOD_US SEC_2_US(1.0)
#define DFLT_GNSS_PER_MS 1000U
#define RETRANSMITT_CNT 15

typedef enum  {
    RTK_ROVER = 0,
    RTK_BASE_SURVEY_IN = 1,
    RTK_BASE_FIX = 2,
    RTK_NONE = 3,
} RTKmode_t;

typedef enum  {
    TIME_UTC = 0,
    TIME_GPS = 1,
    TIME_GLONASS = 2,
    TIME_BEIDOU = 3,
    TIME_GALILEO = 4,
} TimeSystem_t;

typedef struct {
    bool gps;
    bool glonass;
    bool galileo;
    bool beidou;
}GnssCorrections_t;

typedef struct  {
    struct tm time_date;
    GnssCoordinate_t coordinate_base; /*Location of RTK base station*/
   // GnssCoordinate_t coordinate_cur;
   // GnssCoordinate_t coordinate_last;
    double alt_base;
    uint16_t rate_ms;
    GnssCorrections_t corrections;
    int8_t time_zone;
    RTKmode_t rtk_mode;
    uint32_t fixed_position_3daccuracy_mm;
    Interfaces_t channel;
    // TODO:  time since update
    bool is_init;
} ZedF9P_t;

extern ZedF9P_t ZedF9P;

bool zed_f9p_init(void);
bool zed_f9p_load_params(void);
bool zed_f9p_proc(void);
#ifdef HAS_GNSS_RTK
bool zed_f9p_deploy_rover(void);
bool zed_f9p_deploy_base(GnssCoordinate_t coordinate_base,
                         double altitude_sea_lev_m,
                         RTKmode_t receiver_mode,
                         uint32_t fixed_position_3daccuracy_mm);
#endif
#endif /* ZED_F9P_DRV_H  */
