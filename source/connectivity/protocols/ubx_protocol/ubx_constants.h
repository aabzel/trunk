#ifndef UBX_PROTOCOL_CONSTANTS_H
#define UBX_PROTOCOL_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#define UBX_SYN_0 0xB5 /* u */
#define UBX_SYN_1 0x62 /* b */

#define UBX_INDEX_CLS 2U
#define UBX_INDEX_ID 3U
#define UBX_INDEX_LEN 4U
#define UBX_INDEX_PAYLOAD 6U

#define UBX_RX_FRAME_SIZE 100U
#define UBX_LEN_SIZE 2
#define UBX_CRC_SIZE 2
#define UBX_HEADER_SIZE (UBX_LEN_SIZE + 4)

#define UBX_ACK_ACK 0x01
#define UBX_ACK_NAK 0x00

/*UBX messages overview*/
#define UBX_CLA_NAV 0x01
#define UBX_CLA_RXM 0x02
#define UBX_CLA_INF 0x04
#define UBX_CLA_ACK 0x05
#define UBX_CLA_CFG 0x06
#define UBX_CLA_UPD 0x09
#define UBX_CLA_MON 0x0A
#define UBX_CLA_TIM 0x0D
#define UBX_CLA_ESF 0x10
#define UBX_CLA_MGA 0x13
#define UBX_CLA_SEC 0x27

#define UBX_CLA_NMEA 0xF0

/*3.10.26 UBX-CFG-VALSET (0x06 0x8a)*/
#define UBX_ID_CFG_PRT 0x00
#define UBX_ID_CFG_MSG 0x01
#define UBX_ID_CFG_SET_VAL 0x8A
/*3.10.25 UBX-CFG-VALGET (0x06 0x8b)*/
#define UBX_ID_CFG_GET_VAL 0x8B
/*3.10.21 (0x06 0x71)*/
#define UBX_ID_CFG_TMODE3 0x71
/*3.10.2.1 Clear, save and load configurations*/
#define UBX_ID_CFG_CFG 0x09
/*3.10.17 UBX-CFG-RATE (0x06 0x08)*/
#define UBX_ID_CFG_RATE 0x08
#define UBX_ID_CFG_NMEA 0x17

#define UBX_ID_CFG_NMEA_GLL 0x01
#define UBX_ID_CFG_NMEA_GGA 0x00
#define UBX_ID_CFG_NMEA_ZDA 0x08

#define UBX_ID_NAV_POSECEF 0x01 //Position solution in ECEF
#define UBX_ID_NAV_SVIN 0x3b /*Survey-in data*/
#define UBX_ID_NAV_POSLLH 0x02
#define UBX_ID_NAV_PVT 0x07
#define UBX_ID_NAV_STATUS 0x03
#define UBX_ID_NAV_ATT 0x05
#define UBX_ID_NAV_VELECEF 0x11
#define UBX_ID_NAV_VELNED 0x12
#define UBX_ID_NAV_HPPOSLLH 0x14
#define UBX_ID_NAV_TIMEUTC 0x21
#define UBX_ID_NAV_CLK 0x22

#define UBX_ID_MON_VER 0x04
#define UBX_ID_MON_HW 0x09

#define UBX_ID_SEC_UNIQID 0x03
#define UBX_ID_MGA_INI 0x40

#define UBX_CLA_CNT 15

#define LAYER_MASK_RAM (1)
#define LAYER_MASK_BBR (2) /*Battery-backed RAM*/
#define LAYER_MASK_FLASH (4)
#define LAYER_MASK_RAM_FLASH (LAYER_MASK_RAM & LAYER_MASK_FLASH)

typedef enum eUbxProtState_t {
    UBX_WAIT_SYC0 = 0U,
    UBX_WAIT_SYC1 = 1U,
    UBX_WAIT_CLASS = 2U,
    UBX_WAIT_ID = 3U,
    UBX_WAIT_LEN = 4U,
    UBX_WAIT_PAYLOAD = 5U,
    UBX_WAIT_CRC = 6U,
    UBX_RX_DONE = 7U
} UbxProtState_t;

typedef enum eUbxReceiverMode_t {
   RX_MODE_DISABLED=0,
   RX_MODE_SURVEY_IN=1,
   RX_MODE_FIXED=2,
   RX_MODE_UNDEF=3,
}__attribute__((packed))  UbxReceiverMode_t;


typedef enum eReceiverMode_t {
    MODE_DISABLED = 0x00,
    MODE_SURVEY_IN = 0x01,
    MODE_FIXED = 0x02,
} ReceiverMode_t;

typedef enum eSatConst_t {
    SC_GPS = 0,
    SC_GLONASS = 1,
    SC_GALILEO = 2,
    SC_BEI_DOU = 3,
    SC_NONE = 4,
} SatConst_t;



/*UBX data types*/
typedef enum eUbxType_t {
    UBX_U1 = 1,
    UBX_U2 = 2,
    UBX_U4 = 3,
    UBX_X1 = 4,
    UBX_X2 = 5,
    UBX_X4 = 6,
    UBX_I1 = 7,
    UBX_I2 = 8,
    UBX_I4 = 9,
    UBX_R4 = 10,
    UBX_R8 = 11,
    UBX_CH = 12,
    UBX_L = 13,
} UbxType_t;

typedef enum eGnssFixType_t {
    FIX_TYPE_NO_FIX                           =0,
    FIX_TYPE_DEAD_RECKONING_ONLY              =1,
    FIX_TYPE_2D_FIX                           =2,
    FIX_TYPE_3D_FIX                           =3,
    FIX_TYPE_GNSS_DEAD_RECKONING_COMBINED     =4,
    FIX_TYPE_TIME_ONLY_FIX                    =5,
    FIX_TYPE_UNDEF                            =6,
} GnssFixType_t;

#ifdef __cplusplus
}
#endif

#endif /* UBX_PROTOCOL_CONSTANTS_H */
