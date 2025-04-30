#ifndef SD_CARD_CONST_H
#define SD_CARD_CONST_H

#define BLOCK_SIZE_BYTE (512U)
#define SD_ERASE_DONE_TIME_OUT_MS 5000

#define DUMMY_BYTE 0xFF
#define SD_R1_ERROR_BYTE 0xFF
#define SD_IDLE_RETRY_COUNT 50
#define SD_SPI_R1_IN_IDLE_STATE 0x01

typedef enum {
    TOKEN_BUSY = 0x00,
    TOKEN_MULT_BLK_WR= 0xFC, /* 0b1111_1100 CMD25*/
    TOKEN_START_BLOCK= 0xFE, /* 0b1111_1110 CMD17 /CMD18/ CMD19 */
    TOKEN_STOP= 0xFD         /* 0b1111_1101 StopTranToken */
}SdCardTonen_t;

/* Definitions for MMC/SDC command
 * TODO make LUT*/
typedef enum{
    CMD0 = 0 ,   /*0b0100_0000 GO_IDLE_STATE */
    CMD1 = 1 ,   /* SEND_OP_COND (MMC) */
    CMD8 = 8 ,   /* SEND_IF_COND SEND_IF_COND */
    CMD9 = 9 ,   /* SEND_CSD */
    CMD10 = 10,  /* SEND_CID */
    CMD12 = 12,  /* STOP_TRANSMISSION */
    CMD13 = 13,  /* SEND_STATUS*/
    CMD16 = 16,  /* SET_BLOCKLEN */
    CMD17 = 17,  /* READ_SINGLE_BLOCK */
    CMD18 = 18,  /* READ_MULTIPLE_BLOCK */
    CMD23 = 23,  /* SET_BLOCK_COUNT */
    CMD24 = 24,  /* WRITE_BLOCK */
    CMD25 = 25,  /* WRITE_MULTIPLE_BLOCK */
    CMD41 = 41,  /* SD_SEND_OP_COND (ACMD) */
    CMD30 = 30,  /* SEND_WRITE_PROT */
    CMD32 = 32,  /* ERASE_WR_BLK_START_ADDR */
    CMD33 = 33,  /* ERASE_WR_BLK_END_ADDR */
    CMD38 = 38,  /* ERASE */
    CMD55 = 55 ,  /* APP_CMD */
    CMD42 = 42 ,  /* LOCK_UNLOCK */
    CMD58 = 58,  /* READ_OCR */
    CMD59 = 59,  /* */
    ACMD41 = 41 /*Send host capacity support info and activates the card's init process */
                        //SEND_OP_COND (SDC)
}SdCmd_t;

typedef enum{
    HCS_SDHC_SDXC_NO=0,
    HCS_SDHC_SDXC_YES=1,
    HCS_SDHC_SDXC_UNDEF=2,
}Hcs_t;

typedef enum{
    SD_ERR_CODE_OK=0,
    SD_ERR_CODE_17=17,
    SD_ERR_CODE_IDLE=1,
    SD_ERR_CODE_UNDEF=0xFF,
}SdErrCode_t;

typedef enum{
    CCS_SDSC=0, /**/
    CCS_SDHC_OR_SDXC=1, /**/
    CCS_UNDEF=2, /**/
}CCS_t;

typedef enum {
    VOLT_ACCEP_NOT_DEF = 0, /*Not Defined*/
    VOLT_ACCEP_2_7_3_6 = 1, /**/
    VOLT_ACCEP_RES_LOW_VOLTAGE=2, /*Reserved for Low Voltage Range*/
    VOLT_ACCEP_RES_1=4, /*Reserved*/
    VOLT_ACCEP_RES_2=8, /*Reserved*/
    VOLT_ACCEP_UNDEF=2, /**/
}VoltAccept_t;

typedef enum {
    DAT_RESP_TOKEN_DATA_ACCEPTED=2,
    DAT_RESP_TOKEN_DATA_REJECTED_DUE_TO_CRC=5,
    DAT_RESP_TOKEN_DATA_REJECTED_DUE_TO_WR_ERR=6,

    DAT_RESP_TOKEN_UNDEF=0,
} DataRespTokenStatus_t;

typedef enum {
    APP_CMD = CMD55,
    GO_IDLE_STATE = CMD0,
    READ_SINGLE_BLOCK = CMD17,
    READ_OCR = CMD58,
    SEND_WRITE_PROT = CMD30,
    SEND_STATUS = CMD13,
    SEND_IF_COND = CMD8,
    SD_SEND_OP_COND = ACMD41,
    WRITE_SINGLE_BLOCK = CMD24,
}CmdAlias_t;


/* MMC card type flags (MMC_GET_TYPE) */
#define CT_MMC 0x01   /* MMC ver 3 */
#define CT_SD1 0x02   /* SD ver 1 */
#define CT_SD2 0x04   /* SD ver 2 */
#define CT_SDC 0x06   /* SD */
#define CT_BLOCK 0x08 /* Block addressing */

typedef enum{
    CSD_VERSION_1_0=0,
    CSD_VERSION_2_0=1,
    CSD_VERSION_RES1=2,
    CSD_VERSION_RES2=3,
}ScdStruct_t;

typedef enum{
    SD_SPI_RES_R1=1,
    SD_SPI_RES_R1B=11,
    SD_SPI_RES_R2=2,
    SD_SPI_RES_R3=3,
    SD_SPI_RES_R7=7,
    SD_SPI_RES_UNDEF=0,
}SdSpiRespType_t;

typedef enum{
    SD_SPI_ADDR_BYTE=0,
    SD_SPI_ADDR_BLOCK=1,
    SD_SPI_ADDR_UNDEF=2,
}SdSpiAddressMethod_t;


typedef enum{
    SD_MONTH_JANUARY = 1,
    SD_MONTH_FEBRUARY = 2,
    SD_MONTH_MARCH = 3,
    SD_MONTH_APRIL = 4,
    SD_MONTH_MAY = 5,
    SD_MONTH_JUNE = 6,
    SD_MONTH_JULY = 7,
    SD_MONTH_AUGUST = 8,
    SD_MONTH_SEPTEMBER = 9,
    SD_MONTH_OCTOBER = 10,
    SD_MONTH_NOVEMBER = 11,
    SD_MONTH_DECEMBER = 12,

    SD_MONTH_UNDEF=13,
}SdMonth_t;

#endif /* SD_CARD_CONST_H */
