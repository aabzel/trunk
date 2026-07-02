#ifndef FAT_FS_CONST_H
#define FAT_FS_CONST_H

#include "time_mcal.h"
#include "fat_fs_dep.h"

#define FAT_FS_VERSION "2"
#define FAT_FS_PERIOD_US MSEC_2_USEC(500)

typedef enum {
    MOUNT_DELAYED = 0,
    MOUNT_IMMEDIATELY = 1,
} MountOpt_t;

#endif /* FAT_FS_CONST_H */
