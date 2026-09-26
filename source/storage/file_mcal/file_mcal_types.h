#ifndef FILE_MCAL_TYPES_H
#define FILE_MCAL_TYPES_H

#include "std_includes.h"
#include "file_mcal_const.h"

#ifdef HAS_FILE_CUSTOM
#include "file_mcal_types_custom.h"
#else
#define FILE_MCAL_CUSTOM_VARIABLES
#endif

typedef union {
    uint16_t word;
    struct {
        uint16_t num:5; /*0... 31 Code 0x1F means all instanced */
        uint16_t file_system:11; /* see enum FileSystem_t for variants */
    };
} FileSystemType_t;
/*
  { .file_system = FILE_SYS_FAT_FS, .num = 1, },
*/

#define FILE_MCAL_COMMON_VARIABLES                      \
    uint8_t num;         /*File system number*/         \
    char* name;                                         \
    FileSystemType_t fileSystem;                        \
    bool valid;

typedef struct {
    FILE_MCAL_COMMON_VARIABLES
}FileMcalConfig_t;

typedef struct {
    FILE_MCAL_COMMON_VARIABLES
    FILE_MCAL_CUSTOM_VARIABLES
    bool init;
    char file_name[80];
    FileState_t state;
    uint32_t read_error_cnt;
    uint32_t write_error_cnt;
    uint32_t write_total;
    uint32_t read_total;
    uint32_t spin;
}FileMcalHandle_t;


#endif /* FILE_MCAL_TYPES_H */
