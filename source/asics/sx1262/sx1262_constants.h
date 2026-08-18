#ifndef SX1262_CONSTANTS_H
#define SX1262_CONSTANTS_H

#include <stdint.h>

#include "sx1262_op_codes.h"

#define SX1262_MAX_FRAME_SIZE 252U /*TODO Explore*/

#define RC_FREQ_HZ 13000000U
#define XTAL_FREQ_HZ 32000000U
#define SX1262_PERIOD_US 300U

#define FREQ_DIV 33554432U // 0x02000000 ( double )pow( 2.0, 25.0 )
#define MHZ_TO_FRF 1048576 /* ((float)XTAL_FREQ_HZ))*10000000.0f)*/
#define FREQ_STEP         0.95367431640625 // ( ( double )( XTAL_FREQ / ( double )FREQ_DIV ) )


#define RX_SIZE 256
#define TX_SIZE 256

#define FIFO_SIZE 256
#define TX_SINGLE_MODE 0
#define OPCODE_SIZE 1
#define DEV_SEL_SX1262 0
#define DEV_SEL_SX1261 1
#define RX_CONTINUOUS_MODE 0xFFFFFF

// Table 13-41: RampTime Definition
// RampTime Value RampTime (μs)
typedef enum eRampTime_t{
  SET_RAMP_10US= 0x00,   /*10  */
  SET_RAMP_20US= 0x01,   /*20  */
  SET_RAMP_40US= 0x02,   /*40  */
  SET_RAMP_80US= 0x03,   /*80  */
  SET_RAMP_200US= 0x04,  /*200 */
  SET_RAMP_800US =0x05,  /*800 */
  SET_RAMP_1700US= 0x06, /*1700*/
  SET_RAMP_3400US= 0x07, /*3400*/
}RampTime_t;


typedef enum Dio3Vol_t{
 DIO3_OUTPUTS_1_6_V= 0,
 DIO3_OUTPUTS_1_7_V= 1,
 DIO3_OUTPUTS_1_8_V= 2,
 DIO3_OUTPUTS_2_2_V= 3,
 DIO3_OUTPUTS_2_4_V= 4,
 DIO3_OUTPUTS_2_7_V= 5,
 DIO3_OUTPUTS_3_0_V= 6,
 DIO3_OUTPUTS_3_3_V= 7,
}Dio3Vol_t;


/* OpError Bits */
#define OP_ERR_BIT_RC64K_CALIB_ERR 0 /*RC64k calibration failed */
#define OP_ERR_BIT_RC13M_CALIB_ERR 1 /*RC13M calibration failed */
#define OP_ERR_BIT_PLL_CALIB_ERR 2   /*PLL calibration failed   */
#define OP_ERR_BIT_ADC_CALIB_ERR 3   /*ADC calibration failed   */
#define OP_ERR_BIT_IMG_CALIB_ERR 4   /*IMG calibration failed   */
#define OP_ERR_BIT_XOSC_START_ERR 5  /*XOSC failed to start     */
#define OP_ERR_BIT_PLL_LOCK_ERR 6    /*PLL failed to lock       */
#define OP_ERR_BIT_PA_RAMP_ERR 8     /*PA ramping failed        */


#define IRQ_BIT_TXDONE 0           /* Packet transmission completed All   */
#define IRQ_BIT_RXDONE 1           /* Packet received All */
#define IRQ_BIT_PREAMBLEDETECTED 2 /* Preamble detected All   */
#define IRQ_BIT_SYNCWORDVALID 3    /* Valid sync word detected FSK   */
#define IRQ_BIT_HEADERVALID 4      /* Valid LoRa header received LoRa®   */
#define IRQ_BIT_HEADERERR 5        /* LoRa header CRC error LoRa®  */
#define IRQ_BIT_CRCERR 6           /* Wrong CRC received All  */
#define IRQ_BIT_CADDONE 7          /* Channel activity detection finished LoRa® */
#define IRQ_BIT_CADDETECTED 8      /* Channel activity detected LoRa®   */
#define IRQ_BIT_TIMEOUT 9          /* Rx or Tx timeout All */

#define IQR_ALL_INT MASK_10BIT
#define IQR_MAIN_INT MASK_10BIT


typedef enum eCadNunSym_t{
    CAD_ON_1_SYMB =0x00, /* 1  Symbol*/
    CAD_ON_2_SYMB =0x01, /* 2  Symbols*/
    CAD_ON_4_SYMB =0x02, /* 4  Symbols*/
    CAD_ON_8_SYMB =0x03, /* 8  Symbols*/
    CAD_ON_16_SYMB =0x04, /* 16 Symbols*/
    CAD_UNDEF=0x05,
}CadNunSym_t;


typedef enum eCadExtMode_t{
    CAD_ONLY =0x00, /*The chip performs the CAD operation in LoRa�. Once done and whatever the
activity on the channel, the chip goes back to STBY_RC mode.*/
    CAD_RX =0x01,/*The chip performs a CAD operation and if an activity is detected, it stays in RX until
a packet is detected or the timer reaches the timeout defined by
cadTimeout * 15.625 us*/
}CadExtMode_t;

typedef enum eRegulatorMode_t{
   REG_MODE_ONLY_LDO= 0x00,  /*used for all modes*/
   REG_MODE_DC_DC_LDO= 0x01, /*used for STBY_XOSC,FS, RX and TX modes*/
}__attribute__ ((__packed__))RegulatorMode_t;

/*controlling the external RX switch*/
typedef enum eDio2Mode_t{
    DIO2_FREE=0,
    DIO2_RF_SW=1,
}__attribute__ ((__packed__))Dio2Mode_t;

/*Rx Gain Configuration*/
typedef enum eRxGain_t{
    RXGAIN_POWER_SAVING = 0x94,
    RXGAIN_BOOSTED = 0x96,
    RXGAIN_UNDEF = 0x00,
}__attribute__ ((__packed__))RxGain_t;

/*StdbyConfig Value Description*/
typedef enum eStandbyMode_t {
    STDBY_RC = 0,   /* Device running on RC13M, set STDBY_RC mode       */
    STDBY_XOSC = 1, /* Device running on XTAL 32MHz, set STDBY_XOSC mode*/
    STDBY_UNFED = 2,
} __attribute__ ((__packed__))StandbyMode_t;


/*Table 13-70: LoRa� PacketParam6 - InvertIQ*/
typedef enum eLoRaIQSetUp_t{
    IQ_SETUP_STANDARD=0x00,
    IQ_SETUP_INVERTED=0x01,
}__attribute__ ((__packed__))LoRaIQSetUp_t;

/*Status Bytes Definition*/
typedef enum eCommandStatus_t{
   COM_STAT_DATA_AVAIL= 0x2,   /*Data is available to host*/
   COM_STAT_COM_TIMEOUT= 0x3,  /*Command timeout2 */
   COM_STAT_COM_PROC_ERR= 0x4, /*Command processing error3*/
   COM_STAT_EXE_ERR =0x5,      /*Failure to execute command4*/
   COM_STAT_COM_TX_DONE= 0x6,  /*Command TX done5 */
}__attribute__ ((__packed__))CommandStatus_t;

/*!
 * Represents the interruption masks available for the radio
 *
 * Note that not all these interruptions are available for all packet types
 */
typedef enum eRadioIrqMasks_t {
    IRQ_MASK_RADIO_NONE = 0x0000,
    IRQ_MASK_TX_DONE = 0x0001,
    IRQ_MASK_RX_DONE = 0x0002,
    IRQ_MASK_PREAMBLE_DETECTED = 0x0004,
    IRQ_MASK_SYNCWORD_VALID = 0x0008,
    IRQ_MASK_HEADER_VALID = 0x0010,
    IRQ_MASK_HEADER_ERROR = 0x0020,
    IRQ_MASK_CRC_ERROR = 0x0040,
    IRQ_MASK_CAD_DONE = 0x0080,
    IRQ_MASK_CAD_ACTIVITY_DETECTED = 0x0100,
    IRQ_MASK_RX_TX_TIMEOUT = 0x0200,
    IRQ_MASK_RADIO_ALL = 0xFFFF
} __attribute__ ((__packed__)) RadioIrqMasks_t;

/*PacketType Definition*/
typedef enum eRadioPacketTypes_t {
    PACKET_TYPE_GFSK = 0x00, /*GFSK packet type*/
    PACKET_TYPE_LORA = 0x01, /*LORA mode*/
    PACKET_TYPE_LR_FHSS = 0x03, /* Long Range FHSS mode Explore*/
    PACKET_TYPE_NONE = 0x0F,
    PACKET_TYPE_UNDEF = 0xFF
}__attribute__ ((__packed__)) RadioPacketType_t;


typedef enum eOutputPower_t { OP_14_DBM = 0, OP_17_DBM = 1, OP_20_DBM = 2, OP_22_DBM = 3, OP_UNDEF = 4 } OutputPower_t;

typedef enum eChipMode_t {
    CHP_MODE_UNDEF = 0x0,
    CHP_MODE_STBY_RC = 0x2,
    CHP_MODE_STBY_XOSC = 0x3,
    CHP_MODE_FS = 0x4,
    CHP_MODE_RX = 0x5,
    CHP_MODE_TX = 0x6
} __attribute__ ((__packed__)) ChipMode_t;

#endif /* SX1262_CONSTANTS_H  */
