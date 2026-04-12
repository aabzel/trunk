#ifndef STORE_FS_CONFIG_H
#define STORE_FS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "store_fs_types.h"

extern const StoreFsConfig_t StoreFsConfig[];
extern StoreFsHandle_t StoreFsInstance[];

uint32_t store_fs_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* STORE_FS_CONFIG_H */
