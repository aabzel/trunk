#ifndef SW_UART_TYPES_H
#define SW_UART_TYPES_H

#include "std_includes.h"
#include "sw_uart_const.h"
#include "gpio_types.h"
#include "fifo_char_types.h"

#ifdef HAS_EXT_INT
#include "ext_int_types.h"
#endif

typedef union {
    uint32_t dword;
    uint16_t word[2];
    struct {
        uint32_t start_bit:1;  /* 8      */
        uint32_t byte:8;       /* 1-8    */
        uint32_t parity:1;     /* 9      */
        uint32_t stop1:1;      /* 10  */
        uint32_t stop2:1;      /* 11  */
        uint32_t res:12;       /* 12-31 dummy bits to DMA tx sample reliability */
        uint32_t idle:8;       /* 0 7      */
    };
}SwUartFrameTx_t;

typedef union {
    uint32_t dword;
    uint16_t word[2];
    struct {
        uint32_t start_bit:1;  /* 8      */
        uint32_t byte:8;       /* 1-8    */
        uint32_t parity:1;     /* 9      */
        uint32_t stop1:1;      /* 10  */
        uint32_t stop2:1;      /* 11  */
        uint32_t res:20;       /* 12-31 dummy bits to DMA tx sample reliability */
    };
}SwUartFrameRx_t;

#define SW_UART_GPIO     \
    Pad_t Tx;            \
    Pad_t Rx;

#define SW_UART_COMMON_TX_VARIABLES                    \
    uint8_t* TxFifoMem;                                \
    uint32_t tx_fifo_mem_size;                         \
    uint8_t tx_timer_num;                              \
    uint32_t tx_over_sampling;                         \
    uint8_t bin_dac_num;

#define SW_UART_COMMON_RX_VARIABLES                    \
    uint8_t* RxFifoMem;                                \
    uint32_t rx_fifo_mem_size;                         \
    uint8_t rx_timer_num;                              \
    uint32_t rx_over_sampling;                         \
    uint8_t bin_adc_num;

#define SW_UART_COMMON_VARIABLES                       \
    SW_UART_COMMON_TX_VARIABLES                        \
    SW_UART_COMMON_RX_VARIABLES                        \
    SW_UART_GPIO                                       \
    uint32_t baud_rate;                                \
    uint8_t num;                                       \
    uint8_t stop_bit_cnt;                              \
    bool parity_check;                                 \
    bool valid;                                        \
    char *name;

typedef struct {
    SW_UART_COMMON_VARIABLES
} SwUartConfig_t;

#define SW_UART_VARIABLES_TX                     \
    FifoChar_t TxByteFifo;                       \
    uint8_t txSamples[SW_UART_SAMPLE_PER_FRAME]; \
    uint32_t tx_cnt;

#define SW_UART_VARIABLES_RX                          \
    uint8_t rx_byte;                                  \
    uint8_t RxFrame[SW_UART_BIT_PER_FRAME_MAX];       \
    uint8_t rxFrameSamples[SW_UART_SAMPLE_PER_FRAME]; \
    SwUartRxFrameState_t rx_frame_state;              \
    volatile SwUartRxAction_t rx_action;              \
    FifoChar_t RxByteFifo;                            \
    uint32_t rx_frame_cnt;                            \
    uint32_t rx_cnt;

typedef struct {
    SW_UART_COMMON_VARIABLES
    SW_UART_VARIABLES_TX
    SW_UART_VARIABLES_RX
    bool init;
    GpioLogicLevel_t rx_state;
    uint32_t error_cnt;
    uint32_t max_frame_duration_us;
    uint32_t event_pause_us;
    uint32_t event_cnt;
    uint32_t rx_bit_diff;
    uint32_t bit_duration_us;
    uint32_t bit_i;
    uint32_t spin;
    uint8_t sample;
    uint8_t RxBit[20];
    //SwUartFrame_t RxFrame;
#ifdef HAS_EXT_INT
    ExtIntEvent_t PrevEvent;
    ExtIntEvent_t Event;
#endif
} SwUartHandle_t;

#endif /* SW_UART_TYPES_H */
