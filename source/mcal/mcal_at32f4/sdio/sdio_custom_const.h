#ifndef SDIO_CUSTOM_CONST_H
#define SDIO_CUSTOM_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "time_utils.h"

#define SDIO_PERIOD_US SEC_2_USEC(5)
#define BLOCK_SIZE_BYTE (512U)
#define SDIO_RX_TIME_OUT_MS 4000U
#define SDIO_TX_TIME_OUT_MS 4000U
#define SDIO_TIME_OUT_MS 40U
//1-err < SDIO_TIME_OUT_MS <64
//2-err
//4-err
//8-err
//16-err err
//32-err
//32-ok
//33-ok err
//34-ok
//36-ok
//40-ok
//48-ok
//64-ok

//5-ok
//10-ok
//25-ok

#define SD_CARD_SDIO_NUM 1U
//#define SDMMC_DATATIMEOUT SEC_2_MS(5)
#define NUM_OF_REGISTERS 8U

#define REG_OCR 0x7AU /* operation conditions register */
#define REG_CID 0x4AU /* Card ID */
#define REG_SSR 0x4DU /* SD Status*/
#define REG_CSD 0x49U /* Card specific data */
#define REG_CSR 0x4DU /* Card Status Register  */
#define REG_RCA 0x00U /* relative card address register */
#define REG_DSR 0x00U /* Drive stage register  */
#define REG_SCR 0x00U /* SD Card Configuration register */


#ifdef __cplusplus
}
#endif

#endif /* SDIO_CUSTOM_CONST_H  */
