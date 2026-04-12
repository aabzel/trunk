#include "interrupt_config.h"


#ifdef HAS_DATA_MISC
#include "data_utils.h"
#endif


const InterruptConfig_t InterruptConfig[] ={

};


uint32_t interrupt_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(InterruptConfig);
    return cnt;

}
