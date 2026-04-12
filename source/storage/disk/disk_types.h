#ifndef DISK_TYPES_H
#define DISK_TYPES_H

#include "std_includes.h"
#include "disk_const.h"
#include "interfaces_types.h"

#ifdef HAS_FAT_FS
#include "integer.h"
/* Status of Disk Functions */
typedef BYTE DSTATUS;
#endif

#define DISK_COMMON_VARIABLES                           \
    char* name;                                         \
    InterfaceType_t inter_face;                         \
    uint32_t block_size;                                \
    uint8_t num;                                        \
    bool valid;

typedef struct {
    DISK_COMMON_VARIABLES
}DiskConfig_t;

typedef struct {
    DISK_COMMON_VARIABLES
    bool init;
    uint32_t spin;
}DiskHandle_t;


#endif /* DISK_TYPES_H */
