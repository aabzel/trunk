#include "interrupt_config.h"
//#include "sys_config.h"

#include "data_utils.h"


#define  INTERRUPT_CONFIG_DMA

#define INTERRUPT_CONFIG_UART


#define INTERRUPT_CONFIG_TIMER


#define INTERRUPT_CONFIG_EXINT

#define INTERRUPT_CONFIG_CAN


#define INTERRUPT_CONFIG_I2C

#define INTERRUPT_CONFIG_SPI


#define INTERRUPT_CONFIG_USB

const InterruptConfig_t InterruptConfig[] ={
   INTERRUPT_CONFIG_EXINT
   INTERRUPT_CONFIG_CAN
   INTERRUPT_CONFIG_DMA
   INTERRUPT_CONFIG_I2C
   INTERRUPT_CONFIG_SPI
   INTERRUPT_CONFIG_TIMER
   INTERRUPT_CONFIG_USB
   INTERRUPT_CONFIG_UART
};


uint32_t interrupt_get_cnt(void) {
    uint32_t cnt = 0;
    cnt =ARRAY_SIZE(InterruptConfig);
    return cnt;
}
