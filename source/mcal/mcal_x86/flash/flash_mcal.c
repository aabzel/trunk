#include "flash_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifdef HAS_LOG
#include "log.h"
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

#include "bit_utils.h"
#include "data_utils.h"
#include "x86x.h"
#include "flash_custom_const.h"
#include "flash_custom_drv.h"
#include "microcontroller_const.h"

static const Reg32_t FlashRegisters[] = {
    {
        .num = 1,
        .valid = true,
        .name = "FLASH_PSR",
        .offset = 0x00,
    },
    {
        .num = 2,
        .valid = true,
        .name = "FLASH_UNLOCK",
        .offset = 0x04,
    },
    {
        .num = 3,
        .valid = true,
        .name = "FLASH_USD_UNLOCK",
        .offset = 0x08,
    },
    {
        .num = 4,
        .valid = true,
        .name = "FLASH_STS",
        .offset = 0x0C,
    },
    {
        .num = 5,
        .valid = true,
        .name = "FLASH_CTRL",
        .offset = 0x10,
    },
    {
        .num = 6,
        .valid = true,
        .name = "FLASH_ADDR",
        .offset = 0x14,
    },
    {
        .num = 7,
        .valid = true,
        .name = "FLASH_USD",
        .offset = 0x1C,
    },
    {
        .num = 8,
        .valid = true,
        .name = "FLASH_EPPS0",
        .offset = 0x20,
    },
    {
        .num = 9,
        .valid = true,
        .name = "FLASH_EPPS1",
        .offset = 0x2C,
    },
    {
        .num = 10,
        .valid = true,
        .name = "FLASH_UNLOCK2",
        .offset = 0x44,
    },
    {
        .num = 11,
        .valid = true,
        .name = "FLASH_STS2",
        .offset = 0x4C,
    },
    {
        .num = 12,
        .valid = true,
        .name = "FLASH_CTRL2",
        .offset = 0x50,
    },
    {
        .num = 13,
        .valid = true,
        .name = "FLASH_ADDR2",
        .offset = 0x54,
    },
    {
        .num = 14,
        .valid = true,
        .name = "FLASH_CONTR",
        .offset = 0x58,
    },
    {
        .num = 15,
        .valid = true,
        .name = "FLASH_DIVR",
        .offset = 0x60,
    },
    {
        .num = 16,
        .valid = true,
        .name = "SLIB_STS2",
        .offset = 0xC8,
    },
    {
        .num = 17,
        .valid = true,
        .name = "SLIB_STS0",
        .offset = 0xCC,
    },
    {
        .num = 18,
        .valid = true,
        .name = "SLIB_STS1",
        .offset = 0xD0,
    },
    {
        .num = 19,
        .valid = true,
        .name = "SLIB_PWD_CLR",
        .offset = 0xD4,
    },
    {
        .num = 20,
        .valid = true,
        .name = "SLIB_MISC_STS",
        .offset = 0xD8,
    },
    {
        .num = 21,
        .valid = true,
        .name = "SLIB_SET_PWD",
        .offset = 0xDC,
    },
    {
        .num = 22,
        .valid = true,
        .name = "SLIB_SET_RANGE0",
        .offset = 0xE0,
    },
    {
        .num = 23,
        .valid = true,
        .name = "SLIB_SET_RANGE1",
        .offset = 0xE4,
    },
    {
        .num = 24,
        .valid = true,
        .name = "SLIB_UNLOCK",
        .offset = 0xF0,
    },
    {
        .num = 25,
        .valid = true,
        .name = "FLASH_CRC_CTRL",
        .offset = 0xF4,
    },
    {
        .num = 26,
        .valid = true,
        .name = "FLASH_CRC_CHKR",
        .offset = 0xF8,
    },
};

uint32_t flash_reg_get_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(FlashRegisters);
    return cnt;
}

static const FlashInfo_t FlashInfo = {
    .num = 1,
    .valid = true,
    // .FLASHx = (struct flash_type*) (FLASH), // 0x40023C00 - 0x4002 3FFF (Boundary address)
    .clockBus = CLOCK_BUS_AHB,
    //.clockType = CRM_FLASH_PERIPH_LOWPOWER,
    .irqNn = 555,
    .RegArray = FlashRegisters,
    .regCnt = ARRAY_SIZE(FlashRegisters),
};

const FlashInfo_t* FlashGetInfo(const uint8_t num) {
    FlashInfo_t* Info = &FlashInfo;
    return Info;
}
#ifdef HAS_FREE_RTOS
SemaphoreHandle_t xFlashWrireSem = NULL;
#endif

/**
 * @brief  read data using halfword mode
 * @param  read_addr: the address of reading
 * @param  p_buffer: the buffer of reading data
 * @param  num_read: the number of reading data
 * @retval none
 */
void flash_read_u16(uint32_t read_addr, uint16_t* p_buffer, uint16_t num_read) {
    uint16_t i;
    for(i = 0; i < num_read; i++) {
        p_buffer[i] = *(uint16_t*)(read_addr);
        read_addr += 2;
    }
}

bool flash_init(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_INFO(LG_FLASH, "Init");
#endif

    FlashInstance.start = ROM_START;
    FlashInstance.size = ROM_SIZE;
    FlashInstance.init = true;
    FlashInstance.page_cnt = 8;
#ifdef HAS_FREE_RTOS
    xFlashWrireSem = xSemaphoreCreateMutex();
    xSemaphoreGive(xFlashWrireSem);
#endif
#ifdef HAS_LOG
    LOG_INFO(LG_FLASH, "Ready");
#endif
    res = true;

    return res;
}

#ifdef HAS_FLASH_EX
bool Addr2SectorSize(uint32_t addr, uint32_t* sector, uint32_t* sec_size) {
    bool res = false;
    if(sector && sec_size) {
        uint32_t cnt = flash_get_sector_cnt();
        uint32_t i = 0;
        for(i = 0; i < cnt; i++) {
            uint32_t end_addr = FlashSectorConfig[i].start + FlashSectorConfig[i].size;
            if((FlashSectorConfig[i].start <= addr) && (addr <= end_addr)) {
                (*sector) = (uint32_t)FlashSectorConfig[i].sector;
                (*sec_size) = (uint32_t)FlashSectorConfig[i].size;
                res = true;
            }
        }
    }
    return res;
}
#endif

bool is_flash_addr(const uint32_t address) {
    bool res = false;
    if(address) {
        res = true;
    }
    return res;
}
