#include "auto_version_config.h"

#include "auto_version_types.h"
#include "data_utils.h"

const AutoVersionConfig_t AutoVersionConfig = {
        .filename = "version_auto.h",
        .valid = true,
};

AutoVersionHandle_t AutoVersionInstance = {
    .valid = true,
};

