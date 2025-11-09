//**************************************************************************************************
// @Module  ACCELEROMETER
//! \file   accelerometer_type.h
//! \brief  data types of the ACCELEROMETER module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef ACCEL_EHAL_TYPES_H
#define ACCEL_EHAL_TYPES_H

//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// platform types
#include "platform.h"

// accelerometer constants
#include "accelerometer_constants.h"

// vector types
#include "vector_type.h"

//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

#define ACCEL_EHAL_CALIBRATION_DATA         \
    VECTOR_F scale;                         \
    VECTOR_F offset;

typedef struct {
    ACCEL_EHAL_CALIBRATION_DATA
} ACCEL_CALIB_DATA;

#define ACCEL_EHAL_COMMON_VARIABLES      \
    ACCEL_EHAL_CALIBRATION_DATA          \
    ACCEL_PHY accelPhy;                  \
    FLOAT32 precision;                   \
    U8 accelNum;                         \
    U8 valid;                            \
    U8 num;                              \
    char* name;

typedef struct {
    ACCEL_EHAL_COMMON_VARIABLES
} ACCEL_CONFIG;

typedef struct {
    ACCEL_EHAL_COMMON_VARIABLES
    //! real calibrated acceleration vector in g
    VECTOR_F Acceleration;
    //! raw acceleration ADC code
    VECTOR_S16 adcCode;
    //! init flag
    U8 init;
    //! deInit flag
    U8 deInit;
} ACCEL_HANDLE;

//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************



#endif // #ifndefACCEL_EHAL_TYPES_H

//****************************************** end of file *******************************************
