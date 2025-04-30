#include "board_config.h"

#include "data_utils.h"
#include "log.h"
#include "board_nucleo_f446re.h"

#ifdef HAS_BOARD_INFO
#include "board_types.h"

const BoardConfig_t BoardConfig = {
    .volt_id_pad = {.port=PORT_UNDEF, .pin=0,},
    .volt_id = 0.0,
    .name = BOARD_NAME,
    .xtall_freq_hz = XTALL_FREQ_HZ,
};

const Wire_t Wires[] = {
		/*TODO Add rest wires*/
        {.pad={.port=PORT_B, .pin=10}, .wire_name="I2S2_CK", .silk="D6", .conn={ .designator="CN", .num=10, .pin=25,} },
        {.pad={.port=PORT_C, .pin=1}, .wire_name="I2S2_SD", .silk="A4", .conn={ .designator="CN", .num=7, .pin=36,} },
        {.pad={.port=PORT_C, .pin=7}, .wire_name="-", .silk="D9", .conn={ .designator="CN", .num=5, .pin=2,} },
        {.pad={.port=PORT_A, .pin=5}, .wire_name="-", .silk="LD2", .conn={ .designator="CN", .num=5, .pin=6,} },
        {.pad={.port=PORT_A, .pin=6}, .wire_name="I2S2_MCK", .silk="D12", .conn={ .designator="CN", .num=10, .pin=13,} },
        {.pad={.port=PORT_B, .pin=12}, .wire_name="I2S2_WS", .silk="--", .conn={ .designator="CN", .num=10, .pin=16,} },
        {.pad={.port=PORT_B, .pin=6}, .wire_name=" ", .silk="D10", .conn={ .designator="CN", .num=10, .pin=17,} },
        {.pad={.port=PORT_B, .pin=7}, .wire_name=" ", .silk="--", .conn={ .designator="CN", .num=7, .pin=21,} },
};

uint32_t wires_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(Wires);
    return cnt;
}
#endif /*HAS_BOARD_INFO*/

bool board_init(void) {
    bool res = true;
    set_log_level(BOARD, LOG_LEVEL_INFO);
    LOG_WARNING(BOARD,"Init");
#ifdef HAS_BOARD_INFO
    LOG_INFO(BOARD,"XTall: %u Hz", BoardConfig.xtall_freq_hz);
    LOG_INFO(BOARD,"BoardName: [%s]", BoardConfig.name);
#endif /*HAS_BOARD_INFO*/

    return res;
}

