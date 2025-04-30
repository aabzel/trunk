#include "watchdog_custom_diag.h"

#include "storage_const.h"
#include "mcu32_memory_map.h"
#include "debugger.h"
#include "mcal_types.h"
#include "watchdog_config.h"
#include "array.h"
#include "watchdog_custom.h"

/* see Table 135 – Watchdog Timer Module Registers*/
static const Reg32_t WatchDogRegs[]={
    {.num=1, .access=ACCESS_WRITE_ONLY, .name="KEY", .offset=0x9C, .valid=true, },
    {.num=2, .access=ACCESS_READ_WRITE, .name="CON", .offset=0x84, .valid=true, },
    {.num=3, .access=ACCESS_READ_ONLY, .name="STA", .offset=0x9C, .valid=true, },
};

bool WatchDogDiagRegConfig(const WatchDogRegConfig_t *const Reg) {
    bool res = false;
    if (Reg) {
    	uint32_t offset = ((uint32_t) Reg)-WDT_BASE_ADDRESS;
        LOG_WARNING(WATCHDOG, "CON Offset:0x%x=0x%08x",offset, Reg->dword);
        LOG_INFO(WATCHDOG, "PRELOAD:%u", Reg->PRELOAD);
        LOG_INFO(WATCHDOG, "PRESCALE:%u=Div:%u", Reg->PRESCALE,WatchDogPrescalerCodeToDivider(Reg->PRESCALE));
        LOG_INFO(WATCHDOG, "RES:%u", Reg->RES);
        res = true;
    }
    return res;
}

bool WatchDogDiagRegStatus(const WatchDogRegStatus_t *const Reg) {
    bool res = false;
    if (Reg) {
    	uint32_t offset = ((uint32_t) Reg)-WDT_BASE_ADDRESS;
        LOG_WARNING(WATCHDOG, "STA Offset:0x%x=0x%02x",offset, Reg->byte);
        LOG_INFO(WATCHDOG, "TIMERENABLED:%u", Reg->TIMERENABLED);
        LOG_INFO(WATCHDOG, "TIMERLOADING:%u", Reg->TIMERLOADING);
        LOG_INFO(WATCHDOG, "WATCHDOG_RST_FLAG:%u", Reg->WATCHDOG_RST_FLAG);
        res = true;
    }
    return res;
}


bool WatchDogDiagRegKey(const WatchDogRegKey_t *const Reg) {
    bool res = false;
    if (Reg) {
    	uint32_t offset = ((uint32_t) Reg)-WDT_BASE_ADDRESS;
        LOG_WARNING(WATCHDOG, "KEY: Offset:0x%x=0x%02x",offset, Reg->byte);
        LOG_INFO(WATCHDOG, "KEY:%u", Reg->KEY);
        res = true;
    }
    return res;
}

bool watchdog_diag_low_level(void) {
    bool res = false;
    WatchDogDiagRegConfig(   &WatchDogInstance.WATCHDOGx->CON);
    WatchDogDiagRegStatus(   &WatchDogInstance.WATCHDOGx->STA);
   // WatchDogDiagRegKey(   &WatchDogInstance.WATCHDOGx->KEY);
    return res;
}

bool watchdog_raw_reg(void) {
    bool res = false;
    uint32_t cnt  = ARRAY_SIZE(WatchDogRegs);
    res = debug_raw_reg_diag(WATCHDOG, WDT_BASE_ADDRESS, WatchDogRegs, cnt );
    return res;
}

