#include "microcontroller_drv.h"

#include "compiler_const.h"
#include "microcontroller.h"
#include "std_includes.h"

#ifdef HAS_CLOCK
#include "clock_mcal.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_EEPROM
#include "eeprom_mcal.h"
#endif

#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif

#ifdef HAS_SPIFI
#include "spifi_mcal.h"
#endif

McuPhyAddress_t mcu_phy_assress_classify(const uint32_t phy_address) {
    McuPhyAddress_t phy_address_class = MCU_PHY_ADDR_UNDEF;
    (void)phy_address;
    bool res = false;
    (void)res;
#ifdef HAS_EEPROM
    res = eeprom_is_address(phy_address);
    if(res) {
        phy_address_class = MCU_PHY_ADDR_EEPROM;
    }
#endif

#ifdef HAS_SPIFI
    res = spifi_is_address(phy_address);
    if(res) {
        phy_address_class = MCU_PHY_ADDR_SPIFI;
    }
#endif

#ifdef HAS_CORE
    res = is_ram_addr(phy_address);
    if(res) {
        phy_address_class = MCU_PHY_ADDR_SRAM;
    }
#endif

    return phy_address_class;
}

bool mcu_is_text_addr(const uint32_t address) {
    bool res = true;
    (void)address;
#ifdef HAS_EEPROM
    res = eeprom_is_address(address);
    if(false == res) {
        res = is_spi_flash_address(address);
    }
#endif

    return res;
}

_WEAK_FUN_ bool microcontroller_custom_init(void) {
    bool res = true;
    return res;
}

bool microcontroller_init(void) {
    bool res = false;
#ifdef HAS_LOG
    uint32_t core_freq_hz = clock_core_freq_get();
    LOG_WARNING(MICROCONTROLLER, "Init,MCU:%s,CPUclk:%u Hz", MCU_NAME, core_freq_hz);
#endif

    res = microcontroller_custom_init();
    return res;
}

bool is_mem_addr(uint32_t addr) {
    bool res = true;

    (void)addr;
#ifdef HAS_CORE
    res = is_ram_addr(addr);
#endif

#ifdef HAS_FLASH_EX
    if(false == res) {
        res = is_flash_addr(addr);
    }
#endif
    return res;
}
