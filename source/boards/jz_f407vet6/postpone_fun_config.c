#include "postpone_fun_config.h"

#include "data_utils.h"
#include "log.h"

#ifdef HAS_STORE_FS
#include "store_fs.h"
#endif

#ifdef HAS_ADC
#include "adc_mcal.h"
#endif

#ifdef HAS_CAN
#include "can_mcal.h"
#endif

static bool fun1(void) {
    bool res = true;
    LOG_INFO(POSTPONE_FUN,"Start:%s",__FUNCTION__);
#ifdef HAS_CAN_CUSTOM
    res = can_rx_all(1);
#endif
    //res = log_level_time_stamp(false);
    return res;
}

static bool fun2(void){
    bool res = true;
    LOG_INFO(POSTPONE_FUN,"Start:%s",__FUNCTION__);
#ifdef HAS_CAN_CUSTOM
    res = can_rx_all(2);
#endif
    return res;
}

static bool fun3_app_loaded_fine(void) {
    bool res = true;
    (void) res;
    LOG_INFO(GENERIC, "AppLoadedFine!");
#ifdef HAS_STORE_FS
    uint8_t boot_cnt = 0;
    res = store_fs_set(PAR_ID_BOOT_CNT, (void*)&boot_cnt);
    log_info_res(GENERIC, res,  "AppLoadedFineSave");
#endif
    return res;
}

#ifdef HAS_ADC
static bool adc1_start(void){
    bool res = true;
    LOG_INFO(POSTPONE_FUN,"Start:%s",__FUNCTION__);
    res = adc_start(1);
    return res;
}
#endif


/*constant compile-time known settings*/
const PostponeFunConfig_t PostponeFunConfig[] = {
    { .num = 1, .name = "fun1", .call_back = fun1,  .valid = true, .up_time_s = 5.0, },
#ifdef HAS_ADC
    { .num = 2, .name = "Adc1Start", .call_back = adc1_start,   .valid = true, .up_time_s = 3.0, },
#endif
    { .num = 3, .name = "fun3_app_loaded_fine", .call_back = fun3_app_loaded_fine,  .valid = true, .up_time_s = 15.0, },
    { .num = 4, .name = "fun2", .call_back = fun2,   .valid = true, .up_time_s = 4.0, },
};

PostponeFunHandle_t PostponeFunInstance[] = {
    {  .num = 1, .valid = true, },
#ifdef HAS_ADC
    {  .num = 2, .valid = true, },
#endif
    {  .num = 3, .valid = true, },
    {  .num = 4, .valid = true, },
};

COMPONENT_GET_CNT(PostponeFun, postpone_fun)
