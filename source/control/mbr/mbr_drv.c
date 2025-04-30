#include "mbr_drv.h"

#include "std_includes.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

#ifdef HAS_BOOT
#include "boot_driver.h"
#endif

#ifdef HAS_LED
#include "led_drv.h"
#endif
#ifdef HAS_FLASH
#include "flash_config.h"
#endif

static bool mbr_init_ll(const MbrConfig_t* const Config, MbrHandle_t* const  Node){
    bool res = false;
    if(Config) {
    	if(Node) {
    		Node->boot_start_address = Config->boot_start_address;
#ifdef HAS_PARAM
    	    res = param_get(PAR_ID_BOOT_START, (uint8_t*) &boot_start_address);
#endif
    	    if(false == res) {
    	    	Node->boot_start_address = Config->boot_start_address;
    	        res = true;
    	    }
    	#ifdef HAS_LED_MONO
    	    LedMonoHandle_t* LedNode = LedMonoGetNode(LED_HEARTBEAT_ID);
    	    if(LedNode) {
    	        LedNode->mode = LED_MODE_PWM;
    	        if(false == res) {
    	            LedNode->period_ms = LED_ALARM_PERIOD_MS;
    	        } else {
    	            LedNode->period_ms = LED_HEARTBEAT_PERIOD_MS;
    	        }
    	        LedNode->duty = 50;
    	    }
    	#endif /*HAS_LED_MONO*/

    	    Node->init = true;
    	}
    }
    return res;
}

bool mbr_init(void) {
    bool res = false;
    res = mbr_init_ll(&MbrConfig, &MbrInstance);
    return res;
}

bool mbr_proc(void) {
    bool res = false;
    if(MbrInstance.init) {
        res = boot_jump_to_code(MbrInstance.boot_start_address);
    } else {
        res = mbr_init();
    }
    return res;
}
