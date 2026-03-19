//**************************************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   nau8814_diagnostic.h
//! \brief  Interface of the MODULE module.
//!
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************
#ifndef NAU8814_DIAGNOSTIC_H
#define NAU8814_DIAGNOSTIC_H

#include "nau8814_type.h"

#ifdef HAS_NAU8814_ADC_DIAG
#include "nau8814_adc_diagnostic.h"
#endif

#ifdef HAS_NAU8814_DAC_DIAG
#include "nau8814_dac_diagnostic.h"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif // HAS_LOG

#ifndef HAS_NAU8814
#error "+HAS_NAU8814"
#endif // HAS_NAU8814

#ifndef HAS_NAU8814_DIAG
#error "+HAS_NAU8814_DIAG"
#endif // HAS_DIAG_NAU8814

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif // HAS_DIAG

//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************

const char* Nau8814_ConfigurationToStr(const NAU8814_CONFIG* const Config);
const char* NAU8814_NodeToStr(const NAU8814_HANDLE* const Node);
const char* NAU8814_RegAddrToName(const NAU8814_REGISTER_ADDR addr);

STD_RESULT NAU8814_DiagnosticHighLevel(const U8 num);
STD_RESULT NAU8814_DiagnosticPll(const U8 num);
STD_RESULT NAU8814_DiagRegMap(const U8 num,
                              const char * const key_word1,
                              const char * const key_word2);

STD_RESULT NAU8814_DiagRegMapHidden(const U8 num);
STD_RESULT NAU8814_RegHazy(const U8 num);

#endif // NAU8814_DIAGNOSTIC_H
//******************************* end of file ******************************************************
