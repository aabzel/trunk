#include "postpone_fun_config.h"

#include "data_utils.h"
#include "log.h"

#ifdef HAS_CAN
#include "can_mcal.h"
#endif

#include "store_fs.h"
#include "led_mono_drv.h"

static bool fun_led_off(void) {
    bool res = true;
    LOG_INFO(POSTPONE_FUN,"Start:%s",__FUNCTION__);
    led_mono_ctrl(LED_ID_CAN, false);
    led_mono_ctrl(LED_ID_ERROR, false);

    return res;
}

static bool fun1(void) {
    bool res = true;
    LOG_INFO(POSTPONE_FUN,"Start:%s",__FUNCTION__);
#ifdef HAS_CAN_CUSTOM
    res = can_rx_all(1);
#endif
  //  res = log_level_time_stamp(false);
    fun_led_off();
    return res;
}



static bool fun2(void){
    bool res = true;
    LOG_INFO(POSTPONE_FUN,"Start:%s",__FUNCTION__);
#ifdef HAS_CAN_CUSTOM
    res = can_rx_all(2);
#endif
    fun_led_off();
    return res;
}

static bool fun3_app_loaded_fine(void) {
    bool res = true;
    (void) res;
    LOG_INFO(GENERIC, "AppLoadedFine!");
#ifdef HAS_STORE_FS
    uint8_t boot_cnt = 0;
    res = store_fs_set_lazy(1, PAR_ID_BOOT_CNT, (void*)&boot_cnt);
    log_info_res(GENERIC, res,  "AppLoadedFineSave");
#endif
    fun_led_off();
    return res;
}



/*constant compile-time known settings*/
const PostponeFunConfig_t PostponeFunConfig[] = {
    { .num = 1, .name = "fun1", .call_back = fun1,  .valid = true, .up_time_s = 5.0, },
    { .num = 2, .name = "fun_led_off", .call_back = fun_led_off,   .valid = true, .up_time_s = 35.0, },
    { .num = 3, .name = "fun3_app_loaded_fine", .call_back = fun3_app_loaded_fine,  .valid = true, .up_time_s = 15.0, },
    { .num = 4, .name = "fun2", .call_back = fun2,   .valid = true, .up_time_s = 4.0, },
};

PostponeFunHandle_t PostponeFunInstance[] = {
    {  .num = 1, .valid = true, },
    {  .num = 2, .valid = true, },
    {  .num = 3, .valid = true, },
    {  .num = 4, .valid = true, },
};

COMPONENT_GET_CNT(PostponeFun, postpone_fun)
