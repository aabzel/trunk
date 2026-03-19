//**************************************************************************************************
// @Module  PYRAMID_ACCEL_CALIBRATION
//! \file   pyramid_accel_calibration_configuration.h
//! \brief  Interface of the PYRAMID_ACCEL_CALIBRATION module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 11.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef PYRAMID_ACCEL_CALIB_CONFIG_H
#define PYRAMID_ACCEL_CALIB_CONFIG_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get platform data types
#include "platform.h"

// Get pyramid accel calibration data types
#include "pyramid_accel_calibration_types.h"

//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

//! PYRAMID ACCEL CALIB ROM Config
extern const PYRAMID_ACCEL_CALIB_CONFIG PYRAMID_ACCEL_CALIB_Config[];

//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

//! PYRAMID ACCEL CALIB RAM Instances
extern PYRAMID_ACCEL_CALIB_HANDLE PYRAMID_ACCEL_CALIB_Instance[];

//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

//! \brief Get the number of calibration data in an assembly
U32 PYRAMID_ACCEL_CALIB_GetCnt(void);



#endif // #ifndef PYRAMID_ACCEL_CALIB_CONFIG_H

//****************************************** end of file *******************************************
