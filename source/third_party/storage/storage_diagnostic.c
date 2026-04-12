#include "storage_diagnostic.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
//#include <time.h>

#include "common_diag.h"
#include "storage_constants.h"
#include "data_types.h"
#include "general_macros.h"
#include "general_types.h"
#include "log.h"
#include "time_diag.h"

#define STORAGE_INFO_1_BYTE                                                      \
    {.type=STORAGE_TYPE_UINT8,  .typeSize=1,  .typeName="U8", .valid=TRUE,},   \
    {.type=STORAGE_TYPE_INT8,  .typeSize=1,  .typeName="i8", .valid=TRUE,},   \
    {.type=STORAGE_TYPE_BOOL,  .typeSize=1,  .typeName="Bool", .valid=TRUE,},

#define STORAGE_INFO_2_BYTE                                                      \
    {.type=STORAGE_TYPE_UINT16,  .typeSize=2,  .typeName="U16", .valid=TRUE,},     \
    {.type=STORAGE_TYPE_INT16,  .typeSize=2,  .typeName="i16", .valid=TRUE,},


#define STORAGE_INFO_4_BYTE                                                      \
    {.type=STORAGE_TYPE_FLOAT,  .typeSize=4,  .typeName="Float", .valid=TRUE,},    \
    {.type=STORAGE_TYPE_INT32,  .typeSize=4,  .typeName="u32", .valid=TRUE,},    \
    {.type=STORAGE_TYPE_UINT32,  .typeSize=4,  .typeName="u32", .valid=TRUE,},    \
    {.type=STORAGE_TYPE_UINT32_HEX,  .typeSize=4,  .typeName="u32_hex", .valid=TRUE,},

#define STORAGE_INFO_8_BYTE      \
    {.type=STORAGE_TYPE_DOUBLE,  .typeSize=8,  .typeName="Double", .valid=TRUE,},     \
    {.type=STORAGE_TYPE_UINT64,  .typeSize=8,  .typeName="u64", .valid=TRUE,},     \
    {.type=STORAGE_TYPE_INT64,  .typeSize=8,  .typeName="i64", .valid=TRUE,},

#define STORAGE_INFO_COMPLEX_TYPES     \
    {.type=STORAGE_TYPE_ARRAY,  .typeSize=0xFF,  .typeName="Array", .valid=TRUE,},    \
    {.type=STORAGE_TYPE_TIME_DATE,  .typeSize=0xFF,  .typeName="Time", .valid=TRUE,},    \
    {.type=STORAGE_TYPE_STRUCT,  .typeSize=0xFF,  .typeName="Struct", .valid=TRUE,},    \
    {.type=STORAGE_TYPE_STRING,  .typeSize=0xFF,  .typeName="Str", .valid=TRUE,},

static const STORAGE_INFO STORAGE_Info[]={
    STORAGE_INFO_1_BYTE \
    STORAGE_INFO_2_BYTE \
    STORAGE_INFO_4_BYTE \
    STORAGE_INFO_8_BYTE \
    STORAGE_INFO_COMPLEX_TYPES
};


STORAGE_INFO* STORAGE_GetInfo(STORAGE_TYPE type) {
    STORAGE_INFO* Info=NULL;
    U32 i=0;
    U32 cnt= SIZE_OF_ARRAY(STORAGE_Info);
    for(i=0; i<cnt; i++){
        if(STORAGE_Info[i].valid){
            if(type==STORAGE_Info[i].type){
                Info=&STORAGE_Info[i];
                break;
            }
        }
    }
    return Info;
}

const char* STORAGE_AccessToStr(STORAGE_ACCESS access) {
    const char* name = "?";
    switch((U8)access) {
    case STORAGE_ACCESS_READ_ONLY:
        name = "RO";
        break;
    case STORAGE_ACCESS_READ_WRITE:
        name = "RW";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}


const char* STORAGE_TypeToStr(STORAGE_TYPE type) {
    const char* name = "?";

    STORAGE_INFO* Info = STORAGE_GetInfo(type);
    if(Info){
        name = Info->typeName;
    }
    return name;
}

/*TODO: Test it
 *
 * buff [in]
 * value_len [in]
 * type [in]
 * outStr [out]
 * str_size [in]
 * */

U8 STORAGE_DataToStrLine(const U8* const buff,
                           U32 value_len,
                           STORAGE_TYPE type,
                           char* const outStr,
                           U32 str_size) {
    U8 ret = false;

    if(buff) {
        if(value_len) {
            if(outStr) {
                if(str_size) {
                    ret = true;
                }
            }
        }
    }

    if(ret) {
        ret = false;
        switch(type) {
        case STORAGE_TYPE_ARRAY:
            if((2 * value_len) < str_size) {
                ret = hex2ascii(buff, value_len, (U8*)outStr, str_size);
            }
            break;

        case STORAGE_TYPE_TIME_DATE: {
#ifdef HAS_TIME_DIAG
            struct tm time_date = {0};
            memcpy(&time_date, buff, sizeof(struct tm));
            ret = TimeDate2Str(&time_date, outStr, str_size);
            if(ret) {

            } else {
                LOG_ERROR(STORAGE, "ConvertErr");
            }
#endif /*HAS_TIME_DIAG*/
        } break;
        case STORAGE_TYPE_BOOL:
        case STORAGE_TYPE_UINT8:
            if(1 == value_len) {
                //  Type8Union_t un8;
                //  memcpy(&un8.u8, value, sizeof(Type8Union_t));
                snprintf(outStr, str_size, "%3u", *buff);
                ret = true;
            }
            break;

        case STORAGE_TYPE_INT8:
            if(1 == value_len) {
                Type8Union_t un8;
                memcpy(&un8, buff, sizeof(Type8Union_t));
                snprintf(outStr, str_size, "%3d", un8.s8);
                ret = true;
            }
            break;

        case STORAGE_TYPE_UINT16:
            if(2 == value_len) {
                Type16Union_t un16;
                memcpy(&un16, buff, sizeof(Type16Union_t));
                snprintf(outStr, str_size, "%" PRIu16, un16.u16);
                ret = true;
            }
            break;
        case STORAGE_TYPE_INT16:
            if(2 == value_len) {
                Type16Union_t un16 = {0};
                memcpy(&un16, buff, sizeof(Type16Union_t));
                snprintf(outStr, str_size, "%" PRId16, un16.s16);
                ret = true;
            }
            break;
        case STORAGE_TYPE_UINT32:
            if(4 == value_len) {
                Type32Union_t un32;
                memcpy(&un32, buff, sizeof(Type32Union_t));
                snprintf(outStr, str_size, "%" PRIu32, un32.u32);
                ret = true;
            }
            break;
        case STORAGE_TYPE_UINT32_HEX:
            if(4 == value_len) {
                Type32Union_t un32;
                memcpy(&un32, buff, sizeof(Type32Union_t));
                snprintf(outStr, str_size, "0x%08" PRIx32, un32.u32);
                ret = true;
            }
            break;
        case STORAGE_TYPE_INT32:
            if(4 == value_len) {
                Type32Union_t un32;
                memcpy(&un32, buff, sizeof(Type32Union_t));
                snprintf(outStr, str_size, "%" PRId32, un32.s32);
                ret = true;
            }
            break;
        case STORAGE_TYPE_UINT64:
            if(8 == value_len) {
                Type64Union_t un64;
                memcpy(&un64, buff, sizeof(Type64Union_t));
                snprintf(outStr, str_size, "%" PRIu64, un64.u64);
                ret = true;
            }
            break;
        case STORAGE_TYPE_INT64:
            if(8 == value_len) {
                Type64Union_t un64 = {0};
                memcpy(&un64, buff, sizeof(Type64Union_t));
                snprintf(outStr, str_size, "%" PRId64, un64.s64);
                ret = true;
            }
            break;
        case STORAGE_TYPE_STRING:
            if(strlen((char*)buff) < str_size) {
                snprintf(outStr, str_size, "%s", buff);
                ret = true;
            }
            break;
        case STORAGE_TYPE_STRUCT:
            if(strlen((char*)buff) < str_size) {
                ret = hex2ascii(buff, value_len, (U8*)outStr, str_size);
            }
            break;

        case STORAGE_TYPE_FLOAT:
            if(4 == value_len) {
                Type32Union_t un32;
                memcpy(&un32, buff, sizeof(Type32Union_t));
                snprintf(outStr, str_size, "%.1f", un32.f32);
                ret = true;
            }
            break;
        case STORAGE_TYPE_DOUBLE:
            if(8 == value_len) {
                Type64Union_t un64;
                memcpy(&un64, buff, sizeof(Type64Union_t));
                snprintf(outStr, str_size, "%.3f", un64.d64);
                ret = true;
            }
            break;
        default:
            ret = false;
            break;
        } /*switch*/
    }
    return ret;
}

const char* STORAGE_DataToStr(const U8* const buff, U32 size, STORAGE_TYPE type) {
    static char text[80] = {0};
    strncpy(text, "?", sizeof(text));
    if(buff) {
        if(size) {
            U8 ret = STORAGE_DataToStrLine(buff, size, type, text, sizeof(text));
            if(false == ret) {
                strncpy(text, "DataErr", sizeof(text));
            } else {
            }
        } else {
            strncpy(text, "SizeErr", sizeof(text));
        }
    } else {
        strncpy(text, "BuffErr", sizeof(text));
    }
    return text;
}
