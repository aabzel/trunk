#ifndef W25Q32JV_TYPES_H
#define W25Q32JV_TYPES_H

#include "std_includes.h"
//#include "data_types.h"
#include "w25q32jv_const.h"
#include "w25q32jv_registers_types.h"
#ifdef HAS_SPIFI
#include "mik32_hal_spifi.h"
#endif

#ifdef HAS_GPIO
#include "gpio_types.h"

#define W25Q32JV_GPIO_VARIABLE     \
    Pad_t chip_select;             \
    Pad_t reset;                   \
    Pad_t write_protection;

#else
#define W25Q32JV_GPIO_VARIABLE
#endif

#define W25Q32JV_COSTOM_VARIABLE

#define W25Q32JV_COMMON_VARIABLE   \
	W25Q32JV_GPIO_VARIABLE         \
    uint8_t num;                   \
    bool valid;                    \
    uint8_t spi_num;               \
    uint8_t spifi_num;

typedef struct {
	W25Q32JV_COMMON_VARIABLE
} W25q32jvConfig_t;

typedef struct {
	W25Q32JV_COMMON_VARIABLE
	W25Q32JV_COSTOM_VARIABLE
	W25q32jvRegStatus_t status;
	W25q32jvRegStatus2_t status1;
	W25q32jvRegStatus3_t status3;
} W25q32jvHandle_t;


#endif /* W25Q32JV_TYPES_H */
