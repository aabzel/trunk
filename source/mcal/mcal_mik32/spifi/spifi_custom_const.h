#ifndef SPIFI_MIK_CONST_H
#define SPIFI_MIK_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "spifi_dep.h"


/*
see https://wiki.mik32.ru/SPIFI
 */


typedef enum {
    SPIFI_CTRL_FBCLK_INTERNAL = 0,
    SPIFI_CTRL_FBCLK_EXTERNAL = 1,
    SPIFI_CTRL_FBCLK_UNDEF = 2,
}SpiFICtrlFbClk_t;

typedef enum {
    SPIFI_CTRL_DUAL_4BIT = 0,
    SPIFI_CTRL_DUAL_2BIT = 1,
    SPIFI_CTRL_DUAL_UNDEF = 2,
}SpiFICtrlDual_t;


typedef enum {
    SPIFI_CMD_DOUT_FLASH_READ = 0,
    SPIFI_CMD_DOUT_FLASH_WRITE = 1,
    SPIFI_CMD_DOUT_UNDEF = 2,
}SpiFiCmdDout_t;


typedef enum {
    SPIFI_CMD_POLL_NO = 0,
    SPIFI_CMD_POLL_YES = 1,
    SPIFI_CMD_POLL_UNDEF = 2,
}SpiFiCmdPoll_t;

typedef enum {
    SPIFI_CTRL_RFCLK_POS = 0,
    SPIFI_CTRL_RFCLK_NEQ = 1,
    SPIFI_CTRL_RFCLK_UNDEF = 2,
}SpiFICtrlRfClk_t;

typedef enum {
    SPIFI_STAT_INTRQ_NONE = 0,
    SPIFI_STAT_INTRQ_RESET_QUERY = 1,
    SPIFI_STAT_INTRQ_UNDEF = 2,
}SpiFiStatIntrQ_t;



typedef enum {
    SPIFI_STATE_IDLE = 1,
    SPIFI_STATE_CSWAIT = 2,
    SPIFI_STATE_TRCODE = 3,
    SPIFI_STATE_RDDATA = 4,
    SPIFI_STATE_EOCMD = 5,
    SPIFI_STATE_UNDEF = 0,
}SpiFiState_t;


typedef enum {
    SPI_FI_CACHE_DISABLE    = 0,
    SPI_FI_CACHE_ENABLE     = 1,
    SPI_FI_CACHE_UNDEF = 2,
}SpiFiCacheEn_t;



/*
 Command Operation Code and Address Field Control Bit
  FRAMEFORM - Бит управления полями кода операции и адреса команды:
  0 – резерв;
  1 – выдается только код операции, адреса нет; (SPIFI_CONFIG_CMD_FRAMEFORM_OPCODE_NOADDR)
  2 – код операции и младший байт адреса;
  3 – код операции и два младших байта адреса;
  4 – код операции и три младших байта адреса;
  5 – код операции и 4 байта адреса;
  6 – нет кода операции, три младших байта адре-са;
  7 – нет кода операции, 4 байта адреса
*/
typedef enum {
  SPIFI_CMD_FRAME_FORM_OPCODE_NOADDR = 1, /* only the operation code is given, no address */
  SPIFI_CMD_FRAME_FORM_OPCODE_1ADDR = 2, /* opcode and low byte of address */
  SPIFI_CMD_FRAME_FORM_OPCODE_2ADDR = 3, /* operation code and the two lower bytes of the address */
  SPIFI_CMD_FRAME_FORM_OPCODE_3ADDR = 4, /*operation code and three lower bytes of the address  */
  SPIFI_CMD_FRAME_FORM_OPCODE_4ADDR = 5, /* operation code and 4 address bytes */
  SPIFI_CMD_FRAME_FORM_NOOPCODE_3ADDR = 6, /* no opcode, three lower bytes of address */
  SPIFI_CMD_FRAME_FORM_NOOPCODE_4ADDR = 7, /* no opcode, 4 bytes address */
  SPIFI_CMD_FRAME_FORM_UNDEF = 0, /* */
}SpiFiFrameForm_t;

/*
  FIELDFORM Command field output format
  FIELDFORM - Формат вывода полей команды:
  0 – все поля выводятся в последовательном режиме; (SPIFI_CONFIG_CMD_FIELDFORM_ALL_SERIAL)
  1 – данные выводятся в четырех или двух битовом режиме, а остальные поля в последовательном режиме;
  2 – код операции выводится в последовательном режиме, а остальные в четырех или двух битовом;
  3 – все поля в четырех или двух битовом режиме
*/
typedef enum {
    /*all fields are output in sequential mode*/
    SPIFI_CMD_FIELDFORM_ALL_SERIAL = 0,

    /*data is output in four or two bit mode, and
     * the remaining fields in serial mode */
    SPIFI_CMD_FIELDFORM_DATA_PARALLEL = 1,

    /*the operation code is output in serial mode,
     * and the rest in four or two bit */
    SPIFI_CMD_FIELDFORM_OPCODE_SERIAL = 2,

    /* all fields in four or two bit mode */
    SPIFI_CMD_FIELDFORM_ALL_PARALLEL = 3,
}SpiFiFieldForm_t;


#ifdef __cplusplus
}
#endif

#endif /* SPIFI_MIK_CONST_H  */
