#ifndef I2S_CUSTOM_TYPES_H
#define I2S_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "i2s_custom_const.h"
#include "clock_custom_const.h"
#include "clock_const.h"
#include "i2s_register_types.h"
#include "microcontroller_const.h"
#include "dma_types.h"

typedef union {
	volatile uint8_t buff[36];
	volatile uint32_t reg[9];
    struct {
        volatile SpiCtrl1_t SPI_CTRL1;  // offset 0x00
        volatile SpiCtrl2_t SPI_CTRL2;   // offset 0x04
        volatile SpiStatus_t SPI_STS;   // offset 0x08
        volatile SpiData_t SPI_DT;   // offset   0x0C
        volatile SpiCpoly_t SPI_CPOLY;   // offset   0x10
        volatile SpiRxCrc_t SPI_RCRC;   // offset 0x14
        volatile SpiTxCrc_t SPI_TCRC;   // offset 0x18
        volatile SpiI2sCtrl_t SPI_I2SCTRL;   // offset 0x1C
        volatile SpiI2sClkPrescaler_t SPI_I2SCLKP;   // offset 0x20
    };
}I2sRegMap_t;

#define I2S_CUSTOM_VARIABLES      \
    spi_type *I2Sx;

typedef struct {
    uint8_t num;
    bool valid;
    spi_type *I2Sx;
    ClockBus_t clock_bus;
    crm_periph_clock_type clock_type;
    IRQn_Type irq_n;
    DmaIsrHandler_t CallBackTxHalf;
    DmaIsrHandler_t CallBackTxDone;
    DmaIsrHandler_t CallBackRxHalf;
    DmaIsrHandler_t CallBackRxDone;
}I2sInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* I2S_CUSTOM_TYPES_H */
