
#ifndef GPIO_PWM_DRV_H
#define GPIO_PWM_DRV_H

#include <stdbool.h>
#include <stdint.h>

#define GPIO_PWM_PERIOD_US 1

#define NUM_OF_PWM_DIO 10U

typedef enum  { DIO_SPARE = 2U, DIO_ON = 1, DIO_OFF = 0 } GpioPwmDioStates_t;

typedef struct  {
    uint8_t dio;
    uint8_t duty_cycle;
    float frequency;
    uint32_t period_ms;
    int32_t phase_ms;
    GpioPwmDioStates_t satus; /*on off spare*/
} GpioPwmDio_t;

extern GpioPwmDio_t GpioPwmDioTable[NUM_OF_PWM_DIO];

bool gpio_pwm_add(uint8_t dio, uint32_t period_ms, uint8_t in_duty, int32_t phase_ms, GpioPwmDioStates_t in_state);
bool gpio_pwm_init(void);
bool gpio_pwm_proc(void);

#endif /* GPIO_PWM_DRV_H  */
