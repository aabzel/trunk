#ifndef GFSK_CONSTANTS_H
#define GFSK_CONSTANTS_H

#define DFLT_WHITENING_INIT 0x0100
#define DFLT_SYNC_WORD_BITS_LEN (8*8)
#define DFLT_PAYLOAD_LEN 255

typedef enum eGfskBandwidth_t {
    GFSK_BW_4800 = 0x1F,
    GFSK_BW_5800 = 0x17,
    GFSK_BW_7300 = 0x0F,
    GFSK_BW_9700 = 0x1E,
    GFSK_BW_11700 = 0x16,
    GFSK_BW_14600 = 0x0E,
    GFSK_BW_19500 = 0x1D,
    GFSK_BW_23400 = 0x15,
    GFSK_BW_29300 = 0x0D,
    GFSK_BW_39000 = 0x1C,
    GFSK_BW_46900 = 0x14,
    GFSK_BW_58600 = 0x0C,
    GFSK_BW_78200 = 0x1B,
    GFSK_BW_93800 = 0x13,
    GFSK_BW_117300 = 0x0B,
    GFSK_BW_156200 = 0x1A,
    GFSK_BW_187200 = 0x12,
    GFSK_BW_234300 = 0x0A,
    GFSK_BW_312000 = 0x19,
    GFSK_BW_373600 = 0x11,
    GFSK_BW_467000 = 0x09,
} __attribute__((__packed__)) GfskBandwidth_t;

typedef enum eAddrComp_t {
    ADDR_FILT_DISABLE = 0x00,
    ADDR_FILT_NODE_ADDR = 0x01,
    ADDR_FILT_NODE_BROADCAST_ADDR = 0x02,
} AddrComp_t;

typedef enum eGfskCrcType_t {
    CRC_OFF = 0x01,
    CRC_1BYTE = 0x00,
    CRC_2BYTE = 0x02,
    CRC_1BYTE_INV = 0x04,
    CRC_2BYTE_INV = 0x06,
} GfskCrcType_t;

// Table 13-59: GFSK PacketParam6 - PacketType
typedef enum eGfskPacketType_t {
    GFSK_PACKET_VAR = 0x00,
    GFSK_PACKET_FIXED = 0x01,
} GfskPacketType_t;

typedef enum eWhitening_t {
    Whitening_OFF = 0x00,
    Whitening_ENABLE = 0x01,
} Whitening_t;

typedef enum eGfskPulseShape_t {
    PSH_NO = 0x00,
    PSH_Gaussian_BT_0_3 = 0x08,
    PSH_Gaussian_BT_0_5 = 0x09,
    PSH_Gaussian_BT_0_7 = 0x0A,
    PSH_Gaussian_BT_1_0 = 0x0B,
} GfskPulseShape_t;

typedef enum ePreDetLen_t {
    PLE_DET_OFF = 0x00,
    PLE_DET_1BYTE = 0x04,
    PLE_DET_2BYTE = 0x05,
    PLE_DET_3BYTE = 0x06,
    PLE_DET_4BYTE = 0x07,
} PreDetLen_t;

#endif /* GFSK_CONSTANTS_H  */
