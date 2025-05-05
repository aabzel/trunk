#include "dashboard.h"

#include <stdio.h>
#include <string.h>

//#include "c_defines_generated.h"
#include "running_line.h"

#ifdef HAS_GNSS
#include "gnss_drv.h"
#endif

#include "code_generator.h"
#include "dashboard_dep.h"
#include "data_utils.h"
#include "str_utils.h"

#ifdef HAS_NMEA
#include "nmea_protocol.h"
#endif /*HAS_NMEA*/

#ifdef HAS_DISPLAY
#include "display_drv.h"
#endif /*HAS_DISPLAY*/

#ifdef HAS_SCHMITT_TRIGGER
#include "schmitt_trigger.h"
#endif

#ifdef HAS_BH1750
#include "bh1750_drv.h"
#endif

#ifdef HAS_LTR390
#include "ltr390_drv.h"
#endif

#ifdef HAS_DECAWAVE
#include "decawave.h"
#endif

#ifdef HAS_UWB
#include "uwb_diag.h"
#endif

#ifdef HAS_PLANETARIUM
#include "planetarium.h"
#endif

#ifdef HAS_DS_TWR
#include "ds_twr.h"
#endif
#include "log.h"

#ifdef HAS_RTC
#include "rtc_mcal.h"
#endif

#ifdef HAS_LIGHT_NAVIGATOR
#include "gnss_diag.h"
#include "light_navigator.h"
#endif

#ifdef HAS_SSD1306
#include "ssd1306_drv.h"
#endif

#ifdef HAS_TIME_DIAG
#include "time_diag.h"
#endif

#include "time_mcal.h"

COMPONENT_GET_NODE(DashBoard, dashboard)
COMPONENT_GET_CONFIG(DashBoard, dashboard)

#ifdef HAS_DECAWAVE
// TODO move to decawave code
static bool dashboard_decawave(DashBoardHandle_t* Node) {
    bool res = false;
    DecaWaveHandle_t* DecaNode = DecaWaveGetNode(1);
    double distance_real_m = 0.0;
    res = decawave_dist_get_ll(DecaNode, &distance_real_m);
    res = true;
    if(res) {
        LOG_DEBUG(DASHBOARD, "UwbDist %f", distance_real_m);
        if(DecaNode) {
            uint32_t up_time_ms = time_get_ms32();
            double up_time_s = MSEC_2_SEC(up_time_ms);
            snprintf(Node->text, sizeof(Node->text), "UpTime: %s", UpTimeSec2Str(up_time_s));
            snprintf(Node->text, sizeof(Node->text), "%s, Dist:%6.2f m", Node->text, distance_real_m);
            snprintf(Node->text, sizeof(Node->text), "%s, Spin: %u", Node->text, DecaNode->spin_cnt);
            snprintf(Node->text, sizeof(Node->text), "%s, DistFilt:%6.2f m", Node->text,
                     DecaNode->distance_filtered_real_m);
            snprintf(Node->text, sizeof(Node->text), "%s, Flow %u/%u", Node->text, DecaNode->Flow.cur,
                     DecaNode->Flow.maximum_continuous);
            snprintf(Node->text, sizeof(Node->text), "%s, MyAddr:0x%x", Node->text, DecaNode->addr);
            snprintf(Node->text, sizeof(Node->text), "%s, Role:%s", Node->text, UwbRole2Str(DecaNode->role));
            res = true;
        }
    } else {
        LOG_DEBUG(DASHBOARD, "GetDistErr");
        snprintf(Node->text, sizeof(Node->text), "WaitValue...");
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_NMEA
static bool dashboard_nmea(void) {
    bool res = false;
    NmeaHandle_t* Nmea = NmeaGetNode(1);
    if(Nmea) {
        char text[300]="";
        memset(text, 0, sizeof(text));
        snprintf(text, sizeof(text), "%s%s,",text,NmeaNodeMainToStr(Nmea));
        res = running_line_add_suffix(1, text);
    }
    return res;
}
#endif

#ifdef HAS_LTR390
static bool dashboard_ltr390(DashBoardHandle_t* Node) {
    bool res = false;
    if(Node) {
        Ltr390Handle_t* Ltr390Node = Ltr390GetNode(  Node->light_sensor_num);
        char text[200]="";
        memset(text,0,sizeof(text));
        if(Ltr390Node){
            snprintf(text, sizeof(text), "%s%s,",text,Ltr390Diag2Str(Ltr390Node));
            snprintf(text, sizeof(text), "%s%s,",text,Ltr390UvsDiag2Str(Ltr390Node));
            snprintf(text, sizeof(text), "%s%s,",text,Ltr390AlsDiag2Str(Ltr390Node));
        }
        res= running_line_set_text(2, text);
    } else {
        LOG_ERROR(DASHBOARD, "LiNavErr");
    }
    return res;
}
#endif

#ifdef HAS_LIGHT_NAVIGATOR
static bool dashboard_light_navigator(DashBoardHandle_t* Node) {
    bool res = false;
    LightNavigatorHandle_t* LiNavNode = LightNavigatorGetNode(Node->light_nav_num);
    if(LiNavNode) {
        char text[400]="";
        memset(text,0,sizeof(text));
        snprintf(text, sizeof(text), "%s,%s", text, LightNavigatorDiag2Str(LiNavNode));
        res = running_line_set_text(3, text);

    } else {
        LOG_ERROR(DASHBOARD, "LiNavErr");
    }

    return res;
}
#endif

#ifdef HAS_RTC
bool dashboard_rtc(DashBoardHandle_t* Node){
    bool res = false;
    char time_date_str[40] = "";
    res = rtc_get(Node->rtc_num, &Node->time_date);
    if(res) {
        res = TimeDate2Str(&Node->time_date, time_date_str, sizeof(time_date_str));
        LOG_PARN(DASHBOARD, "GetTime:%s", time_date_str);
        if(res) {
            res= running_line_set_text(1, time_date_str);
        }
    } else {
        LOG_ERROR(DASHBOARD, "GetTimeErr");
    }
    return res;
}
#endif

#ifdef HAS_SCHMITT_TRIGGER
#ifdef HAS_LIGHT_NAVIGATOR
bool dashboard_schmitt_trigger(DashBoardHandle_t* Node){
    bool res = false;
    if(Node) {
        LightNavigatorHandle_t* LiNavNode = LightNavigatorGetNode(Node->light_nav_num);
        if(LiNavNode) {
            SchmittTriggerHandle_t* Trigger=SchmittTriggerGetNode(LiNavNode->trigger_num);
            if(Trigger) {
                char text[400]="";
                memset(text,0,sizeof(text));
                snprintf(text, sizeof(text), "%s,%s", text, SchmittTriggerNode2Str(Trigger));
                res= running_line_set_text(4, text);
            }

        }
    }
    return res;
}
#endif
#endif

#ifdef HAS_BH1750
        res = bh1750_read_lx(Node->bh1750_num, &Node->lighting);
        if(res) {
            if(LiNavNode) {
                snprintf(Node->text, sizeof(Node->text), "%s,Li:%6.2f", Node->text, Node->lighting);
            }
        } else {
            LOG_ERROR(DASHBOARD, "Bh1750Err");
        }
#endif

// ll dashboard parn
static bool dashboard_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(DASHBOARD, "Proc:%u", num);
    DashBoardHandle_t* Node = DashBoardGetNode(num);
    if(Node) {
        LOG_PARN(DASHBOARD, "Spot %u", num);
        memset(Node->text, 0, sizeof(Node->text));

        uint32_t up_time = time_get_ms32();
        double up_time_s = MSEC_2_SEC(up_time);
        snprintf(Node->text, sizeof(Node->text), "UpTime:%s", UpTimeSec2Str(up_time_s));
#ifdef HAS_DECAWAVE
        res = dashboard_decawave(Node);
#endif /*HAS_DECAWAVE*/

#ifdef HAS_RTC
        res = dashboard_rtc(Node);
#endif

#ifdef HAS_LIGHT_NAVIGATOR
        res = dashboard_light_navigator(Node);
#endif

#ifdef HAS_LTR390
        res = dashboard_ltr390(Node);
#endif

#ifdef HAS_LIGHT_NAVIGATOR
        res = dashboard_schmitt_trigger(Node);
#endif

#ifdef HAS_BH1750
        res = dashboard_bh1750(Node);
#endif

#ifdef HAS_NMEA
        res = dashboard_nmea();
#endif

        str_del_char_inplace(Node->text, ' ');
        res = true;

#ifdef HAS_SSD1306
        if(res) {
            ssd1306_sram_clean(Node->display_num);

            snprintf(Node->text,sizeof(Node->text),"%s"CRLF"%s"CRLF"%s"CRLF"%s"CRLF,
                    running_line_get_text(1),
                    running_line_get_text(2),
                    running_line_get_text(3),
                    running_line_get_text(4));
            LOG_DEBUG(DASHBOARD, "St:%u, [%s] %u Byte", Node->text, strlen(Node->text));
            res = ssd1306_write_string(Node->display_num, 0, 0, Node->text,strlen(Node->text), FONT_16);
            if(res) {

            } else {
                LOG_ERROR(DASHBOARD, "Display %u Err", Node->display_num);
            }
        } else {
            LOG_ERROR(DASHBOARD, "DisplayData %u Err", Node->display_num);
        }
#endif /*HAS_SSD1306*/

#if defined(HAS_TIME) && defined(HAS_PC)
        res = time_get_cur(&Node->time_date);
        if(res) {
            sprintf(Node->text, "%s" CRLF "UpTime: %4.1f s", TimeDate2StrShort(&Node->time_date), MSEC_2_SEC(up_time));
        }
#endif

#ifdef HAS_DISPLAY // That is SW display
        if(res) {
            // display_sram_clean(Node->display_num);
            LOG_DEBUG(DASHBOARD, "St:%u,[%s] %u Byte", Node->run_text_start_index,
                      &Node->text[Node->run_text_start_index], strlen(&Node->text[Node->run_text_start_index]));
            res = display_write_string(Node->display_num, 0, 0, &Node->text[Node->run_text_start_index],
                                       strlen(&Node->text[Node->run_text_start_index]), FONT_12);
            if(res) {

            } else {
                LOG_ERROR(DASHBOARD, "DisplayErr");
            }
        }
#endif /*HAS_DISPLAY*/
    }
    return res;
}

bool dashboard_init_custom(void){
    bool res = true;
    return res;
}


static bool dashboard_init_one(uint8_t num) {
    bool res = false;
    const DashBoardConfig_t* Config = DashBoardGetConfig(num);
    if(Config) {
        DashBoardHandle_t* Node = DashBoardGetNode(num);
        if(Node) {
            LOG_WARNING(DASHBOARD, "DASHBOARD_%u Init", num);
            Node->display_num = Config->display_num;
            Node->rtc_num = Config->rtc_num;
            Node->light_sensor_num = Config->light_sensor_num;
            Node->light_nav_num = Config->light_nav_num;
            snprintf(Node->text, sizeof(Node->text), "DashBoard_%u init", num);
            // snprintf(Node->run_text, sizeof(Node->run_text), "RunText", num);
#ifdef HAS_SSD1306
            res = ssd1306_sram_clean(Node->display_num);
            res = ssd1306_write_string(Node->display_num, 0, 0, Node->text, strlen(Node->text), FONT_12);
#endif /*HAS_SSD1306*/

#ifdef HAS_DISPLAY
            res = display_sram_clean(Node->display_num);
            res = display_write_string(Node->display_num, 0, 0, Node->text, strlen(Node->text), FONT_12);
#endif /*HAS_DISPLAY*/
        } else {
            LOG_ERROR(DASHBOARD, "%u NodeErr", num);
        }
    } else {
        LOG_DEBUG(DASHBOARD, "%u NoConf", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(DASHBOARD, DASHBOARD, dashboard)

COMPONENT_PROC_PATTERT(DASHBOARD, DASHBOARD, dashboard)
