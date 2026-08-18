#ifndef SA51034_CONST_H
#define SA51034_CONST_H

#include "time_mcal.h"
#include "sa51034_dep.h"

#define SA51034_REG_CNT 3

#define REG_SET_TRY_CNT 1
#define SA51034_VERIFY_DURATION_MS 1000
#define SA51034_VERIFY_AMP 1000

#define SA51034_PERIOD_US SEC_2_USEC(1)


//13. REGISTER DESCRIPTION
typedef enum {
    SA51034_REG_LATCHED_FAULT  = 0x01, /*Latched Fault Register*/
    SA51034_REG_STATUS_AND_LOAD_DIAGNOSTIC = 0x02, /*Status and Load Diagnostic Register*/
    SA51034_REG_CONTROL = 0x03, /*Control Register*/


    SA51034_REG_UNDEF = 0xFF,
} Sa51034RegAddr_t;

//Table 5. Control Register (0x03)
typedef enum {
	SA51_SW_FREQ_400KHZ = 0, /*Switching frequency set to 400kHz*/
	SA51_SW_FREQ_500KHZ = 1, /*Switching frequency set to 500kHz*/

    SA51_SW_FREQ_UNDEF = 2,
}Sa51SwFrequency_t;

//Table 5. Control Register (0x03)
typedef enum {
    SA51_GAIN_CODE_20_DB = 0, /*20dB gain*/
    SA51_GAIN_CODE_26_DB = 1, /*26dB gain*/
    SA51_GAIN_CODE_32_DB = 2, /*32dB gain*/
    SA51_GAIN_CODE_36_DB = 3, /*36dB gain*/

    SA51_GAIN_CODE_UNDEF = 5,
}Sa51GainCode_t;

//Table 5. Control Register (0x03)
typedef enum {
    SA51_POWER_LIMIT_DISABLE = 7, /*  Power limit function disable    */
    SA51_POWER_LIMIT_11_5_V = 6,  /*  Power limit to 11.5V peak output*/
    SA51_POWER_LIMIT_9_6_V = 5,   /*  Power limit to 9.6V peak output */
    SA51_POWER_LIMIT_7_5_V = 4,   /*  Power limit to 7.5V peak output */
    SA51_POWER_LIMIT_6_1_V = 3,   /*  Power limit to 6.1V peak output */
    SA51_POWER_LIMIT_4_9_V = 2,   /*  Power limit to 4.9V peak output */
    SA51_POWER_LIMIT_4_2_V = 1,   /*  Power limit to 4.2V peak output */
    SA51_POWER_LIMIT_3_4_V = 0,   /*  Power limit to 3.4V peak output */
}Sa51PowerLimit_t;

#endif /* SA51034_CONST_H */
