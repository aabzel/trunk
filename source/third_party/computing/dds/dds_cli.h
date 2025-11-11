#ifndef DDS_CLI_H
#define DDS_CLI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "std_includes.h"

#ifndef DDS_IN_USE
#error "+ DDS_IN_USE"
#endif /*DDS_IN_USE*/

#ifndef DDS_CLI_IN_USE
#error "+ DDS_CLI_IN_USE"
#endif /*DDS_CLI_IN_USE*/

bool DDS_CLI_Amplitude(int32_t argc, char* argv[]);
bool DDS_CLI_Diagnostic(int32_t argc, char* argv[]);
bool DDS_CLI_FramePerSec(int32_t argc, char* argv[]);
bool DDS_CLI_Init(int32_t argc, char* argv[]);
bool DDS_CLI_Pattern(int32_t argc, char* argv[]);
bool DDS_CLI_Play(int32_t argc, char* argv[]);
bool DDS_CLI_PrintTrack(int32_t argc, char* argv[]);
bool DDS_CLI_SetArray(int32_t argc, char* argv[]);
bool DDS_CLI_SetFence(int32_t argc, char* argv[]);
bool DDS_CLI_SetPwm(int32_t argc, char* argv[]);
bool DDS_CLI_SetSaw(int32_t argc, char* argv[]);
bool DDS_CLI_SetSin(int32_t argc, char* argv[]);


#define DDS_CLI                                                                 \
    SHELL_CMD("DDS_Init", "d2si", DDS_CLI_Init, "DDS_Init"),                    \
    SHELL_CMD("DDS_Amp", "d2sa", DDS_CLI_Amplitude, "DDS_Amplitude"),           \
    SHELL_CMD("DDS_Frame_Per_Sec", "d2sf", DDS_CLI_FramePerSec, "DDS_Fps"),     \
    SHELL_CMD("DDS_Play", "d2sl", DDS_CLI_Play, "DDS_Play"),                    \
    SHELL_CMD("DDS_Pattern", "d2sp", DDS_CLI_Pattern, "DDS_Pattern"),           \
    SHELL_CMD("DDS_Set_Array", "d2sar", DDS_CLI_SetArray, "DDS_SetArray"),      \
    SHELL_CMD("DDS_Print_Track", "d2spt", DDS_CLI_PrintTrack, "DDS_PrintTack"), \
    SHELL_CMD("DDS_Set_Pwm", "d2ssp", DDS_CLI_SetPwm, "DDS_SetPWMWave"),        \
    SHELL_CMD("DDS_Set_Sin", "d2sin", DDS_CLI_SetSin, "DDS_SetSinWave"),        \
    SHELL_CMD("DDS_Set_Fence", "d2sfe", DDS_CLI_SetFence, "DDS_SetFenceWave"),  \
    SHELL_CMD("DDS_Diagnostic", "d2sd", DDS_CLI_Diagnostic, "DDS_Diagnostic"),

#ifdef __cplusplus
}
#endif

#endif /* DDS_CLI_H */
