#include "file_api_config.h"

#include "data_utils.h"

const FileApiConfig_t FileApiConfig[] = {
    {
        .num = 1,
        .valid = true,
        .name = "FILE_API1",
    },

    {
        .num = 2,
        .valid = true,
        .name = "FILE_API2",
    },
};

FileApiHandle_t FileApiInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },

};

COMPONENT_GET_CNT(FileApi, file_api)


