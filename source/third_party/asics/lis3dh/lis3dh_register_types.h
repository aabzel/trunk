//**************************************************************************************************
// @Module  LIS3DH
//! \file   lis3dh_register_types.h
//! \brief  Interface of the LIS3DH module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef LIS3DH_REGIS_TYPES_H
#define LIS3DH_REGIS_TYPES_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************


// Get platform types
#include "platform.h"



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//! CTRL_REG1 (20h)
typedef union{
    //! raw byte of register value
    U8 byte;
    struct{
        //!  bit 0  X-axis enable
        U8 xen : 1;
        //!  bit 1  Y-axis enable.
        U8 yen : 1;
        //! bit 2  Z-axis enable.
        U8 zen : 1;
        //! bit 3  Low-power mode enable
        U8 lpen : 1;
        //! bit 7-4  Data rate selection
        U8 odr : 3;
    };
}__attribute__((__packed__))LIS3DH_REGIS_CTRL_REG1;

//! CTRL_REG2 (21h)
typedef union {
    //! raw byte of register value
    U8 byte;
    struct {
        //! bit 0   High-pass filter enabled for AOI function on interrupt 1
        U8 hp_ia1 : 1;
        //! bit 1   High-pass filter enabled for AOI function on interrupt 2
        U8 hp_ia2 : 1;
        //! bit 2   High-pass filter enabled for CLICK function
        U8 hpclick : 1;
        //! bit 3   Filtered data selection.
        U8 fds : 1;
        //! bit 5-4 High-pass filter cutoff frequency selection
        U8 hpcf : 2;
        //! bit 7-6 High-pass filter enabled for AOI function on interrupt 1
        U8 hpm : 2;
    };
}LIS3DH_REGIS_CTRL_REG2;

//! CTRL_REG4 (23h)
typedef union {
    //! raw byte of register value
    U8 byte;
    struct {
        //! bit 0   SPI serial interface mode selection
        U8 sim : 1;
        //! bit 2 1   Self-test enable.
        U8 st : 2;
        //! bit 3   High-resolution output mode
        U8 hr : 1;
        //! bit 5 4  Full-scale selection
        U8 fs : 2;
        //! bit 6 Big/little endian data selection
        U8 ble : 1;
        //! bit 7 Block data update
        U8 bdu : 1;
    };
}LIS3DH_REGIS_CTRL_REG4;

//! CTRL_REG5 (24h)
typedef union {
    //! raw byte of register value
    U8 byte;
    struct {
        //! bit 0   4D enable: 4D detection is enabled on INT2 pin when 6D
        U8 d4d_int2 : 1;
        //! bit 1   Latch interrupt request on INT2_SRC (35h) register
        U8 lir_int2 : 1;
        //! bit 2    4D enable
        U8 d4d_int1 : 1;
        //! bit 3   Latch interrupt request on INT1_SRC register
        U8 lir_int1 : 1;
        // bit 5-4 res
        U8 res : 2;
        //! bit 6 FIFO enable
        U8 fifo_en : 1;
        //! bit 7 Reboot memory content
        U8 boot : 1;
    };
}LIS3DH_REGIS_CTRL_REG5;

//! FIFO_CTRL_REG (2Eh)
typedef union {
    //! raw byte of register value
    U8 byte;
    struct {
        //! bit 4-0 Default value: 00000
        U8 fth : 5;
        //! bit 5   Trigger selection
        U8 tr : 1;
        //! bit 7-6  FIFO mode selection
        U8 fm : 2;
    };
}LIS3DH_REGIS_FIFO_CTRL;

//! TEMP_CFG_REG (1Fh)
typedef union {
    //! raw byte of register value
    U8 byte;
    struct {
        //! bit 5-0 reserved
        U8 res : 6;
        //! bit 6   Temperature sensor (T) enable (0: T disabled; 1: T enabled)
        U8 temp_en : 1;
        //! bit 7   ADC enable (0: ADC disabled; 1: ADC enabled)
        U8 adc_en : 1;
    };
}LIS3DH_REGIS_TEMP_CFG;

//! LIS3DH Universal register
typedef union {
    //! raw byte of register value
    U8 byte;
    //! CTRL_REG1 (20h)
    LIS3DH_REGIS_CTRL_REG1 CtrlReg1;
    //! CTRL_REG2 (21h)
    LIS3DH_REGIS_CTRL_REG2 CtrlReg2;
    //! CTRL_REG4 (23h)
    LIS3DH_REGIS_CTRL_REG4 CtrlReg4;
    //! CTRL_REG5 (24h)
    LIS3DH_REGIS_CTRL_REG5 CtrlReg5;
    //! TEMP_CFG_REG (1Fh)
    LIS3DH_REGIS_TEMP_CFG TempCfg;
    //! FIFO_CTRL_REG (2Eh)
    LIS3DH_REGIS_FIFO_CTRL FifoCtrlReg;
}LIS3DH_REGIS_UNIVERSAL;



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************



#endif // #ifndef LIS3DH_REGIS_TYPES_H

//****************************************** end of file *******************************************
