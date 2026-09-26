#include "board_config.h"

#include "scheduler_mcal.h"

#ifdef HAS_LOG
#include "log.h"
#endif

const Wire_t Wires[] = {
};

bool board_init(void) {
    bool res = true;
#ifdef HAS_LOG
    set_log_level(SYS, LOG_LEVEL_INFO);
    LOG_INFO(SYS,"XTall: %u Hz", XTAL_FREQ_HZ);
#endif
    return res;
}

uint32_t wires_get_cnt(void){
    return 0;
}

bool board_boost(bool on_off) {
    bool res = true;
    if(on_off) {
        res = scheduler_task_ctrl(  1, TASK_DASHBOARD, false);
        res = scheduler_task_ctrl(  1, TASK_SSD1306, false);
        res = scheduler_task_ctrl(  1, TASK_EXT_INT, false);
        res = scheduler_task_ctrl(  1, TASK_INCREMENTAL_ENCODER, false);
        res = scheduler_task_ctrl(  1, TASK_INCREMENTAL_ENCODER_SHOW, false);
        res = scheduler_task_ctrl(  1, TASK_RUNNING_LINE, false);
    }else{
        res = scheduler_task_ctrl(  1, TASK_DASHBOARD, true);
        res = scheduler_task_ctrl(  1, TASK_SSD1306, true);
        res = scheduler_task_ctrl(  1, TASK_EXT_INT, true);
        res = scheduler_task_ctrl(  1, TASK_INCREMENTAL_ENCODER, true);
        res = scheduler_task_ctrl(  1, TASK_INCREMENTAL_ENCODER_SHOW, true);
        res = scheduler_task_ctrl(  1, TASK_RUNNING_LINE, true);
    }
    return res;
}



