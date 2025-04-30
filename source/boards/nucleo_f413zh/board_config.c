#include "board_config.h"

#include "data_utils.h"
#include "log.h"
#ifdef HAS_BOARD_INFO
#include "board_types.h"
#endif
#include "board_nucleo_f413zh.h"

#ifdef HAS_BOARD_INFO

const BoardConfig_t BoardConfig = {
    .volt_id_pad = {.port=PORT_UNDEF, .pin=0,},
    .volt_id = 0.0,
    .name = BOARD_NAME,
    .xtall_freq_hz = XTALL_FREQ,
};

const Wire_t Wires[] = {
        {.pad={.port=PORT_C, .pin=7}, .wire_name="-", .silk="PC7", .conn={ .designator="CN", .num=7, .pin=11,} },
        {.pad={.port=PORT_C, .pin=10}, .wire_name="-", .silk="PC10", .conn={ .designator="CN", .num=8, .pin=6,} },
        {.pad={.port=PORT_C, .pin=12}, .wire_name="-", .silk="PC12", .conn={ .designator="CN", .num=8, .pin=10,} },
        {.pad={.port=PORT_B, .pin=4}, .wire_name="-", .silk="PB4", .conn={ .designator="CN", .num=7, .pin=19,} },
        {.pad={.port=PORT_A, .pin=8}, .wire_name="-", .silk="PA8", .conn={ .designator="CN", .num=12, .pin=23,} },
        {.pad={.port=PORT_A, .pin=11}, .wire_name="USB_DP", .silk="PA11", .conn={ .designator="CN", .num=13, .pin=3,} },
        {.pad={.port=PORT_A, .pin=13}, .wire_name="TMS", .silk="PA13", .conn={ .designator="CN", .num=4, .pin=3,} },
        {.pad={.port=PORT_A, .pin=14}, .wire_name="TCK", .silk="PA14", .conn={ .designator="CN", .num=4, .pin=2,} },
        {.pad={.port=PORT_B, .pin=2}, .wire_name="BOOT1", .silk="PB2", .conn={ .designator="CN", .num=10, .pin=15,} },
        {.pad={.port=PORT_B, .pin=6}, .wire_name="", .silk="PB6", .conn={ .designator="CN", .num=10, .pin=13,} },
        {.pad={.port=PORT_C, .pin=7}, .wire_name="", .silk="PC7", .conn={ .designator="CN", .num=7, .pin=11,} },
        {.pad={.port=PORT_C, .pin=8}, .wire_name="", .silk="PC8", .conn={ .designator="CN", .num=8, .pin=2,} },
        {.pad={.port=PORT_C, .pin=11}, .wire_name="", .silk="PC11", .conn={ .designator="CN", .num=8, .pin=8,} },
        {.pad={.port=PORT_C, .pin=14}, .wire_name="X2.R", .silk="PC14", .conn={ .designator="CN", .num=11, .pin=25,} },
        {.pad={.port=PORT_C, .pin=15}, .wire_name="X2.L", .silk="PC15", .conn={ .designator="CN", .num=11, .pin=27,} },
        {.pad={.port=PORT_D, .pin=0}, .wire_name="X2.L", .silk="PD0", .conn={ .designator="CN", .num=9, .pin=25,} },
        {.pad={.port=PORT_D, .pin=1}, .wire_name="", .silk="PD1", .conn={ .designator="CN", .num=11, .pin=55,} },
        {.pad={.port=PORT_D, .pin=2}, .wire_name="", .silk="PD2", .conn={ .designator="CN", .num=8, .pin=12,} },
        {.pad={.port=PORT_D, .pin=3}, .wire_name="", .silk="PD3", .conn={ .designator="CN", .num=9, .pin=10,} },
        {.pad={.port=PORT_D, .pin=4}, .wire_name="", .silk="PD4", .conn={ .designator="CN", .num=9, .pin=8,} },
        {.pad={.port=PORT_D, .pin=10}, .wire_name="", .silk="PD10", .conn={ .designator="CN", .num=12, .pin=65,} },
        {.pad={.port=PORT_D, .pin=11}, .wire_name="", .silk="PD11", .conn={ .designator="CN", .num=12, .pin=45,} },
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
#endif
    return res;
}

