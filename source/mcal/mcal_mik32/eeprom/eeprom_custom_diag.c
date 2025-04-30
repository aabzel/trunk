#include "eeprom_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "array_diag.h"
#include "debugger.h"
#include "eeprom_custom_types.h"
#include "eeprom_mcal.h"
#include "log.h"
#include "mcal_types.h"
#include "mcu32_memory_map.h"
#include "microcontroller_const.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

/* see Table 125 – EEPROM Controller Registers*/
static const Reg32_t EepromRegs[] = {
    {
        .num = 1,
        .access = ACCESS_READ_WRITE,
        .name = "EEDAT",
        .offset = 0x0,
        .valid = true,
    },
    {
        .num = 2,
        .access = ACCESS_READ_WRITE,
        .name = "EEA",
        .offset = 0x4,
        .valid = true,
    },
    {
        .num = 3,
        .access = ACCESS_READ_WRITE,
        .name = "EECON",
        .offset = 0x8,
        .valid = true,
    },
    {
        .num = 4,
        .access = ACCESS_READ_WRITE,
        .name = "EESTA",
        .offset = 0xC,
        .valid = true,
    },
    {
        .num = 5,
        .access = ACCESS_READ_ONLY,
        .name = "EERB",
        .offset = 0x10,
        .valid = true,
    },
    {
        .num = 7,
        .access = ACCESS_READ_WRITE,
        .name = "EEADJ",
        .offset = 0x14,
        .valid = true,
    },
    {
        .num = 6,
        .access = ACCESS_READ_WRITE,
        .name = "NCYCRL",
        .offset = 0x18,
        .valid = true,
    },
    {
        .num = 8,
        .access = ACCESS_READ_WRITE,
        .name = "NCYCEP1",
        .offset = 0x1C,
        .valid = true,
    },
    {
        .num = 8,
        .access = ACCESS_READ_WRITE,
        .name = "NCYCEP2",
        .offset = 0x20,
        .valid = true,
    },
};

bool eeprom_raw_reg(void) {
    bool res = false;
    uint32_t cnt = ARRAY_SIZE(EepromRegs);
    res = debug_raw_reg_diag(EEPROM, EEPROM_REGS_BASE_ADDRESS, EepromRegs, cnt);
    return res;
}

extern unsigned long __TEXT_START__;
bool eeprom_custum_diag(void) {
    bool res = true;
    cli_printf(CRLF "__TEXT_START__ 0x%x" CRLF, &__TEXT_START__);
    return res;
}

bool eeprom_dump(void) {
    bool res = true;
    LOG_INFO(EEPROM, "Dump:%s", EepromConfigToStr(&EepromConfig));
    uint8_t* buff = (uint8_t*)EepromConfig.start;
    res = print_hex(buff, EepromConfig.size);
#if 0
    res = print_mem(buff,  EepromConfig.size, true, true, true, true);
#endif
    return res;
}

bool eeprom_diag(void) {
    bool res = true;
    uint8_t* base = ROM_START;
    float usage_pec = 0.0;
    uint32_t spare = 0;
    uint32_t busy = 0;
    res = eeprom_scan(base, ROM_SIZE, &usage_pec, &spare, &busy);
    LOG_INFO(EEPROM, "Spare:%u, Busy:%u, Usage:%f", spare, busy, usage_pec);
    return res;
}
