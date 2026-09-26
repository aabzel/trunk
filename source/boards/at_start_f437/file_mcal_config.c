#include "file_mcal_config.h"

#include "data_utils.h"

const FileMcalConfig_t FileMcalConfig[] = {
    {
        .num = 1,
        .valid = true,
        .name = "FILE_MCAL1",
        .fileSystem = { .file_system=FILE_SYS_FAT_FS, .num=1, },
    },
};

FileMcalHandle_t FileMcalInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(FileMcal, file_mcal)


