//*****************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   nau8814_adc_cli.c
//! \par    Platform
//!             PLATFORM_NAME
//! \par    Compatible
//!             COMPATIBLE_PROCESSOR_MODULE
//! \brief  Implementation of the MODULE functionality.
//!             [text]
//! \par    Abbreviations
//!             CLI -
//!             ABBR1 -
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//*****************************************************************************
#include "nau8814_adc_cli.h"

#include "convert.h"
#include "log.h"
#include "nau8814_adc_diagnostic.h"
#include "nau8814_adc_driver.h"
#include "nau8814_diagnostic.h"
#include "nau8814_driver.h"

bool NAU8814_AdcDiagCommand(int32_t argc, char* argv[])
{
    bool res = false;
    U8   num = 1;
    if (1 <= argc)
    {
        res = try_str2uint8(argv[0], &num);
    }

    if (res)
    {
        STD_RESULT ret;
        ret = NAU8814_AdcDiag(num);
        if (RESULT_OK == ret)
        {
            NAU8814_HANDLE* Node = NAU8814_GetNode(num);
            if (Node)
            {
                LOG_INFO(NAU8814, "%s", NAU8814_NodeToStr(Node));
            }
        }
        else
        {
        }
    }
    else
    {
        LOG_ERROR(NAU8814, "Usage: nad Num");
    }
    return res;
}

bool NAU8814_ListenCommand(int32_t argc, char* argv[])
{
    bool   res = false;
    U32    durationMs = 1000;
    FLOAT32 exp_frequencyHz = 0.0;
#ifdef HAS_I2S
    log_level_get_set(I2S, LOG_LEVEL_INFO);
#endif
    if (0 <= argc)
    {
        res = true;
    }

    if (1 <= argc)
    {
        res = try_str2uint32(argv[0], &durationMs);
        if (FALSE == res)
        {
            LOG_ERROR(NAU8814, "ParseErr DurationMs %s", argv[0]);
        }
    }

    if (2 <= argc)
    {
        res = try_str2float(argv[1], &exp_frequencyHz);
        if (FALSE == res)
        {
            LOG_ERROR(NAU8814, "ParseErr ExpFreqHz %s", argv[1]);
        }
    }

    if (res)
    {
        LOG_INFO(NAU8814, "Listen:%u ms", durationMs);
        STD_RESULT ret = NAU8814_ADC_Listen(1, durationMs);
        if (RESULT_OK == ret)
        {
            LOG_INFO(NAU8814, "ListenOk");
            res = true;
        }
        else
        {
            res = false;
            LOG_ERROR(NAU8814, "ListenErr");
        }
    }
    else
    {
        LOG_ERROR(NAU8814, "Usage: nalc durationMs");
    }

    return res;
}

//******************************* end of file *********************************
