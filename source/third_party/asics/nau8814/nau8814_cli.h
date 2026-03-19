//**************************************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   NAU8814_cli.h
//! \brief  Interface of the MODULE module.
//!             CLI for NAU8814 ASIC Driver
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************
#ifndef NAU8814_CLI_H
#define NAU8814_CLI_H

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

#ifdef HAS_NAU8814_ADC_CLI
#include "NAU8814_adc_cli.h"
#else
#define NAU8814_ADC_CLI
#endif

#ifdef HAS_NAU8814_DAC_CLI
#include "NAU8814_dac_cli.h"
#else
#define NAU8814_DAC_CLI
#endif

//**************************************************************************************************
// Declarations of global (public) functions
//**************************************************************************************************


bool NAU8814_DeInitCommand(int32_t argc, char* argv[]);
bool NAU8814_I2cPingCommand(int32_t argc, char* argv[]);
bool NAU8814_InitCommand(int32_t argc, char* argv[]);
bool NAU8814_ReadRegCommand(int32_t argc, char* argv[]);
bool NAU8814_RegHazyCommand(int32_t argc, char* argv[]);
bool NAU8814_RegMapCommand(int32_t argc, char* argv[]);
bool NAU8814_ResetCommand(int32_t argc, char* argv[]);
bool NAU8814_WriteRegCommand(int32_t argc, char* argv[]);
bool NAU8814_reg_map_hidden_command(int32_t argc, char* argv[]);
bool NAU8814_DiagnosticHlCommand(int32_t argc, char* argv[]);

#define NAU8814_CLI                                                                                \
    SHELL_CMD("Nau8814_ping", "napc", NAU8814_I2cPingCommand, "Nau8814PingEhal"),                  \
    SHELL_CMD("Nau8814_map", "nrmc", NAU8814_RegMapCommand, "Nau8814RegMapEhal"),                  \
    SHELL_CMD("Nau8814_hazy", "nrhc", NAU8814_RegHazyCommand, "Nau8814RegHazyEhal"),               \
    SHELL_CMD("Nau8814_read", "nrrc", NAU8814_ReadRegCommand, "Nau8814RegReadEhal"),               \
    SHELL_CMD("Nau8814_write",    "nrwc", NAU8814_WriteRegCommand,   "Nau8814RegWriteEhal"),       \
    SHELL_CMD("NAU8814_diagnostic_hi_lev",   "ndhc",    NAU8814_DiagnosticHlCommand,  "Nau8814DiagHiLevelEhal"),            \
    SHELL_CMD("Nau8814_init", "nic", NAU8814_InitCommand, "Nau8814InitEhal"),  \
    SHELL_CMD("Nau8814_deinit", "ndic", NAU8814_DeInitCommand, "Nau8814DeInitEhal"),  \
    SHELL_CMD("Nau8814_reset", "ntc", NAU8814_ResetCommand, "Nau8814ResetEhal"), \
    NAU8814_ADC_CLI \
    NAU8814_DAC_CLI

#ifdef __cplusplus
}
#endif

#endif // NAU8814_CLI_H 
//******************************* end of file ******************************************************
