#ifndef STORE_FS_TYPES_H
#define STORE_FS_TYPES_H

#include "std_includes.h"
#include "store_fs_const.h"
#include "storage_const.h"

#ifdef HAS_STORE_FS_CUSTOM
#include "store_fs_custom_types.h"
#else
#define STORE_FS_CUSTOM_VARIABLES
#endif

typedef struct {
    uint8_t num;
    bool valid;
}StoreFsInfo_t;

#define STORE_FS_CONNON_VARIABLES                      \
    char* name;                                        \
    uint8_t num;                                       \
    uint8_t fs_num;                                    \
    StorageVariat_t storage_type;                      \
    bool valid;

typedef struct {
    STORE_FS_CONNON_VARIABLES
}StoreFsConfig_t;

typedef struct {
    STORE_FS_CONNON_VARIABLES
    STORE_FS_CUSTOM_VARIABLES
    bool init;
    uint32_t spin;
}StoreFsHandle_t;


#endif /* STORE_FS_TYPES_H */
