#include "adc_commands.h"


#include "adc_mcal.h"
#include "convert.h"
#include "log.h"

bool adc_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = adc_mcal_init();
        if(res) {
            LOG_INFO(LG_ADC, "InitOk");
        } else {
            LOG_ERROR(LG_ADC, "InitErr");
        }
    }
    return res;
}

bool adc_diag_command(int32_t argc, char* argv[]) {
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
#ifdef HAS_ADC_DIAG
        res = adc_diag(keyWord1, keyWord2);
#endif
    } else {
        LOG_ERROR(LG_ADC, "Usage: ad keyWord keyWord");
    }
    return res;
}

bool adc_voltage_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t channel = 0;
    uint8_t adc = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &adc);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr adc %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint16(argv[1], &channel);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr AdcChannel %s", argv[1]);
        }
    }

    if(res) {
        double voltage = 0;
        LOG_INFO(LG_ADC, "TryRead Adc %u Channel %u", adc, channel);
        res = adc_channel_read_voltage(adc, channel, &voltage);
        if(res) {

            LOG_INFO(LG_ADC, "ADC%u CH%u Voltage %1.3fV", adc, channel, voltage);
        }
    } else {
        LOG_ERROR(LG_ADC, "Usage: avr AdcNum Chan");
    }
    return res;
}

bool adc_code_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t adc = 0;
    uint16_t channel = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &adc);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr adc %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint16(argv[1], &channel);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr AdcChannel %s", argv[1]);
        }
    }

    if(res) {
        LOG_INFO(LG_ADC, "TryRead Adc %u Channel %u", adc, channel);
        int32_t code = 0;
        res = adc_channel_read_code(adc, channel, &code);
        if(res) {
            LOG_INFO(LG_ADC, "ADC%u CH%u Code %u=0x%x", adc, channel, code, code);
        }
    } else {
        LOG_ERROR(LG_ADC, "Usage: acr AdcNum Chan");
    }
    return res;
}

bool adc_set_vref_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t adc = 0;
    double v_ref = 3.3;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &adc);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr adc %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &v_ref);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr Vref %s", argv[1]);
        }
    }

    if(res) {
        res = adc_set_vref(adc, v_ref);
        if(res) {
            LOG_INFO(SYS, "SetOk ADC%u Vref %f V", adc, v_ref);
        } else {
            LOG_ERROR(SYS, "SetErr ADC%u Vref %f V", adc, v_ref);
        }
    }
    return res;
}


bool adc_isr_command(int32_t argc, char* argv[]){
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
#ifdef HAS_ADC_DIAG
        res = adc_diag_isr(keyWord1, keyWord2);
#endif
    } else {
        LOG_ERROR(LG_ADC, "Usage: as keyWord keyWord");
    }
    return res;
}


bool adc_channel_diag_command(int32_t argc, char* argv[]){
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
#ifdef HAS_ADC_DIAG
        res = adc_channel_diag(keyWord1, keyWord2);
#endif
    } else {
        LOG_ERROR(LG_ADC, "Usage: acd keyWord keyWord");
    }
    return res;
}
