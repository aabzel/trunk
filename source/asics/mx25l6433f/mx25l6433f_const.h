#ifndef MX25L6433F_CONST_H
#define MX25L6433F_CONST_H

#include "time_mcal.h"
#include "mx25l6433f_dep.h"

#define MX25L6433F_VERSION 1
#define MX25L6433F_PERIOD_US MSEC_2_USEC(500)

/*
  Identification (Table 9, Page 49)
 */
#define MX25L6433F_MANUFACTURER_ID    0xC2
#define MX25L6433F_DIVICE_ID          0x16
#define MX25L6433F_MEMORY_TYPE        0x20
#define MX25L6433F_MEMORY_DENCITY     0x17
#define MX25L6433F_ELECTRONIC_ID      0x16


#define MX25_PAGE_SIZE          256U
/*
  Commands (Table 4, Pages 15-17)
  Table 12. Acceptable Commands During Program/Erase Suspend after tPSL/tES
*/
typedef enum{
    MX25L6433F_CMD_WREN        =   0x06,  /**/
    MX25L6433F_CMD_FAST_READ   =   0x0B,  /**/
    MX25L6433F_CMD_DREAD       =   0x3B,  /**/
    MX25L6433F_CMD_QREAD       =   0x6B,  /**/
    MX25L6433F_CMD_2READ       =   0xBB,  /**/
    MX25L6433F_CMD_4READ       =   0xEB,  /**/
    MX25L6433F_CMD_RDSFDP      =   0x5A,  /**/
    MX25L6433F_CMD_RDID        =   0x9F,  /**/
    MX25L6433F_CMD_REMS        =   0x90,  /**/
    MX25L6433F_CMD_ENSO        =   0xB1,  /**/
    MX25L6433F_CMD_EXSO        =   0xC1,  /**/
    MX25L6433F_CMD_RESUME      =   0x7A,  /**/
    MX25L6433F_CMD_PP          =   0x02,  /**/
    MX25L6433F_CMD_4PP         =   0x38,  /**/
    MX25L6433F_CMD_WRDI        =   0x04,  /**/
    MX25L6433F_CMD_RDSR        =   0x05,  /**/
    MX25L6433F_CMD_RDCR        =   0x15,  /**/
    MX25L6433F_CMD_RDSCUR      =   0x2B,  /**/
    MX25L6433F_CMD_RES         =   0xAB,  /**/
    MX25L6433F_CMD_RSTEN       =   0x66,  /**/
    MX25L6433F_CMD_RST         =   0x99,  /**/
    MX25L6433F_CMD_NOP         =   0x00,  /**/
    MX25L6433F_CMD_WRSR        =   0x01,  /**/
    MX25L6433F_CMD_READ        =   0x03,  /**/
    MX25L6433F_CMD_SECTOR_ERASE=   0x20,  /**/
    MX25L6433F_CMD_BE32K       =   0x52,  /**/
    MX25L6433F_CMD_BE          =   0xD8,  /**/
    MX25L6433F_CMD_CE          =   0xC7,  /**/
    MX25L6433F_CMD_DP          =   0xB9,  /**/
    MX25L6433F_CMD_RDP         =   0xAB,  /**/
    MX25L6433F_CMD_WRSCUR      =   0x2F,  /**/
    MX25L6433F_CMD_SBL         =   0xC0,  /**/
}Mx25l6433fCmd_t;


#endif /* MX25L6433F_CONST_H */
