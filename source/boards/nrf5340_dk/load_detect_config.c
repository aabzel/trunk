#include "load_detect_config.h"

#ifndef HAS_LOAD_DETECT
#error "Add HAS_LOAD_DETECT"
#endif /*HAS_LOAD_DETECT*/

#include "data_utils.h"
#include "gpio_mcal.h"


const LoadDetectPinConfig_t LoadDetectPinConfig[] = {
    {.num = 1, .pin_num = 1, .pad={.port=0, .pin=4}, .valid=true,},
    {.num = 1, .pin_num = 2, .pad={.port=0, .pin=5}, .valid=true,},
    {.num = 1, .pin_num = 3, .pad={.port=0, .pin=10}, .valid=true,},
#if 0
    {.num = 1, .pin_num = 0, .pad={.port=0, .pin=0}, .valid=true,},
    {.num = 1, .pin_num = 1, .pad={.port=0, .pin=1}, .valid=true,},
    {.num = 1, .pin_num = 2, .pad={.port=0, .pin=2}, .valid=true,},
    {.num = 1, .pin_num = 3, .pad={.port=0, .pin=3}, .valid=true,},
    {.num = 1, .pin_num = 5, .pad={.port=0, .pin=5}, .valid=true,},
    {.num = 1, .pin_num = 6, .pad={.port=0, .pin=6}, .valid=true,},
    {.num = 1, .pin_num = 7, .pad={.port=0, .pin=7}, .valid=true,},
    {.num = 1, .pin_num = 8, .pad={.port=0, .pin=8}, .valid=true,},
    {.num = 1, .pin_num = 9, .pad={.port=0, .pin=9}, .valid=true,},
    {.num = 1, .pin_num = 10, .pad={.port=0, .pin=10}, .valid=true,},
    {.num = 1, .pin_num = 11, .pad={.port=0, .pin=11}, .valid=true,},
    {.num = 1, .pin_num = 12, .pad={.port=0, .pin=12}, .valid=true,},
    {.num = 1, .pin_num = 13, .pad={.port=0, .pin=13}, .valid=true,},
    {.num = 1, .pin_num = 14, .pad={.port=0, .pin=14}, .valid=true,},
    {.num = 1, .pin_num = 15, .pad={.port=0, .pin=15}, .valid=true,},
    {.num = 1, .pin_num = 16, .pad={.port=0, .pin=16}, .valid=true,},
    {.num = 1, .pin_num = 17, .pad={.port=0, .pin=17}, .valid=true,},
    {.num = 1, .pin_num = 18, .pad={.port=0, .pin=18}, .valid=true,},
    {.num = 1, .pin_num = 19, .pad={.port=0, .pin=19}, .valid=true,},
    {.num = 1, .pin_num = 20, .pad={.port=0, .pin=20}, .valid=true,},
    {.num = 1, .pin_num = 21, .pad={.port=0, .pin=21}, .valid=true,},
    {.num = 1, .pin_num = 22, .pad={.port=0, .pin=22}, .valid=true,},
    {.num = 1, .pin_num = 23, .pad={.port=0, .pin=23}, .valid=true,},
    {.num = 1, .pin_num = 24, .pad={.port=0, .pin=24}, .valid=true,},
    {.num = 1, .pin_num = 25, .pad={.port=0, .pin=25}, .valid=true,},
    {.num = 1, .pin_num = 26, .pad={.port=0, .pin=26}, .valid=true,},
    {.num = 1, .pin_num = 27, .pad={.port=0, .pin=27}, .valid=true,},
    {.num = 1, .pin_num = 28, .pad={.port=0, .pin=28}, .valid=true,},
    {.num = 1, .pin_num = 29, .pad={.port=0, .pin=29}, .valid=true,},
    {.num = 1, .pin_num = 30, .pad={.port=0, .pin=30}, .valid=true,},
    {.num = 1, .pin_num = 31, .pad={.port=0, .pin=31}, .valid=true,},
    {.num = 1, .pin_num = 32, .pad={.port=1, .pin=0}, .valid=true,},
    {.num = 1, .pin_num = 33, .pad={.port=1, .pin=1}, .valid=true,},
    {.num = 1, .pin_num = 34, .pad={.port=1, .pin=2}, .valid=true,},
    {.num = 1, .pin_num = 35, .pad={.port=1, .pin=3}, .valid=true,},
    {.num = 1, .pin_num = 36, .pad={.port=1, .pin=4}, .valid=true,},
    {.num = 1, .pin_num = 37, .pad={.port=1, .pin=5}, .valid=true,},
    {.num = 1, .pin_num = 38, .pad={.port=1, .pin=6}, .valid=true,},
    {.num = 1, .pin_num = 39, .pad={.port=1, .pin=7}, .valid=true,},
    {.num = 1, .pin_num = 40, .pad={.port=1, .pin=8}, .valid=true,},
    {.num = 1, .pin_num = 41, .pad={.port=1, .pin=9}, .valid=true,},
    {.num = 1, .pin_num = 42, .pad={.port=1, .pin=10}, .valid=true,},
    {.num = 1, .pin_num = 43, .pad={.port=1, .pin=11}, .valid=true,},
    {.num = 1, .pin_num = 44, .pad={.port=1, .pin=12}, .valid=true,},
    {.num = 1, .pin_num = 45, .pad={.port=1, .pin=13}, .valid=true,},
    {.num = 1, .pin_num = 46, .pad={.port=1, .pin=14}, .valid=true,},
    {.num = 1, .pin_num = 47, .pad={.port=1, .pin=15}, .valid=true,},
#endif
#ifdef HAS_DWM1000
    {.num = 2, .pin_num = 48, .pad={.port=0, .pin=0}, .valid=true,},
    {.num = 2, .pin_num = 49, .pad={.port=0, .pin=1}, .valid=true,},
    {.num = 2, .pin_num = 50, .pad={.port=0, .pin=2}, .valid=true,},
    {.num = 2, .pin_num = 51, .pad={.port=0, .pin=3}, .valid=true,},
    {.num = 2, .pin_num = 52, .pad={.port=0, .pin=4}, .valid=true,},
    {.num = 2, .pin_num = 53, .pad={.port=0, .pin=5}, .valid=true,},
    {.num = 2, .pin_num = 54, .pad={.port=0, .pin=6}, .valid=true,},
    {.num = 2, .pin_num = 55, .pad={.port=0, .pin=7}, .valid=true,},
    {.num = 2, .pin_num = 56, .pad={.port=0, .pin=8}, .valid=true,},
#endif
#ifdef HAS_DWM3000
    {.num = 3, .pin_num = 57, .pad={.port=0, .pin=0}, .valid=true,},
    {.num = 3, .pin_num = 58, .pad={.port=0, .pin=1}, .valid=true,},
    {.num = 3, .pin_num = 59, .pad={.port=0, .pin=2}, .valid=true,},
    {.num = 3, .pin_num = 60, .pad={.port=0, .pin=3}, .valid=true,},
    {.num = 3, .pin_num = 61, .pad={.port=0, .pin=4}, .valid=true,},
    {.num = 3, .pin_num = 62, .pad={.port=0, .pin=5}, .valid=true,},
    {.num = 3, .pin_num = 63, .pad={.port=0, .pin=6}, .valid=true,},
    {.num = 3, .pin_num = 64, .pad={.port=0, .pin=7}, .valid=true,},
    {.num = 3, .pin_num = 65, .pad={.port=0, .pin=8}, .valid=true,},
#endif
};

LoadDetectPinInfo_t LoadDetectPinInstance[] = {
        {.num = 1, .pin_num = 1,  .valid=true,},
        {.num = 1, .pin_num = 2,  .valid=true,},
        {.num = 1, .pin_num = 3,  .valid=true,},
#if 0
        {.num = 1, .pin_num = 3,  .valid=true,},
        {.num = 1, .pin_num = 4,  .valid=true,},
        {.num = 1, .pin_num = 5,  .valid=true,},
        {.num = 1, .pin_num = 6,  .valid=true,},
        {.num = 1, .pin_num = 7,  .valid=true,},
        {.num = 1, .pin_num = 8,  .valid=true,},
        {.num = 1, .pin_num = 9,  .valid=true,},
        {.num = 1, .pin_num = 10,  .valid=true,},
        {.num = 1, .pin_num = 11,  .valid=true,},
        {.num = 1, .pin_num = 12,  .valid=true,},
        {.num = 1, .pin_num = 13,  .valid=true,},
        {.num = 1, .pin_num = 14,  .valid=true,},
        {.num = 1, .pin_num = 15,  .valid=true,},
        {.num = 1, .pin_num = 16,  .valid=true,},
        {.num = 1, .pin_num = 17,  .valid=true,},
        {.num = 1, .pin_num = 18,  .valid=true,},
        {.num = 1, .pin_num = 19,  .valid=true,},
        {.num = 1, .pin_num = 20,  .valid=true,},
        {.num = 1, .pin_num = 21,  .valid=true,},
        {.num = 1, .pin_num = 22,  .valid=true,},
        {.num = 1, .pin_num = 23,  .valid=true,},
        {.num = 1, .pin_num = 24,  .valid=true,},
        {.num = 1, .pin_num = 25,  .valid=true,},
        {.num = 1, .pin_num = 26,  .valid=true,},
        {.num = 1, .pin_num = 27,  .valid=true,},
        {.num = 1, .pin_num = 28,  .valid=true,},
        {.num = 1, .pin_num = 29,  .valid=true,},
        {.num = 1, .pin_num = 30,  .valid=true,},
        {.num = 1, .pin_num = 31,  .valid=true,},
        {.num = 1, .pin_num = 32,  .valid=true,},
        {.num = 1, .pin_num = 33,  .valid=true,},
        {.num = 1, .pin_num = 34,  .valid=true,},
        {.num = 1, .pin_num = 35,  .valid=true,},
        {.num = 1, .pin_num = 36,  .valid=true,},
        {.num = 1, .pin_num = 37,  .valid=true,},
        {.num = 1, .pin_num = 38,  .valid=true,},
        {.num = 1, .pin_num = 39,  .valid=true,},
        {.num = 1, .pin_num = 40,  .valid=true,},
        {.num = 1, .pin_num = 41,  .valid=true,},
        {.num = 1, .pin_num = 42,  .valid=true,},
        {.num = 1, .pin_num = 43,  .valid=true,},
        {.num = 1, .pin_num = 44,  .valid=true,},
        {.num = 1, .pin_num = 45,  .valid=true,},
        {.num = 1, .pin_num = 46,  .valid=true,},
        {.num = 1, .pin_num = 47,  .valid=true,},
#endif
#ifdef HAS_DWM1000
        {.num = 2, .pin_num = 48,  .valid=true,},
        {.num = 2, .pin_num = 49,  .valid=true,},
        {.num = 2, .pin_num = 50,  .valid=true,},
        {.num = 2, .pin_num = 51,  .valid=true,},
        {.num = 2, .pin_num = 52,  .valid=true,},
        {.num = 2, .pin_num = 53,  .valid=true,},
        {.num = 2, .pin_num = 54,  .valid=true,},
        {.num = 2, .pin_num = 55,  .valid=true,},
        {.num = 2, .pin_num = 56,  .valid=true,},
#endif
#ifdef HAS_DWM3000
        {.num = 3, .pin_num = 57,  .valid=true,},
        {.num = 3, .pin_num = 58,  .valid=true,},
        {.num = 3, .pin_num = 59,  .valid=true,},
        {.num = 3, .pin_num = 60,  .valid=true,},
        {.num = 3, .pin_num = 61,  .valid=true,},
        {.num = 3, .pin_num = 62,  .valid=true,},
        {.num = 3, .pin_num = 63,  .valid=true,},
        {.num = 3, .pin_num = 64,  .valid=true,},
        {.num = 3, .pin_num = 65,  .valid=true,},
#endif
};
/*num counrs from 1*/
const LoadDetectConfig_t LoadDetectConfig[] = {
    {.num = 1, .name="MCUgpio", .valid=true,  .gpio_class=GPIO_CLASS_MCU, },
#ifdef HAS_DWM1000
    {.num = 2, .name="DW1000gpio", .valid=true,  .gpio_class=GPIO_CLASS_DW1000,},
#endif /*HAS_DWM1000*/
#ifdef HAS_DWM3000
    {.num = 3, .name="DW3000gpio", .valid=true,  .gpio_class=GPIO_CLASS_DW3000,},
#endif /*HAS_DWM3000*/
};

LoadDetectHandle_t LoadDetectInstance[] = {
    {.num = 1, .valid=true, },
#ifdef HAS_DWM1000
    {.num = 2, .valid=true, },
#endif /*HAS_DWM1000*/
#ifdef HAS_DWM3000
    {.num = 3, .valid=true, },
#endif /*HAS_DWM3000*/
};

uint32_t load_detect_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(LoadDetectConfig);
    uint32_t cnt_ints = ARRAY_SIZE(LoadDetectInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}

uint32_t load_detect_get_pin_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(LoadDetectPinConfig);
    uint32_t cnt_ints = ARRAY_SIZE(LoadDetectPinInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}

