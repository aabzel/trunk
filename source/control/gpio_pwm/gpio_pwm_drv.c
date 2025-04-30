#include "gpio_pwm_drv.h"

#include <stdbool.h>
#include <stdint.h>

#include "clocks.h"
#include "gpio_drv.h"
#include "time_mcal.h"
#include "utils_math.h"

GpioPwmDio_t GpioPwmDioTable[NUM_OF_PWM_DIO];
static bool gpio_pwm_init_done = false;

bool gpio_pwm_init(void) {
    bool res = false;
    uint16_t i = 0;
    for(i = 0; i < NUM_OF_PWM_DIO; i++) {
        GpioPwmDioTable[i].dio = 0xFF;
        GpioPwmDioTable[i].duty_cycle = 0xFF;
        GpioPwmDioTable[i].frequency = -10.0;
        GpioPwmDioTable[i].period_ms = 0U;
        GpioPwmDioTable[i].phase_ms = 0U;
        GpioPwmDioTable[i].satus = DIO_SPARE;
        res = true;
    }
    gpio_pwm_init_done = true;
    return res;
}

bool gpio_pwm_add(uint8_t dio, uint32_t period_ms, uint8_t in_duty, int32_t phase_ms, GpioPwmDioStates_t in_state) {
    bool res = false;
    uint16_t spot_index = 0;
    uint16_t i = 0;
    for(i = 0U; i < NUM_OF_PWM_DIO; i++) {
        if(GpioPwmDioTable[i].dio == dio) {
            spot_index = i;
            res = true;
        }
    }
    if(false == res) {
        uint16_t i = 0;
        for(i = 0; i < NUM_OF_PWM_DIO; i++) {
            if(DIO_SPARE == GpioPwmDioTable[i].satus) {
                spot_index = i;
                GpioPwmDioTable[i].dio = dio;
                i = NUM_OF_PWM_DIO;
                res = true;
            }
        }
    }

    if(true == res) {
        GpioPwmDioTable[spot_index].duty_cycle = in_duty;
        GpioPwmDioTable[spot_index].phase_ms = phase_ms;
        GpioPwmDioTable[spot_index].period_ms = period_ms;
        GpioPwmDioTable[spot_index].satus = in_state;
    }
    return res;
}

static bool gpio_pwm_proc_one(uint8_t dio, uint8_t des_duty_cycle, uint32_t period_ms, int32_t phase_ms) {
    bool res = false;
    uint8_t amplitude = 0;
    uint32_t cur_time_ms = get_time_ms32();
    amplitude = pwm_sample_calc_num(cur_time_ms, period_ms, des_duty_cycle, phase_ms);
    // uint8_t amplitude = pwm_sample_calc(cur_time_us, des_frequency, des_phase, des_duty_cycle);
    res = gpio_set_state(dio, amplitude);
    return res;
}

bool gpio_pwm_proc(void) {
    bool res = false;
    if(true == gpio_pwm_init_done) {
        uint16_t i = 0;
        for(i = 0U; i < NUM_OF_PWM_DIO; i++) {
            if(DIO_ON == GpioPwmDioTable[i].satus) {
                res = gpio_pwm_proc_one(GpioPwmDioTable[i].dio, GpioPwmDioTable[i].duty_cycle,
                                        GpioPwmDioTable[i].period_ms, GpioPwmDioTable[i].phase_ms);
            }
            if(DIO_OFF == GpioPwmDioTable[i].satus) {
                res = gpio_set_state(GpioPwmDioTable[i].dio, 0);
            }
        }
    }
    return res;
}
