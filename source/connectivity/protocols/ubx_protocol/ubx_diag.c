#include "ubx_diag.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "data_utils.h"
#include "debug_info.h"
#include "io_utils.h"
#include "ubx_constants.h"
#include "ubx_protocol.h"

char* ReceiverMode2Str(uint8_t mode) {
    char* name = "?";
    switch(mode) {
    case RX_MODE_DISABLED:
        name = "Dis";
        break;
    case RX_MODE_SURVEY_IN:
        name = "SurveyIn";
        break;
    case RX_MODE_FIXED:
        name = "Fixed";
        break;
    default:
        break;
    }
    return name;
}

char* FixType2Str(uint8_t mode) {
    char* name = "?";
    switch(mode) {
    case FIX_TYPE_NO_FIX:
        name = "No";
        break;
    case FIX_TYPE_DEAD_RECKONING_ONLY:
        name = "DeadRecOnly";
        break;
    case FIX_TYPE_2D_FIX:
        name = "2D";
        break;
    case FIX_TYPE_3D_FIX:
        name = "3D";
        break;
    case FIX_TYPE_GNSS_DEAD_RECKONING_COMBINED:
        name = "GnssDrComb";
        break;
    case FIX_TYPE_TIME_ONLY_FIX:
        name = "TIME";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

char* class2str(uint8_t class_id) {
    char* name = "?";
    switch(class_id) {
    case UBX_CLA_NAV:
        name = "NAV";
        break;
    case UBX_CLA_RXM:
        name = "RXM";
        break;
    case UBX_CLA_INF:
        name = "INF";
        break;
    case UBX_CLA_ACK:
        name = "ACK";
        break;
    case UBX_CLA_CFG:
        name = "CFG";
        break;
    case UBX_CLA_UPD:
        name = "UPD";
        break;
    case UBX_CLA_MON:
        name = "MON";
        break;
    case UBX_CLA_TIM:
        name = "TIM";
        break;
    case UBX_CLA_ESF:
        name = "ESF";
        break;
    case UBX_CLA_MGA:
        name = "MGA";
        break;
    case UBX_CLA_SEC:
        name = "SEC";
        break;
    }
    return name;
}

const static NavId2StrLut_t NavId2strLut[] = {
    {0x01, "POSECEF"},   {0x02, "POSLLH"},  {0x03, "STATUS"},  {0x04, "DOP"},      {0x07, "PVT"},
    {0x09, "ODO"},       {0x10, "ESETODO"}, {0x11, "VELECEF"}, {0x12, "VELNED"},   {0x13, "HPPOSECEF"},
    {0x14, "HPPOSLLH"},  {0x20, "TIMEGPS"}, {0x21, "TIMEUTC"}, {0x22, "CLOCK"},    {0x23, "TIMEGLO"},
    {0x24, "TIMEBDS"},   {0x25, "TIMEGAL"}, {0x26, "TIMELS"},  {0x27, "TIMEQZSS"}, {0x32, "SBAS"},
    {0x34, "ORB"},       {0x35, "SAT"},     {0x36, "COV"},     {0x39, "GEOFENCE"}, {0x3b, "SVIN"},
    {0x3c, "RELPOSNED"}, {0x42, "SLAS"},    {0x43, "SIG"},     {0x61, "EOE"},      {0x62, "PL"}};

static char* NavId2str(uint8_t id) {
    char* nameId = "?";
    uint16_t i = 0;
    for(i = 0; i < ARRAY_SIZE(NavId2strLut); i++) {
        if(id == NavId2strLut[i].id) {
            nameId = NavId2strLut[i].name;
        }
    }
    return nameId;
}

char* ClassId2str(uint8_t cls, uint8_t id) {
    static char name[40];
    char* nameCl = "?";
    char* nameId = "?";
    switch(cls) {
    case UBX_CLA_NAV:
        nameCl = "NAV";
        nameId = NavId2str(id);
        break;
    case UBX_CLA_RXM:
        nameCl = "RXM";
        break;
    case UBX_CLA_INF:
        nameCl = "INF";
        break;
    case UBX_CLA_ACK:
        nameCl = "ACK";
        break;
    case UBX_CLA_CFG:
        nameCl = "CFG";
        break;
    case UBX_CLA_UPD:
        nameCl = "UPD";
        break;
    case UBX_CLA_MON:
        nameCl = "MON";
        break;
    case UBX_CLA_TIM:
        nameCl = "TIM";
        break;
    case UBX_CLA_ESF:
        nameCl = "ESF";
        break;
    case UBX_CLA_MGA:
        nameCl = "MGA";
        break;
    case UBX_CLA_SEC:
        nameCl = "SEC";
        break;
    }
    snprintf(name, sizeof(name), "CLA:0x%02x=%s ID:0x%02x=%s", cls, nameCl, id, nameId);
    return name;
}

#ifdef HAS_LOG
bool ubx_print_frame(uint8_t* frame) {
    bool res = false;
    io_printf(CRLF "%s", class2str(frame[UBX_INDEX_CLS]));
    io_printf("0x%02x" CRLF, frame[UBX_INDEX_ID]);
    uint16_t* len = NULL;
    len = (uint16_t*)&frame[UBX_INDEX_LEN];
    print_mem(&frame[UBX_INDEX_PAYLOAD], *len, true, false, false, true);
    io_printf(CRLF);
    return res;
}
#endif
