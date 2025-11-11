//**************************************************************************************************
// @Module  LIS3DH
//! \file   lis3dh_driver.h
//! \brief  Interface of the LIS3DH module.
//!             This is a driver for the ASIC LIS3DH.
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 18.11.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef LIS3DH_EHAL_DRIVER_H
#define LIS3DH_EHAL_DRIVER_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

// platform
#include "platform.h"

// Get data types
#include "general_types.h"

// Get configuration of the program module
#include "lis3dh_configuration.h"

// Get lis3dh data types
#include "lis3dh_type.h"

//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

//! LIS3DH Operation Modes Info Table
//extern const LIS3DH_OP_MODE_INFO LIS3DH_OperationModeInfo[];



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

//! \brief LIS3DH init all instances
extern STD_RESULT LIS3DH_Init(void);

//! \brief LIS3DH init deall instances
extern STD_RESULT LIS3DH_DeInit(void);

//! \brief LIS3DH init one instance
extern STD_RESULT LIS3DH_InitOne(const U8 num);

//! \brief LIS3DH deinit one instance
extern STD_RESULT LIS3DH_DeInitOne(const U8 num);

//! \brief LIS3DH periodicaly invoke function
extern STD_RESULT LIS3DH_Process(void);

//! \brief LIS3DH proc one instance
extern STD_RESULT LIS3DH_ProcessOne(const U8 num);

//! \brief LIS3DH get node instance
extern LIS3DH_HANDLE* LIS3DH_GetNode(const U8 num);

//! \brief LIS3DH get sensitivity
extern S8 LIS3DH_GetSensitivity(const U8 num);

//! \brief LIS3DH get operation mode cnt
extern U32 LIS3DH_GetOperationModeCnt(void);

//! \brief LIS3DH Convert ADC values To Real accel sample
extern STD_RESULT LIS3DH_AdcToReal(LIS3DH_ACCELERATION* const Acceleration,
                                   const S8 mgPerDigit);

//! \brief LIS3DH adc to real low level
extern STD_RESULT LIS3DH_AdcToRealLowLevel(LIS3DH_HANDLE* const Node);

//! \brief LIS3DH Read ADC Code
extern STD_RESULT LIS3DH_ReadAdcCode(const U8 num,
                                     const U8 adcNum,
                                     U16 * const adcCode);

//! \brief LIS3DH get acceleration fast low level
extern STD_RESULT LIS3DH_GetAccelerationFastLowLevel(LIS3DH_HANDLE* const Node,
                                                     LIS3DH_ACCELERATION* const Acceleration);

//! \brief LIS3DH get acceleration slow low level
extern STD_RESULT LIS3DH_GetAccelerationSlowLowLevel(LIS3DH_HANDLE* const Node,
                                                     LIS3DH_ACCELERATION* const Acceleration);

//! \brief LIS3DH get measurement resolution in bit
extern STD_RESULT LIS3DH_GetResolution(const U8 num,
                                       LIS3DH_BIT_DEPTH* const resolutionBit);

//! \brief LIS3DH get data rate in hz
extern STD_RESULT LIS3DH_GetDataRateHz(const U8 num,
                                       U32* const dataRateHz);

//! \brief LIS3DH get operation mode
extern STD_RESULT LIS3DH_GetOperationMode(const U8 num,
                                          LIS3DH_OPERATION_MODE* const opMode);

//! \brief LIS3DH get measurement range in g
extern STD_RESULT LIS3DH_GetRange(const U8 num,
                                  U8* const range);

//! \brief LIS3DH get precision in g
extern FLOAT32 LIS3DH_GetPrecision(const U8 num);

//! \brief LIS3DH get config
extern const LIS3DH_CONFIGURATION* LIS3DH_GetConfig(const U8 num);

//! \brief LIS3DH get reg Quantity
extern U32 LIS3DH_GetRegCnt(void);

//! \brief LIS3DH get operation mode low level
extern STD_RESULT LIS3DH_GetOperationModeLowLevel(LIS3DH_HANDLE* const Node,
                                                  LIS3DH_OPERATION_MODE* const opMode);

//! \brief LIS3DH set data rate in hz
extern STD_RESULT LIS3DH_SetDataRateHz(const U8 num,
                                       const U32 dataRateHz);

//! \brief LIS3DH set measurement range in g
extern STD_RESULT LIS3DH_SetRangeInG(const U8 num,
                                     const U8 rangeG);

//! \brief LIS3DH set measurement resolution in bit
extern STD_RESULT LIS3DH_SetResolution(const U8 num,
                                       const LIS3DH_BIT_DEPTH resolutionBit);

//! \brief LIS3DH is connected
extern STD_RESULT LIS3DH_IsConnected(const U8 num);

//! \brief convert LIS3DH reg addr to info node
extern const ASIC_REG_INFO* LIS3DH_RegAddrToInfo(const LIS3DH_REGISTER_ADDR regAddr);

//! \brief LIS3DH is valid register addr
extern STD_RESULT LIS3DH_IsValidAddr(const U8 regAddr);

//! \brief LIS3DH proc link
extern STD_RESULT LIS3DH_ProcessLink(void);

//! \brief LIS3DH read acceleration
extern STD_RESULT LIS3DH_ReadAcceleration(const U32 num,
                                          VECTOR_F* const AccelReal);

//! \brief LIS3DH read register
extern STD_RESULT LIS3DH_ReadRegister(const U8 num,
                                      const LIS3DH_REGISTER_ADDR regAddr,
                                      U8* const regVal);

//! \brief LIS3DH read register low level
extern STD_RESULT LIS3DH_ReadRegisterLowLevel(LIS3DH_HANDLE* const Node,
                                              const LIS3DH_REGISTER_ADDR regAddr,
                                              U8* const rxbyte);

//! \brief LIS3DH read ADC code
extern STD_RESULT LIS3DH_ReadCode(const U8 num,
                                  VECTOR_S16* const accelCode);

//! \brief LIS3DH write register
extern STD_RESULT LIS3DH_WriteRegister(const U8 num,
                                       const LIS3DH_REGISTER_ADDR regAddr,
                                       const U8 regVal);

//! \brief LIS3DH write register low level
extern STD_RESULT LIS3DH_WriteRegisterLowLevel(LIS3DH_HANDLE* const Node,
                                               const LIS3DH_REGISTER_ADDR regAddr,
                                               const U8 byte);

//! \brief LIS3DH write register verify
extern STD_RESULT LIS3DH_WriteRegisterVerify(const U8 num,
                                             const LIS3DH_REGISTER_ADDR regAddr,
                                             const U8 value);

//! \brief get LIS3DH resolution info by operation mode
extern
const LIS3DH_RESOLUTION_INFO* LIS3DH_ResolitionInfoByOpMode(const LIS3DH_OPERATION_MODE opMode);

//! \brief get LIS3DH resolution info by operation mode
extern const
LIS3DH_RESOLUTION_INFO* LIS3DH_GetResolutionInfoByOpMode(const LIS3DH_OPERATION_MODE opMode);

#endif // #ifndef LIS3DH_EHAL_DRIVER_H

//****************************************** end of file *******************************************
