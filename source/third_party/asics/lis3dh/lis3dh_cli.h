#ifndef LIS3DH_CLI_H
#define LIS3DH_CLI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "std_includes.h"
#include "diag_dep.h"
#include "platform.h"


#ifndef HAS_LIS3DH_EHAL
#error "+ HAS_LIS3DH"
#endif

#ifndef HAS_LIS3DH_CLI
#error "+ HAS_LIS3DH_CLI"
#endif

bool LIS3DH_ReadAccelerationCommand(int32_t argc, char* argv[]);
bool LIS3DH_AdcCommand(int32_t argc, char* argv[]);
bool LIS3DH_DiagHiLevelCommand(int32_t argc, char* argv[]);
bool LIS3DH_DiagLowLevelCommand(int32_t argc, char* argv[]);
bool LIS3DH_I2C_PingCommand(int32_t argc, char* argv[]);
bool LIS3DH_InitCommand(int32_t argc, char* argv[]);
bool LIS3DH_WriteRegisterCommand(int32_t argc, char* argv[]);
bool LIS3DH_ReadRegisterCommand(int32_t argc, char* argv[]);
bool LIS3DH_RegMapCommand(int32_t argc, char* argv[]);

#define LIS3DH_CLI                                                                                 \
    SHELL_CMD("LIS3DHDiag_hi_lev", "elid", LIS3DH_DiagHiLevelCommand, "LIS3DHDiagHiLevel"),        \
    SHELL_CMD("LIS3DHAdc", "elic", LIS3DH_AdcCommand, "LIS3DHAdcRead"),                            \
    SHELL_CMD("LIS3DHReadAcceleration", "elia", LIS3DH_ReadAccelerationCommand, "LIS3DHAccelRead"),\
    SHELL_CMD("LIS3DHread", "elirr", LIS3DH_ReadRegisterCommand, "LIS3DHRegRead"),                 \
    SHELL_CMD("LIS3DHping", "elip", LIS3DH_I2C_PingCommand, "LIS3DHPing"),                          \
    SHELL_CMD("LIS3DHmap", "elirm", LIS3DH_RegMapCommand, "LIS3DHRegMap"),                         \
    SHELL_CMD("LIS3DHwrite", "eliw", LIS3DH_WriteRegisterCommand, "LIS3DHRegWrite"),               \
    SHELL_CMD("LIS3DHDiag_ll", "eeadl", LIS3DH_DiagLowLevelCommand, "LIS3DHDiagLowLevel"),         \
    SHELL_CMD("LIS3DHInit", "elii", LIS3DH_InitCommand, "LIS3DHInit"),


#ifdef __cplusplus
}
#endif

#endif /* LIS3DH_CLI_H */
