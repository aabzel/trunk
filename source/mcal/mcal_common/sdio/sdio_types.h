#ifndef SDIO_COMMON_TYPES_H
#define SDIO_COMMON_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "sys_config.h"
#include "sdio_const.h"
#include "sdio_custom_const.h"

#ifndef HAS_SDIO
#error "+HAS_SDIO"
#endif

#ifdef USE_HAL_DRIVER
#include "stm32f4xx_hal.h"
#endif /*USE_HAL_DRIVER*/

typedef struct {
    uint8_t num;
    uint32_t bus_clock;
}SdioBusClock_t;

typedef struct  {
    uint8_t num; /*SDIO ID*/
    volatile bool tx_int;
    volatile bool rx_int;
    volatile bool rxtx_int;
    volatile bool it_done;
    uint8_t *rx_buff;
    uint8_t RxData[SDIO_BLOCK_SIZE + 1];
    uint32_t rx_byte_cnt;
    uint32_t spare_block_cnt;
    uint32_t busy_block_cnt;
    uint32_t try_read_cnt;
    uint32_t try_write_cnt;
    uint32_t tx_byte_cnt;
    uint32_t read_err_cnt;
    uint32_t read_cnt;
    uint32_t read_ok_cnt;
    uint32_t tx_cnt_prev;
    uint32_t rx_cnt_prev;
    volatile uint32_t rxtx_cnt;
    volatile uint32_t tx_cnt;
    volatile uint32_t rx_time_stamp;
    volatile uint32_t tx_time_stamp;
    volatile uint32_t rx_cnt;
    volatile uint32_t err_cnt;
    volatile uint32_t abort_cnt;
    volatile uint32_t it_cnt;
    uint32_t rx_buff_size;
    uint32_t tx_cpl_cnt;
#ifdef USE_HAL_DRIVER
    SD_HandleTypeDef sdio_h;
    HAL_SD_CardCSDTypeDef CSD;
    HAL_SD_CardCIDTypeDef CID ;
    HAL_SD_CardStatusTypeDef status;
    HAL_SD_CardStateTypeDef SD_CardState;
    HAL_SD_CardInfoTypeDef CardInfo;
#endif /*USE_HAL_DRIVER*/
    bool init_done;
    bool valid;
}SdioHandle_t;

typedef struct  {
    uint32_t base_addr;
    uint32_t bit_rate_hz;
    char name[SDIO_NAME_SIZE_BYTE];
    uint8_t num;
    bool valid;
}SdioConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* SDIO_COMMON_TYPES_H */
