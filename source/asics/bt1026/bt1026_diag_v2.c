#include "bt1026_diag.h"

#include <stdint.h>

#include "bt1026_const.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log_utils.h"

#ifndef HAS_BT1026
#error "+HAS_BT1026"
#endif

char* Bt1026I2sBusRoleToStr(uint8_t bus_mode) {
    char* name = "?";
    switch(bus_mode) {
    case BT1026_I2SMODE_SLAVE:
        name = "Slave";
        break;
    case BT1026_I2SMODE_MASTER:
        name = "Master";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

char* Bt1026ResolutionToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case RES_16_BIT:
        name = "16";
        break;
    case RES_24_BIT:
        name = "24";
        break;
    case RES_32_BIT:
        name = "32";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

char* Bt1026SampleRateToStr(uint8_t code) {
    char* name = "?";
    switch(code) {
    case BT_SAMPLE_RATE_44100_HZ:
        name = "44100";
        break;
    case BT_SAMPLE_RATE_48000_HZ:
        name = "48000";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

bool parse_i2s_config(uint8_t byte_val) {
    bool res = false;
    Bt1026I2sConfig_t I2sCfg;
    I2sCfg.byte = byte_val;
    cli_printf("RegVal: 0x%02x 0b%s " CRLF, byte_val, utoa_bin8(byte_val));
    cli_printf("5-6 resolution: %u=%s bit" CRLF, I2sCfg.resolution, Bt1026ResolutionToStr(I2sCfg.resolution));
    cli_printf("3-4 format: %u " CRLF, I2sCfg.format);
    cli_printf("2 sample_rate: %u=%s" CRLF, I2sCfg.sample_rate, Bt1026SampleRateToStr(I2sCfg.sample_rate));
    cli_printf("1 role: %u=%s" CRLF, I2sCfg.role, Bt1026I2sBusRoleToStr(I2sCfg.role));
    cli_printf("0 status: %u=%s" CRLF, I2sCfg.status, OnOffToStr(I2sCfg.status));

    return res;
}
