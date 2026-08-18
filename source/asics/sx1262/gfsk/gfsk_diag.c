#include "gfsk_diag.h"

#include <stdio.h>

#include "data_utils.h"
#include "gfsk_constants.h"

static const BandWithVal_t BandWithLut[] = {
    {GFSK_BW_4800, 4800},     {GFSK_BW_5800, 5800},     {GFSK_BW_7300, 7300},     {GFSK_BW_9700, 9700},
    {GFSK_BW_11700, 11700},   {GFSK_BW_14600, 14600},   {GFSK_BW_19500, 19500},   {GFSK_BW_23400, 23400},
    {GFSK_BW_29300, 29300},   {GFSK_BW_39000, 39000},   {GFSK_BW_46900, 46900},   {GFSK_BW_58600, 58600},
    {GFSK_BW_78200, 78200},   {GFSK_BW_93800, 93800},   {GFSK_BW_117300, 117300}, {GFSK_BW_156200, 156200},
    {GFSK_BW_187200, 187200}, {GFSK_BW_234300, 234300}, {GFSK_BW_312000, 312000}, {GFSK_BW_373600, 373600},
    {GFSK_BW_467000, 467000}};

char* SyncWordToStr(uint64_t syn_word) {
    static char name[30] = "";
    snprintf(name, sizeof(name), "0x%llx", syn_word);
    return name;
}

char* PreDetLenToStr(uint8_t code) {
    uint8_t num_bytes = 0;
    switch(code) {
    case PLE_DET_OFF:
        num_bytes = 0;
        break;
    case PLE_DET_1BYTE:
        num_bytes = 1;
        break;
    case PLE_DET_2BYTE:
        num_bytes = 2;
        break;
    case PLE_DET_3BYTE:
        num_bytes = 3;
        break;
    case PLE_DET_4BYTE:
        num_bytes = 4;
        break;
    default:
        num_bytes = 0;
        break;
    }
    static char name[30] = "";
    snprintf(name, sizeof(name), "%u Byte", num_bytes);
    return name;
}

char* SyncWordLenToStr(uint8_t bits_cnt){
    static char name[30] = "";
    snprintf(name, sizeof(name), "%u Bits=%.1f Bytes", bits_cnt, ((double)bits_cnt)/8.0);
    return name;
}


char* CrcToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case CRC_OFF:
        name = "Off";
        break;
    case CRC_1BYTE:
        name = "1Byte";
        break;
    case CRC_2BYTE:
        name = "2Byte";
        break;
    case CRC_1BYTE_INV:
        name = "1ByteInv";
        break;
    case CRC_2BYTE_INV:
        name = "2ByteInv";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

uint32_t GfskBandWith2Hz(uint8_t code) {
    uint32_t i = 0;
    uint32_t bandwith_hz=0;
    for(i = 0; i < ARRAY_SIZE(BandWithLut); i++) {
        if(code == BandWithLut[i].code) {
            bandwith_hz= BandWithLut[i].bandwith_hz;
        }
    }
    return bandwith_hz;
}

char* GfskBandwithToStr(uint8_t code) {
    static char name[30] = "??";
    uint32_t bandwith_hz = GfskBandWith2Hz(code);
    snprintf(name, sizeof(name), "%f kHz", ((double)bandwith_hz) / 1000.0);
    return name;
}


char* GfskPacetTypeToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case GFSK_PACKET_VAR:
        name = "PktVar";
        break;
    case GFSK_PACKET_FIXED:
        name = "PktFix";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

char* PulseShapeToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case PSH_NO:
        name = "No";
        break;
    case PSH_Gaussian_BT_0_3:
        name = "Gaus0.3";
        break;
    case PSH_Gaussian_BT_0_5:
        name = "Gaus0.5";
        break;
    case PSH_Gaussian_BT_0_7:
        name = "Gaus0.7";
        break;
    case PSH_Gaussian_BT_1_0:
        name = "Gaus1.0";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}
