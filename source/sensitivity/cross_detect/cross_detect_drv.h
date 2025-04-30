#ifndef CROSS_DETECT_DRIVER_H
#define CROSS_DETECT_DRIVER_H

#include <stdbool.h>
#include <stdint.h>

#include "cross_detect_config.h"
#include "cross_detect_dep.h"
#include "cross_detect_types.h"
#include "gpio_types.h"

extern uint64_t cross_detect_period_us;
extern const CrossDetectSolutionInfo_t CrossDetectSolutionInfo[36];

CrossDetectHandle_t* CrossDetectGetNode(uint8_t num);
uint32_t cross_detect_get_lut_size(void);
U16Pair_t calc_next_uniq_u16pair(U16Pair_t pair);
bool cross_detect_init(void);
bool cross_detect_reset_pair(const CrossDetectPairInfo_t* const pair);
bool cross_detect_init_one(uint8_t num);
bool cross_detect_enable(uint8_t num, bool on_off);
bool cross_detect_proc(void);
bool cross_detect_init_pair(CrossDetectPairInfo_t* const pair, Pad_t left, Pad_t right);

#endif /* CROSS_DETECT_DRIVER_H  */
