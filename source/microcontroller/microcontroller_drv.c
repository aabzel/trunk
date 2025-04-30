#include "microcontroller_drv.h"

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

#ifdef HAS_PIN
bool mcu_get_prev_pin(PinData_t cur_pin, PinData_t* prev_pin) {
    bool res = false;
    return res;
}

bool mcu_get_next_pin(PinData_t cur_pin, PinData_t* next_pin) {
    bool res = false;
    return res;
}

bool mcu_get_up_pin(PinData_t cur_pin, PinData_t* const up_pin) {
    bool res = false;
    return res;
}

bool mcu_get_down_pin(PinData_t cur_pin, PinData_t* const down_pin) {
    bool res = false;
    return res;
}

bool mcu_get_right_pin(PinData_t cur_pin, PinData_t* const right_pin) {
    bool res = false;
    return res;
}

bool mcu_get_left_pin(PinData_t cur_pin, PinData_t* const left_pin) {
    bool res = false;
    return res;
}
#endif

bool mcu_is_text_addr(const uint32_t address) {
    bool res = true;
#ifdef HAS_EEPROM
    res = eeprom_is_address(address);
    if(false == res) {
        res = is_spi_flash_address(address);
    }
#endif

    return res;
}
