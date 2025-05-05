#include "end_of_block_config.h"

#include "end_of_block_types.h"
#include "data_utils.h"

const EndOfBlockConfig_t EndOfBlockConfig = {
        .filename = "",
        .valid = true,
};

EndOfBlockHandle_t EndOfBlockInstance = {
    .valid = true,
};

