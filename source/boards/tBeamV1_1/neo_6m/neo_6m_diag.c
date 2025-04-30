#include "zed_f9p_diag.h"
 
#include <stdint.h>
#include <stdio.h>

#include "timer_utils.h"
#include "gnss_utils.h"
#include "timer_utils.h"
#include "zed_f9p_drv.h"

static char name[40] = "";

char *mSec2str(uint16_t m_sec){
    snprintf(name, sizeof(name), "%u ms=%f s", m_sec, MSEC_2_S(m_sec));
    return name;
}

char *Distance2str(double distance){
    snprintf(name, sizeof(name), "%f m", distance);
    return name;
}

char *GnssDot2str(GnssCoordinate_t coordinate){
    snprintf(name, sizeof(name), "%f %f", coordinate.latitude, coordinate.longitude);
    return name;
}

char *RtkFixDur2str(uint32_t time_ms){
    snprintf(name, sizeof(name), "%7.1fs=%7.1fmin=%7.2f h",
             MSEC_2_S(time_ms),
             MSEC_2_MIN(time_ms),
             MSEC_2_H(time_ms)
             );
    return name;
}

char *mm2str(uint32_t base_acc_mm){
    snprintf(name, sizeof(name), "%u mm=%f m", base_acc_mm, MM_TO_METER(base_acc_mm));
    return name;
}

char *OnOff2str(bool status){
    char *out_name ="-";
    switch(status){
    case true: out_name ="On";break;
    case false: out_name ="Off";break;
    }
    return out_name;
}

char *uint2str(uint32_t val){
    snprintf(name, sizeof(name), "%u", val);
    return name;
}

const char *rtk_mode2str(uint8_t rtk_code) {
    const char *name ="undef";
    switch(rtk_code){
    case RTK_NONE:
        name ="Norm";
        break;
    case RTK_BASE_SURVEY_IN:
        name ="BaseSurveyIn";
        break;
    case RTK_BASE_FIX:
        name ="BaseFix";
        break;
    case RTK_ROVER:
        name ="Rover";
        break;
    default:
        name ="error";
        break;
    }
    return name;
}
