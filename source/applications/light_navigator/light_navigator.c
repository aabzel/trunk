#include "light_navigator.h"

#include <float.h>
#include <stdio.h>
#include <string.h>

#include "code_generator.h"
#include "gnss_utils.h"
#include "light_sensor_drv.h"
#include "log.h"
#include "planetarium.h"
#include "schmitt_trigger.h"
#include "time_diag.h"
#include "utils_math.h"

#ifdef HAS_NMEA
#include "nmea_protocol.h"
#endif

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

#ifdef HAS_RTC
#include "rtc_mcal.h"
#endif

#ifdef HAS_PHOTORESISTOR
#include "photoresistor.h"
#endif

#ifdef HAS_FAT_FS
#include "fat_fs.h"
#endif

COMPONENT_GET_NODE(LightNavigator, light_navigator)

COMPONENT_GET_CONFIG(LightNavigator, light_navigator)

static bool light_navigator_init_common(const LightNavigatorConfig_t* const Config,
                                        LightNavigatorHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->coordinate_filename = Config->coordinate_filename;
            Node->day_light_filename = Config->day_light_filename;
            Node->dawn_id = Config->dawn_id;
            Node->filename = Config->filename;
            Node->light_sensor_num = Config->light_sensor_num;
            Node->num = Config->num;
            Node->rtc_num = Config->rtc_num;
            Node->TrueCoordinate = Config->TrueCoordinate;
            Node->trigger_num = Config->trigger_num;
            Node->sunset_id = Config->sunset_id;
            res = true;
        }
    }
    return res;
}

bool light_navigator_init_one(uint32_t num) {
    bool res = false;
    LOG_WARNING(LIGHT_NAVIGATOR, "Init:%u", num);
    set_log_level(LIGHT_NAVIGATOR, LOG_LEVEL_DEBUG);

    const LightNavigatorConfig_t* Config = LightNavigatorGetConfig(num);
    if(Config) {
        LightNavigatorHandle_t* Node = LightNavigatorGetNode(num);
        if(Node) {
            LOG_INFO(LIGHT_NAVIGATOR, "RTC%u,File:%s", Node->rtc_num, Node->filename);
            res = light_navigator_init_common(Config, Node);

            Node->valid = true;
            Node->illumination.cur = 0.0;
            Node->illumination.min = DBL_MAX;
            Node->illumination.max = DBL_MIN;
            Node->max_day_length_h = DBL_MIN;
            Node->cnt = 0;
            Node->day_cnt = 0;
            Node->temperature = 0;
            Node->delta_deg = 0;
            Node->day_length_h = 0.0;

            memset(&Node->time_date, 0, sizeof(struct tm));
            memset(&Node->time_date_max_illumination, 0, sizeof(struct tm));
            memset(&Node->time_date_min_illumination, 0, sizeof(struct tm));
            memset(&Node->time_date_sunrise, 0, sizeof(struct tm));
            memset(&Node->time_date_sunset, 0, sizeof(struct tm));
            memset(&Node->time_date_noon, 0, sizeof(struct tm));
            memset(&Node->coordinate, 0, sizeof(GnssCoordinate_t));

#ifdef HAS_PARAM
            res = param_get(Node->dawn_id, (void*)&Node->time_date_sunrise);
            res = param_get(Node->sunset_id, (void*)&Node->time_date_sunset);
#endif

            LOG_INFO(LIGHT_NAVIGATOR, "TmepFile: %s", Node->filename);

            set_log_level(LIGHT_NAVIGATOR, LOG_LEVEL_INFO);
            Node->init = true;
            res = true;
        }
    }

    return res;
}

bool light_navigator_sunrise_proc(uint8_t num) {
    bool res = false;
    LOG_INFO(LIGHT_NAVIGATOR, "SunRise! %u", num);
    LightNavigatorHandle_t* Node = LightNavigatorGetNode(num);
    if(Node) {
        Node->illumination.max = 0.0;
        Node->day_length_h = 0.0;
        Node->day_start_ms = time_get_ms32();
#ifdef HAS_RTC
        res = rtc_get(Node->rtc_num, &Node->time_date_sunrise);
#endif
        res = print_time_date("SunRise!", &Node->time_date_sunrise, true);

        if(Node->dawn_id) {
#ifdef HAS_PARAM
            param_set(Node->dawn_id, &Node->time_date_sunrise);
#endif
        }
    }

    return res;
}

static bool light_navigator_save_metrics(const LightNavigatorHandle_t* const Node) {
    bool res = false;
    if(Node) {
        if(0.0 < Node->day_length_h) {
            char temp[200] = "";
            char sunRiseLine[30] = "";
            char NoonStr[30] = "";
            char SunSetStr[30] = "";

            res = TimeDateToStrExt(&Node->time_date_sunrise, sunRiseLine, sizeof(sunRiseLine));
            res = TimeToStr(&Node->time_date_noon, NoonStr, sizeof(NoonStr));
            res = TimeDateToStrExt(&Node->time_date_sunset, SunSetStr, sizeof(SunSetStr));

            snprintf(temp, sizeof(temp), "DayDur:%7.3f h,SunDec:%7.3f Deg,Rise:%s,Noon:%s,Set:%s,Lambda:%f Deg",
                     Node->day_length_h, Node->delta_deg, sunRiseLine, NoonStr, SunSetStr, Node->coordinate.lambda);

            LOG_INFO(LIGHT_NAVIGATOR, "Save:%s", temp);
#ifdef HAS_FAT_FS
            res = fat_fs_write_line(1, Node->day_light_filename, temp);
#endif
        }
    }
    return res;
}

static bool save_coordinare(LightNavigatorHandle_t* Node) {
    bool res = false;
    if(Node) {
#ifdef HAS_FAT_FS
        char temp[600] = {0};
        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%s,%s", LightNavigatorCordLogToStr(Node), rtc_get_str(Node->rtc_num));
        res = fat_fs_write_line(1, Node->coordinate_filename, temp);
#endif
    }
    return res;
}

bool light_navigator_sunset_proc(uint8_t num) {
    bool res = false;
    LOG_WARNING(LIGHT_NAVIGATOR, CRLF CRLF "SunSet");
    // const LightNavigatorConfig_t* Config = LightNavigatorGetConfig(num);
    LightNavigatorHandle_t* Node = LightNavigatorGetNode(num);
    if(Node) {
#ifdef HAS_RTC
        res = rtc_get(Node->rtc_num, &Node->time_date_sunset);
#endif
        if(res) {
            res = print_time_date("SunSet", &Node->time_date_sunset, true);
        }
        Node->day_cnt++;

#ifdef HAS_PARAM
        if(Node->sunset_id) {
            param_set(Node->sunset_id, (uint8_t*)&Node->time_date_sunset);
        }
#endif
        res = calc_lambda(&Node->time_date_max_illumination, &Node->lambda_max_illumination);
        if(res) {
            char temp[150] = "";
            snprintf(temp, sizeof(temp), "lambda:%f,", Node->lambda_max_illumination);
            snprintf(temp, sizeof(temp), "%s,%s,", temp, TimeDateToStrShort(&Node->time_date_max_illumination));
            snprintf(temp, sizeof(temp), "%sLightMax:%fLx", temp, Node->illumination.max);
#ifdef HAS_FAT_FS
            res = fat_fs_write_line(1, "MaxLiLong.csv", temp);
#endif
        }

        int32_t seconds = time_date_cmp(&Node->time_date_sunrise, &Node->time_date_sunset);
        double day_length_candidat_h = SEC_2_HOUR(seconds);

        res = calc_delta_deg(&Node->time_date_sunset, &Node->delta_deg);

        LOG_WARNING(LIGHT_NAVIGATOR, "DayLight %f Hour", day_length_candidat_h);
        if(day_length_candidat_h < 48.0) {
            Node->day_length_prev_h = Node->day_length_h;
            Node->day_length_h = day_length_candidat_h;
            res = calc_noon_time(&Node->time_date_sunrise, &Node->time_date_sunset, &Node->time_date_noon);
            res = print_time_date("Noon", &Node->time_date_noon, true);

            res = calc_phi_v2(Node->day_length_h, &Node->time_date_sunset, &Node->coordinate.phi);
            if(res) {
                LOG_WARNING(LIGHT_NAVIGATOR, "phi(-) %f Deg", Node->coordinate.phi);
            } else {
                LOG_ERROR(LIGHT_NAVIGATOR, "CalcLatitudeErr %f Deg", Node->coordinate.phi);
            }

            // Node->time_date_noon.tm_year -= START_YEAR;
            // Node->coordinate.lambda = 0.0;
            res = calc_lambda(&Node->time_date_noon, &Node->coordinate.lambda);
            if(res) {
                LOG_INFO(LIGHT_NAVIGATOR, "Lambda %f Deg", Node->coordinate.lambda);
            } else {
                LOG_ERROR(LIGHT_NAVIGATOR, "CalcLongitudeErr:%f Deg", Node->coordinate.lambda);
            }

            res = light_navigator_diag_one(num);
            res = save_coordinare(Node);
            res = light_navigator_save_metrics(Node);
        }
        Node->illumination_max_prev = Node->illumination.max;
        Node->illumination.max = 0.0;
    }

    return res;
}

static bool light_navigator_limits_proc_ll(LightNavigatorHandle_t* const Node) {
    bool res = false;
    if(Node) {
        if(Node->illumination.max < Node->illumination.cur) {
            Node->illumination.max = Node->illumination.cur;
#ifdef HAS_RTC
            res = rtc_get(Node->rtc_num, &(Node->time_date_max_illumination));
#endif

            LOG_WARNING(LIGHT_NAVIGATOR, "UpdMaxLight:%f,%s", Node->illumination.cur,
                        TimeDateToStrShort(&(Node->time_date_max_illumination)));
        }

        if(Node->illumination.cur < Node->illumination.min) {
            Node->illumination.min = Node->illumination.cur;
#ifdef HAS_RTC
            res = rtc_get(Node->rtc_num, &Node->time_date_min_illumination);
#endif
            LOG_WARNING(LIGHT_NAVIGATOR, "UpdMinLight:%f,%s", Node->illumination.cur,
                        TimeDateToStrShort(&(Node->time_date_max_illumination)));
        }
    }
    return res;
}

bool light_navigator_check_ll(LightNavigatorHandle_t* const Node) {
    bool res = true;
    if(Node) {
        if(24.0 < Node->day_length_h) {
            LOG_WARNING(LIGHT_NAVIGATOR, "InvalidDayDur:%6.3f H", Node->day_length_h);
            Node->day_length_h = 0.0;
            res = false;
        }

        if(Node->day_length_h < 0.0) {
            LOG_WARNING(LIGHT_NAVIGATOR, "InvalidDayDur:%6.3f H", Node->day_length_h);
            Node->day_length_h = 0.0;
            res = false;
        }
    }
    return res;
}

bool light_navigator_light_to_lambda_proc_one(uint32_t num) {
    bool res = false;
    LightNavigatorHandle_t* Node = LightNavigatorGetNode(num);
    if(Node) {
        Node->illumination.cur = light_sensor_read(Node->light_sensor_num);
        res = light_navigator_limits_proc_ll(Node);
    }
    return res;
}

bool light_navigator_proc_one(uint32_t num) {
    bool res = false;
    LightNavigatorHandle_t* Node = LightNavigatorGetNode(num);
    if(Node) {
#ifdef HAS_RTC
        res = rtc_get(Node->rtc_num, &Node->time_date);
#endif
        LOG_INFO(LIGHT_NAVIGATOR, "%s", LightNavigatorDiagToStr(Node));
        if(res) {
            res = schmitt_trigger_proc_val(Node->trigger_num, Node->illumination.cur);
            SchmittTriggerHandle_t* Trigger = SchmittTriggerGetNode(Node->trigger_num);
            if(Trigger) {
                switch(Trigger->state) {
                case SCHMITT_TRIGGER_STATE_UP: {
                    uint32_t up_time_ms = time_get_ms32();
                    uint32_t day_length_ms = up_time_ms - Node->day_start_ms;
                    Node->day_length_h = MSEC_2_HOUR(day_length_ms);
                    Node->max_day_length_h = MATH_MAX(Node->max_day_length_h, Node->day_length_h);

                    res = calc_noon_time(&Node->time_date_sunrise, &Node->time_date, &Node->time_date_noon);
                } break;
                case SCHMITT_TRIGGER_STATE_DOWN: {
                    // Node->day_length_h = 0.0;
                    Node->day_start_ms = time_get_ms32();
                } break;
                default:
                    break;
                }
            }
            char time_text[100] = {0};
            TimeDate2CsvStr(&Node->time_date, time_text, sizeof(time_text));
            char temp[200] = {0};
            snprintf(temp, sizeof(temp), "%4u,", Node->cnt);
            snprintf(temp, sizeof(temp), "%sLight:%7.3f,", temp, Node->illumination.cur);
            snprintf(temp, sizeof(temp), "%s%s,", temp, time_text);
            snprintf(temp, sizeof(temp), "%sDayDur:%7.3fh", temp, Node->day_length_h);
            LOG_WARNING(LIGHT_NAVIGATOR, "LiNav_%u Save [%s] %u byte", num, temp, strlen(temp));
#ifdef HAS_FAT_FS
            res = fat_fs_write_line(1, Node->filename, temp);
#endif
            Node->cnt++;
        }
        res = light_navigator_check_ll(Node);
#ifdef HAS_NMEA
        NmeaHandle_t* Nmea = NmeaGetNode(1);
        if(Nmea) {
            Node->TrueCoordinate = Nmea->coordinate_dd;
        }
#endif

        Node->cordinate_error_m = gnss_calc_distance_m(&Node->coordinate, &Node->TrueCoordinate);
    }

    return res;
}

bool light_navigator_init_custom(void) {
    bool res = true;
    return res;
}

#if 0
bool light_navigator_proc_all(void) {
    bool res = false;
    uint32_t i = 0;
    static uint32_t line_cnt = 0;
    uint32_t cnt = light_navigator_get_cnt();
    char temp[120] = "";
    snprintf(temp, sizeof(temp), "%4u", line_cnt);
    struct tm time_date;
#ifdef HAS_RTC
    res = rtc_get(1, &time_date);
#endif
    if(res) {
        char time_text[100]={0};
        TimeDate2CsvStr(&time_date, time_text, sizeof(time_text));
        snprintf(temp, sizeof(temp), "%s, %s", temp, time_text);

        for(i = 0; i <= cnt; i++) {

                LightNavigatorHandle_t* Node = LightNavigatorGetNode(i);
                if(Node) {
                    Node->illumination.cur = light_sensor_read(Node->light_sensor_num);
                    snprintf(temp, sizeof(temp), "%s, %7.3f", temp, Node->illumination.cur);
                }

        }
        line_cnt++;

        res = fat_fs_write_line(1,"All.csv", temp);
    }
    return res;
}
#endif

bool light_navigator_light_to_lambda_proc(void) {
    bool res = true;
    uint32_t ok = 0;
    uint32_t cnt = light_navigator_get_cnt();
    (void)cnt;
    LOG_PROC_ALL
    uint32_t i = 0;
    for(i = 0; i <= cnt; i++) {
        res = light_navigator_light_to_lambda_proc_one(i);
        if(res) {
            LOG_PROC_OK
            ok++;
        } else {
            LOG_PROC_ERROR
        }
    }
    if(ok) {
        res = true;
        LOG_PROC_STATISTIC
    } else {
        res = false;
    }
    return res;
}

COMPONENT_PROC_PATTERT(LIGHT_NAVIGATOR, LIGHT_NAVIGATOR, light_navigator)
// COMPONENT_PROC_PATTERT(LIGHT_NAVIGATOR, LIGHT_NAVIGATOR, light_navigator_light_to_lambda)

COMPONENT_INIT_PATTERT(LIGHT_NAVIGATOR, LIGHT_NAVIGATOR, light_navigator)
