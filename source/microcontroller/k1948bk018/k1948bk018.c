#include "k1948bk018.h"

#include "microcontroller.h"
#include "boot_const.h"

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_PINS
const PinData_t PinConfig[]={0};
#endif

bool mcu_init(void) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(SYS,"Init,MCU:%s",MCU_NAME);
#endif
    res = true;
    return res;
}

#ifdef HAS_PINS
uint16_t pin_get_cnt(void) {
    return 0xFFFF;
}
#endif


bool mik32_launch_eeprom(void) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(SYS,"LaunchFromEeprom");
#endif

#ifdef HAS_PARAM
#ifdef HAS_BOOTLOADER
    uint32_t start_addr = ROM_START;
    res = param_set(PAR_ID_APP_START,(void*) &start_addr);
#endif
#endif

#ifdef HAS_PARAM
    uint8_t bootloader_cnt = 0;
    res = param_set(PAR_ID_BOOT_CNT,(void*) &bootloader_cnt);

    BootCmd_t command = BOOT_CMD_LAUNCH_APP;
    res=param_set(PAR_ID_BOOT_CMD,(void*) &command) && res;
#endif

    return res;
}
