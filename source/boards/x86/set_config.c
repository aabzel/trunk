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

uint32_t set_get_instance_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(SetConfig);
    uint32_t cnt_ints = ARRAY_SIZE(SetItem);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
