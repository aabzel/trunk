#include "set_config.h"

#include <stddef.h>

#include "data_utils.h"

const SetConfig_t SetConfig[] = {
    {
    	    .num=1,
    	    .nvram_num=2,
    	    .valid=true,
    },

};

SetItem_t SetItem[] = {
    {
        .num = 1,
        .init = false,
        .valid = true,
    },
};


COMPONENT_GET_CNT(Set, set)

