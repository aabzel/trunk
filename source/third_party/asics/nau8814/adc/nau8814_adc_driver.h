//**************************************************************************************************
// @Module  NAU8814 ADC Driver
//! \file   nau8814_adc_driver.h
//! \brief  Interface of the NAU8814 ADC module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef NAU8814_ADC_H
#define NAU8814_ADC_H



//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#include "nau8814_constants.h"
#include "nau8814_type.h"



//**************************************************************************************************
// Declarations of global (public) data types
//**************************************************************************************************

// None.



//**************************************************************************************************
// Definitions of global (public) constants
//**************************************************************************************************

// None.



//**************************************************************************************************
// Declarations of global (public) variables
//**************************************************************************************************

// None.



//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

//! \brief NAU8814 Ctrl Adc
extern STD_RESULT NAU8814_ADC_Ctrl(const U8 num,
                                   const U8 adcOn);

//! \brief NAU8814 Ctrl Record
extern STD_RESULT NAU8814_ADC_CtrlRecord(const U8 num,
                                         const U8 onOff);

//! \brief NAU8814 De Init Adc
extern STD_RESULT NAU8814_ADC_DeInit(const U8 num);

//! \brief NAU8814 Get Adc
extern STD_RESULT NAU8814_ADC_GetAdc(const U8 num,
                                     U8* const adcOn);

//! \brief NAU8814 Get Aux Gain
extern STD_RESULT NAU8814_ADC_GetAuxGain(const U8 num,
                                         NAU8814_GAIN* const auxGain);

//! \brief NAU8814 get pga gain
extern STD_RESULT NAU8814_ADC_GetPgaGain(const U8 num,
                                         FLOAT32* const pgaGain);

//! \brief NAU8814 set pga gain
extern STD_RESULT NAU8814_ADC_SetPgaGain(const U8 num,
                                         const FLOAT32 pgaGain);

//! \brief NAU8814 get pmic gain
extern STD_RESULT NAU8814_ADC_GetPmicGain(const U8 num,
                                          NAU8814_GAIN* const pMicGain);

//! \brief NAU8814 Init ADC
extern STD_RESULT NAU8814_ADC_Init(const U8 num);

//! \brief NAU8814 listen
extern STD_RESULT NAU8814_ADC_Listen(const U8 num,
                                     const U32 desDurationMs);

//! \brief NAU8814 set aux gain
extern STD_RESULT NAU8814_ADC_SetAuxGain(const U8 num,
                                         const NAU8814_GAIN auxGain);

//! \brief NAU8814 set pmic gain
extern STD_RESULT NAU8814_ADC_SetPmicGain(const U8 num,
                                          const NAU8814_GAIN pMicGain);



#endif // #ifndef  NAU8814_ADC_H
//***********************8888888888888******** end of file ****************88888888*****************
