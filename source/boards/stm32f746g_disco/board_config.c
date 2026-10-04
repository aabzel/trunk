#include "board_config.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_SEGGER_RTT
#include "segger_rtt_mcal.h"
#endif

#ifdef HAS_LED_RGB
#include "led_rgb_drv.h"
#endif

#ifdef HAS_ISO_TP
#include "iso_tp_mcal.h"
#endif

#ifdef HAS_BOARD_INFO
const Wire_t Wires[] = { };
#endif

bool board_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_INFO(SYS, "PCB:[%s],XTall:%u Hz", PCB_NAME, XTAL_FREQ_HZ);
#endif

#ifdef HAS_ISO_TP
    res = iso_tp_writer(1);
#endif

#ifdef HAS_SEGGER_RTT
    res = segger_rtt_writer(1);
#endif

    return res;
}

bool board_indicate_init_error(void) {
    bool res = true;
#ifdef HAS_LED_RGB
    res = led_rgb_set_color(1, COLOR_RED);
#endif
    return res;
}

uint32_t wires_get_cnt(void) {
    uint32_t cnt = 0;
#ifdef HAS_BOARD_INFO
    cnt = ARRAY_SIZE(Wires);
#endif
    return cnt;
}
