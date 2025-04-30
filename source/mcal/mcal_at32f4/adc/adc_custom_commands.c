#include "adc_commands.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "adc_custom_diag.h"
#include "adc_mcal.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "log_constants.h"
#include "log_utils.h"
#include "microcontroller_const.h"
#include "none_blocking_pause.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool adc_start_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t adc = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &adc);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr adc %s", argv[0]);
        }
    }

    if(res) {
        LOG_INFO(LG_ADC, "Start Adc%u", adc);
        res = adc_start(adc);
        if(res) {
            LOG_INFO(LG_ADC, "ADC%u Ok", adc);
        } else {
            LOG_ERROR(LG_ADC, "ADC%u Err ", adc);
        }
    } else {
        LOG_ERROR(LG_ADC, "Usage: ast AdcNum ");
    }
    return res;
}
