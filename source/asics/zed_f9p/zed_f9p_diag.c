#include "zed_f9p_diag.h"
 
#include <stdint.h>
#include <stdio.h>

#include "timer_utils.h"
#include "gnss_utils.h"
#include "timer_utils.h"
#include "zed_f9p_drv.h"

static char name[40] = "";

char *Distance2str(double distance){
    snprintf(name, sizeof(name), "%f m", distance);
    return name;
}

char *GnssDot2str(GnssCoordinate_t coordinate){
    snprintf(name, sizeof(name), "%f %f", coordinate.latitude, coordinate.longitude);
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
