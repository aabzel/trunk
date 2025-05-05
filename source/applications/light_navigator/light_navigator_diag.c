#include "light_navigator_diag.h"

#include <stdio.h>
#include <string.h>

#include "light_navigator.h"
#include "log.h"
#include "schmitt_trigger.h"
#include "num_to_str.h"
#include "time_diag.h"
#include "gnss_diag.h"

bool light_navigator_diag_one(uint8_t num) {
    bool res = false;

    LightNavigatorHandle_t* Node=LightNavigatorGetNode(num) ;
    if(Node) {
        res = print_time_date("Time", &Node->time_date, true);
        res = print_time_date("SunRise", &Node->time_date_sunrise, true);
        res = print_time_date("Noon", &Node->time_date_noon, true);
        res = print_time_date("SunSet", &Node->time_date_sunset, true);
        res = print_time_date("MaxLiTime", &Node->time_date_max_illumination , true);
        res = print_time_date("MinLiTime", &Node->time_date_min_illumination , true);
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
    return res;
}

const char* LightNavigatorDiag2Str(const LightNavigatorHandle_t* const Node) {
    static char text[300]={0};
    if(Node) {
        strcpy(text,"");
        snprintf(text,sizeof(text),"%sCordErr:%s m,", text, DoubleToStr(Node->cordinate_error_m) );
#ifdef HAS_GNSS_DIAG
       snprintf(text,sizeof(text),"%sCord:%s,",text, GnssCoordinateToStr(&Node->coordinate));
#endif
        snprintf(text,sizeof(text),"%sRise:%s,", text,TimeDate2StrShort(&Node->time_date_sunrise) );
        snprintf(text,sizeof(text),"%sSet:%s,", text,TimeDate2StrShort(&Node->time_date_sunset) );
        snprintf(text,sizeof(text),"%sNoon:%s,", text,TimeDate2StrShort(&Node->time_date_noon) );
        snprintf(text,sizeof(text),"%sMaxLi:%s,", text,TimeDate2StrShort(&Node->time_date_max_illumination ) );
        snprintf(text,sizeof(text),"%sMinLi:%s,", text,TimeDate2StrShort(&Node->time_date_min_illumination ) );
        snprintf(text,sizeof(text),"%sDayLen:%6.3f", text, Node->day_length_h );
        snprintf(text,sizeof(text),"%s/%6.3f h,", text, Node->max_day_length_h);
        snprintf(text,sizeof(text),"%sCnt:%u,", text, Node->cnt );
        snprintf(text,sizeof(text),"%sDayStat:%u ms,", text, Node->day_start_ms );
        snprintf(text,sizeof(text),"%sDayCnt:%u,", text, Node->day_cnt );
        //snprintf(text,sizeof(text),"%sTimeData:%s,", text,TimeDate2StrShort(&Node->time_date) );
    }
    return text;
}

bool LightNavigatorDiag(const LightNavigatorHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(LIGHT_NAVIGATOR, "%s", LightNavigatorDiag2Str(Node));
        res = true;
    }
    return res;
}
