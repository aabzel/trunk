#include "board_config.h"

#include "data_utils.h"
#include "log.h"
#include "board_black_pill_v2_0.h"
#include "debugger.h"

#ifdef HAS_BOARD_INFO
#include "board_types.h"

const BoardConfig_t BoardConfig = {
    .volt_id_pad = {.port=PORT_UNDEF, .pin=0,},
    .volt_id = 0.0,
    .name = BOARD_NAME,
    .xtall_freq_hz = XTALL_FREQ,
};

const Wire_t Wires[] = {
};

uint32_t wires_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(Wires);
    return cnt;
}
#endif /*HAS_BOARD_INFO*/

bool board_init(void) {
    bool res = true;
#if (25000000==HSE_VALUE)
#else
#error Wrong external quartz value
#endif

    ASSERT_CRITICAL(25000000==HSE_VALUE);
    set_log_level(BOARD, LOG_LEVEL_INFO);
    LOG_WARNING(BOARD,"Init");
#ifdef HAS_BOARD_INFO
    LOG_INFO(BOARD,"XTall: %u Hz", BoardConfig.xtall_freq_hz);
    LOG_INFO(BOARD,"BoardName: [%s]", BoardConfig.name);
#endif
    return res;
}

