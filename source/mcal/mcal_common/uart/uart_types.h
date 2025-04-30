#ifndef UART_MCAL_TYPES_H
#define UART_MCAL_TYPES_H

#include "std_includes.h"
#include "mcal_types.h"
#include "uart_const.h"
#include "microcontroller_const.h"

#ifdef HAS_INTERFACE
#include "interfaces_types.h"
#endif

#ifdef HAS_MISCELLANEOUS
#include "data_utils.h"
#include "data_types.h"
#endif


#ifdef HAS_FIFO
#include "fifo_char.h"
#endif

#ifdef HAS_DMA
#include "dma_types.h"
#endif

#ifdef HAS_UART_CUSTOM
#include "uart_custom_types.h"
#else
#define UART_CUSTOM_VARIABLES
#endif

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

typedef struct {
    bool tx;
    bool rx;
}UartDmaCtrl_t;

#define UART_GPIO    \
    Pad_t TxPad;     \
    Pad_t RxPad;

#define UART_COMMON_VARIABLES    \
    UART_GPIO                    \
    bool valid;                  \
    bool interrupts_on;          \
    MoveMode_t momve_method;     \
    bool parity_check;           \
    uint32_t rx_buff_size;       \
    uint32_t baud_rate;          \
    uint8_t stop_bit_cnt;        \
    uint32_t tx_buff_size;       \
    char *name;                  \
    uint8_t* RxFifoArray;        \
    uint8_t word_len_bit;        \
    uint8_t* TxFifoArray;        \
    uint8_t num;

typedef struct {
    UART_COMMON_VARIABLES
#ifdef HAS_DMA
#endif
    UartDmaCtrl_t dma;
}UartConfig_t;

#define UART_COMMON_VARIABLES_TX         \
    FifoChar_t TxFifo;                   \
    uint8_t TxBuff[UART_TX_BUFF_SIZE];   \
    uint32_t real_byte_tx_time_us;       \
    volatile uint32_t tx_cpl_cnt;        \
    volatile uint32_t tx_bytes;  /* Total tx byte */    \
    U32Value_t tx_rate;                  \
    volatile bool sending;               \
    volatile bool tx_done;               \
    volatile uint32_t tx_cnt;            \
    uint32_t tx_time_out_cnt;            \
    uint32_t tx_time_out;                \
    uint8_t* tx_buff; /*  pointer to memory chunk in heap*/   \
    uint32_t tx_len; /*byte len of current tx*/


#define UART_COMMON_VARIABLES_RX   \
    volatile uint32_t rx_bytes;  /* Total rx byte */   \
    volatile bool rx_done;   \
    volatile uint32_t rx_time_out_cnt;   \
    volatile uint8_t rx_byte;   \
    volatile uint8_t* rx_buff;   \
    volatile uint32_t rx_cnt;   \
    bool rx_it_proc_done;   \
    bool first_rx;   \
    uint8_t rx_byte_it;   \
    FifoChar_t RxFifo;   \
    U32Value_t rx_rate;

typedef struct {
    UART_CUSTOM_VARIABLES
    UART_COMMON_VARIABLES
    UART_COMMON_VARIABLES_TX
    UART_COMMON_VARIABLES_RX
    UartDmaCtrl_t dma;
#ifdef HAS_DMA
#endif
    volatile bool in_progress;
#ifdef HAS_INTERFACE
    volatile FlowCnt_t cnt;
    FlowCnt_t cnt_prev;
#endif

    uint32_t error_cnt;
    int16_t irq_n;
    uint32_t wait_iter;
    uint32_t error_cnt_prev;
    bool init_done;
    volatile uint32_t err_heap;
} UartHandle_t;

#endif /* UART_MCAL_TYPES_H */
