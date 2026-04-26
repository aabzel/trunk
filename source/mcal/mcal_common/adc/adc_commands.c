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

bool adc_set_vref_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t adc = 0;
    float v_ref = 3.3;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &adc);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr adc %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &v_ref);
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

bool adc_isr_command(int32_t argc, char* argv[]) {
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
