#include "board_config.h"

#ifdef HAS_LOG
#include "log.h"
#endif


#ifdef HAS_BOARD_INFO
#include "array.h"

const BoardConfig_t BoardConfig = {
    .name = "DUMMY_BOARD",
    .xtall_freq_hz = XTALL_FREQ_HZ,
};

const Wire_t Wires[] = {
        { .pad = {  .pin = 4, .port = GPIO_PORT_A, }, .conn = {.designator = "?", .num = 1, .pin = 1,}, .wire_name = "?", .silk="pin1",   },
};

uint32_t wires_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(Wires);
    return cnt;
}
#endif

bool board_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_WARNING(SYS, "BoardInit");
    set_log_level(SYS, LOG_LEVEL_INFO);
#endif

#ifdef HAS_BOARD_INFO
    LOG_INFO(SYS, "BoardName:[%s]", BoardConfig.name);
    LOG_INFO(SYS, "XTall:%u Hz", BoardConfig.xtall_freq_hz);
#endif

    /*Run board detect. Did we really start on  needed borad?*/
    return res;
}
