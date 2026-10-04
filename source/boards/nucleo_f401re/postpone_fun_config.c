#include "postpone_fun_config.h"

#include "data_utils.h"
#include "log.h"
#include "esp_01.h"

static bool fun1(void) {
    bool res = true;
    LOG_INFO(POSTPONE_FUN,"Start:%s",__FUNCTION__);
    static char temp[20]={0};
    snprintf(temp,sizeof(temp),"AT");
    res=esp_01_send(1, temp, strlen(temp));
    return res;
}

static bool fun2(void) {
    bool res = true;
    LOG_INFO(POSTPONE_FUN,"Start:%s",__FUNCTION__);
    static char temp[20]={0};
    snprintf(temp,sizeof(temp),"AT+CWMODE=1");
    res=esp_01_send(1, temp, strlen(temp));
    return res;
}


static bool fun3_app_loaded_fine(void) {
    bool res = true;
    (void) res;
    LOG_INFO(GENERIC, "AppLoadedFine!");
#if 0
    uint8_t boot_cnt = 0;
    res = store_fs_set_lazy(1, PAR_ID_BOOT_CNT, (void*)&boot_cnt);
    log_info_res(GENERIC, res,  "AppLoadedFineSave");
#endif
    return res;
}

/*constant compile-time known settings*/
const PostponeFunConfig_t PostponeFunConfig[] = {
    { .num = 1, .name = "fun3_app_loaded_fine", .call_back = fun3_app_loaded_fine,  .valid = true, .up_time_s = 3.0, },
    { .num = 2, .name = "fun1", .call_back = fun1,  .valid = true, .up_time_s = 6.0, },
    { .num = 3, .name = "fun2", .call_back = fun2,   .valid = true, .up_time_s = 9.0, },
};

PostponeFunHandle_t PostponeFunInstance[] = {
    {  .num = 1, .valid = true, },
    {  .num = 2, .valid = true, },
    {  .num = 3, .valid = true, },
};

COMPONENT_GET_CNT(PostponeFun, postpone_fun)
