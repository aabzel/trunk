#ifndef CAN_MCAL_TYPES_H
#define CAN_MCAL_TYPES_H

#include "std_includes.h"
#include "can_const.h"
#include "mcal_const.h"
#ifdef HAS_GPIO
#include "gpio_mcal.h"
#endif
#include "microcontroller_const.h"
#include "connectivity_types.h"
#ifdef HAS_CAN_CUSTOM
#include "can_custom_types.h"
#else
#define CAN_CUSTOM_VARIABLES
#endif



typedef union {
    uint16_t word;
    struct {
        uint16_t can0:1;
        uint16_t can1:1;
        uint16_t can2:1;
        uint16_t can3:1;
        uint16_t can4:1;
        uint16_t can5:1;
        uint16_t can6:1;
        uint16_t can7:1;
        uint16_t can8:1;
        uint16_t can9:1;
        uint16_t can10:1;
        uint16_t can11:1;
        uint16_t can12:1;
        uint16_t can13:1;
        uint16_t can14:1;
        uint16_t can15:1;
    };
}Cans_t;
/*
 ------------------------------------------------------
 | synchronization  | propagation | phase_1 | phase_2|
 -------------------------------------------------------
 N = synchronization+propagation+phase_1+phase_2
 K = 4
 C(n, k) = n! / k!(n-k)!

 C(n, 4) = n! / 4!(n-4)!

 */
typedef struct{
    uint32_t             prescaler;   /* Presdiv for can                   */

    uint32_t             synchronization;      /* Synchronization Segment   This segment has a fixed length of one time quantum.                 */
    uint32_t             propagation; /* Propagation Segment               */
    uint32_t             phase_1;     /*  Phase Segment 1                  */
    uint32_t             phase_2;     /*  Phase Segment 2                 */
} CanSegmentInfo_t;

typedef union{
    uint32_t standard;   /* specifies the 11 bits standard identifier. value between 0 to 0x7FF. */
    uint32_t extended;                  /* specifies the 29 bits extended identifier. value between 0 to 0x1FFFFFFF. */
}CanId_t;

typedef struct {
    uint32_t time_stamp;
    int8_t can_bus_num;                      /* The CAN bus number this package came from*/
    uint8_t data[CAN_MAX_PAYLOAD_SIZE];      /* contains the transmit data. it ranges from 0 to 0xFF. */
    CanId_t identifier;                /* ID value */
    CanIdentifier_t id_type;           /* std or ext  specifies identifier type for the transmit message.*/
    CanTxFrame_t frame_type;           /* specifies frame type for the transmit message.*/
    uint8_t size;                      /* Data Length Code. specifies frame data length that will be transmitted.
                                              this parameter can be a value between 0 to 8 */
    uint8_t mesg_buff_idx; /*Filter Match Index*/
    bool is_fd; /* true - CAN-FD, false - Classic CAN */
#ifdef HAS_CAN_FD
    CanFdBitRateSwitch_t bit_rate_switch;
#endif
} CanMessage_t;


#ifdef HAS_LED
#define CAN_LED_VARIABLES             \
    uint8_t led_num_tx;               \
    uint8_t led_num_rx;

#else
#define CAN_LED_VARIABLES
#endif

#ifdef HAS_GPIO
#define CAN_GPIO_VARIABLES     \
    Pad_t PadTx;               \
    Pad_t PadRx;               \

#else
#define CAN_GPIO_VARIABLES
#endif

#define CAN_FD_MCAL_COMMON_VARIABLES                                          \
    bool fd_enable;    /* Enable/Disable the Flexible Data Rate feature. */   \
    uint32_t bit_rate_fd;   /*for CAD FD data phase*/

#define CAN_MCAL_SPECIFIC_VARIABLES                                           \
    uint32_t watermark;                                                       \
    bool bus_off_auto_recovery;                                               \
    uint8_t padding;                                                          \
    uint8_t payload_size;                                                     \
    CanMode_t mode;                                                           \
    CanMacMode_t mac_mode;                                                    \
    CanClockSource_t clock_source;                                            \
    CanIdentifier_t identifier;                                               \
    uint32_t bit_rate;                                                        \
    uint32_t* rx_id;                                                          \
    uint32_t rx_id_cnt;                                                       \
    bool re_tx;                                                               \
    bool heart_beat;                                                          \
    bool rx_fifo_on_off;

#define CAN_MCAL_COMMON_VARIABLES                                             \
    CAN_GPIO_VARIABLES                                                        \
    CAN_LED_VARIABLES                                                         \
    CAN_FD_MCAL_COMMON_VARIABLES                                              \
    CAN_MCAL_SPECIFIC_VARIABLES                                               \
    MoveMode_t move_mode;                                                     \
    bool valid;                                                               \
    bool interrupt_on;                                                        \
    bool rx_all;                                                              \
    uint8_t interrupt_priority;                                               \
    uint32_t my_id;     /*just for tests*/                                    \
    uint8_t slcan_num;                                                        \
    uint8_t num;                                                              \
    uint8_t dma_channel_rx;                                                   \
    uint8_t dma_channel_tx;

typedef struct {
    CAN_MCAL_COMMON_VARIABLES
    char *name;
}CanConfig_t;

typedef struct {
    ConnectivitDir_t direction;
    CanIdentifier_t id_type;
    uint8_t num;
    Cans_t cans;
    uint8_t mb_index;
    uint32_t frame_id;
    bool interrupt_on;
    bool valid;
    char *name;
}CanMessageBufferConfig_t;


typedef struct {
    uint8_t num;
    uint8_t can_num;
    uint8_t mb_index;
    bool valid;
    char *name;
    uint8_t state;
} CanMessageBufferHandle_t;

#define CAN_ISR_TX_VARIABLE                    \
    volatile uint32_t tx_time_stamp;           \
    volatile uint32_t tx_cnt;                  \
    volatile bool tx_done;

#define CAN_ISR_RX_VARIABLE                    \
    volatile uint32_t rx_cnt;                  \
    volatile uint32_t rx_time_stamp;           \
    volatile bool rx_done;                     \
    volatile uint32_t rx_fifo_full_cnt;        \
    volatile bool rx_fifo_full_done;




#define CAN_ISR_WARNING                         \
    volatile uint32_t warning_tx_cnt;           \
    volatile uint32_t warning_rx_cnt;           \
    volatile bool warning_tx ;                  \
    volatile bool warning_rx ;

#define CAN_ISR_ERROR                           \
    volatile uint32_t error_cnt;                \
    volatile uint32_t error_overrun_cnt;        \
    volatile uint32_t error_bus_off_cnt;        \
    volatile uint32_t error_bus_off_done_cnt;   \
    volatile uint32_t error_data_phase_cnt;     \
    volatile bool error;                        \
    volatile bool error_overrun ;               \
    volatile bool error_bus_off ;               \
    volatile bool error_bus_off_done ;          \
    volatile bool error_data_phase;


#define CAN_ISR_VARIABLE                \
    CAN_ISR_ERROR                       \
    CAN_ISR_WARNING                     \
    CAN_ISR_TX_VARIABLE                 \
    CAN_ISR_RX_VARIABLE                 \
    volatile uint32_t isr_cnt;          \
    volatile bool isr_done;             \
    volatile bool unproc_rx_message;

typedef struct {
    CAN_MCAL_COMMON_VARIABLES
    CAN_ISR_VARIABLE
    CAN_CUSTOM_VARIABLES
    volatile bool error_for_test;
    volatile bool re_init;  //
    volatile uint32_t rec_err_cnt;
    volatile uint32_t tec_err_cnt;
    volatile uint32_t tx_error_cnt;
    volatile uint32_t arbitration_lost_cnt;  
    volatile uint32_t rx_bytes;  // Total rx byte
    volatile uint32_t tx_bytes;  // Total tx byte
    volatile uint32_t err_code;
    volatile uint32_t heart_beat_sn; // serial number of sent heart_beat message
    volatile CanMessage_t RxMessage;
    bool init_done;
    uint32_t spin;
} CanHandle_t;

/*
 */
typedef union {
    uint8_t buff[8];
    uint32_t dword[2];
}CanClassicPayload_t;


/*
 */
typedef union {
    uint8_t buff[64];
    uint32_t dword[16];
}CanFdPayload_t;


#endif /* CAN_MCAL_TYPES_H */
