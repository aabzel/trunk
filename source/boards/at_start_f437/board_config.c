#include "board_config.h"

#include "log.h"
#ifdef HAS_I2S_FULL_DUPLEX
#include "i2s_full_duplex.h"
#endif

#include "board_const.h"

#ifdef HAS_BOARD_INFO
#include "array.h"

const BoardConfig_t BoardConfig = {
    .name = "AT_START_F437",
    .xtall_freq_hz = XTALL_FREQ_HZ,

};

const Wire_t Wires[] = {};

uint32_t wires_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(Wires);
    return cnt;
}
#endif

bool board_init(void) {
    bool res = true;
    LOG_WARNING(SYS, "BoardInit");
#ifdef HAS_LOG
    set_log_level(SYS, LOG_LEVEL_INFO);
#endif
#ifdef HAS_BOARD_INFO
    LOG_INFO(SYS, "BoardName:[%s]", BoardConfig.name);
    LOG_INFO(SYS, "XTall:%u Hz", BoardConfig.xtall_freq_hz);
#endif

#ifdef HAS_I2S_FULL_DUPLEX
    res = i2s_full_duplex_ctrl(1, true);
#endif
    /*Run board detect. Did we really start on TeraTest?*/
    return res;
}
