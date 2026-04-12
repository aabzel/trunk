#ifndef FAT_FS_TYPES_H
#define FAT_FS_TYPES_H

#include "std_includes.h"
#include "fat_fs_const.h"
#include "ff.h"

#ifndef HAS_FAT_FS
#error "+HAS_FAT_FS"
#endif

typedef union {
    uint32_t dword;
    struct {
        uint32_t second :5;      /*bit:4:0    (Second/2) (0..29, e.g. 25 for 50)*/
        uint32_t minute :6;      /*bit:10:5   Minute (0..59)*/
        uint32_t hour :5;        /*bit:15:11  Hour (0..23)*/
        uint32_t day_of_month:5; /*bit:20:16  Day of the month (1..31)*/
        uint32_t month :4;       /*bit:24:21  Month (1..12)*/
        uint32_t year :7;        /*bit:31:25  Year origin from the 1980 (0..127, e.g. 37 for 2017) */
    };
}FatFsTime_t;

#define FAT_FS_CONNON_VARIABLES                        \
    char* name;                                        \
    uint8_t num;                                       \
    uint8_t disk_num;                                       \
    bool valid;

typedef struct {
    FAT_FS_CONNON_VARIABLES
}FatFsConfig_t;

typedef struct {
    FAT_FS_CONNON_VARIABLES
    bool init;
    uint32_t spin;
    char path[100];
    char dirr_name[100];
    FIL file;
    FATFS fileSystem;
    FILINFO FileInfo;
    DIR Dir;
}FatFsHandle_t;


#endif /* FAT_FS_TYPES_H */
