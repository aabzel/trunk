#ifndef SPI_COMMON_TYPES_H
#define SPI_COMMON_TYPES_H


#ifdef __cplusplus
extern "C" {
#endif

#include "interfaces_const.h"
#include "mcal_const.h"
#include "spi_const.h"
#include "std_includes.h"
#include "sys_config.h"

#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_types.h"
#endif

#ifdef HAS_SPI_CUSTOM
#include "spi_custom_types.h"
#else
#define SPI_CUSTOM_VARIABLES
#endif

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif /**/


#define SPI_GPIO_VARIABLES                                                   \
    Pad_t GpioRxDebug;                                                       \
    Pad_t GpioTxDebug;                                                       \
    Pad_t PadCs; /*Some MCU SPI has HW chip select capability*/              \
    Pad_t PadSck;                                                            \
    Pad_t PadMosi;                                                           \
    Pad_t PadMiso;

#ifdef HAS_SPI_DMA
#define SPI_DMA_VARIABLES     \
    DmaChannelPad_t DmaRx;    \
    DmaChannelPad_t DmaTx;
#else
#define SPI_DMA_VARIABLES
#endif

#define SPI_COMMON_VARIABLES                                                \
    SPI_GPIO_VARIABLES                                                      \
    SPI_DMA_VARIABLES                                                       \
    uint32_t bit_rate_hz;                                                   \
    uint8_t num;                                                            \
    uint8_t frame_size;                                                     \
    IfBusRole_t bus_role;                                                   \
    SpiTxMode_t tx_mode;                                                    \
    MoveMode_t move_mode;                                                   \
    IfBitOrder_t bit_order;                                                 \
    SpiDirection_t direction;                                               \
    SpiPolarity_t polarity;                                                 \
    SpiClkIdleLevel_t phase;                                                \
    ChipSelect_t chip_select;                                               \
    uint8_t irq_priority;                                                   \
    char* name;                                                             \
    bool interrupt_on;                                                      \
    bool valid;

typedef struct {
    SPI_COMMON_VARIABLES
    /* irq_priority*/
} SpiConfig_t;

#define SPI_ISR_RX_VARIABLES                                  \
    volatile uint32_t rx_half_cnt;                            \
    volatile uint32_t rx_cnt;                                 \
    volatile bool rx_half_done;                               \
    volatile bool rx_done;

#define SPI_ISR_TX_VARIABLES                         \
    volatile uint32_t tx_half_cnt;                   \
    volatile uint32_t tx_cnt;                        \
    volatile bool tx_half_done;                      \
    volatile bool tx_done;

#define SPI_ISR_TX_RX_VARIABLES                      \
    volatile bool txrx_done;                         \
    volatile uint32_t txrx_cnt;

#define SPI_ISR_START_VARIABLES                      \
    volatile bool start_done;                        \
    volatile uint32_t start_cnt;

#define SPI_ISR_MOVE_VARIABLES                      \
    volatile bool move_done;                        \
    volatile uint32_t move_cnt;


#define SPI_ISR_ERROR_VARIABLES                      \
    volatile bool error_done;                        \
    volatile uint32_t error_cnt;

#define SPI_ISR_COMMON_VARIABLES                     \
    SPI_ISR_RX_VARIABLES                             \
    SPI_ISR_START_VARIABLES                          \
    SPI_ISR_ERROR_VARIABLES                          \
    SPI_ISR_MOVE_VARIABLES                           \
    SPI_ISR_TX_VARIABLES                             \
    SPI_ISR_TX_RX_VARIABLES                          \
    volatile bool it_done;                           \
    volatile uint32_t it_cnt;
    
#define SPI_RX_VARIABLES                     \
    uint8_t* rx_buff;                        \
    uint32_t rx_buff_size;                   \
    uint32_t rx_byte_cnt;

#define SPI_TX_VARIABLES                     \
    uint8_t* tx_buff;                        \
    uint32_t tx_byte_cnt;                    \
    uint32_t tx_cpl_cnt;

typedef struct {
    SPI_COMMON_VARIABLES
    SPI_ISR_COMMON_VARIABLES
    SPI_CUSTOM_VARIABLES
    uint8_t* rx_buff;
    uint32_t rx_byte_cnt;
    uint32_t tx_byte_cnt;
    uint32_t err_cnt;
    uint32_t rx_buff_size;
    uint32_t spin;
    uint32_t tx_cpl_cnt;
    IfOperation_t operation;
    uint32_t busy_time_out;
    bool init;
} SpiHandle_t;

typedef struct {
    uint8_t num;
    uint32_t bus_clock;
} SpiBusClock_t;

#ifdef __cplusplus
}
#endif

#endif /* SPI_COMMON_TYPES_H */
