#include "postpone_fun_config.h"

#include "data_utils.h"
#include "log.h"

static bool fun1(void){
    LOG_INFO(POSTPONE_FUN,"Start:%s",__FUNCTION__);
    return true;
}

static bool fun2(void){
    LOG_INFO(POSTPONE_FUN,"Start:%s",__FUNCTION__);
    return true;
}

static bool fun3(void){
    LOG_INFO(POSTPONE_FUN,"Start:%s",__FUNCTION__);
    return true;
}


/* instances inside CommandArray must be sorted by up time!*/
static const PostponeFunCmd_t CommandArray[] = {
    {  .up_time_s=6,  .call_back = fun1, .valid = true,},
    {  .up_time_s=9,  .call_back = fun2, .valid = true,},
    {  .up_time_s=15, .call_back = fun3, .valid = true,},
};

/*constant compile-time known settings*/
const PostponeFunConfig_t PostponeFunConfig[] = {
    {
        .num = 1,
        .name = "PostponeFun1",
        .Routine = (PostponeFunCmd_t*) CommandArray,
        .line_cnt = ARRAY_SIZE(CommandArray),
        .valid = true,
    },
};

PostponeFunHandle_t PostponeFunInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t postpone_fun_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(PostponeFunConfig);
    uint32_t cnt_ints = ARRAY_SIZE(PostponeFunInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
