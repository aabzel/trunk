#include "board_config.h"

#include "log.h"
#ifdef HAS_MIC2026
#include "mic2026_drv.h"
#endif

#ifdef HAS_USB_DEVICE
#include "usb_device.h"
#endif

#include "none_blocking_pause.h"

bool board_init(void) {
    bool res = true;
#ifdef HAS_LOG
    set_log_level(SYS,LOG_LEVEL_INFO);
#endif
    LOG_INFO(SYS,"XTall:%u Hz",XTAL_FREQ_HZ);
#ifdef HAS_PASTILDA
    set_log_level(PASTILDA,LOG_LEVEL_INFO);
#endif /**/

#ifdef HAS_KEEPASS
    set_log_level(KEEPASS,LOG_LEVEL_INFO);
#endif /**/

#ifdef HAS_USB
    set_log_level(USB,LOG_LEVEL_INFO);
    key_insert_timeout_ms = 400;
#ifdef HAS_USB_HOST
    set_log_level(USB_HOST,LOG_LEVEL_INFO);
#endif /*HAS_USB_HOST*/
    set_log_level(HID,LOG_LEVEL_INFO);
#endif /*HAS_USB*/
    return res;
}

bool keyboard_reboot(void){
    bool res = false;
    LOG_WARNING(SYS,"RebootUSBHost");
#ifdef HAS_MIC2026
    res = mic2026_set_channel_ctrl(CHANNEL_A, false);
    wait_in_loop_ms(500);
    res = mic2026_set_channel_ctrl(CHANNEL_A, true);
#endif
    return res;
}
