//*****************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   nau8814_adc_diagnostic.h
//! \brief  Interface of the MODULE module.
//!             [text]
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//*****************************************************************************
#ifndef NAU8814_ADC_DIAG_H
#define NAU8814_ADC_DIAG_H


#include "general_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif // HAS_LOG

#ifndef HAS_NAU8814
#error "+HAS_NAU8814"
#endif // HAS_NAU8814

#ifndef HAS_NAU8814_DIAG
#error "+HAS_NAU8814_DIAG"
#endif // HAS_DIAG_NAU8814

#ifndef HAS_NAU8814_ADC_DIAG
#error "+HAS_NAU8814_ADC_DIAG"
#endif // HAS_NAU8814_ADC_DIAG

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif // HAS_DIAG

//******************************************************************************
// Declarations of global (public) functions
//******************************************************************************

//! \brief [Description...]
STD_RESULT NAU8814_AdcDiag(const U8 num);


#endif // NAU8814_ADC_DIAG_H
//******************************* end of file *********************************
