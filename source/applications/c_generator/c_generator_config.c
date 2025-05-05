#include "c_generator_config.h"

#include "c_generator_types.h"
#include "data_utils.h"

const cGeneratorConfig_t cGeneratorConfig = {
    .filename = "",
    .valid = true,
};

cGeneratorHandle_t cGeneratorInstance = {
    .valid = true,
};
