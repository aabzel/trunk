//*****************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   nau8814_adc_cli.h
//! \brief  Interface of the MODULE module.
//!             CLI for ADC
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//******************************************************************************
#ifndef NAU8814_ADC_CLI_H
#define NAU8814_ADC_CLI_H

#include "std_includes.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef HAS_NAU8814
#error "+ HAS_NAU8814"
#endif

#ifndef HAS_NAU8814_CLI
#error "+ HAS_NAU8814_CLI"
#endif

//******************************************************************************
// Declarations of global (public) functions
//******************************************************************************

//! \brief NAU8814 Adc Diag Command
bool NAU8814_AdcDiagCommand(int32_t argc, char* argv[]);

//! \brief NAU8814 Listen Command
bool NAU8814_ListenCommand(int32_t argc, char* argv[]);


#define NAU8814_ADC_CLI                                                        \
    SHELL_CMD("Nau8814AdcDiag", "nadc",  NAU8814_AdcDiagCommand, "Nau8814AdcDiagEhal"),  \
    SHELL_CMD("Nau8814Listen", "nalc",  NAU8814_ListenCommand,  "Nau8814ListenEhal"),

#ifdef __cplusplus
}
#endif

#endif // NAU8814_ADC_CLI_H
//******************************* end of file *********************************
