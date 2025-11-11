//**************************************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   nau8814_type.h
//! \brief  NAU8814 ASIC Driver types
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef NAU8814_ASIC_TYPES_H
#define NAU8814_ASIC_TYPES_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "platform.h"
#include "general_types.h"
#include "nau8814_constants.h"
#include "nau8814_register_types.h"



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//! Integer gain type
typedef S8 NAU8814_GAIN;

//! Sample type
typedef S16 NAU8814_SAMPLE_TYPE;

//! Fractional gain type
typedef FLOAT32 NAU8814_FRACTIONAL_GAIN;

//! I2C byte write sequence
typedef union {
    //! I2C frame as raw byte array
    U8  buff[2];
    //! I2C frame as one word
    U16 word;
    //! I2C frame structure
    struct
    {
        //! register raw value
        U16 regValue : 9;
        //! register address
        U16 registerAddr : 7;
    };
} NAU8814_WRITE_FRAME;

//! NAU8814 universal register value
typedef struct
{
    //! register address
    NAU8814_REGISTER_ADDR      addr;
    //! register universal value
    NAU8814_REGISTER_UNIVERSAL Reg;
} NAU8814_REGISTER_VAL;

//! NAU8814 register info
typedef struct
{
    //! register address
    NAU8814_REGISTER_ADDR addr;
    //! register name
    char*                 name;
    //! access rights to this register
    NAU8814_STORAGE_ACCESS access;
    //! flag that the data is valid
    U8                    valid;
} NAU8814_REGISTER_INFO;

//! NAU8814 ASIC input gains
#define NAU8814_ASIC_IN_GAINS \
    NAU8814_GAIN auxGain;           \
    NAU8814_GAIN pMicGain;

//! NAU8814_ASIC out gains
#define NAU8814_ASIC_OUT_GAINS \
    NAU8814_GAIN  spkGain;           \
    NAU8814_FRACTIONAL_GAIN dacGain;

//! NAU8814 ASIC gains
#define NAU8814_ASIC_GAINS \
    NAU8814_ASIC_IN_GAINS  \
    NAU8814_ASIC_OUT_GAINS \
    FLOAT32 pgaGain;

//! NAU8814 COMMON VARIABLE for RAM and ROM nodes
#define NAU8814_DRV_COMMON_VARIABLE  \
    NAU8814_ASIC_GAINS               \
    NAU8814_I2S_BUS_ROLE i2sRole;    \
    U32                  pllK;       \
    FLOAT32              mclkFreqHz; \
    U8                   adcOn;      \
    U8                   dacOn;      \
    U8                   valid;      \
    U8                   num;        \
    U8                   chipAddr;   \
    U8                   pllN;       \
    U8                   pllD;       \
    U8                   i2cNum;     \
    U8                   i2sNum;     \
    U8                   ddsNum;

//! NAU8814 ROM config
typedef struct
{
    //! COMMON VARIABLES
    NAU8814_DRV_COMMON_VARIABLE
    //! Pointer to array of registers
    NAU8814_REGISTER_VAL* RegVals;
    //! number of registers for initialization
    U32                   regValCnt;
    //! ASIC configuration name
    char*                 name;
} NAU8814_CONFIG;

//! NAU8814 RAM Node
typedef struct
{
    NAU8814_DRV_COMMON_VARIABLE
    //! play off time stamp ms
    U64           playOffTimeStampMs;
    //! rec off time stamp ms
    U64           recOffTimeStampMs;
    //! NAU8814 state
    NAU8814_STATE state;
    //! init done
    U8            init;
    //! de init done
    U8            deInit;
} NAU8814_HANDLE;

//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

//! None



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

//! None



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

//! None



#endif // #ifndef NAU8814_ASIC_TYPES_H

//******************************* end of file ******************************************************
