#include "eeprom_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "bit_utils.h"
#include "data_utils.h"
#include "eeprom_custom_const.h"
#include "eeprom_custom_drv.h"
#include "hal_mcal.h"
#include "mik32_hal.h"
#include "mik32_hal_eeprom.h"
#include "sys_config.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#ifdef HAS_DIAG
#include "hal_diag.h"
#endif

#ifdef HAS_ARRAY
#include "array.h"
#endif

#ifdef HAS_FREE_RTOS
#include "FreeRTOS.h"
#include "semphr.h"
#endif

#ifdef HAS_CLOCK
#include "none_blocking_pause.h"
#endif
//#include "mik32_hal.h"

#ifdef HAS_FREE_RTOS
SemaphoreHandle_t xEepromWrireSem = NULL;
#endif

#ifdef HAS_EEPROM_EX
bool AddrToSectorSize(uint32_t addr, uint32_t* sector, uint32_t* sec_size) {
    bool res = false;
    if(sector && sec_size) {
        uint32_t cnt = eeprom_get_sector_cnt();
        uint32_t i = 0;
        for(i = 0; i < cnt; i++) {
            uint32_t end_addr = EepromSectorConfig[i].start + EepromSectorConfig[i].size;
            if((EepromSectorConfig[i].start <= addr) && (addr <= end_addr)) {
                (*sector) = (uint32_t)EepromSectorConfig[i].sector;
                (*sec_size) = (uint32_t)EepromSectorConfig[i].size;
                res = true;
            }
        }
    }
    return res;
}
#endif

bool eeprom_mcal_init(void) {
    bool res = false;
    LOG_WARNING(EEPROM, "Init");
    const EepromConfig_t* Config = EepromGetConfig(0);
    if(Config) {
        EepromHandle_t* Node = EepromGetNode(0);
        if(Node) {
            res = eeprom_is_valid_config(Config);
            if(res) {
                res = eeprom_init_common(Config, Node);
                if(res) {
                    Node->EEPROMx = EEPROM_REGS;
#ifdef HAS_DEBUGGER
                    // ASSERT_CRITICAL(EepromConfig.end);
                    // ASSERT_CRITICAL(EepromConfig.start);
#endif
                    res = eeprom_init_common(Config, Node);

                    Node->handle.Instance = EEPROM_REGS;
                    Node->handle.Mode = HAL_EEPROM_MODE_TWO_STAGE;
                    Node->handle.ErrorCorrection = HAL_EEPROM_ECC_ENABLE;
                    Node->handle.EnableInterrupt = HAL_EEPROM_SERR_DISABLE;

                    HAL_StatusTypeDef ret = HAL_ERROR;
                    ret = HAL_EEPROM_Init(&Node->handle);
                    res = MIK32_HalRetToRes(ret);
                    HAL_EEPROM_CalculateTimings(&Node->handle, OSC_SYSTEM_VALUE);
                }
            }
        }
    }

    return res;
}

bool eeprom_read_relative(const uint32_t offset, const uint32_t size) {
    bool res = false;
    LOG_INFO(EEPROM, "Offset:0x%08x,Size:%u", offset, size);
    if(size) {
        if(size <= ROM_SIZE) {
            uint8_t* buff = (uint8_t*)(offset + ROM_START);
            res = print_hex(buff, size);
        } else {
            LOG_ERROR(EEPROM, "BigSize:%u", size);
        }
    } else {
        LOG_ERROR(EEPROM, "ZeroSize");
    }
    return res;
}
