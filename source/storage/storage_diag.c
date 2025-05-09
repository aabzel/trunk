#include "storage_diag.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "common_diag.h"
#include "data_types.h"
#include "log.h"
#include "time_diag.h"

const char* StorageAccessToStr(const StorageAccess_t access) {
    const char* name = "?";
    switch((uint8_t)access) {
    case ACCESS_READ_ONLY:
        name = "RO";
        break;
    case ACCESS_READ_WRITE:
        name = "RW";
        break;
    case ACCESS_WRITE_ONLY:
        name = "WO";
        break;
    case ACCESS_ERASE:
        name = "ER";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* StorageTypeToStr(StorageType_t type) {
    const char* name = "?";
    switch((uint8_t)type) {
    case TYPE_ARRAY:
        name = "Array";
        break;
    case TYPE_UINT8:
        name = "u8";
        break;
    case TYPE_UINT16:
        name = "u16";
        break;
    case TYPE_BOOL:
        name = "Bool";
        break;
    case TYPE_INT8:
        name = "i8";
        break;
    case TYPE_UINT32_HEX:
        name = "u32_hex";
        break;
    case TYPE_UINT32:
        name = "u32";
        break;
    case TYPE_INT16:
        name = "i16";
        break;
    case TYPE_INT32:
        name = "u32";
        break;
    case TYPE_FLOAT:
        name = "Float";
        break;
    case TYPE_STRING:
        name = "Str";
        break;
    case TYPE_INT64:
        name = "i64";
        break;
    case TYPE_UINT64:
        name = "u64";
        break;
    case TYPE_DOUBLE:
        name = "Double";
        break;
    case TYPE_STRUCT:
        name = "Struct";
        break;
    case TYPE_TIME_DATE:
        name = "Time";
        break;
    }
    return name;
}

/*TODO: Test it
 *
 * buff [in]
 * value_len [in]
 * type [in]
 * out_str [out]
 * str_size [in]
 * */

bool DataToValStrBuff(const uint8_t* const buff, size_t value_len, StorageType_t type, char* const out_str,
                      size_t str_size) {
    bool res = false;

    if(buff) {
        if(value_len) {
            if(out_str) {
                if(str_size) {
                    res = true;
                }
            }
        }
    }

    if(res) {
        res = false;
        switch(type) {
        case TYPE_ARRAY:
            if((2 * value_len) < str_size) {
                res = hex2ascii(buff, value_len, (uint8_t*)out_str, str_size);
            }
            break;

        case TYPE_TIME_DATE: {
#ifdef HAS_TIME_DIAG
            struct tm time_date = {0};
            memcpy(&time_date, buff, sizeof(struct tm));
            res = TimeDate2Str(&time_date, out_str, str_size);
            if(res) {

            } else {
                LOG_ERROR(STORAGE, "ConvertErr");
            }
#endif /*HAS_TIME_DIAG*/
        } break;
        case TYPE_BOOL:
        case TYPE_UINT8:
            if(1 == value_len) {
                //  Type8Union_t un8;
                //  memcpy(&un8.u8, value, sizeof(Type8Union_t));
                snprintf(out_str, str_size, "%3u", *buff);
                res = true;
            }
            break;

        case TYPE_INT8:
            if(1 == value_len) {
                Type8Union_t un8;
                memcpy(&un8, buff, sizeof(Type8Union_t));
                snprintf(out_str, str_size, "%3d", un8.s8);
                res = true;
            }
            break;

        case TYPE_UINT16:
            if(2 == value_len) {
                Type16Union_t un16;
                memcpy(&un16, buff, sizeof(Type16Union_t));
                snprintf(out_str, str_size, "%" PRIu16, un16.u16);
                res = true;
            }
            break;
        case TYPE_INT16:
            if(2 == value_len) {
                Type16Union_t un16 = {0};
                memcpy(&un16, buff, sizeof(Type16Union_t));
                snprintf(out_str, str_size, "%" PRId16, un16.s16);
                res = true;
            }
            break;
        case TYPE_UINT32:
            if(4 == value_len) {
                Type32Union_t un32;
                memcpy(&un32, buff, sizeof(Type32Union_t));
                snprintf(out_str, str_size, "%" PRIu32, un32.u32);
                res = true;
            }
            break;
        case TYPE_UINT32_HEX:
            if(4 == value_len) {
                Type32Union_t un32;
                memcpy(&un32, buff, sizeof(Type32Union_t));
                snprintf(out_str, str_size, "0x%08" PRIx32, un32.u32);
                res = true;
            }
            break;
        case TYPE_INT32:
            if(4 == value_len) {
                Type32Union_t un32;
                memcpy(&un32, buff, sizeof(Type32Union_t));
                snprintf(out_str, str_size, "%" PRId32, un32.s32);
                res = true;
            }
            break;
        case TYPE_UINT64:
            if(8 == value_len) {
                Type64Union_t un64;
                memcpy(&un64, buff, sizeof(Type64Union_t));
                snprintf(out_str, str_size, "%" PRIu64, un64.u64);
                res = true;
            }
            break;
        case TYPE_INT64:
            if(8 == value_len) {
                Type64Union_t un64 = {0};
                memcpy(&un64, buff, sizeof(Type64Union_t));
                snprintf(out_str, str_size, "%" PRId64, un64.s64);
                res = true;
            }
            break;
        case TYPE_STRING:
            if(strlen((char*)buff) < str_size) {
                snprintf(out_str, str_size, "%s", buff);
                res = true;
            }
            break;
        case TYPE_STRUCT:
            if(strlen((char*)buff) < str_size) {
                res = hex2ascii(buff, value_len, (uint8_t*)out_str, str_size);
            }
            break;

        case TYPE_FLOAT:
            if(4 == value_len) {
                Type32Union_t un32;
                memcpy(&un32, buff, sizeof(Type32Union_t));
                snprintf(out_str, str_size, "%.1f", un32.f32);
                res = true;
            }
            break;
        case TYPE_DOUBLE:
            if(8 == value_len) {
                Type64Union_t un64;
                memcpy(&un64, buff, sizeof(Type64Union_t));
                snprintf(out_str, str_size, "%.3f", un64.d64);
                res = true;
            }
            break;
        default:
            res = false;
            break;
        } /*switch*/
    }
    return res;
}

const char* DataToValueStr(const uint8_t* const buff, size_t size, StorageType_t type) {
    strncpy(text, "?", sizeof(text));
    if(buff) {
        if(size) {
            bool res = DataToValStrBuff(buff, size, type, text, sizeof(text));
            if(false == res) {
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

const char* StorageMemoryFrameHeaderToStr(const StorageMemoryFrameHeader_t* const Header) {
    static char lText[120] = {0};
    if(Header) {
        strcpy(lText, "");
        memset(lText, 0, sizeof(lText));
        snprintf(lText, sizeof(lText), "%sOp:%s,", lText, StorageAccessToStr(Header->operation));
        snprintf(lText, sizeof(lText), "%sAddr:0x%08x,", lText, Header->address);
        snprintf(lText, sizeof(lText), "%sSize:%u,", lText, Header->size);
    }
    return lText;
}

const char* StorageFrameHeaderToStr(const StorageFrameHeader_t* const Header) {
    static char locText[120] = {0};
    if(Header) {
        strcpy(locText, "");
        memset(locText, 0, sizeof(locText));
        snprintf(locText, sizeof(locText), "%sASIC:%u,", locText, Header->asic_num);
        snprintf(locText, sizeof(locText), "%sOp:%s,", locText, StorageAccessToStr(Header->operation));
        snprintf(locText, sizeof(locText), "%sAddr:0x%08x,", locText, Header->address);
        snprintf(locText, sizeof(locText), "%sSize:%u,", locText, Header->size);
    }
    return locText;
}
