#include "light_navigator_diag.h"

#include <stdio.h>
#include <string.h>

#include "gnss_diag.h"
#include "light_navigator.h"
#include "log.h"
#include "num_to_str.h"
#include "schmitt_trigger.h"
#include "time_diag.h"

static char lText[400] = {0};

bool light_navigator_diag_one(uint8_t num) {
    bool res = false;

    LightNavigatorHandle_t* Node = LightNavigatorGetNode(num);
    if(Node) {
        res = print_time_date("Time", &Node->time_date, true);
        res = print_time_date("SunRise", &Node->time_date_sunrise, true);
        res = print_time_date("Noon", &Node->time_date_noon, true);
        res = print_time_date("SunSet", &Node->time_date_sunset, true);
        res = print_time_date("MaxLiTime", &Node->time_date_max_illumination, true);
        res = print_time_date("MinLiTime", &Node->time_date_min_illumination, true);
        LOG_INFO(LIGHT_NAVIGATOR, "DayLength %f h", Node->day_length_h);
        LOG_INFO(LIGHT_NAVIGATOR, "phi %f h", Node->coordinate.phi);
        LOG_INFO(LIGHT_NAVIGATOR, "lambda %f h", Node->coordinate.lambda);
        LOG_INFO(LIGHT_NAVIGATOR, "illuminationCur %f Msim", Node->illumination.cur);
        LOG_INFO(LIGHT_NAVIGATOR, "illuminationMin %f Msim", Node->illumination.min);
        LOG_INFO(LIGHT_NAVIGATOR, "illuminationMax %f Msim", Node->illumination.max);
        LOG_INFO(LIGHT_NAVIGATOR, "DayCnt %u", Node->day_cnt);
        res = true;
    }

    return res;
}

bool light_navigator_diag(void) {
    bool res = true;
    LightNavigatorHandle_t* Node = LightNavigatorGetNode(1);
    if(Node) {
        res = LightNavigatorDiag(Node);
    }
    return res;
}

bool light_navigator_coordinate(void) {
    bool res = true;
    LightNavigatorHandle_t* Node = LightNavigatorGetNode(1);
    if(Node) {
        res = LightNavigatorDiagCoordinate(Node);
    }
    return res;
}

const char* LightNavigatorDiagCoordinateToStr(const LightNavigatorHandle_t* const Node) {
    if(Node) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%sDayLen:%6.3f,", lText, Node->day_length_h);
        snprintf(lText, sizeof(lText), "%sCordErr:%s m,", lText, DoubleToStr(Node->cordinate_error_m));
#ifdef HAS_GNSS_DIAG
        snprintf(lText, sizeof(lText), "%sMeasCord:%s,", lText, GnssCoordinateToStr(&Node->coordinate));
        snprintf(lText, sizeof(lText), "%sTrueCord:%s,", lText, GnssCoordinateToStr(&Node->TrueCoordinate));
#endif
        // snprintf(lText,sizeof(lText),"%sTimeData:%s,", lText,TimeDateToStrShort(&Node->time_date) );
    }
    return lText;
}

const char* LightNavigatorCordLogToStr(const LightNavigatorHandle_t* const Node) {
    if(Node) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%sDayLen:%6.3f", lText, Node->day_length_h);
        snprintf(lText, sizeof(lText), "%sCordErr:%s m,", lText, DoubleToStr(Node->cordinate_error_m));
        snprintf(lText, sizeof(lText), "%sCord:%s,", lText, GnssCoordinateToStr(&Node->coordinate));
        snprintf(lText, sizeof(lText), "%sRise:%s,", lText, TimeDateToStrShort(&Node->time_date_sunrise));
        snprintf(lText, sizeof(lText), "%sSet:%s,", lText, TimeDateToStrShort(&Node->time_date_sunset));
    }
    return lText;
}

const char* LightNavigatorDiagToStr(const LightNavigatorHandle_t* const Node) {

    if(Node) {
        double day_diff_h = Node->day_length_h - Node->day_length_prev_h;
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%sPrevDayLen:%6.3f,", lText, Node->day_length_prev_h);
        snprintf(lText, sizeof(lText), "%sDayLen:%6.3f,", lText, Node->day_length_h);
        snprintf(lText, sizeof(lText), "%sDayDiff:%6.3f min,", lText, hour_to_min(day_diff_h));
        // snprintf(lText, sizeof(lText), "%sDayMax:%6.3f h,", lText, Node->max_day_length_h);
        snprintf(lText, sizeof(lText), "%sCordErr:%s m,", lText, DoubleToStr(Node->cordinate_error_m));
#ifdef HAS_GNSS_DIAG
        snprintf(lText, sizeof(lText), "%sCord:%s,", lText, GnssCoordinateToStr(&Node->coordinate));
#endif
        snprintf(lText, sizeof(lText), "%sRise:%s,", lText, TimeDateToStrShort(&Node->time_date_sunrise));
        snprintf(lText, sizeof(lText), "%sSet:%s,", lText, TimeDateToStrShort(&Node->time_date_sunset));
        snprintf(lText, sizeof(lText), "%sNoon:%s,", lText, TimeDateToStrShort(&Node->time_date_noon));
        snprintf(lText, sizeof(lText), "%sMaxLi:%s,", lText, TimeDateToStrShort(&Node->time_date_max_illumination));
        snprintf(lText, sizeof(lText), "%sMinLi:%s,", lText, TimeDateToStrShort(&Node->time_date_min_illumination));
        // snprintf(lText, sizeof(lText), "%sCnt:%u,", lText, Node->cnt);
        // snprintf(lText, sizeof(lText), "%sDayStat:%u ms,", lText, Node->day_start_ms);
        snprintf(lText, sizeof(lText), "%sDayCnt:%u,", lText, Node->day_cnt);
        // snprintf(lText,sizeof(lText),"%sTimeData:%s,", lText,TimeDateToStrShort(&Node->time_date) );
    }
    return lText;
}

bool LightNavigatorDiagCoordinate(const LightNavigatorHandle_t* const Node) {
    bool res = false;
    if(Node) {
        cli_printf("%s" CRLF, LightNavigatorDiagCoordinateToStr(Node));
        res = true;
    }
    return res;
}

bool LightNavigatorDiag(const LightNavigatorHandle_t* const Node) {
    bool res = false;
    if(Node) {
        cli_printf("%s" CRLF, LightNavigatorDiagToStr(Node));
        res = true;
    }
    return res;
}
