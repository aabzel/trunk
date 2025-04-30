#ifndef SPI_COMMON_TYPES_H
#define SPI_COMMON_TYPES_H

#include "std_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "interfaces_const.h"
#include "spi_const.h"
#include "mcal_const.h"
#include "sys_config.h"


#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_types.h"
#endif


#ifdef HAS_SPI_CUSTOM
#include "spi_custom_types.h"
#endif

#include "interfaces_const.h"

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif /*HAS_SPI*/




#define SPI_GPIO_VARIABLES                                                   \
    Pad_t PadCs; /*Some MCU SPI has HW chip select capability*/             \
    Pad_t PadSck;             \
    Pad_t PadMosi;             \
    Pad_t PadMiso;

#define SPI_COMMON_VARIABLES                                                \
    SPI_GPIO_VARIABLES                                                      \
    uint8_t num;                                                            \
    Pad_t GpioRxDebug;                                                      \
    Pad_t GpioTxDebug;                                                      \
    uint32_t bit_rate_hz;                                                   \
    IfBusRole_t bus_role;                                                   \
    uint8_t frame_size;                                                     \
    SpiTxMode_t tx_mode;                                                    \
    MoveMode_t move_mode;                                                   \
    IfBitOrder_t bit_order;                                                 \
    SpiPolarity_t polarity;                                                 \
    SpiPhase_t phase;                                                       \
    ChipSelect_t chip_select;                                               \
    bool interrupt_on;                                                      \
    uint8_t irq_priority;                                                   \
    char* name;                                                             \
    bool valid;

typedef struct {
    SPI_COMMON_VARIABLES
    /* irq_priority*/
} SpiConfig_t;

#define SPI_ISR_RX_VARIABLES                         \
    uint32_t rx_half_cnt;                            \
    volatile bool rx_half_done;                      \
    uint32_t rx_cnt;                                 \
    volatile bool rx_done;

#define SPI_ISR_TX_VARIABLES                         \
    uint32_t tx_half_cnt;                            \
    uint32_t tx_cnt;                                 \
    volatile bool tx_half_done;                      \
    volatile bool tx_done;



#define SPI_ISR_COMMON_VARIABLES                     \
    SPI_ISR_RX_VARIABLES                             \
    SPI_ISR_TX_VARIABLES                             \
    uint32_t txrx_cnt;                               \
    volatile bool txrx_done;                         \
    volatile bool it_done;                           \
    volatile uint32_t it_cnt;   \
        volatile bool error_done;                                          \
    volatile uint32_t error_cnt;  

typedef struct {
    SPI_COMMON_VARIABLES
    SPI_ISR_COMMON_VARIABLES
    SPI_CUSTOM_VARIABLES
    uint8_t* rx_buff;
    uint32_t rx_byte_cnt;
    uint32_t tx_byte_cnt;
    uint32_t err_cnt;
    uint32_t rx_buff_size;
    uint32_t tx_cpl_cnt;
    uint32_t base_addr;
    bool init_done;
} SpiHandle_t;

typedef struct {
    uint8_t num;
    uint32_t bus_clock;
} SpiBusClock_t;

#ifdef __cplusplus
}
#endif

#endif /* SPI_COMMON_TYPES_H */
