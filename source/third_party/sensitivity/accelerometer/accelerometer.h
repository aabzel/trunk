//**************************************************************************************************
// @Module  Accelerometer
//! \file   accelerometer.h
//! \brief  Interface of the Accelerometer module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef ACCEL_H
#define ACCEL_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// Get generic definitions
#include "general.h"

// Get configuration of the program module
#include "accelerometer_cfg.h"

// Get accelerometer types
#include "accelerometer_type.h"



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

// None



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

// None



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

// None



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

//! \brief Accelerometers initialization
extern STD_RESULT ACCEL_Init(void);

//! \brief Accelerometers de-initialization
extern STD_RESULT ACCEL_DeInit(void);

//! \brief Accelerometers processing
extern STD_RESULT ACCEL_Process(void);

//! \brief get accelerometer RAM node
extern ACCEL_HANDLE* ACCEL_GetNode(const U8 num);

//! \brief get accelerometer ROM node
extern const ACCEL_CONFIG* ACCEL_GetConfig(const U8 num);

//! \brief read acceleration in g
extern STD_RESULT ACCEL_Read(const U8 num,
                             VECTOR_F* const accelReal);

//! \brief get accelerometer integer code
extern STD_RESULT ACCEL_ReadCode(const U8 num,
                                 VECTOR_S16* const accelCode);

//! \brief set axis offset by offset vector
extern STD_RESULT ACCEL_SetAxisOffset(const U8 num,
                                      const VECTOR_F* const AxisOffset);

//! \brief set axis scale by scale vector
extern STD_RESULT ACCEL_SetAxisScale(const U8 num,
                                     const VECTOR_F* const axisScale);

//! \brief deploy calibration calculated by pyramid algorithm
extern STD_RESULT ACCEL_DeployPyramidCalib(const U8 num,
                                           const U8 calibNum);

//! \brief Save calibration data
STD_RESULT ACCEL_SaveCalibData(const U8 accelNum,
                               const ACCEL_CALIB_DATA *const Calibration);

#endif // #ifndef ACCEL_H

//****************************************** end of file *******************************************
