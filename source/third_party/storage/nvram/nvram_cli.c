#include "nvram_cli.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "nvram_drv.h"
#include "storage_diagnostic.h"
#include "nvram_diagnostic.h"
#include "writer_config.h"
#include "nvram_set_drv.h"
#include "mcal_to_ehal.h"
//#include "str_utils.h"
//#include "system_diag.h"
#include "table_utils.h"


#ifndef HAS_NVRAM_DIAG
#error "+HAS_NVRAM_DIAG"
#endif

bool NVRAM_GetCommand(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t id = 0;
    if(1 == argc) {
        res = try_str2uint16(argv[0], &id);
        if(false == res) {
            LOG_ERROR(NVRAM, "ParseErr id %s", argv[0]);
        }
    }

    if(res) {
        U8 value[100] = {0};
        STD_RESULT ret = NVRAM_Get(id, value);
        res = EHAL_RetToRes(ret);
        const NVRAM_INFO* Info=NVRAM_GetVariableInfo(id);
        if(Info) {
            LOG_INFO(NVRAM, "%s%s", NVRAM_IdToStr(id), STORAGE_DataToStr(value, Info->len, Info->type));
        }
    } else {
        LOG_ERROR(NVRAM, "Usage: ng ParamId");
    }
    return res;
}

bool NVRAM_DefaultCommand(int32_t argc, char* argv[]) {
    bool res = false;

    char keyWord1[20] = "";
    char keyWord2[20] = "";

    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }
    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        res = false;
    }

    if(res) {
        STD_RESULT ret = NVRAM_Default(keyWord1, keyWord2);
        res = EHAL_RetToRes(ret);
    } else {
        LOG_ERROR(NVRAM, "Usage: pdef keyWord1 keyWord2");
    }
    return res;
}

bool NVRAM_DiagCommand(int32_t argc, char* argv[]) {
    bool res = false;

    char keyWord1[20] = "";
    char keyWord2[20] = "";

    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }
    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        res = false;
    }

    if(res) {
        STD_RESULT ret = NVRAM_Diag(keyWord1, keyWord2);
        res = EHAL_RetToRes(ret);
    } else {
        LOG_ERROR(NVRAM, "Usage: pd keyWord1 keyWord2");
    }
    return res;
}

static bool NVRAM_RarseString(uint16_t id,
                              int32_t argc,
                              char* const argv[],
                              U8* const outBinData,
                              size_t* const outWriteLen,
                              size_t sizeData
                              ) {
    bool res = false;
    if(2 <= argc) {
        res = true;
        size_t writeLen = 0;
        STORAGE_TYPE varType = STORAGE_TYPE_UNDEF;
        const NVRAM_INFO* Info = NVRAM_GetVariableInfo(id);
        if(Info) {
            varType = Info->type;
            writeLen  = Info->len;
        }
        if(STORAGE_TYPE_UNDEF != varType) {
            // writeLen = NVRAM_GetTypeLen(  varType);
            res = false;
            U16 argLen = 0;
            argLen = (U16)strlen((char*)argv[1]);
            switch(varType) {
            case STORAGE_TYPE_BOOL:
            case STORAGE_TYPE_UINT8:
                res = try_str2uint8(argv[1], outBinData);
                break;
            case STORAGE_TYPE_INT8:
                res = try_str2int8(argv[1], (int8_t*)outBinData);
                break;
            case STORAGE_TYPE_UINT16:
                res = try_str2uint16(argv[1], (U16*)outBinData);
                break;
            case STORAGE_TYPE_INT16:
                res = try_str2int16(argv[1], (int16_t*)outBinData);
                break;
            case STORAGE_TYPE_UINT32:
            case STORAGE_TYPE_UINT32_HEX:
                res = try_str2uint32(argv[1], (uint32_t*)outBinData);
                break;
            case STORAGE_TYPE_INT32:
                res = try_str2int32(argv[1], (int32_t*)outBinData);
                break;
            case STORAGE_TYPE_UINT64:
                res = try_str2uint64(argv[1], (uint64_t*)outBinData);
                break;
            case STORAGE_TYPE_INT64:
                res = try_str2int64(argv[1], (int64_t*)outBinData);
                break;
            case STORAGE_TYPE_ARRAY:
                if(argLen < sizeData) {
                    res = try_str2array(argv[1], outBinData, sizeData, &writeLen);
                    if(false == res) {
                        strncpy((char*)outBinData, argv[1], sizeData);
                        writeLen = argLen + 1;
                    }
                    res = true;
                }
                break;
            case STORAGE_TYPE_STRING:
                if(argLen < sizeData) {
                    strncpy((char*)outBinData, argv[1], sizeData);
                    res = true;
                    writeLen = argLen + 1;
                }
                break;
            case STORAGE_TYPE_FLOAT:
                res = false;
#ifdef HAS_STR2_FLOAT
                res = try_str2float(argv[1], (float*)outBinData);
#endif
                break;
            case STORAGE_TYPE_DOUBLE: {
                res = false;
#ifdef HAS_STR2_DOUBLE
                double doubleValue = 0.0;
                res = try_str2double(argv[1], &doubleValue); /*Hang On here*/
                if(res) {
                    memcpy(outBinData, &doubleValue, 8);
                }
#endif
            } break;
            default:
                res = false;
                break;
            }
        } else {
            LOG_ERROR(NVRAM, "UndefId:%u", id);
            res = false;
        }

        if (outWriteLen) {
            *outWriteLen = writeLen;
        }
    }
    return res;
}


/*
 ns 1 10
 */
bool NVRAM_SetCommand(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t id = 0;
    if(1<=argc) {
        res = try_str2uint16(argv[0], &id);
        if(false == res) {
            LOG_ERROR(NVRAM, "ParseErr id %s", argv[0]);
        }else{
            LOG_INFO(NVRAM, "ID:%u", id);
        }
    }

    U8 wrData[100] = {0};
    memset(wrData, 0x00, sizeof(wrData));
    size_t writeLen = 0;
    res = NVRAM_RarseString(  id, argc, argv, wrData, &writeLen, sizeof(wrData));
    if(res) {
        res = false;
        if(0 < writeLen) {
            STD_RESULT ret = NVRAM_Set(id, wrData);
            res = EHAL_RetToRes(ret);
            if(res) {
                LOG_INFO(NVRAM, "SetOk,id:%u,%u byte!", id, writeLen);
            } else {
                LOG_ERROR(NVRAM, "SetErr,Id:%u", id);
            }
        }
    }

    if(false==res) {
        LOG_ERROR(NVRAM, "Usage: ns id data");
    }
    return res;
}

bool NVRAM_InitCommand(int32_t argc, char* argv[]) {
    bool res = false;
    STD_RESULT ret = NVRAM_Init();
    res = EHAL_RetToRes(ret);
    return res;
}

bool NVRAM_DeleteCommand(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t id = 0;
    if(1 == argc) {
        res = true;
        res = try_str2uint16(argv[0], &id);
        if(false == res) {
            LOG_ERROR(NVRAM, "ParseErr id %s", argv[0]);
        }
    }

    if(res) {
        STD_RESULT ret = NVRAM_Invalidate(id);
        res = EHAL_RetToRes(ret);
        res = log_res(NVRAM, res, "Invalidate");
    } else {
        LOG_ERROR(NVRAM, "Usage: pe ParamId");
    }
    return res;
}
