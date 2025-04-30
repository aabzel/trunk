#include "uwb_diag.h"

#include <stdio.h>

#include "uwb_if.h"

const char* UwbDistance2Str(double dist) {
    static char text[20] = "NoData";
    bool res = false;
    res = uwb_is_vaild_distance(dist);
    if(res) {
        snprintf(text, sizeof(text), "%7.3f", dist);
    } else {
        snprintf(text, sizeof(text), "Inval");
    }
    return text;
}

const char* UwbRole2Str(UwbRole_t role) {
    const char* name = "?";
    switch((uint8_t)role) {
    case UWB_ROLE_ANCOR:
        name = "Responder";
        break;
    case UWB_ROLE_TAG:
        name = "Initiator";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}
