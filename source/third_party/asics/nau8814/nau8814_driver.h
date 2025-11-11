//**************************************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   nau8814_driver.h
//! \brief  NAU8814 24 bit Audio Codec ASIC Driver
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************
#ifndef NAU8814_DRIVER_H
#define NAU8814_DRIVER_H


//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "nau8814_cfg.h"
#include "nau8814_type.h"
#include "nau8814_configuration.h"

#ifdef NAU8814_ADC_IN_USE
#include "nau8814_adc_driver.h"
#endif

#ifdef NAU8814_DAC_IN_USE
#include "nau8814_dac_driver.h"
#endif

//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

//! None



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

//! None


//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

//! None



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

//! None



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

//! \brief NAU8814 get node
extern NAU8814_HANDLE* NAU8814_GetNode(const U8 num);

//! \brief NAU8814 de init
extern STD_RESULT NAU8814_DeInit(void);

//! \brief NAU8814 deinit one
extern STD_RESULT NAU8814_DeInitOne(const U8 num);

//! \brief NAU8814 get i2s role
extern STD_RESULT NAU8814_GetI2sRole(const U8 num,
                                     NAU8814_I2S_BUS_ROLE* const i2sRole);

//! \brief NAU8814 get master clock div
extern STD_RESULT NAU8814_GetMasterClockDiv(const U8 num,
                                            FLOAT32* const divider);

//! \brief NAU8814 get pll d
extern STD_RESULT NAU8814_GetPllD(const U8 num,
                                  U8* const pllD);

//! \brief NAU8814 get pll k
extern STD_RESULT NAU8814_GetPllK(const U8 num,
                                  U32* const pllK);

//! \brief NAU8814 get pll n
extern STD_RESULT NAU8814_GetPllN(const U8 num,
                                  U8* const pllN);

//! \brief NAU8814 init
extern STD_RESULT NAU8814_Init(void);

//! \brief NAU8814 init one
extern STD_RESULT NAU8814_InitOne(const U8 num);

//! \brief NAU8814 is connected
extern STD_RESULT NAU8814_IsConnected(const U8 num);

//! \brief NAU8814 is valid addr
extern STD_RESULT NAU8814_IsValidI2cRegisterAddr(const U8 registerAddress);

//! \brief NAU8814 proc
extern STD_RESULT NAU8814_Proc(void);

//! \brief NAU8814 read reg
extern STD_RESULT NAU8814_ReadReg(const U8 num,
                                  const NAU8814_REGISTER_ADDR registerAddr,
                                  U16* const regVal);

//! \brief NAU8814 Reset
extern STD_RESULT NAU8814_Reset(const U8 num);

//! \brief NAU8814 set i2s role
extern STD_RESULT NAU8814_SetI2sRole(const U8 num,
                                     const NAU8814_I2S_BUS_ROLE i2sRole);

//! \brief NAU8814 set pll k
extern STD_RESULT NAU8814_SetPllK(const U8 num,
                                  const U32 setPllK);

//! \brief NAU8814 set pll n
extern STD_RESULT NAU8814_SetPllN(const U8 num,
                                  const U8 pllN);

//! \brief NAU8814 write reg
extern STD_RESULT NAU8814_WriteReg(const U8 num,
                                   const NAU8814_REGISTER_ADDR registerAddr,
                                   const U16 regVal);

//! \brief NAU8814 write reg verify
extern STD_RESULT NAU8814_WriteRegVerify(const U8 num,
                                         const NAU8814_REGISTER_ADDR registerAddr,
                                         const U16 setWord);

//! \brief NAU8814 get reg cnt
extern U32 NAU8814_GetRegCnt(void);

//! \brief NAU8814 get config
extern const NAU8814_CONFIG* NAU8814_GetConfig(const U8 num);

//! \brief Nau8814 reg addr to info
extern const NAU8814_REGISTER_INFO* Nau8814_RegAddrToInfo(const NAU8814_REGISTER_ADDR addr);



#endif // #ifndef NAU8814_DRIVER_H
//******************************* end of file ******************************************************
