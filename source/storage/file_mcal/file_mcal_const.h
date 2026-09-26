#ifndef FILE_MCAL_CONST_H
#define FILE_MCAL_CONST_H

#include "file_mcal_dep.h"

#define FILE_MCAL_VERSION 4
#define FILE_MCAL_PERIOD_US 500000

typedef enum {
    FILE_SYS_UNDEF = 0,
    FILE_SYS_FAT_FS = 1,
    FILE_SYS_POSIX_API = 2,
    FILE_SYS_LITTLE_FS = 3,
}FileSystem_t;

typedef enum {
    FILE_STATE_UNDEF = 0,
    FILE_STATE_CLOSED ,
    FILE_STATE_OPEN ,
}FileState_t;



#endif /* FILE_MCAL_CONST_H */
