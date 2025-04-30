#include "gpio_pwm_commands.h"

#include <stdio.h>
#include <string.h>

#include "convert.h"
#include "data_utils.h"
#include "gpio_drv.h"
#include "gpio_pwm_drv.h"
#include "io_utils.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

bool gpio_pwm_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    (void)argv;
    if(0 == argc) {
        static const table_col_t cols[] = {{5, "dio"},  {9, "wire"},     {5, "pin"},   {5, "state"},
                                           {9, "freq"}, {9, "periodMs"}, {7, "duty%"}, {8, "phaseMs"}};
        table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
        uint16_t i = 0;
        for(i = 0; i < NUM_OF_PWM_DIO; i++) {
            if(DIO_SPARE != GpioPwmDioTable[i].satus) {
                io_printf(TABLE_SEPARATOR " %3u ", GpioPwmDioTable[i].dio);
                io_printf(TABLE_SEPARATOR " %5s ", gpio_get_name(GpioPwmDioTable[i].dio));
                io_printf(TABLE_SEPARATOR " %3u ", get_mcu_pin(GpioPwmDioTable[i].dio));
                io_printf(TABLE_SEPARATOR " %3s ", bool2name(GpioPwmDioTable[i].satus));
                GpioPwmDioTable[i].frequency = 1000.0f / ((float)GpioPwmDioTable[i].period_ms);
                io_printf(TABLE_SEPARATOR " %7.2f ", GpioPwmDioTable[i].frequency);
                io_printf(TABLE_SEPARATOR " %7u ", GpioPwmDioTable[i].period_ms);
                io_printf(TABLE_SEPARATOR "  %3u  ", GpioPwmDioTable[i].duty_cycle);
                io_printf(TABLE_SEPARATOR " %4d   " TABLE_SEPARATOR, GpioPwmDioTable[i].phase_ms);

                io_printf(CRLF);
            }
        }
        table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    } else {
        LOG_ERROR(SYS, "syntax: dad");
    }
    return res;
}

bool gpio_pwm_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t dio_num = 0;
    uint8_t state = 0;
    uint32_t period_ms = 0;
    uint8_t duty = 0;
    int32_t phase_ms = 0;
    if(5 == argc) {
        res = true;

        if(true == res) {
            res = try_str2uint8(argv[0], &dio_num);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to parse dio %s", argv[0]);
            }
        }
        if(true == res) {
            res = try_str2uint32(argv[1], &period_ms);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to parse period_ms %s", argv[1]);
            }
        }
        if(true == res) {
            res = try_str2uint8(argv[2], &duty);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to parse duty %s", argv[2]);
            }
        }
        if(true == res) {
            res = try_str2int32(argv[3], &phase_ms);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to parse phase  %s", argv[3]);
            }
        }
        if(true == res) {
            res = try_str2uint8(argv[4], &state);
            if(false == res) {
                LOG_ERROR(SYS, "Unable to parse state %s", argv[4]);
            }
        }
    } else {
        LOG_ERROR(SYS, "Usage: gpwm gpio period_ms duty phase_ms state");
        LOG_INFO(SYS, "state [on-1 off-0]");
    }

    if(true == res) {
        res = gpio_pwm_add(dio_num, period_ms, duty, phase_ms, (GpioPwmDioStates_t)state);
        if(false == res) {
            LOG_ERROR(SYS, "Unable to add GPIO PWM task");
        } else {
            LOG_INFO(SYS, "set %s period %u duty %u %% phase %d us %s", gpio_get_name(dio_num), period_ms, duty,
                     phase_ms, bool2name(state));
        }
    }

    return res;
}
