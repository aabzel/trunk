#include "file_mcal_config.h"

#include "data_utils.h"

const FileMcalConfig_t FileMcalConfig[] = {
    {
        .num = FILE_MCAL_READ,
        .fileSystem = {
                          .num = 1,
                          .file_system = FILE_SYS_POSIX_API,
                      },
        .name = "Read",
        .valid = true,
    },

    {
        .num = FILE_MCAL_WRITE,
        .fileSystem = {
                          .num = 1,
                          .file_system = FILE_SYS_POSIX_API,
                      },
        .name = "Write",
        .valid = true,
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


