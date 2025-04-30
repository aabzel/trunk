#include "board_config.h"

#ifdef HAS_LOG
#include "log.h"
#endif

bool board_init(void) {
    bool res = true;
#ifdef HAS_LOG
    set_log_level(SYS,LOG_LEVEL_INFO);
#endif
    LOG_INFO(SYS,"XTall: %u Hz",XTAL_FREQ_HZ);
#ifdef HAS_PASTILDA
    set_log_level(PASTILDA,LOG_LEVEL_INFO);
#endif /**/

#ifdef HAS_KEEPASS
    set_log_level(KEEPASS,LOG_LEVEL_INFO);
#endif /**/

#ifdef HAS_USB
    set_log_level(USB,LOG_LEVEL_INFO);
#ifdef HAS_USB_HOST
    set_log_level(USB_HOST,LOG_LEVEL_INFO);
#endif /*HAS_USB_HOST*/
    set_log_level(HID,LOG_LEVEL_INFO);
#endif /*HAS_USB*/
    return res;
}

