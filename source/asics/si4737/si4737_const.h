#ifndef SI4737_CONST_H
#define SI4737_CONST_H

#include "timer_utils.h"

#define SI4737_I2C_ADDR_7BIT ((uint8_t )0x63)
#define SI4737_I2C_ADDR (SI4737_I2C_ADDR_7BIT<<1)

#define SI4737_POLL_PERIOD_US MSEC_2_US(200)
#define SI4737_CHIP_REV 0x43

typedef enum{
 SI4737_CMD_POWER_UP        =0x01,
 SI4737_CMD_GET_REV         =0x10,
 SI4737_CMD_POWER_DOWN      =0x11,
 SI4737_CMD_SET_PROPERTY    =0x12,
 SI4737_CMD_GET_PROPERTY    =0x13,
 SI4737_CMD_FM_TUNE_FREQ    =0x20,
 SI4737_CMD_FM_SEEK_START   =0x21,
 SI4737_CMD_FM_RSQ_STATUS   =0x23,
 SI4737_CMD_FM_RDS_STATUS   =0x24,
 SI4737_CMD_AM_TUNE_FREQ    =0x40,
 SI4737_CMD_AM_SEEK_START   =0x41,
 SI4737_CMD_AM_RSQ_STATUS   =0x43,
 SI4737_CMD_WB_TUNE_FREQ    =0x50,
 SI4737_CMD_WB_RSQ_STATUS   =0x53,
 //Undocumanted
 SI4737_FM_TUNE_STATUS      =0x22,
 SI4737_CMD_UNDEF =0xFF,
 SI4737_GET_INT_STATUS = 0x14,
}Si4737Command_t;

#if 0
#define SI4737_PATCH_ARGS               0x15
#define SI4737_PATCH_DATA               0x16
#define SI4737_FM_AGC_STATUS                0x27
#define SI4737_FM_AGC_OVERRIDE              0x28
#define SI4737_AM_TUNE_STATUS               0x42
#define SI4737_AM_AGC_STATUS                0x47
#define SI4737_AM_AGC_OVERRIDE              0x48
#define SI4737_WB_TUNE_STATUS               0x52
#define SI4737_WB_ASQ_STATUS                0x55
#define SI4737_WB_AGC_STATUS                0x57
#define SI4737_WB_AGC_OVERRIDE              0x58
#define SI4737_GPIO_CTL                    0x80
#define SI4737_GPIO_SET                     0x81
#endif


/* Table 16. Selected Si473x Properties */
typedef enum{
 SI4737_FM_DEEMPHASIS                   = 0x1100,
 SI4737_FM_BLEND_STEREO_THRESHOLD       = 0x1105,
 SI4737_FM_BLEND_MONO_THRESHOLD         = 0x1106,
 SI4737_FM_RSQ_INT_SOURCE               = 0x1200,
 SI4737_FM_SOFT_MUTE_RATE               = 0x1300,
 SI4737_FM_SOFT_MUTE_MAX_ATTENUATION    = 0x1302,
 SI4737_FM_SOFT_MUTE_SNR_THRESHOLD      = 0x1303,
 SI4737_FM_SEEK_BAND_BOTTOM             = 0x1400,
 SI4737_FM_SEEK_BAND_TOP                = 0x1401,
 SI4737_FM_SEEK_FREQ_SPACING            = 0x1402,
 SI4737_FM_SEEK_TUNE_SNR_THRESHOLD      = 0x1403,
 SI4737_FM_SEEK_TUNE_RSSI_THRESHOLD     = 0x1404,
 SI4737_FM_RDS_INT_SOURCE               = 0x1500,
 SI4737_FM_RDS_INT_FIFO_COUNT           = 0x1501,
 SI4737_FM_RDS_CONFIG                   = 0x1502,
 SI4737_AM_DEENOHASIS                   = 0x3100,
 SI4737_AM_CHANNEL_FILTER               = 0x3102,
 SI4737_AM_AUTO_VOLUME_CTRL_MAX_GAIN    = 0x3103,
 SI4737_AM_RSQ_INTERRUPTS               = 0x3200,
 SI4737_AM_SOFT_MUTE_RATE               = 0x3300,
 SI4737_AM_SOFT_MUTE_MAX_ATTENUATION    = 0x3302,
 SI4737_AM_SOFT_MUTE_SNR_THRESHOLD      = 0x3303,
 SI4737_AM_SEEK_BAND_BOTTOM             = 0x3400,
 SI4737_AM_SEEK_BAND_TOP                = 0x3401,
 SI4737_AM_SEEK_FREQ_SPACING            = 0x3402,
 SI4737_AM_SEEK_SNR_THRESHOLD           = 0x3403,
 SI4737_AM_SEEK_RSSI_THRESHOLD          = 0x3404,
 SI4737_RX_VOLUME                       = 0x4000,
 SI4737_RX_HARD_MUTE                    = 0x4001,
 SI4737_WB_MAX_TUNE_ERROR               = 0x5108,
 SI4737_WB_RSQ_INT_SOURCE               = 0x5200,
 SI4737_WB_ASQ_INT_SOURCE               = 0x5600,
 SI4737_GPO_IEN                         = 0x0001,
 SI4737_DIGITAL_OUTPUT_FORMAT           = 0x0102,
}Si4737PropertyId_t;

#if 0
#define SI4737_DIGITAL_OUTPUT_SAMPLE_RATE       0x0104
#define SI4737_REFCLK_FREQ                      0x0201
#define SI4737_REFCLK_PRESCALE                  0x0202
#define SI4737_FM_MAX_TUNE_ERROR                0x1108
#define SI4737_FM_RSQ_SNR_HI_THRESHOLD          0x1201
#define SI4737_FM_RSQ_SNR_LO_THRESHOLD          0x1202
#define SI4737_FM_RSQ_RSSI_HI_THRESHOLD         0x1203
#define SI4737_FM_RSQ_RSSI_LO_THRESHOLD         0x1204
#define SI4737_FM_RSQ_BLEND_THRESHOLD           0x1207
#define SI4737_FM_SOFT_MUTE_SLOPE               0x1301
#define SI4737_AM_RSQ_SNR_HIGH_THRESHOLD        0x3201
#define SI4737_AM_RSQ_SNR_LOW_THRESHOLD         0x3202
#define SI4737_AM_RSQ_RSSI_HIGH_THRESHOLD       0x3203
#define SI4737_AM_RSQ_RSSI_LOW_THRESHOLD        0x3204
#define SI4737_AM_SOFT_MUTE_SLOPE               0x3301
#define SI4737_WB_RSQ_SNR_HI_THRESHOLD          0x5201
#define SI4737_WB_RSQ_SNR_LO_THRESHOLD          0x5202
#define SI4737_WB_RSQ_RSSI_HI_THRESHOLD         0x5203
#define SI4737_WB_RSQ_RSSI_LO_THRESHOLD         0x5204
#define SI4737_WB_VALID_SNR_THRESHOLD           0x5403
#define SI4737_WB_VALID_RSSI_THRESHOLD          0x5404
#endif

typedef enum{
    RSQINT_NO=0, // Received Signal Quality measurement has not been triggered.
    RSQINT_YES=1, //Received Signal Quality measurement has been triggered.
    RSQINT_UNDEF=3,
}RxSigQaInt_t;

typedef enum{
    CTS_WAIT=0, //  Wait before sending next command.
    CTS_CLEAR=1, // Clear to send next command.
    CTS_UNDEF=3,
}ClearToSend_t;

typedef enum{
    DIGITAL_OUT_CLK_EDGE_RISING=0, //  DCLK rising edge
    DIGITAL_OUT_CLK_EDGE_FALING=1, // DCLK falling edge
    DIGITAL_OUT_CLK_EDGE_UNDEF=2,
}DigitalOutputDclkEdge_t;

typedef enum{
    DIGITAL_OUT_MODE_I2S=0,              // I2S
    DIGITAL_OUT_MODE_LEFT_JUSTIFIED=6,   // Left-justified
    DIGITAL_OUT_MODE_MSB_AT_2ND_DCLK_AFTER_DFS_PULSE=8,//MSB at second DCLK after DFS pulse
    DIGITAL_OUT_MODE_MSB_AT_1ST_DCLK_AFTER_DFS_PULSE=12,//MSB at first DCLK after DFS pulse
}DigitalOutputMode_t;

typedef enum{
    DIGITAL_OUT_MODE_STEREO=0, // Use mono/stereo blend (per blend thresholds)
    DIGITAL_OUT_MODE_MONO=1,   // Force mono
    DIGITAL_OUT_MODE_UNDEF=2,
}DigitalOutputMonoMode_t;





typedef enum{
    DIG_OUT_AUDIO_PREC_16_BIT=0,
    DIG_OUT_AUDIO_PREC_20_BIT=1,
    DIG_OUT_AUDIO_PREC_24_BIT=2,
    DIG_OUT_AUDIO_PREC_8_BIT=3,
    DIG_OUT_AUDIO_PREC_UNDEF=4,
}DigitalOutputAudioSamplePrecision_t;

typedef enum{
    ERROR_NO=0, // No error
    ERROR_SPOT=1, // Error
    ERROR_UNDEF=3,
}Err_t;

typedef enum{
   USE_EXTERNAL_RCLK=0,
   USE_CRYSTAL_OCILLtor=1,
}CrystalOscillator_t;

typedef enum{
  CTS_INT_DISABLED=0,
  CTS_INT_ENABLED=1,
}CtsInt_t;

typedef enum {
  INT_STATUS_PRESERVED=0,/* Interrupt status preserved*/
  INT_STATUS_CLEAR=1,    /* Clears RSQINT, BLENDINT, SNRHINT, SNRLINT, RSSIHINT, RSSILINT,MULTHINT, MULTLINT.*/
}IntAck_t;

typedef enum{
  GPO2_OUT_DISABLED=0,
  GPO2_OUT_ENABLED=1,
}Gpo2Out_t;

typedef enum{
  PATCH_BOOT_NORM=0,
  PATCH_COPY_NVM_TO_RAM=1,
}Patch_t;

typedef enum{
    SEEK_END_HALT=0, // Halt
    SEEK_END_WRAP=1, // Wrap
    SEEK_END_UNDEF=2,
}SeekEnd_t;

typedef enum{
    SEEK_DIR_DOWN=0, //direction of the search
    SEEK_DIR_UP=1,   // direction of the search
    SEEK_DIR_UNDEF=2,
}SeekDir_t;

typedef enum{
  STC_INT_KEEP=0, //
  STC_INT_CLEAR=1, //clears the seek/tune complete interrupt status indicator.
}SeekTuneIntClear_t;

typedef enum{
  SEEK_KEEP=0, //
  SEEK_ABBORT=1, //aborts a seek currently in progress.
}SeekCancel_t;


typedef enum{
    OP_MODE_ANALOG_AUDIO_OUTPUT=0x05,
    OP_MODE_DIGITAL_AUDIO_OUTPUT=0x0B,
    OP_MODE_DIGITAL_AUDIO_OUTPUTS=0xB0,
    OP_MODE_ANALOG_DIGITAL_AUDIO_OUTPUT=0xB5,
    OP_MODE_UNDEF=0xFF,
}OpMode_t;

typedef enum{
    RDS_RX_FIFO_READ=0, //0 = If FIFO not empty, read and remove oldest FIFO entry.
    RDS_RX_FIFO_CLEAR=1,   // 1 = Clear RDS Receive FIFO.
    RDS_RX_FIFO_UNDEF=2,
}RdsRxFifo_t;

typedef enum{
    RDS_INT_ACK_PRESERVED=0, //0 = RDSINT status preserved.
    RDS_INT_ACK_CLEAR=1,   // 1 = Clear RDS Receive FIFO.
    RDS_INT_ACK_UNDEF=2,
}RdsIntAck_t;


typedef enum{
    RDS_BLOCK_A=0,
    RDS_BLOCK_B=1,
    RDS_BLOCK_C=3,
    RDS_BLOCK_D=4,
    RDS_BLOCK_UNDEF=5,
}RdsBlock_t;

typedef enum{
    RDS_BLOCK_CORR_NO_ERR=0,    // No errors.
    RDS_BLOCK_CORR_1_2_BIT=1,   // 1–2 bit errors detected and corrected.
    RDS_BLOCK_CORR_3_5_BIT=2,   // 3–5 bit errors detected and corrected.
    RDS_BLOCK_CORR_UNCORR=3,    //  Uncorrectable.
    RDS_BLOCK_CORR_UNDEF=4,
}RdsBlobXCorrErr_t;

typedef enum{
    RDS_STATUS_ONLY_OLDEST = 0, /* Data in BLOCKA, BLOCKB, BLOCKC, BLOCKD, and BLE contain
                                 the oldest data in the RDS FIFO.*/
    RDS_STATUS_ONLY_LAST = 1,   /* 1 = Data in BLOCKA will contain the last valid block
                                 A data received for the current station. Data in BLOCKB
                                 will contain the last valid block B data received for the
                                 current station. Data in BLE will describe the bit errors
                                 for the data in BLOCKA and BLOCKB.*/
    RDS_STATUS_ONLY_UNDEF=2,
}RdsStatusOnly_t;



#endif /* SI4737_CONST_H */

