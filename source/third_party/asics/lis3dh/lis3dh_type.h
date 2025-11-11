//**************************************************************************************************
// @Module  LIS3DH
//! \file   lis3dh_type.h
//! \brief  Data types for the ASCIC LIS3DH
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef LIS3DH_EHAL_TYPE_H
#define LIS3DH_EHAL_TYPE_H


//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get data types
#include "platform.h"

// Get data types
#include "lis3dh_register_types.h"

// Get data types
#include "lis3dh_miscellaneous.h"

// Get data types
#include "lis3dh_constants.h"

// Get vector types
#include "vector_type.h"

//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//! Data from ADC
typedef union {
    //! Raw data from ADC
    U8 buff[6];
    struct{
        //! ADC code for X acceleration
        U16_BIT X;
        //! ADC code for Y acceleration
        U16_BIT Y;
        //! ADC code for Z acceleration
        U16_BIT Z;
    }__attribute__((__packed__));
}__attribute__((__packed__))LIS3DH_ACCEL_REGISTERS;

//! LIS3DH acceleration info
typedef struct {
    //! The X value is expressed as two’s complement left-justified.
    U16_BIT X;
    //! The Y value is expressed as two’s complement left-justified.
    U16_BIT Y;
    //! The Z value is expressed as two’s complement left-justified.
    U16_BIT Z;
    //! Acceleration vector
    VECTOR_F AccelReal;
}LIS3DH_ACCELERATION;

//! LIS3DH register value
typedef struct {
    //! LIS3DH register address
    LIS3DH_REGISTER_ADDR address;
    //! register value
    LIS3DH_REGIS_UNIVERSAL Reg;
}LIS3DH_REGISTER_VAL;

#define LIS3DH_I2C_EHAL_COMMON_VARIABLE  \
    U8 chipAddr;                         \
    U8 i2cNum;                           \
    U8 sa0PinValue;

#define LIS3DH_SPI_EHAL_COMMON_VARIABLE  \
    U8 chipSelectPin;                    \
    U8 chipSelectPort;                   \
    U8 spiNum;

#define LIS3DH_PHY_EHAL_COMMON_VARIABLE  \
    LIS3DH_I2C_EHAL_COMMON_VARIABLE      \
    LIS3DH_SPI_EHAL_COMMON_VARIABLE

//! LIS3DH EHAL COMMON VARIABLE
#define LIS3DH_EHAL_COMMON_VARIABLE      \
    LIS3DH_PHY_EHAL_COMMON_VARIABLE      \
    LIS3DH_BIT_DEPTH resolutionBit;      \
    LIS3DH_INTERFACE interface;          \
    FLOAT32 precisionG;                  \
    U32 dataRateHz;                      \
    U8 measurementRangeG;                \
    U8 num;                              \
    U8 valid;

//! LIS3DH ROM Default config
typedef struct {
    LIS3DH_EHAL_COMMON_VARIABLE
    //! Pointer to the array of registers to be initialized
    LIS3DH_REGISTER_VAL* RegConfig;
    //! The size of the array of registers to be initialized
    U32 cfgRegCnt;
    //! Configuration name
    char *name;
}LIS3DH_CONFIGURATION;

//! LIS3DH RAM node
typedef struct {
    LIS3DH_EHAL_COMMON_VARIABLE
    //! init done flag
    U8 init;
    //! de init done flag
    U8 deInit;
    //! proc
    U8 proc;
    //! flag that the sample is not processed
    U8 unprocSample;
    //! current sensitivity mg/digit
    S8 sensitivity;
    //! Operating mode
    LIS3DH_OPERATION_MODE opMode;
    //! Acceleration data
    LIS3DH_ACCELERATION Acceleration;
    //! ADC data
    S16 adcCode[3];
}LIS3DH_HANDLE;


//! Operating mode info node
typedef struct {
    //! bit depth bits
    U8 resolutionBit;
    //! sensitivity mg/digit
    S8 sensitivity;
    //! full Scale
    LIS3DH_FULL_SCALE fullScale;
}LIS3DH_OP_MODE_INFO;

//! resolution info node
typedef struct {
    //! bit depth bits
    U8 resolutionBit;
    //! Mode name
    char* name;
    //! Operating mode
    LIS3DH_OPERATION_MODE opMode;
    //! Low-power mode CTRL_REG1[3]
    U8 lowPowerEnable;
    //! High-resolution output mode CTRL_REG4[3]
    U8 highResolutionEnable;
    U8 valid;
}LIS3DH_RESOLUTION_INFO;

//! ADC INFO
typedef struct {
    //! ADC Num
    U8 adcNum;
    //! ADC bitness
    U8 bitness;
    //! data adequacy flag
    U8 valid;
    //! ADC address Low
    LIS3DH_REGISTER_ADDR addressLow;
    //! ADC address Hi
    LIS3DH_REGISTER_ADDR addressHi;
}LIS3DH_ADC_INFO;

//! LIS3DH RATE INFO
typedef struct {
    //! data rate Hz
    U32 dataRateHz;
    //! data adequacy flag
    U8 valid;
    //! output data rate ctrl code
    LIS3DH_ODR odr;
}LIS3DH_RATE_INFO;

//! LIS3DH RANGE INFO
typedef struct {
    //! range
    U8 range;
    //! data adequacy flag
    U8 valid;
    //! measurement range
    LIS3DH_FULL_SCALE fullScale;
}LIS3DH_RANGE_INFO;



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************


#endif // #ifndef LIS3DH_EHAL_TYPE_H

//****************************************** end of file *******************************************
