#include "cross_detect_config.h"

#ifndef HAS_CROSS_DETECT
#error "Add HAS_CROSS_DETECT"
#endif /*HAS_CROSS_DETECT*/

#include "data_utils.h"
#include "gpio_mcal.h"
#include "log.h"

const CrossDetectPinConfig_t CrossDetectPinConfig[CROSS_DETECT_PIN_CNT] = {
    {.num = 1, .pin_num = 1, .pad={.port=0, .pin=4}, .valid=true,}, /*A0 AIN0 P2.1*/
    {.num = 1, .pin_num = 2, .pad={.port=0, .pin=5}, .valid=true,}, /*A1 P0.05 AIN1*/
    {.num = 1, .pin_num = 3, .pad={.port=0, .pin=6}, .valid=true,}, /*A0 AIN0 P2.1*/
    {.num = 1, .pin_num = 4, .pad={.port=0, .pin=7}, .valid=true,}, /*A0 AIN0 P2.1*/
    {.num = 1, .pin_num = 5, .pad={.port=0, .pin=8}, .valid=true,}, /*A0 AIN0 P2.1*/
    {.num = 1, .pin_num = 6, .pad={.port=0, .pin=9}, .valid=true,}, /*A0 AIN0 P2.1*/
    {.num = 1, .pin_num = 7, .pad={.port=0, .pin=13}, .valid=true,}, /**/
    {.num = 1, .pin_num = 8, .pad={.port=0, .pin=14}, .valid=true,}, /**/
    {.num = 1, .pin_num = 9, .pad={.port=0, .pin=15}, .valid=true,}, /**/
    {.num = 1, .pin_num = 10, .pad={.port=0, .pin=16}, .valid=true,}, /**/
    {.num = 1, .pin_num = 11, .pad={.port=0, .pin=17}, .valid=true,}, /**/
    {.num = 1, .pin_num = 12, .pad={.port=0, .pin=18}, .valid=true,}, /**/
    {.num = 1, .pin_num = 13, .pad={.port=0, .pin=19}, .valid=true,}, /**/
    {.num = 1, .pin_num = 14, .pad={.port=0, .pin=21}, .valid=true,}, /**/
    {.num = 1, .pin_num = 15, .pad={.port=0, .pin=23}, .valid=true,}, /**/
    {.num = 1, .pin_num = 16, .pad={.port=0, .pin=24}, .valid=true,}, /**/
    {.num = 1, .pin_num = 17, .pad={.port=0, .pin=25}, .valid=true,}, /**/
    {.num = 1, .pin_num = 18, .pad={.port=0, .pin=26}, .valid=true,}, /**/
    {.num = 1, .pin_num = 19, .pad={.port=0, .pin=27}, .valid=true,}, /**/
    {.num = 1, .pin_num = 20, .pad={.port=1, .pin=2}, .valid=true,}, /**/
    {.num = 1, .pin_num = 21, .pad={.port=1, .pin=3}, .valid=true,}, /**/
    {.num = 1, .pin_num = 22, .pad={.port=1, .pin=4}, .valid=true,}, /**/
    {.num = 1, .pin_num = 23, .pad={.port=1, .pin=5}, .valid=true,}, /**/
    {.num = 1, .pin_num = 24, .pad={.port=1, .pin=6}, .valid=true,}, /**/
    {.num = 1, .pin_num = 25, .pad={.port=1, .pin=7}, .valid=true,}, /**/
    {.num = 1, .pin_num = 26, .pad={.port=1, .pin=8}, .valid=true,}, /**/
    {.num = 1, .pin_num = 27, .pad={.port=1, .pin=9}, .valid=true,}, /**/
    {.num = 1, .pin_num = 28, .pad={.port=1, .pin=10}, .valid=true,}, /**/
    {.num = 1, .pin_num = 29, .pad={.port=1, .pin=11}, .valid=true,}, /**/
    {.num = 1, .pin_num = 30, .pad={.port=1, .pin=12}, .valid=true,}, /**/
    {.num = 1, .pin_num = 31, .pad={.port=1, .pin=13}, .valid=true,}, /**/
    {.num = 1, .pin_num = 32, .pad={.port=1, .pin=14}, .valid=true,}, /**/
    {.num = 1, .pin_num = 33, .pad={.port=1, .pin=15}, .valid=true,}, /**/
};

CrossDetectResult_t CrossDetectResult[CROSS_DETECT_PIN_CNT][CROSS_DETECT_PIN_CNT] = { 0 };

/*num counrs from 1*/
const CrossDetectConfig_t CrossDetectConfig[] = {
    {.num = 1, .name="MCUgpio", .valid=true,},
};

CrossDetectHandle_t CrossDetectInstance[] = {
    {.num = 1, .valid = true, },
};

uint32_t cross_detect_get_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(CrossDetectConfig);
    return cnt;
}

uint32_t cross_detect_get_pin_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(CrossDetectPinConfig);
    return cnt;
}

