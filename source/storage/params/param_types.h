#ifndef PARAM_TYPES_H
#define PARAM_TYPES_H

#include "flash_fs_file_ids.h"
#include "storage_const.h"
#include "sys_constants.h"
#include "std_includes.h"
#include "param_constants.h"

#ifndef HAS_SYSTEM
#error "+HAS_SYSTEM"
#endif

typedef struct {
    facility_t facility;
    Id_t id;
    uint16_t len;
    StorageType_t type;
    char* name;
    char* default_value;
    bool hide;
    /*char* units*/
} ParamItem_t;

typedef struct {
    StorageType_t type;
    uint16_t len;
} ParamTypeSize_t;

#endif /* PARAM_TYPES_H  */
