#include "postpone_fun_config.h"

#include <float.h>

#include "data_utils.h"
#include "log.h"

static bool fun1(void){
    LOG_INFO(POSTPONE_FUN,"Start:%s",__FUNCTION__);
    return true;
}



static bool reset(void){
    LOG_WARNING(POSTPONE_FUN,"Start:%s",__FUNCTION__);
    return true;
}


/*constant compile-time known settings*/
const PostponeFunConfig_t PostponeFunConfig[] = {
    {
        .num = POST_FUN_FUN1,
        .up_time_s = 6.0,
        .call_back = fun1,
        .name = "fun1",
        .valid = true,
    },
    {
        .num = POST_FUN_RESET,
        .up_time_s = FLT_MAX,
        .call_back = reset,
        .name = "Reset",
        .valid = true,
    },
};

PostponeFunHandle_t PostponeFunInstance[] = {
    {        .num = POST_FUN_FUN1,        .valid = true,    },
    {        .num = POST_FUN_RESET,        .valid = true,    },
};


COMPONENT_GET_CNT(PostponeFun, postpone_fun)
