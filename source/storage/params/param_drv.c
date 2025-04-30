#include "param_drv.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#ifndef HAS_FLASH_FS
#error "Params need FLASH_FS"
#endif

#ifdef HAS_HAS_BOOT
#include "boot_driver.h"
#endif

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "std_includes.h"

#ifdef HAS_FLASH_FS
#include "flash_fs.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#include "param_diag.h"
#include "storage_diag.h"

static const ParamTypeSize_t TypeSizeLut[] = {
    {.type = TYPE_UINT8, .len = 1},
    {.type = TYPE_BOOL, .len = 1},
    {.type = TYPE_INT8, .len = 1},
    {.type = TYPE_UINT16, .len = 2},
    {.type = TYPE_INT16, .len = 2},
    {.type = TYPE_UINT32, .len = 4},
    {.type = TYPE_UINT32_HEX, .len = 4},
    {.type = TYPE_INT32, .len = 4},
    {.type = TYPE_UINT64, .len = 8},
    {.type = TYPE_UINT64, .len = 8},
    {.type = TYPE_INT64, .len = 8},
    {.type = TYPE_DOUBLE, .len = 8},
    {.type = TYPE_FLOAT, .len = 4},
    {.type = TYPE_STRUCT, .len = TYPE_UNDEF_LEN},    /*Any*/
    {.type = TYPE_ARRAY, .len = TYPE_UNDEF_LEN},     /*Any*/
    {.type = TYPE_STRING, .len = TYPE_UNDEF_LEN},    /*Any*/
    {.type = TYPE_OPERATION, .len = TYPE_UNDEF_LEN}, /*Any*/
};

static bool is_param_id_uniq(Id_t id) {
    bool res = false;
    uint32_t match_cnt = 0, i = 0;
    uint32_t cnt = param_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(id == ParamArray[i].id) {
            match_cnt++;
        }
    }
    if(1 == match_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

uint16_t param_get_type_len(StorageType_t type_id) {
    uint16_t len = 0;
    bool res = false;
    uint16_t i = 0;
    for(i = 0; i < ARRAY_SIZE(TypeSizeLut); i++) {
        if(type_id == TypeSizeLut[i].type) {
            res = true;
            len = TypeSizeLut[i].len;
            break;
        }
    }
    if(false == res) {
        LOG_ERROR(PARAM, "UndefLenForTypeID:%u=%s", type_id, StorageTypeToStr(type_id));
    }
    return len;
}

size_t param_get_len(Id_t param_id) {
    uint16_t len = 0;
    uint16_t i = 0;
    uint32_t cnt = param_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(param_id == ParamArray[i].id) {
            len = ParamArray[i].len;
            break;
        }
    }
    return len;
}

uint16_t param_get_real_len(Id_t id) {
    uint16_t len = 0;
    bool res = false;
    uint16_t i = 0;
    uint32_t cnt = param_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(id == ParamArray[i].id) {
            res = true;
            len = ParamArray[i].len;
            break;
        }
    }
    if(false == res) {
        LOG_ERROR(PARAM, "UndefLenForParID %u", id);
    }
    return len;
}

/*TODO: implement bin search */
StorageType_t param_get_type(Id_t id) {
    StorageType_t ret_type = TYPE_UNDEF;
    uint16_t i = 0;
    uint32_t cnt = param_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(id == ParamArray[i].id) {
            ret_type = ParamArray[i].type;
            break;
        }
    }
    return ret_type;
}

bool param_proc(void) {
    bool res = false;
    /*Syn params between flash and RAM*/
    return res;
}

#ifdef HAS_PARAM_SET
bool param_set(Id_t param_id, const void* const wrData) {
    bool res = false;
    uint16_t write_len = 0;
    // determine param type
    StorageType_t par_type = param_get_type((Id_t)param_id);
    // get data
    if(TYPE_UNDEF != par_type) {
        write_len = param_get_type_len(par_type);
        if(TYPE_UNDEF_LEN == write_len) {
            write_len = param_get_real_len(param_id);
            if(TYPE_STRING == par_type) {
                write_len = strlen((char*)wrData);
            }
        }

        if(write_len) {
            res = true;
        } else {
            LOG_ERROR(PARAM, "WrLenError");
        }
    } else {
        LOG_ERROR(PARAM, "UndefParamId %u", param_id);
        res = false;
    }

    if((res) && (0 < write_len)) {
        LOG_DEBUG(PARAM, "Id %u Type:%u Len:%u", param_id, par_type, write_len);
        /* write data to flash FS*/
        res = flash_fs_set(param_id, wrData, write_len);
        char* IdName = "?";
#ifdef HAS_PARAM_DIAG
        IdName = ParamId2Str(param_id);
#endif /*HAS_PARAM_DIAG*/
        if(res) {
            LOG_INFO(PARAM, "FlashFsWriteOk ID:%u=%s,%u byte", param_id, IdName, write_len);
        } else {
            LOG_ERROR(PARAM, "FlashFsWriteErr Id:%u=%s,len:%u byte", param_id, IdName, write_len);
        }
    } else {
        LOG_ERROR(PARAM, "LenError %d", write_len);
    }

    if(false == res) {
        LOG_ERROR(PARAM, "SetErr");
    }

    return res;
}
#endif

bool param_get(Id_t param_id, void* const out_data) {
    bool res = false;
    uint16_t len;
    /*TODO: Add is legal id check*/
    len = param_get_len(param_id);
    StorageType_t type = param_get_type(param_id);
    if(TYPE_STRING == type) {
        len = 0xFFFF;
    }
    uint16_t type_len = param_get_type_len(type);
    if(len && (out_data)) {
        uint16_t value_len = 0;
        res = flash_fs_get(param_id, out_data, len, &value_len);
        if(res) {
            if(type_len < value_len) {
                LOG_ERROR(PARAM, "ID:%u RealLenEcedsTypeLen  Real:%u Type:%u Byte", param_id, value_len, type_len);
            }
            if(value_len <= len) {
                res = true;
            } else {
                LOG_ERROR(PARAM, "LenError %u Byte", value_len);
                res = false;
            }
        } else {
            LOG_ERROR(PARAM, "GetError ID:%u", param_id);
        }
    } else {
#ifdef HAS_PARAM_DIAG
        LOG_ERROR(PARAM, "LackId: %u %s", param_id, ParamId2Str(param_id));
#endif
    }
    return res;
}

bool param_init(void) {
    bool res = true;
    bool out_res = true;
    uint32_t i = 0;
    uint32_t ok = 0;
    uint32_t err_cnt = 0;
    uint32_t cnt = param_get_cnt();
    LOG_WARNING(PARAM, "Init Cnt:%u", cnt);
    uint8_t value[512];
    for(i = 0; i < cnt; i++) {
        res = is_param_id_uniq(ParamArray[i].id);
        if(res) {
            res = param_get(ParamArray[i].id, value);
            if(res) {
                ok++;
            } else {
                LOG_WARNING(PARAM, "NoParam:%u=%s,NVRAM", ParamArray[i].id, ParamArray[i].name);
                if(ParamArray[i].default_value) {
                    uint8_t data[100] = {0};
                    res = try_str2type(ParamArray[i].default_value, ParamArray[i].type, data, sizeof(data));
                    if(res) {
                        LOG_WARNING(PARAM, "Set,ID:%u=%s:[%s]", ParamArray[i].id, ParamArray[i].name,
                                    ParamArray[i].default_value);
                        res = param_set(ParamArray[i].id, data);
                        if(res) {
                            ok++;
                            LOG_INFO(PARAM, "SetID:%uOk", ParamArray[i].id);
                        } else {
                            LOG_ERROR(PARAM, "SetID:%uErr", ParamArray[i].id);
                        }
                    } else {
                        LOG_ERROR(PARAM, "ParseDefVal:[%s]Err", ParamArray[i].default_value);
                    }
                } else {
                    LOG_ERROR(PARAM, "NoDefVal,ID:%u", ParamArray[i].id);
                    err_cnt++;
                }
            }
        } else {
            LOG_ERROR(PARAM, "Param %u is not uniq", ParamArray[i].id);
            out_res = false;
        }
    }

    if(ok) {
        LOG_INFO(PARAM, "OkCnt:%u/%u,Err:%u", ok, cnt, err_cnt);
        res = true;
    } else {
        res = false;
    }
    return out_res;
}

bool param_set_lazy(Id_t param_id, const void* const rw_data) {
    bool res = false;
    uint8_t read_data[128] = {0};
    size_t len = param_get_len(param_id);
    if(len < sizeof(read_data)) {
        res = param_get(param_id, read_data);
        if(res) {
            int ret = memcmp(rw_data, read_data, len);
            if(0 == ret) {
                LOG_INFO(PARAM, "ID%u AlreadyTheSame", param_id);
                res = true;
            } else {
                res = false;
            }
        }

        if(false == res) {
            res = param_set(param_id, rw_data);
        }
    } else {
        LOG_ERROR(PARAM, "TooBigParam");
    }

    return res;
}

bool param_invalidate(Id_t param_id) {
    bool res = false;
    LOG_ERROR(PARAM, "InValidate:%u=%s", param_id, ParamId2Str(param_id));
    res = flash_fs_invalidate((uint16_t)param_id);
    return res;
}
