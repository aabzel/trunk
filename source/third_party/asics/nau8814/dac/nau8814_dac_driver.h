//**************************************************************************************************
// @Module  NAU8814 DAC Driver
//! \file   nau8814_dac_driver.h
//! \brief  Interface of the MODULE module.
//!             [text]
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************

#ifndef NAU8814_DAC_H
#define NAU8814_DAC_H


//**************************************************************************************************
// Project Includes
//**************************************************************************************************

#ifdef I2S_IN_USE
#include "i2s_drv_types.h"
#endif
#include "nau8814_type.h"

#ifndef NAU8814_DAC_IN_USE
#warning "+NAU8814_DAC_IN_USE"
#endif

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

//! \brief NAU8814 Ctrl Play
extern STD_RESULT NAU8814_DAC_CtrlPlay(const U8 num,
                                       const U8 onOff);

//! \brief NAU8814 DAC De Init
extern STD_RESULT NAU8814_DAC_DeInit(const U8 num);

//! \brief NAU8814 Get Dac Gain
extern STD_RESULT NAU8814_DAC_GetDacGain(const U8 num,
                                         NAU8814_FRACTIONAL_GAIN* const dacGain);

//! \brief NAU8814 Get Spk Gain
extern STD_RESULT NAU8814_DAC_GetSpkGain(const U8 num,
                                         NAU8814_GAIN* const spkGain);

//! \brief NAU8814 Init Dac
extern STD_RESULT NAU8814_DAC_Init(const U8 num);

//! \brief NAU8814 Mute
extern STD_RESULT NAU8814_DAC_Mute(const U8 num);

//! \brief NAU8814 Play 1kHz
extern STD_RESULT NAU8814_DAC_Play1kHz(const U8 num,
                                       const NAU8814_SAMPLE_TYPE amplitude,
                                       const U32 duratinMs);

//! \brief NAU8814 Play 1kHz Continuous
extern STD_RESULT NAU8814_DAC_Play1kHzContinuous(const U8 num,
                                                 const NAU8814_SAMPLE_TYPE amplitude);

//! \brief NAU8814 Play Indefinite
extern STD_RESULT NAU8814_DAC_PlayIndefinite(const U8 num,
                                             const U32 frequencyHz,
                                             const NAU8814_SAMPLE_TYPE amplitude);

//! \brief NAU8814 Play Tone
extern STD_RESULT NAU8814_DAC_PlayTone(const U8 num,
                                       const U32 frequencyHz,
                                       const NAU8814_SAMPLE_TYPE amplitude,
                                       const U64 durationMs);

//! \brief NAU8814 Play Tone 1kHz
extern STD_RESULT NAU8814_DAC_PlayTone1kHz(const U8 num,
                                           const NAU8814_SAMPLE_TYPE amplitude,
                                           const U32 durationMs);

//! \brief NAU8814 Set Dac Gain
extern STD_RESULT NAU8814_DAC_SetDacGain(const U8 num,
                                         const NAU8814_FRACTIONAL_GAIN dacGain);

//! \brief NAU8814 Set Spk Gain
extern STD_RESULT NAU8814_DAC_SetSpkGain(const U8 num,
                                         const NAU8814_GAIN speakerGain);

//! \brief NAU8814 Dac Gain Code To Gain
extern NAU8814_FRACTIONAL_GAIN NAU8814_DAC_DacGainCodeToGain(const U16 code);



#endif // #ifndef NAU8814_DAC_H
//******************************* end of file ******************************************************
