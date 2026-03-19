#include "dds_cli.h"

//#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "dds.h"
#include "dds_configuration.h"
#include "dds_diagnostic.h"
#include "debug_info.h"
#include "log.h"

#ifndef DDS_IN_USE
#error "+ DDS_IN_USE"
#endif

#ifndef DDS_CLI_IN_USE
#error "+ DDS_CLI_IN_USE"
#endif


bool DDS_CLI_Amplitude(int32_t argc,
                       char* argv[])
{
    bool res = false;
    U8   num = 0U;
    if (1 <= argc)
    {
        res = try_str2uint8(argv[0], &num);
        if (false == res)
        {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }

    int32_t amplitude = 0;
    if (2 <= argc)
    {
        res = try_str2int32(argv[1], (int32_t*)&amplitude);
        if (false == res)
        {
            LOG_ERROR(DDS, "ParseErr Pattern [%s]", argv[1]);
        }
        else
        {
            LOG_INFO(DDS, "ReadAmp %d", amplitude);
        }
    }
    LOG_INFO(DDS, "argc %d", argc);
    if (res)
    {
        DDS_HANDLE* Node = DDS_GetNode(num);
        if (Node)
        {
            LOG_INFO(DDS, "SeNode");
            if (2 == argc)
            {
                // LOG_INFO(DDS, "AmpTrySet %d",amplitude);
                Node->amplitude = (DDS_SAMPLE_TYPE)amplitude;
                LOG_INFO(DDS, "AmpSet %d", Node->amplitude);
            }
            else
            {
                LOG_INFO(DDS, "AmpGet %d", Node->amplitude);
            }
        }
        else
        {
            LOG_ERROR(DDS, "NoNode %u", num);
        }
    }
    else
    {
        LOG_ERROR(DDS, "Usage: dda DacNum Amp");
    }

    return res;
}


bool DDS_CLI_Diagnostic(int32_t argc,
                        char* argv[])
{
    bool res = false;
    (void)argv;
    if (0 == argc)
    {
        STD_RESULT ret = RESULT_NOT_OK;
        ret = DDS_Diagnostic();
        if (RESULT_OK == ret)
        {
            LOG_INFO(DDS, LOG_OK);
        }
        else
        {
            LOG_ERROR(DDS, "Err");
        }
    }
    else
    {
        LOG_ERROR(DDS, "Usage: dad");
    }
    return res;
}


bool DDS_CLI_FramePerSec(int32_t argc,
                         char* argv[])
{
    bool res = false;
    U8   num = 0U;
    U32  framePerSec = 0;
    if (1 <= argc)
    {
        res = try_str2uint8(argv[0], &num);
        if (false == res)
        {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }

    if (2 <= argc)
    {
        res = try_str2uint32(argv[1], &framePerSec);
        if (false == res)
        {
            LOG_ERROR(DDS, "ParseErr Pattern [%s]", argv[1]);
        }
        else
        {
            LOG_INFO(DDS, "ReadAmp %d", framePerSec);
        }
    }

    LOG_INFO(DDS, "argc %d", argc);
    if (res)
    {
        STD_RESULT ret = RESULT_NOT_OK;
        ret = DDS_SetFramePerSec(num, framePerSec);
        if (RESULT_OK == ret)
        {
            LOG_INFO(DDS, LOG_OK);
        }
        else
        {
            LOG_ERROR(DDS, "Err");
        }
    }
    else
    {
        LOG_ERROR(DDS, "Usage: ddf DacNum FPS");
    }

    return res;
}


bool DDS_CLI_Init(int32_t argc,
                  char* argv[])
{
    bool res = false;
    U8   num = 0U;
    if (1 <= argc)
    {
        res = try_str2uint8(argv[0], &num);
        if (false == res)
        {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }


    if (res)
    {
        STD_RESULT ret = RESULT_NOT_OK;
        ret = DDS_InitOne(num);
        if (RESULT_OK == ret)
        {
            res = true;
            LOG_INFO(DDS, "Init,Ok");
        }
        else
        {
            res = false;
            LOG_ERROR(DDS, "Init,Err");
        }
    }
    else
    {
        LOG_ERROR(DDS, "Usage: d2si DacNum");
    }
    return res;
}



bool DDS_CLI_Pattern(int32_t argc,
                     char* argv[])
{
    bool res = false;
    U8   num = 0U;
    U8   pattern = 0U;
    if (1 <= argc)
    {
        res = try_str2uint8(argv[0], &num);
        if (false == res)
        {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }

    if (2 <= argc)
    {
        res = try_str2uint8(argv[1], &pattern);
        if (false == res)
        {
            LOG_ERROR(DDS, "ParseErr Pattern [%s]", argv[1]);
        }
    }

    if (res)
    {
        LOG_INFO(DDS, "Set Pattern %u", pattern);
        STD_RESULT ret = RESULT_NOT_OK;
        ret = DDS_SetPattern(num, pattern);
        if (RESULT_OK == ret)
        {
            LOG_INFO(DDS, "Ok");
        }
    }
    else
    {
        LOG_ERROR(DDS, "Usage: ddrd DacNum Pattern");
    }
    return res;
}


/* example
 * ddp 1 3000
 */
bool DDS_CLI_Play(int32_t argc,
                  char* argv[])
{
    bool res = false;
    U8   num = 0U;
    U64  durationMs = 0U;
    if (1 <= argc)
    {
        res = try_str2uint8(argv[0], &num);
        if (false == res)
        {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }

    if (2 <= argc)
    {
        res = try_str2uint64(argv[1], &durationMs);
        if (false == res)
        {
            LOG_ERROR(DDS, "ParseErr Duration [%s]", argv[1]);
        }
        else
        {
            LOG_INFO(DDS, "Duration %d", durationMs);
        }
    }

    if (res)
    {
        STD_RESULT ret = RESULT_NOT_OK;
        ret = DDS_Play(num, durationMs);
        if (RESULT_OK == ret)
        {
            res = true;
            LOG_INFO(DDS, "Play:%u ms,Ok", durationMs);
        }
        else
        {
            res = false;
            LOG_ERROR(DDS, "Play,Err");
        }
    }
    else
    {
        LOG_ERROR(DDS, "Usage: d2sl DacNum DurationMs");
    }
    return res;
}

bool DDS_CLI_PrintTrack(int32_t argc,
                        char* argv[])
{
    bool res = false;
    U8   num = 1U;
    if (0 == argc)
    {
        res = TRUE;
    }

    if (1 <= argc)
    {
        res = try_str2uint8(argv[0], &num);
        if (false == res)
        {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }

    if (res)
    {
        STD_RESULT ret = RESULT_NOT_OK;
        ret = DDS_print_track(num);
        if (RESULT_NOT_OK == ret)
        {
            LOG_ERROR(DDS, "PrintTrackErr %u", num);
        }
    }
    else
    {
        LOG_ERROR(DDS, "Usage: ddpt DacNum");
    }
    return res;
}

bool DDS_CLI_SetArray(int32_t argc,
                      char* argv[])
{
    bool res = false;
    U8   num = 0U;
    U32  periods = 2;
    if (1 <= argc)
    {
        res = try_str2uint8(argv[0], &num);
        if (false == res)
        {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }

    if (2 <= argc)
    {
        res = try_str2uint32(argv[1], &periods);
        if (false == res)
        {
            LOG_ERROR(DDS, "ParseErr periods [%s]", argv[1]);
        }
    }

    if (res)
    {
        STD_RESULT ret = RESULT_NOT_OK;
        ret = DDS_SetArray(num, periods, 0);
        if (RESULT_OK == ret)
        {
            LOG_INFO(DDS, LOG_OK);
        }
        else
        {
            LOG_ERROR(DDS, "Err");
        }
    }
    else
    {
        LOG_ERROR(DDS, "Usage: ddsa num periods");
    }

    return res;
}

bool DDS_CLI_SetFence(int32_t argc,
                      char* argv[])
{
    bool res = false;
    if (5 == argc)
    {
        res = TRUE;
        U8 num = 0U;
        if (res)
        {
            res = try_str2uint8(argv[0], &num);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
            }
        }
        FLOAT32 dacFrequency = 0.0f;
        if (res)
        {
            res = try_str2float(argv[1], &dacFrequency);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr frequency [%s]", argv[1]);
            }
        }
        FLOAT32 dac_amplitude = 0.0f;
        if (res)
        {
            res = try_str2float(argv[2], &dac_amplitude);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr amplitude [%s]", argv[2]);
            }
        }

        FLOAT32 dacPhase = 0.0f;
        if (res)
        {
            res = try_str2float(argv[3], &dacPhase);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr phase [%s]", argv[3]);
            }
        }
        FLOAT32 dacVoltageOffset = 0.0f;
        if (res)
        {
            res = try_str2float(argv[4], &dacVoltageOffset);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr voltage Y offset [%s]", argv[4]);
            }
        }
        if (res)
        {
            LOG_INFO(DDS,
                     "Frequency:%f,Amplitude:%f,Phase:%f,offset:%f",
                     dacFrequency,
                     dac_amplitude,
                     dacPhase,
                     dacVoltageOffset);
            STD_RESULT ret = RESULT_NOT_OK;
            ret = DDS_SetFence(num,
                               dacFrequency,
                               (DDS_SAMPLE_TYPE)dac_amplitude,
                               dacPhase,
                               (DDS_SAMPLE_TYPE)dacVoltageOffset);
            if (RESULT_NOT_OK == ret)
            {
                LOG_ERROR(DDS, "Unable to adjust saw signal");
            }
        }
    }
    else
    {
        LOG_ERROR(DDS, "set saw syntax: num frequency amplitude phase Yoffset");
    }
    return res;
}


bool DDS_CLI_SetPwm(int32_t argc,
                    char* argv[])
{
    bool res = false;
    if (6 == argc)
    {
        U8 num = 0U;
        res = try_str2uint8(argv[0], &num);
        if (false == res)
        {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
        FLOAT32 dac_amplitude = 0.0f;

        FLOAT32 dacFrequency = 0.0f;
        if (res)
        {
            res = try_str2float(argv[1], &dacFrequency);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr frequency  [%s]", argv[1]);
            }
        }

        if (res)
        {
            res = try_str2float(argv[2], &dac_amplitude);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr voltage amplitude [%s]", argv[2]);
            }
        }

        FLOAT32 dacDutyCycle = 0.0f;
        if (res)
        {
            res = try_str2float(argv[3], &dacDutyCycle);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr duty cycle  [%s]", argv[3]);
            }
        }

        FLOAT32 dacPhase = 0.0f;
        if (res)
        {
            res = try_str2float(argv[4], &dacPhase);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr phase [%s]", argv[4]);
            }
        }

        FLOAT32 dacVoltageOffset = 0.0f;
        if (res)
        {
            res = try_str2float(argv[5], &dacVoltageOffset);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr voltage Y offset  [%s]", argv[5]);
            }
        }
        LOG_INFO(DDS,
                 "Frequency:%f,Amplitude:%f,DutyCycle:%f,Phase:%f,offset:%f",
                 dacFrequency,
                 dac_amplitude,
                 dacDutyCycle,
                 dacPhase,
                 dacVoltageOffset);
        if (res)
        {
            STD_RESULT ret = RESULT_NOT_OK;
            ret = DDS_SetPwm(num,
                             dacFrequency,
                             (DDS_SAMPLE_TYPE)dac_amplitude,
                             dacDutyCycle,
                             dacPhase,
                             (DDS_SAMPLE_TYPE)dacVoltageOffset);
            if (RESULT_NOT_OK == ret)
            {
                LOG_ERROR(DDS, "Unable to set PWM signal on DAC [%u]", num);
            }
        }
    }
    else
    {
        LOG_ERROR(DDS, "set pwm syntax: num freq amplitude DutyCycle phase offset");
    }
    return res;
}



bool DDS_CLI_SetSaw(int32_t argc,
                    char* argv[])
{
    bool res = false;
    if (5 == argc)
    {
        res = TRUE;
        U8 num = 0U;
        if (res)
        {
            res = try_str2uint8(argv[0], &num);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
            }
        }
        FLOAT32 dacFrequency = 0.0f;
        FLOAT32 dacVoltageOffset = 0.0f;
        if (res)
        {
            res = try_str2float(argv[1], &dacFrequency);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr frequency [%s]", argv[1]);
            }
        }
        FLOAT32 dac_amplitude = 0.0f;
        if (res)
        {
            res = try_str2float(argv[2], &dac_amplitude);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr amplitude [%s]", argv[2]);
            }
        }

        FLOAT32 dacPhase = 0.0f;
        if (res)
        {
            res = try_str2float(argv[3], &dacPhase);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr phase [%s]", argv[3]);
            }
        }
        if (res)
        {
            res = try_str2float(argv[4], &dacVoltageOffset);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr voltage Y offset [%s]", argv[4]);
            }
        }
        if (res)
        {
            LOG_INFO(DDS,
                     "Frequency: %f Amplitude: %f Phase: %f offset %f",
                     dacFrequency,
                     dac_amplitude,
                     dacPhase,
                     dacVoltageOffset);
            STD_RESULT ret = RESULT_NOT_OK;
            ret = DDS_SetSaw(num,
                             dacFrequency,
                             (DDS_SAMPLE_TYPE)dac_amplitude,
                             dacPhase,
                             (DDS_SAMPLE_TYPE)dacVoltageOffset);
            if (RESULT_NOT_OK == ret)
            {
                LOG_ERROR(DDS, "Unable to adjust saw signal");
            }
        }
    }
    else
    {
        LOG_ERROR(DDS, "set saw syntax: num frequency amplitude phase Yoffset");
    }
    return res;
}

bool DDS_CLI_SetSin(int32_t argc,
                    char* argv[])
{
    bool res = false;
    if (5 == argc)
    {
        res = TRUE;
        U8 num = 0U;
        if (res)
        {
            res = try_str2uint8(argv[0], &num);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
            }
        }
        FLOAT32 dac_amplitude = 0.0f;
        FLOAT32 dacFrequency = 0.0f;
        FLOAT32 dacPhase = 0.0f;
        FLOAT32 dacVoltageOffset = 0.0f;
        if (res)
        {
            res = try_str2float(argv[1], &dacFrequency);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr frequency [%s]", argv[1]);
            }
        }
        if (res)
        {
            res = try_str2float(argv[2], &dac_amplitude);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr amplitude [%s]", argv[2]);
            }
        }

        if (res)
        {
            res = try_str2float(argv[3], &dacPhase);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr phase [%s]", argv[3]);
            }
        }
        if (res)
        {
            res = try_str2float(argv[4], &dacVoltageOffset);
            if (false == res)
            {
                LOG_ERROR(DDS, "ParseErr voltage Y offset [%s]", argv[4]);
            }
        }

        if (res)
        {
            LOG_INFO(DDS,
                     "Frequency:%f,Amplitude:%f,Phase:%f,offset:%f",
                     dacFrequency,
                     dac_amplitude,
                     dacPhase,
                     dacVoltageOffset);
            STD_RESULT ret = RESULT_NOT_OK;
            ret = DDS_SetSin(num,
                             dacFrequency,
                             (DDS_SAMPLE_TYPE)dac_amplitude,
                             dacPhase,
                             (DDS_SAMPLE_TYPE)dacVoltageOffset);
            if (RESULT_NOT_OK == ret)
            {
                LOG_ERROR(DDS, "Unable to adjust sin signal");
            }
        }
    }
    else
    {
        LOG_ERROR(DDS, "set sin syntax: num frequency amplitude phase Yoffset");
    }
    return res;
}

