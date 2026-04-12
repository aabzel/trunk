#ifndef LITTLE_FS_TYPES_H
#define LITTLE_FS_TYPES_H

#include "std_includes.h"
#include "little_fs_const.h"
#include "lfs.h"

#ifdef HAS_LITTLE_FS_CUSTOM
#include "little_fs_custom_types.h"
#else
#define LITTLE_FS_CUSTOM_VARIABLES
#endif

#define LITTLE_FS_CONNON_VARIABLES                     \
    uint32_t base_address;                             \
    struct lfs_file_config file_config;                \
    struct lfs_config cfg;                             \
    char* name;                                        \
    uint8_t num;                                       \
    bool valid;

typedef struct {
    LITTLE_FS_CONNON_VARIABLES
}LittleFsConfig_t;

typedef struct {
    LITTLE_FS_CONNON_VARIABLES
    LITTLE_FS_CUSTOM_VARIABLES
    bool init;

    lfs_t lfs;
    lfs_file_t file;
    uint32_t spin;
}LittleFsHandle_t;



#endif /* LITTLE_FS_TYPES_H */
