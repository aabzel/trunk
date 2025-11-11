//**************************************************************************************************
// @Module  NAU8814 ASIC Driver
//! \file   nau8814_diagnostic.c
//! \par    Platform
//!             PLATFORM_NAME
//! \par    Compatible
//!             COMPATIBLE_PROCESSOR_MODULE
//! \brief  Implementation of the MODULE functionality.
//!
//! \par    Abbreviations
//!             ASIC - Application-specific integrated circuit
//!             MCU - microcontroller unit
//! \par    History
//! | Date       | Version | Author  | Comment
//! |:----------:|:-------:|:-------:|--------------------------------------------------------------
//! | 01.07.2024 |  1.0.0  |   AAB   | First release.
//**************************************************************************************************
#include "nau8814_diagnostic.h"

#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "interfaces_diag.h"
#include "log.h"
#include "num_to_str.h"

#ifdef HAS_NAU8814_ADC
#include "nau8814_adc_diagnostic.h"
#endif //

#ifdef HAS_NAU8814_DAC
#include "nau8814_dac_diagnostic.h"
#endif //

#include "nau8814_driver.h"
#include "none_blocking_pause.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"



static const char* ValU16ToStar(const U16 word);

//**************************************************************************************************
//! [Description of MODULE_FunctionThree]
//!
//! \note       [text]
//!
//! \param[in]  Config - [description of parameterZero]
//!
//! \return     [Description of return value]
//**************************************************************************************************
const char* Nau8814_ConfigurationToStr(const NAU8814_CONFIG* const Config)
{
    static char name[80] = "?";
    if (Config)
    {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sN:%u,", name, Config->num);
        snprintf(name, sizeof(name), "%sI2C:%u,", name, Config->i2cNum);
        snprintf(name, sizeof(name), "%sI2S:%u,", name, Config->i2sNum);
        snprintf(name, sizeof(name), "%sAddr:0x%x", name, Config->chipAddr);
    }
    return name;
} // end of MODULE_FunctionThree()

//**************************************************************************************************
//! [Description of MODULE_FunctionThree]
//!
//! \note       [text]
//!
//! \param[in]  parameterZero - [description of parameterZero]
//! \param[in]  parameterOne - [description of parameterOne]
//! \param[out] parameterTwo - [description of parameterTwo]
//!
//! \return     [Description of return value]
//**************************************************************************************************
const char* NAU8814_NodeToStr(const NAU8814_HANDLE* const Node)
{
    static char name[150] = "";
    if (Node)
    {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sN:%u,", name, Node->num);
        snprintf(name, sizeof(name), "%sI2C:%u,", name, Node->i2cNum);
        snprintf(name, sizeof(name), "%sI2S:%u,", name, Node->i2sNum);
        snprintf(name, sizeof(name), "%sAddr:0x%x,", name, Node->chipAddr);
        snprintf(name, sizeof(name), "%sPmicGain:%d,", name, Node->pMicGain);
        snprintf(name, sizeof(name), "%sAdcOn:%u,", name, Node->adcOn);
        snprintf(name, sizeof(name), "%sDacGain:%d,", name, Node->dacGain);
        snprintf(name,
                 sizeof(name),
                 "%sI2Srole:%s",
                 name,
                 BusRoleToStr(Node->i2sRole));
    }
    return name;
} // end of MODULE_FunctionThree()

//**************************************************************************************************
//! [Description of MODULE_FunctionThree]
//!
//! \note       [text]
//!
//! \param[in]  word - [description of parameterZero]
//!
//! \return     [Description of return value]
//**************************************************************************************************
static const char* ValU16ToStar(const U16 word)
{
    const char* name = "";
    if (0 < word)
    {
        name = "*";
    }
    return name;
} // end of ValU16ToStar()

//**************************************************************************************************
//! [Description of NAU8814_RegAddrToName]
//!
//! \note       [text]
//!
//! \param[in]  parameterZero - [description of parameterZero]
//! \param[in]  parameterOne - [description of parameterOne]
//! \param[out] parameterTwo - [description of parameterTwo]
//!
//! \return     [Description of return value]
//**************************************************************************************************
const char* NAU8814_RegAddrToName(const NAU8814_REGISTER_ADDR addr)
{
    const char*                  name = "?";
    const NAU8814_REGISTER_INFO* Info = Nau8814_RegAddrToInfo(addr);
    if (Info)
    {
        name = Info->name;
    }
    return name;
} // end of NAU8814_RegAddrToName()

//**************************************************************************************************
//! [Description of NAU8814_DiagnosticHighLevel]
//!
//! \note       [text]
//!
//! \param[in]  num - ASIC number
//!
//! \return     [Description of return value]
//**************************************************************************************************
STD_RESULT NAU8814_DiagnosticHighLevel(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LOG_INFO(NAU8814, "DiagHighLevel");

    ret = NAU8814_IsConnected(num);
    if (RESULT_OK == ret)
    {
        LOG_INFO(NAU8814, "Connected");
        NAU8814_HANDLE* Node = NAU8814_GetNode(num);
        if (Node)
        {
            ret = NAU8814_GetI2sRole(num, &Node->i2sRole);
            LOG_INFO(NAU8814, " %s", NAU8814_NodeToStr(Node));
        }
        ret = NAU8814_DiagnosticPll(num);
    }

    return ret;
} // end of NAU8814_DiagnosticHighLevel()


//**************************************************************************************************
//! [Description of NAU8814_DiagnosticPll]
//!
//! \note       [text]
//!
//! \param[in]  num - ASIC number
//!
//! \return     [Description of return value]
//**************************************************************************************************

// Table 25: Registers associated with PLL
STD_RESULT NAU8814_DiagnosticPll(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LOG_INFO(NAU8814, "DiagPll");

    const NAU8814_CONFIG* Config = NAU8814_GetConfig(num);
    if (Config)
    {
        FLOAT32 f_1 = 1.0;
        FLOAT32 f_2 = 1.0;
        FLOAT32 imclk = 1.0;
        U8     N = 0;
        U8     D = 0;
        U32    K = 0;
        ret = NAU8814_GetPllD(num, &D);
        ret = NAU8814_GetPllN(num, &N);
        ret = NAU8814_GetPllK(num, &K);
        f_1 = Config->mclkFreqHz / ((FLOAT32)D);
        FLOAT32 fractional = ((FLOAT32)K) / ((FLOAT32)NAU8814_MAX_PCM);
        FLOAT32 R = ((FLOAT32)N) + fractional;
        // R = f_2/f_1;
        f_2 = R * f_1;
        FLOAT32 f_pll = f_2 / 4.0;
        FLOAT32 P = 1.0;
        ret = NAU8814_GetMasterClockDiv(num, &P);
        imclk = f_pll / ((FLOAT32)P);

        char text[300] = "";
        strcpy(text, "");
        snprintf(text,
                 sizeof(text),
                 "%sMCLK:%sHz,",
                 text,
                 DoubleToStr(Config->mclkFreqHz));
        snprintf(text, sizeof(text), "%sD:%u,", text, D);
        snprintf(text, sizeof(text), "%sN:%u,", text, N);
        snprintf(text, sizeof(text), "%sK:%u,", text, K);
        snprintf(text, sizeof(text), "%sR:%f,", text, R);
        snprintf(text, sizeof(text), "%sP:%2.1f,", text, P);
        snprintf(text, sizeof(text), "%sF1:%sHz,", text, DoubleToStr(f_1));
        snprintf(text, sizeof(text), "%sF2:%sHz,", text, DoubleToStr(f_2));
        snprintf(text, sizeof(text), "%sFpll:%sHz,", text, DoubleToStr(f_pll));
        snprintf(text, sizeof(text), "%sIMCLK:%sHz,", text, DoubleToStr(imclk));
        LOG_INFO(NAU8814, "%s", text);

        ret = RESULT_OK;
    }
    return ret;
} // end of NAU8814_DiagnosticPll()

//**************************************************************************************************
//! [Description of NAU8814_DiagRegMap]
//!
//! \note       [text]
//!
//! \param[in]  num - ASIC number
//! \param[in]  key_word - [description of parameterOne]
//! \param[in]  key_word2 - [description of parameterOne]
//! \param[out] parameterTwo - [description of parameterTwo]
//!
//! \return     [Description of return value]
//**************************************************************************************************
STD_RESULT NAU8814_DiagRegMap(const U8 num,
                              const char * const key_word1,
                              const char * const key_word2)
{
    STD_RESULT               ret = RESULT_NOT_OK;
    U32                      addr = 0;
    U32                      cnt = 0;
    static const table_col_t cols[] = {
        { 5, "No" },  { 6, "addrD" },      { 6, "addrH" },
        { 8, "val" }, { 21, "val [bin]" }, { 21, "name" },
    };
    char text[120] = "";
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    for (addr = 0; addr < 0xFF; addr++)
    {
        const NAU8814_REGISTER_INFO* Info = Nau8814_RegAddrToInfo(addr);
        if (Info)
        {
            U16 word = 0;
            ret = NAU8814_ReadReg(num, addr, &word);
            if (RESULT_OK == ret)
            {
                strcpy(text, TSEP);
                cli_printf(TSEP " %3u ", cnt);
                snprintf(text, sizeof(text), "%s %4u " TSEP, text, addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, addr);
                snprintf(text, sizeof(text), "%s 0x%04x " TSEP, text, word);
                snprintf(
                    text, sizeof(text), "%s %9s " TSEP, text, utoa_bin16(word));
                snprintf(text, sizeof(text), "%s %19s " TSEP, text, Info->name);
                cli_printf("%s" CRLF, text);
                wait_in_loop_ms(10);
                cnt++;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));


    if (0 < cnt)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of NAU8814_DiagRegMap()

//**************************************************************************************************
//! NAU8814 Diag Reg Map Hidden
//!
//! \note       NAU8814 Diag Reg Map Hidden
//!
//! \param[in]  num - ASIC number
//!
//! \return     [Description of return value]
//**************************************************************************************************
STD_RESULT NAU8814_DiagRegMapHidden(const U8 num)
{
    STD_RESULT               ret = RESULT_NOT_OK;
    static const table_col_t cols[] = {
        { 5, "No" },  { 6, "addr" },       { 6, "addr" },
        { 8, "val" }, { 11, "val [bin]" },
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    char    text[120] = "";
    int32_t i = 0;
    int32_t cnt = 0;
    for (i = 0; i <= 127; i++)
    {
        U8 someI2cAddr = i;
        ret = NAU8814_IsValidI2cRegisterAddr(someI2cAddr);
        if (RESULT_NOT_OK == ret)
        {
            U16 word = 0;
            ret = NAU8814_ReadReg(num, someI2cAddr, &word);
            if (RESULT_OK == ret)
            {
                strcpy(text, TSEP);
                snprintf(text, sizeof(text), "%s %4u " TSEP, text, someI2cAddr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, someI2cAddr);
                snprintf(text, sizeof(text), "%s 0x%04x " TSEP, text, word);
                snprintf(text, sizeof(text), "%s %9s " TSEP, text, utoa_bin16(word));
                cli_printf(TSEP " %3u ", cnt);
                cli_printf("%s" CRLF, text);
                cnt++;
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return ret;
} // end of NAU8814_DiagRegMapHidden()
//******************************* end of file ******************************************************


//**************************************************************************************************
//! [Description of MODULE_FunctionThree]
//!
//! \note       [text]
//!
//! \param[in]  num - ASIC number
//! \param[in]  parameterOne - [description of parameterOne]
//! \param[out] parameterTwo - [description of parameterTwo]
//!
//! \return     [Description of return value]
//**************************************************************************************************
STD_RESULT NAU8814_RegHazy(const U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LOG_INFO(NAU8814, "HazyRegs");
    static const table_col_t cols[] = {
        { 5, "No" },  { 6, "addrD" },      { 6, "addrH" },
        { 8, "val" }, { 21, "val [bin]" }, { 6, "mark" },
    };
    char text[120] = "";
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    U32 i = 0;
    U32 cnt = 0;
    for (i = 0; i <= 127; i++)
    {
        U8 someI2cAddr = i;
        ret = NAU8814_IsValidI2cRegisterAddr(someI2cAddr);
        if (RESULT_NOT_OK == ret)
        {
            U16 word = 0;
            ret = NAU8814_ReadReg(num, someI2cAddr, &word);
            if (RESULT_OK == ret)
            {
                if (word)
                {
                    strcpy(text, TSEP);
                    snprintf(
                        text, sizeof(text), "%s %4u " TSEP, text, someI2cAddr);
                    snprintf(
                        text, sizeof(text), "%s 0x%02x " TSEP, text, someI2cAddr);
                    snprintf(text, sizeof(text), "%s 0x%04x " TSEP, text, word);
                    snprintf(text,
                             sizeof(text),
                             "%s %9s " TSEP,
                             text,
                             utoa_bin16(word));
                    snprintf(text,
                             sizeof(text),
                             "%s %4s " TSEP,
                             text,
                             ValU16ToStar(word));
                    cli_printf(TSEP " %3u ", cnt);
                    cli_printf("%s" CRLF, text);
                    wait_in_loop_ms(10);
                    cnt++;
                }
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));


    if (0 < cnt)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
} // end of NAU8814_RegHazy()
