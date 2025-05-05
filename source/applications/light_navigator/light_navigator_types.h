#ifndef NOR_LIGHT_NAVIGATOR_TYPES_H
#define NOR_LIGHT_NAVIGATOR_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "data_types.h"
#include "flash_fs_file_ids.h"
#include "gnss_types.h"
#include "light_navigator_const.h"

#define LIGHT_NAVIGATOR_COMMON_VARIABLES                     \
    uint8_t num;                                             \
    GnssCoordinate_t TrueCoordinate;                         \
    bool valid;                                              \
    uint8_t rtc_num;                                         \
    uint8_t light_sensor_num;                                \
    uint8_t trigger_num;                                     \
    char* filename;                                          \
    char* day_light_filename;                                \
    char* coordinate_filename;                               \
    Id_t dawn_id;                                            \
    Id_t sunset_id;

typedef struct {
    LIGHT_NAVIGATOR_COMMON_VARIABLES
} LightNavigatorConfig_t;

typedef struct {
    LIGHT_NAVIGATOR_COMMON_VARIABLES
    bool init;
    uint32_t cnt;
    uint32_t day_start_ms;
    uint32_t day_cnt;
    struct tm time_date;
    struct tm time_date_max_illumination;
    struct tm time_date_min_illumination;
    struct tm time_date_sunrise;
    struct tm time_date_sunset;
    struct tm time_date_noon;
    DoubleValue_t illumination;
    double illumination_max_prev;
    double temperature;
    double lambda_max_illumination;
    double day_length_h;
    double max_day_length_h; /*continuous*/
    double delta_deg;
    double cordinate_error_m;
    GnssCoordinate_t coordinate;
} LightNavigatorHandle_t;

#endif /* NOR_LIGHT_NAVIGATOR_TYPES_H */
