//**************************************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   nau8814_dac_cli.h
//! \brief  Interface of the MODULE module.
//!             [text]
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************
#ifndef NAU8814_DAC_CLI_H
#define NAU8814_DAC_CLI_H

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

//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************


bool NAU8814_DAC_GainCommand(int32_t argc, char* argv[]);
bool NAU8814_PlayInfiniteCommand(int32_t argc, char* argv[]);
bool NAU8814_PlayTone1kHzCommand(int32_t argc, char* argv[]);
bool NAU8814_PlayToneCommand(int32_t argc, char* argv[]);

#define NAU8814_DAC_CLI                                                \
    SHELL_CMD("NAU8814_Play_1kHz",    "noc", NAU8814_PlayTone1kHzCommand, "Nau8814Play1kHzEhal"),   \
    SHELL_CMD("NAU8814_play", "npc", NAU8814_PlayToneCommand, "Nau8814PlayEhal"),     \
    SHELL_CMD("NAU8814_dac_Gain", "ngc", NAU8814_DAC_GainCommand, "Nau8814DacGainEhal"),             \
    SHELL_CMD("NAU8814_play_infinite", "npic", NAU8814_PlayInfiniteCommand, "Nau8814PlayInfiniteEhal"),

#ifdef __cplusplus
}
#endif

#endif // NAU8814_DAC_CLI_H 
//******************************* end of file ******************************************************
