#ifndef RELAY_CONFIG_H
#define RELAY_CONFIG_H

#include "relay_types.h"

typedef enum {
    RELAY_NUM_UNDEF = 0,

    RELAY_NUM_OUT1_1 = 1, /* 86 PD5 OUT1_1 */
    RELAY_NUM_OUT1_2 , /* 84 PD3 OUT1_2 */
    RELAY_NUM_OUT1_3 , /* 83 PD2 OUT1_3 */
    RELAY_NUM_OUT1_4 , /* 81 PD0 OUT1_4 */

    RELAY_NUM_OUT2_1 , /* 64 PC7 OUT2_1 */
    RELAY_NUM_OUT2_2 , /* 67 PA8 OUT2_2 */
#ifndef HAS_UART1_HW_HOT_FIX
    RELAY_NUM_OUT2_3 , /* 68 PA9 OUT2_3 */
    RELAY_NUM_OUT2_4 , /* 69 PA10 OUT2_4 */
#endif

    RELAY_NUM_OUT3_1 , /* 63 PC6 OUT3_1 */
    RELAY_NUM_OUT3_2 , /* 61    PD14    OUT3_2 */
    RELAY_NUM_OUT3_3 , /* 60    PD13    OUT3_3 */
    RELAY_NUM_OUT3_4 , /* 58    PD11    OUT3_4 */

    RELAY_NUM_OUT4_1 , /* 57    PD10    OUT4_1 */
    RELAY_NUM_OUT4_2 , /* 55    PD8 OUT4_2 */
    RELAY_NUM_OUT4_3 , /* 54    PB15    OUT4_3 */
    RELAY_NUM_OUT4_4 , /* 88    PD7 OUT4_4 */

} RelayLegalNums_t;

extern const RelayConfig_t RelayConfig[];
extern RelayHandle_t RelayInstance[];

uint32_t relay_get_cnt(void);

#endif /* RELAY_CONFIG_H  */
