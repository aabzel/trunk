#include "dac_channel_commands.h"

#include "dac_channel_mcal.h"
#include "convert.h"
#include "log.h"


bool dac_channel_code_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t channel = 0;
    uint8_t dac_num = 0;
    uint16_t code = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &dac_num);
    }

    if(2 <= argc) {
        res = try_str2uint16(argv[1], &channel);
    }

    if(2 <= argc) {
        res = try_str2uint16(argv[2], &code);
    }

    if(res) {
        LOG_INFO(LG_DAC, "TryRead Dac %u Channel %u,code:%u", dac_num, channel,code);
        res = dac_channel_code_set(  dac_num,   channel,     code);
        if(res) {
            LOG_INFO(LG_DAC, "DAC%u,CH%u,Code:%u", dac_num, channel, code);
        }
    } else {
        LOG_ERROR(LG_DAC, "Usage: dccs DacNum Ch Code");
    }
    return res;
}


bool dac_channel_voltage_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t channel = 0;
    uint8_t dac_num = 0;
    float voltage = 0 ;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &dac_num);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr dac %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint16(argv[1], &channel);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr DacChannel %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2float(argv[2], &voltage);
    }

    if(res) {
        LOG_INFO(LG_DAC, "Setm,Dac:%u,Channel:%u,Volt:%f", dac_num, channel,voltage);
        res = dac_channel_voltage_set(dac_num, channel,  voltage);
    } else {
        LOG_ERROR(LG_DAC, "Usage: avr DacNum Chan");
    }
    return res;
}

bool dac_channel_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";

    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }

    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(res) {
#ifdef HAS_DAC_DIAG
        res = dac_channel_diag(keyWord1, keyWord2);
#endif
    } else {
        LOG_ERROR(LG_DAC, "Usage: acd keyWord keyWord");
    }
    return res;
}

bool dac_code_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t dac = 0;
    uint16_t channel = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &dac);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr dac %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint16(argv[1], &channel);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr DacChannel %s", argv[1]);
        }
    }

    if(res) {
        LOG_INFO(LG_DAC, "TryRead Dac %u Channel %u", dac, channel);
        int32_t code = 0;
        res = dac_channel_code_read(dac, channel, &code);
        if(res) {
            LOG_INFO(LG_DAC, "DAC%u CH%u Code %u=0x%x", dac, channel, code, code);
        }
    } else {
        LOG_ERROR(LG_DAC, "Usage: acr DacNum Chan");
    }
    return res;
}
