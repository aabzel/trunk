#ifndef SDIO_MCAL_TYPES_H
#define SDIO_MCAL_TYPES_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "microcontroller_const.h"
#include "mcal_const.h"
#include "sdio_const.h"

#ifdef HAS_SDIO_CUSTOM
#include "sdio_custom_types.h"
#else
#define SDIO_CUSTOM_TYPES
#endif

#ifndef HAS_SDIO
#error "+HAS_SDIO"
#endif


typedef struct {
    uint8_t num;
    uint32_t bus_clock;
}SdioBusClock_t;


#define SDIO_ISR_VARIABLE_TX                 \
    volatile bool tx_done;                    \
    volatile uint32_t tx_cnt;

#define SDIO_ISR_VARIABLE_RX                 \
    volatile bool rx_done;                    \
    volatile uint32_t rx_cnt;

#define SDIO_ISR_VARIABLE_RX_TX                 \
    volatile uint32_t rxtx_cnt;                 \
    volatile bool rxtx_done;

#define SDIO_ISR_VARIABLE_ERROR                 \
    volatile uint32_t err_cnt;                  \
    volatile uint32_t abort_cnt;

#define SDIO_ISR_VARIABLE_CORE                \
    volatile bool it_done;                    \
    volatile uint32_t it_cnt;

#define SDIO_ISR_VARIABLE                    \
    SDIO_ISR_VARIABLE_CORE                   \
    SDIO_ISR_VARIABLE_ERROR                  \
    SDIO_ISR_VARIABLE_RX_TX                  \
    SDIO_ISR_VARIABLE_TX                     \
    SDIO_ISR_VARIABLE_RX                     \
    volatile uint32_t rx_time_stamp;         \
    volatile uint32_t tx_time_stamp;


#define SDIO_TX_VARIABLE                    \
    uint32_t tx_byte_cnt;                   \
    uint32_t try_write_cnt;                 \
    uint32_t tx_cnt_prev;                   \
    uint32_t tx_cpl_cnt;

#define SDIO_RX_VARIABLE                    \
    uint8_t RxData[SDIO_BLOCK_SIZE + 1];    \
    uint8_t *rx_buff;                       \
    uint32_t rx_cnt_prev;                   \
    uint32_t rx_buff_size;                  \
    uint32_t rx_byte_cnt;                   \
    uint32_t read_err_cnt;                  \
    uint32_t read_cnt;                      \
    uint32_t read_ok_cnt;                   \
    uint32_t try_read_cnt;


#define SDIO_COMMON_VARIABLES         \
    uint8_t num;                      \
    uint32_t bit_rate_hz;             \
    bool interrupt_on;                \
    char* name;                       \
    MoveMode_t move_mode;             \
    bool valid;

typedef struct  {
    SDIO_COMMON_VARIABLES
    SDIO_ISR_VARIABLE
    SDIO_RX_VARIABLE
    SDIO_TX_VARIABLE
    SDIO_CUSTOM_TYPES
    uint32_t spare_block_cnt;
    uint32_t spin;
    uint32_t busy_block_cnt;
    bool init;
}SdioHandle_t;


typedef struct  {
    SDIO_COMMON_VARIABLES
}SdioConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* SDIO_MCAL_TYPES_H */
