#ifndef I2C_CUSTOM_TYPE_H
#define I2C_CUSTOM_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "microcontroller_const.h"
#include "clock_const.h"
#include "i2c_custom_const.h"
#include "i2c_application.h"

#define I2C_CUSTOM_TYPES     \
    i2c_type *I2Cx;          \
    i2c_handle_type i2c_h;


typedef struct {
    bool valid;
    i2c_type *I2Cx;
    uint8_t num;
    ClockBus_t clock_bus;
    crm_periph_clock_type clock_type;
    IRQn_Type irq_evt_n;
    IRQn_Type irq_err_n;
}I2cInfo_t;

/* I2C_CLKCTRL
 * 11.7.5 Timing register (I2C_CLKCTRL)
 */
typedef union {
    uint32_t qword;
    struct {
        uint32_t scll :8;/*Bit 7:0  , SCL low level*/
        uint32_t sclh :8;/*Bit 15:8 , SCL high level*/
        uint32_t sdad :4;/*Bit 19:16, SDAD Data hold time */
        uint32_t scld :4;/*Bit 23:20, SCLD Data setup time*/
        uint32_t divh :4;/*Bit 27:24, High 4 bits of clock divider value*/
        uint32_t divl :4;/*Bit 31:28, Low 4 bits of clock divider value*/
    };
}I2cClkCtrl_t;


//const I2cInfo_t* I2cGetInfo(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* I2C_CUSTOM_TYPE_H */
