//**************************************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   NAU8814_cli.c
//! \par    Platform
//!             PLATFORM_NAME
//! \par    Compatible
//!             COMPATIBLE_PROCESSOR_MODULE
//! \brief  Implementation of the MODULE functionality.
//!             [text]
//! \par    Abbreviations
//!             ABBR0 -
//!             ABBR1 -
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************
#include "NAU8814_cli.h"


#include "convert.h"
#include "log.h"
#include "NAU8814_driver.h"
#include "NAU8814_diagnostic.h"

bool NAU8814_DeInitCommand(int32_t argc, char* argv[])
{
    bool res = false;
    U8   num = 1;

    if (0 <= argc)
    {
        res = true;
    }

    if (1 <= argc)
    {
        res = try_str2uint8(argv[0], &num);
    }

    if (res)
    {
        STD_RESULT ret;
        LOG_INFO(NAU8814, "TryDeInit:%u...", num);
        ret = NAU8814_DeInitOne(num);
        if (RESULT_OK == ret)
        {
            LOG_INFO(NAU8814, "DeInit:%uOk", num);
            res = true;
        }
        else
        {
            res = false;
            LOG_ERROR(NAU8814, "DeInitErr", num);
        }
    }
    else
    {
        LOG_INFO(NAU8814, "Usage: ndic Num");
    }
    return res;
} // end of NAU8814_InitCommand()


bool NAU8814_I2cPingCommand(int32_t argc, char* argv[])
{
    bool       res = false;
    STD_RESULT ret;
    U8         num = 1;

    if (0 <= argc)
    {
        res = true;
    }

    if (1 <= argc)
    {
        res = try_str2uint8(argv[0], &num);
    }

    if (res)
    {
        res = true;
        ret = NAU8814_IsConnected(num);
        if (RESULT_OK == ret)
        {
            LOG_INFO(NAU8814, "Connected!");
        }
        else
        {
            LOG_ERROR(NAU8814, "Disconnected!");
        }
    }
    else
    {
        LOG_ERROR(NAU8814, "Usage: napc Num");
    }
    return res;
} // end of NAU8814_I2cPingCommand()


bool NAU8814_InitCommand(int32_t argc, char* argv[])
{
    bool res = false;
    U8   num = 1;

    if (0 <= argc)
    {
        res = true;
    }

    if (1 <= argc)
    {
        res = try_str2uint8(argv[0], &num);
    }

    if (res)
    {
        STD_RESULT ret;
        ret = NAU8814_InitOne(num);
        if (RESULT_OK == ret)
        {
            LOG_INFO(NAU8814, "Init:%uOk", num);
            res = true;
        }
        else
        {
            res = false;
            LOG_ERROR(NAU8814, "InitErr");
        }
    }
    else
    {
        LOG_INFO(NAU8814, "Usage: nic Num");
    }
    return res;
} // end of NAU8814_InitCommand()

bool NAU8814_ReadRegCommand(int32_t argc, char* argv[])
{
    bool res = false;
    U8   num = 1;
    U8   addr = 0;

    if (1 == argc)
    {
        res = try_str2uint8(argv[0], &addr);
    }

    if (res)
    {
        U16        word = 0;
        STD_RESULT ret;
        ret = NAU8814_ReadReg(num, addr, &word);
        if (RESULT_OK == ret)
        {
            LOG_INFO(NAU8814, "Addr:0x%02x,Val:0x%04x", addr, word);
        }
    }
    else
    {
        LOG_INFO(NAU8814, "Usage: maar RegAddr");
    }

    return res;
} // end of MODULE_FunctionThree()


bool NAU8814_RegHazyCommand(int32_t argc, char* argv[])
{
    bool res = false;
    if (0 <= argc)
    {
        res = true;
    }

    if (res)
    {
        STD_RESULT ret;
        ret = NAU8814_RegHazy(1);
        ret = NAU8814_DiagRegMapHidden(1);
        if (RESULT_OK == ret)
        {
            res = true;
        }
    }
    else
    {
        LOG_ERROR(NAU8814, "Usage: nrh");
    }
    return res;
} // end of MODULE_FunctionThree()


bool NAU8814_RegMapCommand(int32_t argc, char* argv[])
{
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    if (0 <= argc)
    {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }

    if (1 <= argc)
    {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if (2 <= argc)
    {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if (2 < argc)
    {
        LOG_ERROR(NAU8814, "Usage: maxregs keyWord keyWord");
    }
    if (res)
    {
        STD_RESULT ret;
        ret = NAU8814_DiagRegMap(1, keyWord1, keyWord2);
        if (RESULT_OK == ret)
        {
            res = true;
        }
    }
    return res;
} // end of MODULE_FunctionThree()

bool NAU8814_ResetCommand(int32_t argc, char* argv[])
{
    bool       res = false;
    STD_RESULT ret;
    ret = NAU8814_Reset(1);
    if (RESULT_OK == ret)
    {
        LOG_INFO(NAU8814, "ResetOk");
        res = true;
    }
    else
    {
        LOG_ERROR(NAU8814, "ResetErr");
    }
    return res;
} // end of NAU8814_ResetCommand()


bool NAU8814_WriteRegCommand(int32_t argc, char* argv[])
{
    bool res = false;
    U8   addr = 0;
    U16  word = 0;

    if (2 <= argc)
    {
        res = try_str2uint8(argv[0], &addr);
        res = try_str2uint16(argv[1], &word);
    }

    if (res)
    {
        STD_RESULT ret;
        LOG_INFO(NAU8814, "Try,Write,RegAddr:0x%02x,Value:0x%04x", addr, word);
        ret = NAU8814_WriteReg(1, addr, word);
        if (RESULT_OK == ret)
        {
            LOG_INFO(NAU8814, "Write,Addr:0x%02x:Val:0x%02x,Ok", addr, word);
        }
        else
        {
            LOG_ERROR(NAU8814, "Write,Addr:0x%02x:Val:0x%02x,Err", addr, word);
        }
    }
    else
    {
        LOG_ERROR(NAU8814, "Usage: nrwc RegAddr RegValue");
    }
    return res;
} // end of NAU8814_WriteRegCommand()

bool NAU8814_reg_map_hidden_command(int32_t argc, char* argv[])
{
    bool res = false;

    if (0 <= argc)
    {
        res = true;
    }

    if (res)
    {
        STD_RESULT ret;
        ret = NAU8814_DiagRegMapHidden(1);
        if (RESULT_OK == ret)
        {
            res = true;
        }
    }
    return res;
} // end of NAU8814_reg_map_hidden_command()

bool NAU8814_DiagnosticHlCommand(int32_t argc, char* argv[])
{
    bool       res = false;
    STD_RESULT ret;
    ret = NAU8814_DiagnosticHighLevel(1);
    if (RESULT_OK == ret)
    {
        res = true;
    }
    return res;
} // end of NAU8814_DiagnosticHlCommand()

//******************************* end of file ******************************************************
