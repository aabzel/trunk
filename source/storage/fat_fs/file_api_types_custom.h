#ifndef FILE_API_TYPES_CUSTOM_H
#define FILE_API_TYPES_CUSTOM_H

#include "ff.h"

#define FILE_API_CUSTOM_VARIABLES       \
    DIR FatFsDir;                       \
    char path[100];                     \
    char dirr_name[100];          \
    FIL FatFsFile;                \
    FATFS FatFsFileSystem;        \
    FILINFO FatFsFileInfo;


#endif /*FILE_API_TYPES_CUSTOM_H*/
