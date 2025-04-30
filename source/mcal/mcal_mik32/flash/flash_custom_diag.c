#include "flash_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "debugger.h"
#include "flash_custom_types.h"
#include "flash_mcal.h"
#include "log.h"
#include "mcal_types.h"
#include "mcu32_memory_map.h"
#include "microcontroller_const.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

extern unsigned long __TEXT_START__;
bool flash_custum_diag(void) {
    bool res = true;
    cli_printf(CRLF "__TEXT_START__ 0x%x" CRLF, &__TEXT_START__);
    return res;
}

bool flash_external_diag(void) {
    bool res = true;
    uint8_t* base = EXT_ROM_START;
    float usage_pec = 0.0;
    uint32_t spare = 0;
    uint32_t busy = 0;
    res = flash_scan(base, EXT_ROM_SIZE, &usage_pec, &spare, &busy);
    LOG_INFO(LG_FLASH, "Spare:%u, Busy:%u, Usage:%f", spare, busy, usage_pec);
    return res;
}
