
#ifndef TCAN4550_CONST_H
#define TCAN4550_CONST_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_NUM_STD_ID_FIL 128
#define MAX_NUM_EXT_ID_FIL 64
#define MAX_NUM_RX_FIFO_0_EL 64

//*****************************************************************************
// DLC Value Defines: Used for RX and TX elements. The DLC[3:0] bit field
//*****************************************************************************
#define MCAN_DLC_0B                                 0x00000000
#define MCAN_DLC_1B                                 0x00000001
#define MCAN_DLC_2B                                 0x00000002
#define MCAN_DLC_3B                                 0x00000003
#define MCAN_DLC_4B                                 0x00000004
#define MCAN_DLC_5B                                 0x00000005
#define MCAN_DLC_6B                                 0x00000006
#define MCAN_DLC_7B                                 0x00000007
#define MCAN_DLC_8B                                 0x00000008
#define MCAN_DLC_12B                                0x00000009
#define MCAN_DLC_16B                                0x0000000A
#define MCAN_DLC_20B                                0x0000000B
#define MCAN_DLC_24B                                0x0000000C
#define MCAN_DLC_32B                                0x0000000D
#define MCAN_DLC_48B                                0x0000000E
#define MCAN_DLC_64B                                0x0000000F

typedef enum  {
    CLK_REF_20MHZ = 0,
    CLK_REF_40MHZ = 1,
    CLK_REF_UNDEF = 1,
} ClkRef_t;

typedef enum {
    RX_FIFO0=0,
    RX_FIFO1=1,
    RX_FIFO_CNT=2
}TCAN4550_MCAN_FIFO_Enum_t;

typedef enum  {
    MODE_SLEEP = 0,
    MODE_STANDBY = 1,
    MODE_NORMAL = 2,
    MODE_RESERVED = 3,
    MODE_UNDEF = 4,
} CanDevMode_t;


typedef enum  {
    FIFO_OP_MODE_BLOCKING = 0,
    FIFO_OP_MODE_OVERWRITE = 1,
} FiFo0OpMode_t;

typedef enum  {
    LEC_NO_ERROR = 0,
    LEC_STUFF_ERROR  = 1,
    LEC_FORM_ERROR=2,
    LEC_ACK_ERROR=3,
    LEC_BIT1_ERROR=4,
    LEC_BIT0_ERROR=5,
    LEC_CRC_ERROR=6,
    LEC_NO_CHANGE=7,
    LEC_UNDEF=8,
} LastErrorCode_t;

typedef enum  {
    //! Disabled filter. This filter will match nothing
    TCAN4550_SID_SFT_DISABLED           = 0x3,
    //! Classic filter with SFID1 as the ID to match, and SFID2 as the bit mask that applies to SFID1
    TCAN4550_SID_SFT_CLASSIC            = 0x2,
    //! Dual ID filter, where both SFID1 and SFID2 hold IDs that can match (must match exactly)
    TCAN4550_SID_SFT_DUALID             = 0x1,
    //! Range Filter. SFID1 holds the start address, and SFID2 holds the end address. Any address in between will match
    TCAN4550_SID_SFT_RANGE              = 0x0
} StandardFilterType_t;


typedef enum {
    //! Disabled filter. This filter will do nothing if it matches a packet
    TCAN4550_SID_SFEC_DISABLED          = 0x0,

    //! Store in RX FIFO 0 if the filter matches the incoming message
    TCAN4550_SID_SFEC_STORERX0          = 0x1,

    //! Store in RX FIFO 1 if the filter matches the incoming message
    TCAN4550_SID_SFEC_STORERX1          = 0x2,

    //! Reject the packet (do not store, do not notify MCU) if the filter matches the incoming message
    TCAN4550_SID_SFEC_REJECTMATCH       = 0x3,

    //! Store in default location but set a high priority message interrupt if the filter matches the incoming message
    TCAN4550_SID_SFEC_PRIORITY          = 0x4,

    //! Store in RX FIFO 0 and set a high priority message interrupt if the filter matches the incoming message
    TCAN4550_SID_SFEC_PRIORITYSTORERX0  = 0x5,

    //! Store in RX FIFO 1 and set a high priority message interrupt if the filter matches the incoming message
    TCAN4550_SID_SFEC_PRIORITYSTORERX1  = 0x6,

    //! Store in RX Buffer for debug if the filter matches the incoming message. SFT is ignored if this is selected.
    TCAN4550_SID_SFEC_STORERXBUFORDEBUG = 0x7
} TCAN4550_SID_SFEC_Values;


/**
 * @brief Data payload defines for the different MRAM sections, used by the @c TCAN4550_MRAM_Config struct
 */
typedef enum {
    MRAM_8_BYTE_DATA = 0,   // 8  bytes of data payload
    MRAM_12_BYTE_DATA = 0x1,// 12 bytes of data payload
    MRAM_16_BYTE_DATA = 0x2,// 16 bytes of data payload
    MRAM_20_BYTE_DATA = 0x3,// 20 bytes of data payload
    MRAM_24_BYTE_DATA = 0x4,// 24 bytes of data payload
    MRAM_32_BYTE_DATA = 0x5,// 32 bytes of data payload
    MRAM_48_BYTE_DATA = 0x6,// 48 bytes of data payload
    MRAM_64_BYTE_DATA = 0x7 // 64 bytes of data payload
} TCAN4550_MRAM_Element_Data_Size;


#endif /* TCAN4550_CONST_H */
