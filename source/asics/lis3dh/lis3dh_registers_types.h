#ifndef LIS3DH_REG_TYPES_H
#define LIS3DH_REG_TYPES_H

#include "std_includes.h"
#include "lis3dh_const.h"


/* 8.8 CTRL_REG1 (20h)
 */
typedef union{
    uint8_t byte;
    struct{
        uint8_t xen : 1;  /*bit 0  X-axis enable */
        uint8_t yen : 1;  /*bit 1  Y-axis enable.*/
        uint8_t zen : 1;  /*bit 2  Z-axis enable. */
        uint8_t lpen : 1; /*bit 3  Low-power mode enable  */
        uint8_t odr : 3; /*bit 7-4  Data rate selection  */
    };
}__attribute__((__packed__))Lis3dhRegisterCtrlReg1_t;

/* 8.9 CTRL_REG2 (21h)
 */
typedef union {
    uint8_t byte;
    struct {
        uint8_t hp_ia1 : 1;   /*bit 0   High-pass filter enabled for AOI function on interrupt 1 */
        uint8_t hp_ia2 : 1;   /*bit 1   High-pass filter enabled for AOI function on interrupt 2*/
        uint8_t hpclick : 1;  /*bit 2   High-pass filter enabled for CLICK function */
        uint8_t fds : 1;      /*bit 3   Filtered data selection. */
        uint8_t hpcf : 2;     /*bit 5-4 High-pass filter cutoff frequency selection  */
        uint8_t hpm : 2;      /*bit 7-6 High-pass filter enabled for AOI function on interrupt 1  */
    };
}Lis3dhRegisterCtrlReg2_t;


/*8.11 CTRL_REG4 (23h)
 */
typedef union {
    uint8_t byte;
    struct {
        uint8_t sim : 1;   /*bit 0   SPI serial interface mode selection */
        uint8_t st : 2;   /*bit 2 1   Self-test enable.*/
        uint8_t hr : 1;  /*bit 3   High-resolution output mode */
        uint8_t fs : 2;      /*bit 5 4  Full-scale selection */
        uint8_t ble : 1;     /*bit 6 Big/little endian data selection */
        uint8_t bdu : 1;      /*bit 7 Block data update  */
    };
}Lis3dhRegisterCtrlReg4_t;



/*8.12 CTRL_REG5 (24h)
 */
typedef union {
    uint8_t byte;
    struct {
        uint8_t d4d_int2 : 1;   /*bit 0   4D enable: 4D detection is enabled on INT2 pin when 6D */
        uint8_t lir_int2 : 1;   /*bit 1   Latch interrupt request on INT2_SRC (35h) register*/
        uint8_t d4d_int1 : 1;   /*bit 2    4D enable*/
        uint8_t lir_int1 : 1;   /*bit 3   Latch interrupt request on INT1_SRC register */
        uint8_t res : 2;    // bit 5-4 res
        uint8_t fifo_en : 1;   /*bit 6 FIFO enable */
        uint8_t boot : 1;      /*bit 7 Reboot memory content */
    };
}Lis3dhRegisterCtrlReg5_t;


/*8.19 FIFO_CTRL_REG (2Eh)
 */
typedef union {
    uint8_t byte;
    struct {
        uint8_t fth : 5;   /*bit 4-0 Default value: 00000 */
        uint8_t tr : 1;   /*bit 5   Trigger selection*/
        uint8_t fm : 2;   /*bit 7-6  FIFO mode selection*/
    };
}Lis3dhRegisterFifoCtrlReg_t;


typedef union {
    uint8_t byte;
    Lis3dhRegisterCtrlReg1_t CtrlReg1;
    Lis3dhRegisterCtrlReg2_t CtrlReg2;
    Lis3dhRegisterCtrlReg4_t CtrlReg4;
    Lis3dhRegisterCtrlReg5_t CtrlReg5;
    Lis3dhRegisterFifoCtrlReg_t FifoCtrlReg;
}Lis3dhRegUniversal_t;

#endif /* LIS3DH_REG_TYPES_H */
