#ifndef SPI_CUSTOM_CONST_H
#define SPI_CUSTOM_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "spi_dep.h"

#define SPI_TX_DONE_TIMEOUT_MS 300
#define SPI_RX_DONE_TIMEOUT_MS 300

typedef enum  {
    SPI0_INX = 0,
    SPI1_INX = 1,
    SPI2_INX = 2,
    SPI3_INX = 3,
    SPI4_INX = 4,
    SPI5_INX = 5,
    SPI_UNDEF_INX = 0,
    //SPI_CNT = 6
} SpiName_t;

// Bit 0,,CLKPHA
typedef enum {
	SPI_AT32_CLOCK_PHASE_1ST=0,
	SPI_AT32_CLOCK_PHASE_2ND=1,
	SPI_AT32_CLOCK_PHASE_UNDEF=2,
}SpiAtClockPhase_t;

// Bit 1,,CLKPOL
typedef enum {
    SPI_AT32_CLOCK_POLARITY_LOW=0,
    SPI_AT32_CLOCK_POLARITY_HIGH=1,
    SPI_AT32_CLOCK_POLARITY_UNDEF=2,
}SpiAtClockPolarity_t;

// Bit 2 Master enable,MSTEN
typedef enum {
    SPI_AT32_BUS_ROLE_SLAVE =0,//0: Disabled (Slave)
    SPI_AT32_BUS_ROLE_MASTER =1,//1: Enabled (Master)
    SPI_AT32_BUS_ROLE_UNDEF=2,
}SpiAtBusRole_t;


// Bit 5:3 Master clock frequency division,MDIV
typedef enum {
    SPI_AT32_MASTER_CLK_DIVIDER_2 =0,//Divided by 2
    SPI_AT32_MASTER_CLK_DIVIDER_4 =1,//Divided by 4
    SPI_AT32_MASTER_CLK_DIVIDER_8 =2,//Divided by 8
    SPI_AT32_MASTER_CLK_DIVIDER_16 =3,//Divided by 16
    SPI_AT32_MASTER_CLK_DIVIDER_32 =4,//Divided by 32
    SPI_AT32_MASTER_CLK_DIVIDER_64 =5,//Divided by 64
    SPI_AT32_MASTER_CLK_DIVIDER_128 =6, //Divided by 128
    SPI_AT32_MASTER_CLK_DIVIDER_256 =7, //Divided by 256
    SPI_AT32_MASTER_CLK_DIVIDER_512 =8, //Divided by 512
    SPI_AT32_MASTER_CLK_DIVIDER_1024 =9, //Divided by 1024

    SPI_AT32_MASTER_CLK_DIVIDER_UNDEF=2,
}SpiAtMasterClkFreqDiv_t;


// Bit 6, SPI enable,SPIEN
typedef enum {
    SPI_AT32_CTRL_DISABLED =0,// Disabled
    SPI_AT32_CTRL_ENABLED =1,// Enabled
    SPI_AT32_CTRL_UNDEF=2,
}SpiAtCtrl_t;


//Bit 7, LSB transmit first,LTF
typedef enum {
    SPI_AT32_FIRST_BIT_MSB =0, // MSB
    SPI_AT32_FIRST_BIT_LSB =1, // LSB
    SPI_AT32_FIRST_BIT_UNDEF=2,
}SpiAtFirstBit_t;

//Bit 8, Software CS internal level, SWCSIL
typedef enum {
    SPI_AT32_CHIP_SEL_LEVEL_LOW = 0, // Low level
    SPI_AT32_CHIP_SEL_LEVEL_HIGH = 1, // High level
    SPI_AT32_CHIP_SEL_LEVEL_UNDEF = 2,
}SpiAtChipSelLevlel_t;


//Bit 9, Software CS enable, SWCSEN
typedef enum {
    SPI_AT32_CHIP_SEL_HW = 0, // Software CS Disabled
    SPI_AT32_CHIP_SEL_SW  = 1, // Software CS Enabled
    SPI_AT32_CHIP_SEL_UNDEF = 2,
}SpiAtChipSelCtrl_t;


//Bit 10, Receive-only active, ORA
typedef enum {
    SPI_AT32_MOVE_MODE_TX_AND_RX = 0, // Transmission and reception
    SPI_AT32_MOVE_MODE_RX_ONLY  = 1, // Receive-only mode
    SPI_AT32_MOVE_MODE_UNDEF = 2,
}SpiAtTxMode_t;

//Bit 11, Frame bit num, FBN
typedef enum {
    SPI_AT32_FRAME_SIZE_8_BIT = 0,    // 0: 8-bit data frame
    SPI_AT32_FRAME_SIZE_16_BIT = 1, // 1: 16-bit data frame
    SPI_AT32_FRAME_SIZE_UNDEF = 2,
}SpiAtFrameSize_t;

//Bit 12, Transmit CRC next, NTC
typedef enum {
    SPI_AT32_CRC_OFF = 0, // Next transmitted data is the normal value
    SPI_AT32_CRC_ON = 1, // Next transmitted data is CRC value
    SPI_AT32_CRC_UNDEF = 2,
}SpiAtCrc_t;


//Bit 13, RC calculation enable, CCEN
typedef enum {
    SPI_AT32_RC_OFF = 0, // Disabled
    SPI_AT32_RC_ON = 1, // Enabled
    SPI_AT32_RC_UNDEF = 2,
}SpiAtRc_t;

// Bit 14, Single line bidirectional half-duplex transmission direction
// This bit and the  bit together determine the data
// output direction in
// Single line bidirectional half-duplex, SLBTD
typedef enum {
    SPI_AT32_HALF_DUPLEX_RX_ONLY = 0, // 0: Receive-only mode
    SPI_AT32_HALF_DUPLEX_TX_ONLY = 1, // 1: Transmit-only mode
    SPI_AT32_HALF_DUPLEX_UNDEF = 2,
}SpiAtHalfDuplexMode_t;


// Bit 15, Single line bidirectional half-duplex enable , SLBEN
typedef enum {
    SPI_AT32_SINGLE_LINE_BI_DIR_OFF = 0, // Disabled (Full-duplex mode)
    SPI_AT32_SINGLE_LINE_BI_DIR_ON = 1, // Enabled
    SPI_AT32_SINGLE_LINE_BI_DIR_UNDEF = 2,
}SpiAtSingleLineBiDir_t;


#ifdef __cplusplus
}
#endif

#endif /* SPI_CUSTOM_CONST_H  */
