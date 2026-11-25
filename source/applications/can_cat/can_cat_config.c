#include "can_cat_config.h"

#include "data_utils.h"

const CanCatConfig_t CanCatConfig[] = {
    {
        .num = 1,
        .valid = true,
        .name = "CAN_CAT1",
    },
};

CanCatHandle_t CanCatInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};


COMPONENT_GET_CNT(CanCat, can_cat)
