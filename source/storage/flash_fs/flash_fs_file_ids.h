#ifndef FLASH_FS_FILE_IDENTIFICATIONS_H
#define FLASH_FS_FILE_IDENTIFICATIONS_H

#ifndef HAS_FLASH_FS
#error "+HAS_FLASH_FS"
#endif

//#include "c_defines_generated.h"
/*
 * show all NVRAM IDs in the entire code base
 * grep -rn "PAR_ID_" | grep "\.h"
 * */


#ifdef HAS_WATCHDOG

#define FLASH_FS_WATCHDOG    \
    PAR_ID_WATCHDOG_BOOTLOADER_ON =  70,     \
    PAR_ID_WATCHDOG_GENERIC_ON =  72,     \
    PAR_ID_WATCHDOG_TIME_OUT_MS = 71 ,

#else /*HAS_WATCHDOG*/
#define FLASH_FS_WATCHDOG
#endif /*HAS_WATCHDOG*/



#ifdef HAS_KEEPASS
#define FLASH_FS_KEEPPASS \
    PAR_ID_TRANS_KEY = 75,  \
    PAR_ID_KEEPPASS_FILE_NAME = 79, \
    PAR_ID_KEEPPASS_PASS_WORD = 80,
#else /*HAS_KEEPASS*/
#define FLASH_FS_KEEPPASS
#endif /*HAS_KEEPASS*/

#ifdef HAS_BOARD
#include "board_params.h"
#else
#define PAR_IDS_BOARD
#endif

#ifdef HAS_CLOCK
#define PAR_IDS_CLOCK       PAR_ID_SYS_CLOCK_HZ = 92,
#else
#define PAR_IDS_CLOCK
#endif



#ifdef HAS_BOOTLOADER

#define FLASH_FS_BOOTLOADER    \
    PAR_ID_APP_START = 11,     \
    PAR_ID_APP_CRC32 = 47,     \
    PAR_ID_APP_LEN = 48,       \
    PAR_ID_APP_STATUS = 14,

#else /*HAS_BOOTLOADER*/
#define FLASH_FS_BOOTLOADER
#endif /*HAS_BOOTLOADER*/


/*Do not change existing values.*/
typedef enum  {
    FLASH_FS_BOOTLOADER
    FLASH_FS_WATCHDOG
    FLASH_FS_KEEPPASS
    PAR_IDS_CLOCK
    PAR_ID_REBOOT_CNT = 1,
    PAR_ID_FLASH_FS_TOGGLE_CNT = 87, /*System Diagnostic NVS variable*/
#ifdef HAS_LORA
    PAR_ID_LORA_SF = 3,         /*Chips / Symbol*/
    PAR_ID_LORA_CR = 4,         /*in raw bits / total bits*/
    PAR_ID_LORA_BW = 5,         /*Hz*/
    PAR_ID_CRC_TYPE = 8,        /*On Off*/
    PAR_ID_LORA_HEADER_TYPE = 9,     /*0-Variable length packet / 1-Fixed length packet*/
    PAR_ID_LORA_SYNC_WORD = 29,
#endif /*HAS_LORA*/
    PAR_ID_BOOT_CMD = 12,
    PAR_ID_MAX_UP_TIME = 60,
#ifdef HAS_CAN
    PAR_ID_CAN_NODE_ID = 61,
#endif

#ifdef HAS_AES
    PAR_ID_AES_256BIT_KEY_ID = 62,
#endif /*HAS_AES*/
#ifdef HAS_I2S1
    PAR_ID_I2S1_BUS_ROLE=64,
#endif /*HAS_I2S1*/
#ifdef HAS_I2S2
    PAR_ID_I2S2_BUS_ROLE=66,
#endif /*HAS_I2S2*/
#ifdef HAS_I2S4
    PAR_ID_I2S4_BUS_ROLE=69,
#endif /*HAS_I2S2*/

#ifdef HAS_BT1026
    PAR_ID_BT1026_I2S_BUS_ROLE=76,
    PAR_ID_BT1026_I2S_SAMPLE_RATE=77,
    PAR_ID_BT1026_I2S_RESOLUTION=78,
#endif /*HAS_BT1026    */

#ifdef HAS_BC127
    PAR_ID_BC127_I2S_BUS_ROLE=65,
    PAR_ID_BC127_I2S_SCALING_FACTOR=68,
#endif /*HAS_BC127*/
#ifdef HAS_WM8731
    PAR_ID_WM8731_I2S_BUS_ROLE=67,
#endif /*HAS_WM8731*/
    PAR_ID_BOOT_CNT = 13, /*To spot hangs on in App*/
#ifdef HAS_MBR
    PAR_ID_BOOT_START = 73,
#endif


    PAR_ID_GNSS_MODE = 21,
#ifdef HAS_GNSS_RTK
    PAR_ID_BASE_ACC = 33, /*Base Fix pos Accuracy in MM*/
    PAR_ID_BASE_LOCATION = 20,
    PAR_ID_BASE_ALT = 22, /* Base station altitude above sea level*/
    PAR_ID_RTK_CHANNEL = 24,
    PAR_ID_GPS = 34,
    PAR_ID_GLONASS = 35,
    PAR_ID_GALILEO = 36,
    PAR_ID_BEI_DOU = 37,
    PAR_ID_RTK_FIX_LONG = 26, /*Max Duration in RTK fixed mode*/
#endif /*HAS_GNSS_RTK*/
    PAR_ID_PWR_SRC = 15,        /*power source Battary XP3(1) or external XP1(0)*/
    PAR_ID_SERIAL_NUM = 25,
#ifdef HAS_GNSS
    PAR_ID_TIME_ZONE = 17,      /*TimeZone*/
    PAR_ID_GNSS_PERIOD = 23,
#endif /*HAS_GNSS*/
    PAR_ID_TEST_ID1 = 98,
    PAR_ID_TEST_ID2 = 99,
    PAR_ID_TEST_START = 100,
    PAR_ID_TEST_END = 200,
#ifdef HAS_SDIO
    PAR_ID_SDIO_CLOCKDIV=74,
#endif

#ifdef HAS_SX1262
    PAR_ID_FREQ = 2,       /*Hz*/
    PAR_ID_IQ_SETUP = 10,
    PAR_ID_RETX_CNT = 38,
    PAR_ID_RETX = 59,
    PAR_ID_PREAMBLE_LENGTH = 6, /*byte*/
    PAR_ID_LOW_DATA_RATE = 30,
    PAR_ID_OUT_POWER = 16, /*output power*/
    PAR_ID_MAX_BIT_RATE = 19,
    PAR_ID_MAX_LINK_DIST = 18,
    PAR_ID_TX_MUTE = 47,
    PAR_ID_RX_GAIN = 58,
    PAR_ID_PAYLOAD_LENGTH = 7,  /*byte*/
    PAR_ID_WIRELESS_INTERFACE = 28,    /* GFSK / LoRa*/
#endif /*HAS_SX1262*/

#ifdef HAS_WDT
    PAR_ID_WDT_MUTE = 63,
#endif /*HAS_WDT*/

#ifdef HAS_GFSK
    PAR_ID_CRC_INIT = 32,
    PAR_ID_CRC_POLY = 31,
    PAR_ID_SYNC_WORD = 27,
    PAR_ID_PRE_DET_LEN=40,
    PAR_ID_ADDR_COMP=41,
    PAR_ID_NODE_ADDR=42,
    PAR_ID_BROADCAST_ADDR=43,
    PAR_ID_WHITENING=45,
    PAR_ID_WHITENING_INIT_VALUE=46,
    PAR_ID_GFSK_BANDWIDTH =49,
    PAR_ID_GFSK_CRC_TYPE=44,
    PAR_ID_GFSK_BITRATE=51,
    PAR_ID_GFSK_PULSE_SHAPE=52,
    PAR_ID_GFSK_FREQ_DEV=53,
    PAR_ID_GFSK_PRE_LEN=54,
    PAR_ID_GFSK_PACKET_TYPE=55,
    PAR_ID_SYNC_WORD_LEN=56,
    PAR_ID_GFSK_PAYLOAD_LEN=57,
#endif /*HAS_GFSK*/

#ifdef HAS_PASTILDA
    PAR_ID_PASTILDA_LAST_ENTRY_INDEX = 81,
#endif /*HAS_PASTILDA*/

#ifdef HAS_DS_TWR
    PAR_ID_PHASE1_OFFSET=82,
    PAR_ID_PHASE2_OFFSET=83,
    PAR_ID_FINAL_OFFSET=84,
#endif /*HAS_DS_TWR*/

#ifdef HAS_DECAWAVE
    PAR_ID_DECAWAVE_ID = 85,
#endif

#ifdef HAS_GNSS
    PAR_ID_TRUE_LOCATION = 86,
#endif

#ifdef HAS_LIGHT_NAVIGATOR
    PAR_ID_DAWN_1 = 88,
    PAR_ID_SUNSET_1 = 89,

    PAR_ID_DAWN_2 = 90,
    PAR_ID_SUNSET_2 = 91,
#endif
    PAR_IDS_BOARD



    PAR_ID_NAN,
    PAR_ID_CNT
} Id_t;

#endif /* FLASH_FS_FILE_IDENTIFICATIONS_H */
