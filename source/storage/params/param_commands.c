#include "param_commands.h"

#include <stdio.h>
#include <string.h>

#include "convert.h"
#include "data_utils.h"
#include "flash_fs.h"
#include "log.h"
#include "param_drv.h"
#include "std_includes.h"
#include "storage_diag.h"
#include "writer_config.h"
//#include "str_utils.h"
//#include "system_diag.h"
#include "table_utils.h"

#ifdef ESP32
#define cli_printf printf
#endif

#ifndef HAS_PARAM_DIAG
#error "+HAS_PARAM_DIAG"
#endif

bool cmd_param_get(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t param_id = 0;
    if(1 == argc) {
        res = true;
        res = try_str2uint16(argv[0], &param_id);
        if(false == res) {
            LOG_ERROR(PARAM, "Unable to extract param_id %s", argv[0]);
        }
    }
    if(res) {
        uint16_t i = 0;
        char valStr[80] = "";
        static const table_col_t cols[] = {{5, "id"}, {14, "name"}, {5, "len"}, {12, "val"}, {17, "name"}};
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        for(i = 0; i < param_get_cnt(); i++) {
            if(param_id == ParamArray[i].id) {
                cli_printf(TSEP);
                cli_printf(" %3u " TSEP, ParamArray[i].id);
                cli_printf(" %12s " TSEP, ParamArray[i].name);
                cli_printf(" %3u " TSEP, ParamArray[i].len);

                uint8_t value[100] = {0};
                res = param_get(ParamArray[i].id, value);
                if(res) {
                    res = DataToValStrBuff(value, param_get_len(ParamArray[i].id), ParamArray[i].type, valStr,
                                           sizeof(valStr));
                } else {
                    strncpy(valStr, "lack", sizeof(valStr));
                }

                cli_printf(" %10s " TSEP, valStr);
                cli_printf(" %s " TSEP, param_val2str(ParamArray[i].id, value, sizeof(value)));
                cli_printf(CRLF);
            }
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    } else {
        LOG_ERROR(PARAM, "Usage: pg ParamId");
    }
    return res;
}

bool cmd_param_default(int32_t argc, char* argv[]) {
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
        res = param_default(keyWord1, keyWord2);
    } else {
        LOG_ERROR(PARAM, "Usage: pdef keyWord1 keyWord2");
    }
    return res;
}

bool cmd_param_diag(int32_t argc, char* argv[]) {
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
        res = param_diag(keyWord1, keyWord2);
    } else {
        LOG_ERROR(PARAM, "Usage: pd keyWord1 keyWord2");
    }
    return res;
}

bool cmd_param_set(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        res = true;
        uint8_t wrData[100] = {0};
        memset(wrData, 0x00, sizeof(wrData));
        uint32_t write_len = 0;
        uint16_t param_id = 0;
        if(res) {
            res = try_str2uint16(argv[0], &param_id);
            if(false == res) {
                LOG_ERROR(PARAM, "Unable to extract param_id %s", argv[0]);
            }
        }
        // determine param type
        StorageType_t par_type = param_get_type((Id_t)param_id);
        // get data
        if(TYPE_UNDEF != par_type) {
            // write_len = param_get_type_len(  par_type);
            res = false;
            uint16_t arg_len = 0;
            arg_len = (uint16_t)strlen((char*)argv[1]);
            switch(par_type) {
            case TYPE_BOOL:
            case TYPE_UINT8:
                res = try_str2uint8(argv[1], wrData);
                if(res) {
                    write_len = 1;
                }
                break;
            case TYPE_INT8:
                res = try_str2int8(argv[1], (int8_t*)wrData);
                if(res) {
                    write_len = 1;
                }
                break;
            case TYPE_UINT16:
                res = try_str2uint16(argv[1], (uint16_t*)wrData);
                if(res) {
                    write_len = 2;
                }
                break;
            case TYPE_INT16:
                res = try_str2int16(argv[1], (int16_t*)wrData);
                if(res) {
                    write_len = 2;
                }
                break;
            case TYPE_UINT32:
            case TYPE_UINT32_HEX:
                res = try_str2uint32(argv[1], (uint32_t*)wrData);
                if(res) {
                    write_len = 4;
                }
                break;
            case TYPE_INT32:
                res = try_str2int32(argv[1], (int32_t*)wrData);
                if(res) {
                    write_len = 4;
                }
                break;
            case TYPE_UINT64:
                res = try_str2uint64(argv[1], (uint64_t*)wrData);
                if(res) {
                    write_len = 8;
                }
                break;
            case TYPE_INT64:
                res = try_str2int64(argv[1], (int64_t*)wrData);
                if(res) {
                    write_len = 8;
                }
                break;
            case TYPE_ARRAY:
                if(arg_len < sizeof(wrData)) {
                    res = try_str2array(argv[1], wrData, sizeof(wrData), &write_len);
                    if(false == res) {
                        strncpy((char*)wrData, argv[1], sizeof(wrData));
                        write_len = arg_len + 1;
                    }
                    res = true;
                }
                break;
            case TYPE_STRING:
                if(arg_len < sizeof(wrData)) {
                    strncpy((char*)wrData, argv[1], sizeof(wrData));
                    res = true;
                    write_len = arg_len + 1;
                }
                break;
            case TYPE_FLOAT:
                res = false;
#ifdef HAS_STR2_FLOAT
                res = try_str2float(argv[1], (float*)wrData);
                if(res) {
                    write_len = 4;
                }
#endif
                break;
            case TYPE_DOUBLE: {
                res = false;
#ifdef HAS_STR2_DOUBLE
                double double_value = 0.0;
                res = try_str2double(argv[1], &double_value); /*Hang On here*/
                if(res) {
                    memcpy(wrData, &double_value, 8);
                    write_len = 8;
                }
#endif
            } break;
            default:
                res = false;
                break;
            }
        } else {
            LOG_ERROR(PARAM, "Undef param_id %u", param_id);
            res = false;
        }

        if(res) {
            if(0 < write_len) {
                /* write data to flash FS*/
                res = param_set(param_id, wrData);
                if(res) {
                    LOG_INFO(PARAM, "SetOk id:%u,%u byte!", param_id, write_len);
                } else {
                    LOG_ERROR(PARAM, "SetErr Id:%u", param_id);
                }
            }
        } else {
            LOG_ERROR(PARAM, "LenError");
        }
    } else {
        LOG_ERROR(PARAM, "Usage: ps id data");
    }
    return res;
}

bool cmd_param_init(int32_t argc, char* argv[]) {
    bool res = false;
    res = param_init();
    return res;
}

bool cmd_param_delete(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t param_id = 0;
    if(1 == argc) {
        res = true;
        res = try_str2uint16(argv[0], &param_id);
        if(false == res) {
            LOG_ERROR(PARAM, "Unable to extract param_id %s", argv[0]);
        }
    }

    if(res) {
        res = param_invalidate(param_id);
        res = log_res(PARAM, res, "Invalidate");
    } else {
        LOG_ERROR(PARAM, "Usage: pe ParamId");
    }
    return res;
}
