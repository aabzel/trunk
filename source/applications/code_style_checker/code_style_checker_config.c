#include "code_style_checker_config.h"

#include "code_style_checker_types.h"
#include "data_utils.h"

const CodeStyleCheckerConfig_t CodeStyleCheckerConfig = {
        .filename = "",
        .valid = true,
};

CodeStyleCheckerHandle_t CodeStyleCheckerInstance = {
    .valid = true,
};

