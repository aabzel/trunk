#include "lis3dh_cli.h"

#include "common_diag.h"
#include "convert.h"
#include "lis3dh_driver.h"
#include "lis3dh_diagnostic.h"
#include "general_macros.h"
#include "mcal_to_ehal.h"
#include "log.h"

bool LIS3DH_DiagLowLevelCommand(int32_t argc, char* argv[])
{
    bool res = false;
    char keyWord[20] = "";
    if (0 <= argc)
    {
        res = true;
    }

    if (1 <= argc)
    {
        strcpy(keyWord, argv[0]);
        res = true;
    }

    if (res)
    {
        LOG_INFO(LIS3DH_EHAL, "LowLevelDiag KeyWord [%s]", keyWord);
        STD_RESULT ret = LIS3DH_DiagLowLevel(1, keyWord);
        res = EHAL_RetToRes(ret);
        if (RESULT_OK==ret)
        {
            LOG_INFO(LIS3DH_EHAL, "LowLevelDiagOk");
        }
        else
        {
            LOG_ERROR(LIS3DH_EHAL, "LowLevelDiagOk");
        }
    }
    return res;
}

bool LIS3DH_DiagHiLevelCommand(int32_t argc, char* argv[])
{
    bool res = false;
    STD_RESULT ret = LIS3DH_Diag();
    res = EHAL_RetToRes(ret);
    return res;
}

bool LIS3DH_AdcCommand(int32_t argc, char* argv[])
{
    bool res = false;
    STD_RESULT ret = LIS3DH_AdcDiag();
    res = EHAL_RetToRes(ret);
    return res;
}



bool LIS3DH_WriteRegisterCommand(int32_t argc, char* argv[])
{
    bool res = false;
    U8 addr = 0;
    U8 byte = 0;
    if (1 <= argc)
    {
        res = try_str2uint8(argv[0], &addr);
        res = log_res(LIS3DH_EHAL, res, "Addr");
    }
    if (2 <= argc)
    {
        res = try_str2uint8(argv[1], &byte);
        res = log_res(LIS3DH_EHAL, res, "Val");
    }

    if (res)
    {
        STD_RESULT ret = LIS3DH_WriteRegister(1, addr, byte);
        res = EHAL_RetToRes(ret);
        if (RESULT_OK==ret)
        {
            LOG_INFO(LIS3DH_EHAL, "Addr:0x%02x,Val:0x%02x", byte, byte);
        }
    }
    return res;
}

bool LIS3DH_ReadRegisterCommand(int32_t argc, char* argv[])
{
    bool res = false;
    U8 num = 1;
    U8 addr = 0;

    if (1 == argc)
    {
        res = try_str2uint8(argv[0], &addr);
        res = log_res(LIS3DH_EHAL, res, "Addr");
    }

    if (res)
    {
        U8 byte = 0;
        STD_RESULT ret = LIS3DH_ReadRegister(num, addr, &byte);
        res = EHAL_RetToRes(ret);
        if (RESULT_OK==ret)
        {
            LOG_INFO(LIS3DH_EHAL, "Addr:0x%02x,Val:0x%02x", addr, byte);
        }
    }
    else
    {
        LOG_INFO(LIS3DH_EHAL, "Usage: maar RegAddr");
    }

    return res;
}

bool LIS3DH_InitCommand(int32_t argc, char* argv[])
{
    bool res = false;
    STD_RESULT ret = LIS3DH_InitOne(1);
    res = EHAL_RetToRes(ret);
    return res;
}
//
bool LIS3DH_RegMapCommand(int32_t argc, char* argv[])
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
        LOG_ERROR(LIS3DH_EHAL, "Usage: elirm keyWord keyWord");
    }
    if (res)
    {
        STD_RESULT ret = RESULT_NOT_OK;
        ret = LIS3DH_DiadRegMap(1, keyWord1, keyWord2);
        res = EHAL_RetToRes(ret);
    }
    return res;
}


bool LIS3DH_I2C_PingCommand(int32_t argc, char* argv[])
{
    bool res = false;
    STD_RESULT ret = RESULT_NOT_OK;
    ret = LIS3DH_IsConnected(1);
    res = EHAL_RetToRes(ret);
    if (RESULT_OK==ret)
    {
        LOG_INFO(LIS3DH_EHAL, "Connected!");
    }
    else
    {
        LOG_ERROR(LIS3DH_EHAL, "Disconnected!");
    }
    return res;
}

bool LIS3DH_ReadAccelerationCommand(int32_t argc, char* argv[])
{
    bool res = false;
    U8 num = 1;

    if (1 <= argc)
    {
        res = try_str2uint8(argv[0], &num);
        res = log_res(LIS3DH_EHAL, res, "ASIC");
    }

    LIS3DH_HANDLE* Node = LIS3DH_GetNode(num);
    if (NULL_PTR == Node)
    {
        STD_RESULT ret = RESULT_NOT_OK;
        ret = LIS3DH_GetAccelerationFastLowLevel(Node, &Node->Acceleration);
        res = EHAL_RetToRes(ret);
        if (RESULT_OK==ret)
        {
            ret = LIS3DH_AdcToRealLowLevel(Node);
            LOG_INFO(LIS3DH_EHAL, "%s", LIS3DH_AccelerationToStr(&Node->Acceleration));
        }
    }
    else
    {
        LOG_ERROR(LIS3DH_EHAL, "Usage: lia Num");
    }

    return res;
}
