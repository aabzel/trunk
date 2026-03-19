#include "lis3dh_diagnostic.h"

#include <stdio.h>
#include <string.h>

#include "general_macros.h"
#include "lis3dh_driver.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "lis3dh_miscellaneous.h"
#include "num_to_str.h"
#include "storage_diag.h"
#include "table_utils.h"
#include "vector.h"
#include "writer_config.h"


const char* LIS3DH_ConfigurationToStr(const LIS3DH_CONFIGURATION* const Config)
{
    static char name[80] = "";
    if (Config)
    {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sN:%u,", name, Config->num);
        snprintf(name, sizeof(name), "%sI2C:%u,", name, Config->i2cNum);
        snprintf(name, sizeof(name), "%sAddr:0x%x", name, Config->chipAddr);
    }
    return name;
}

const char* LIS3DH_NodeToStr(const LIS3DH_HANDLE* const Node)
{
    static char name[150] = "";
    if (NULL_PTR != Node)
    {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sN:%u,", name, Node->num);
        snprintf(name, sizeof(name), "%sI2C:%u,", name, Node->i2cNum);
        snprintf(name, sizeof(name), "%sAddr:0x%x,", name, Node->chipAddr);
    }
    return name;
}

#if 0
static const char* LIS3DH_RegDiagToStr(LIS3DH_REGISTER_ADDR addr, U8 value) {
    static char name[150]="";
     STD_RESULT ret = RESULT_NOT_OK;
    switch(addr) {
        case LIS3DH_REGISTER_LATCHED_FAULT: res=RegLatchedFaultToStr(value,name);break;
        case LIS3DH_REGISTER_STATUS_AND_LOAD_DIAGNOSTIC: res=RegStatusAndLoadDiagnosticToStr(value,name); break;
        case LIS3DH_REGISTER_CONTROL: res=RegControlToStr(value,name);break;
    }
    return name;
}
#endif

STD_RESULT LIS3DH_RegDiag(LIS3DH_REGISTER_ADDR addr, U8 value)
{
     STD_RESULT ret = RESULT_NOT_OK;
#ifdef HAS_BIN_2_STR
    LOG_WARNING(LIS3DH_EHAL,
                "Addr 0x%x=%s,Value:0x%x=%s",
                addr,
                LIS3DH_RegAddrToName(addr),
                value,
                utoa_bin8(value));
#endif
    return ret;
}

STD_RESULT LIS3DH_DiagLowLevel(U8 num, const char* const keyWord)
{
     STD_RESULT ret = RESULT_NOT_OK;
    U32 addr = 0;
    U32 cnt = 0;

    for (addr = 0; addr < 0xFF; addr++)
    {
        const ASIC_REG_INFO* Info = LIS3DH_RegAddrToInfo(addr);
        if (Info)
        {
            U8 value = 0;
            STD_RESULT ret = RESULT_NOT_OK;
            ret = LIS3DH_ReadRegister(num, addr, &value);
            if (RESULT_OK==ret)
            {
                ret = LIS3DH_RegDiag(addr, value);
                if (RESULT_OK==ret)
                {
                    cnt++;
                }
            }
        }
    }

    if (0 < cnt)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
}

const char* LIS3DH_AccelerationToStr(const LIS3DH_ACCELERATION* const Acceleration)
{
    static char text[100] = "";
    if (Acceleration)
    {
        FLOAT32 norm = VECTOR_CalcNormF(&Acceleration->AccelReal);
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sX:%6.2f,", text, Acceleration->AccelReal.dx);
        snprintf(text, sizeof(text), "%sY:%6.2f,", text, Acceleration->AccelReal.dy);
        snprintf(text, sizeof(text), "%sZ:%6.2f,", text, Acceleration->AccelReal.dz);
        snprintf(text, sizeof(text), "%sA:%6.2f", text, norm);
    }
    return text;
}

STD_RESULT LIS3DH_DiagHighLevel(U8 num)
{
    STD_RESULT ret = RESULT_NOT_OK;
    LOG_INFO(LIS3DH_EHAL, "DiagHighLevel");
    ret = LIS3DH_IsConnected(num);
    if (RESULT_OK==ret)
    {
        LOG_INFO(LIS3DH_EHAL, "Connected!");
        //LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
        //if (NULL_PTR != Node)
        //{
        //}
    }

    return ret;
}

const char* LIS3DH_RegAddrToName(LIS3DH_REGISTER_ADDR addr)
{
    const char* name = "?";
    const ASIC_REG_INFO* Info = LIS3DH_RegAddrToInfo(addr);
    if (Info)
    {
        name = Info->name;
    }
    return name;
}

STD_RESULT LIS3DH_DiadRegMap(U8 num, char* keyWord, char* keyWord2)
{
    STD_RESULT ret = RESULT_NOT_OK;
    U32 addr = 0;
    U32 cnt = 0;
    static const table_col_t cols[] = {
        { 5, "No" },    { 25, "name" }, { 8, "access" },     { 6, "addrD" },
        { 6, "addrH" }, { 6, "val" },   { 11, "val [bin]" },
    };
    char text[120] = "";
    table_header(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));

    for (addr = 0; addr < 0xFF; addr++)
    {
        const ASIC_REG_INFO* RegInfo = LIS3DH_RegAddrToInfo(addr);
        if (RegInfo)
        {
            U8 value = 0;
            ret = LIS3DH_ReadRegister(num, addr, &value);
            if (RESULT_OK==ret)
            {
                strcpy(text, TSEP);
                cli_printf(TSEP " %3u ", cnt);
                snprintf(text, sizeof(text), "%s %23s " TSEP, text, RegInfo->name);
                snprintf(
                    text, sizeof(text), "%s %6s " TSEP, text,
                    StorageAccessToStr((StorageAccess_t)RegInfo->access));
                snprintf(text, sizeof(text), "%s %4u " TSEP, text, addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, value);
                snprintf(text, sizeof(text), "%s %9s " TSEP, text, utoa_bin8(value));
                cli_printf("%s" CRLF, text);
                wait_in_loop_ms(10);
                cnt++;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));

    if (0 < cnt)
    {
        ret = RESULT_OK;
    }
    else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
}

const char* LIS3DH_OpModeToStr(LIS3DH_OPERATION_MODE opMode)
{
    char* name = "?";
    LIS3DH_RESOLUTION_INFO* Info = LIS3DH_GetResolutionInfoByOpMode(opMode);
    if (Info)
    {
        name = Info->name;
    }
    return name;
}


STD_RESULT LIS3DH_AdcDiag(void)
{
    STD_RESULT ret = RESULT_NOT_OK;
    static const table_col_t cols[] = {
        { 4, "No" },
        { 8, "ADC1" }, { 8, "ADC2" },   { 8, "ADC3" },
        { 8, "ADC1" }, { 8, "ADC2" },   { 8, "ADC3" },
    };

    char text[120] = "";
    table_header(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));
    U32 cnt = LIS3DH_GetCnt()+5;
    U32 i = 0;
    for (i = 0; i <= cnt; i++)
    {
        LIS3DH_HANDLE* Node = LIS3DH_GetNode(i);
        if (NULL_PTR != Node)
        {
            STD_RESULT ret = 0;
            (void) ret;
            U16  adcCode = 0;
            ret = LIS3DH_ReadAdcCode((U8) i, 1, &adcCode);
            ret = LIS3DH_ReadAdcCode((U8) i, 2, &adcCode);
            ret = LIS3DH_ReadAdcCode((U8) i, 3, &adcCode);
            strcpy(text, TSEP);
            snprintf(text, sizeof(text), "%s %2u " TSEP, text, i);
            snprintf(text, sizeof(text), "%s %6u " TSEP, text, Node->adcCode[0]);
            snprintf(text, sizeof(text), "%s %6u " TSEP, text, Node->adcCode[1]);
            snprintf(text, sizeof(text), "%s %6u " TSEP, text, Node->adcCode[2]);

            snprintf(text, sizeof(text), "%s 0x%04x " TSEP, text,(U16) Node->adcCode[0]);
            snprintf(text, sizeof(text), "%s 0x%04x " TSEP, text,(U16) Node->adcCode[1]);
            snprintf(text, sizeof(text), "%s 0x%04x " TSEP, text,(U16) Node->adcCode[2]);

            cli_printf("%s" CRLF, text);
            ret = RESULT_OK;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));

    return ret;
}


STD_RESULT LIS3DH_Diag(void)
{
    STD_RESULT retStat = RESULT_NOT_OK;
    static const table_col_t cols[] = {
        { 4, "No" },
        { 4, "bit" },
        { 7, "preci" },
        {6, "Range" },
        { 7, "mg/dig" },
        { 10, "Op" },
        {7, "FsHz" },
        { 8, "X" }, { 8, "Y" },   { 8, "Z" },
        { 8, "X" },   { 8, "Y" },   { 8, "Z" },
    };

    char text[120] = "";
    table_header(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));
    U32 cnt = LIS3DH_GetCnt()+5;
    U32 i = 0;
    for (i = 0; i <= cnt; i++)
    {
        LIS3DH_HANDLE* Node = LIS3DH_GetNode(i);
        if (NULL_PTR != Node)
        {
            U32 dataRateHz = 0;
            U8 rangeG = 0 ;
            STD_RESULT ret = RESULT_NOT_OK;
            ret = LIS3DH_GetDataRateHz(i, &dataRateHz);
            ret = LIS3DH_GetRange(i, &rangeG);

            LIS3DH_OPERATION_MODE opMode = LIS3DH_OP_MODE_UNDEF;
            ret = LIS3DH_GetOperationModeLowLevel(Node, &opMode);
            if (RESULT_OK==ret)
            {
                LIS3DH_RESOLUTION_INFO* Resolution = LIS3DH_GetResolutionInfoByOpMode(opMode);
                if (Resolution)
                {
                    LIS3DH_AdcToReal(&Node->Acceleration, Node->sensitivity);
                    strcpy(text, TSEP);
                    snprintf(text, sizeof(text), "%s %2u " TSEP, text, i);
                    snprintf(text, sizeof(text), "%s %5.3f " TSEP, text, Node->precisionG);
                    snprintf(text, sizeof(text), "%s %2u " TSEP, text, Node->resolutionBit);
                    snprintf(text, sizeof(text), "%s %4d " TSEP, text, rangeG);
                    snprintf(text, sizeof(text), "%s %5d " TSEP, text, Node->sensitivity);
                    snprintf(text, sizeof(text), "%s %8s " TSEP, text, Resolution->name);
                    snprintf(text, sizeof(text), "%s %5d " TSEP, text, dataRateHz);
                    snprintf(text, sizeof(text), "%s %6d " TSEP, text, Node->Acceleration.X.s16);
                    snprintf(text, sizeof(text), "%s %6d " TSEP, text, Node->Acceleration.Y.s16);
                    snprintf(text, sizeof(text), "%s %6d " TSEP, text, Node->Acceleration.Z.s16);

                    snprintf(
                        text, sizeof(text), "%s %6.2f " TSEP, text, Node->Acceleration.AccelReal.dx);
                    snprintf(
                        text, sizeof(text), "%s %6.2f " TSEP, text, Node->Acceleration.AccelReal.dy);
                    snprintf(
                        text, sizeof(text), "%s %6.2f " TSEP, text, Node->Acceleration.AccelReal.dz);
                    cli_printf("%s" CRLF, text);
                    retStat = RESULT_OK;
                }
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));

    return retStat;
}
