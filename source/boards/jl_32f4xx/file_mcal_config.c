#include "file_mcal_config.h"

#include "data_utils.h"

const FileMcalConfig_t FileMcalConfig[] = {
    {
        .num = FILE_MCAL_READ,
        .valid = true,
        .name = "Read",
        .fileSystem = { .file_system = FILE_SYS_FAT_FS, .num = 1, },
    },

    {
        .num = FILE_MCAL_WRITE,
        .valid = true,
        .name = "Write",
        .fileSystem = { .file_system = FILE_SYS_FAT_FS, .num = 1, },
    },
};

FileMcalHandle_t FileMcalInstance[] = {
    {
        .num = FILE_MCAL_READ,
        .valid = true,
    },
    {
        .num = FILE_MCAL_WRITE,
        .valid = true,
    },
};

COMPONENT_GET_CNT(FileMcal, file_mcal)
