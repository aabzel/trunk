#ifndef SW_NOR_FLASH_MCAL_H
#define SW_NOR_FLASH_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sw_nor_flash_config.h"
#include "sw_nor_flash_types.h"
#ifdef HAS_SW_NOR_FLASH_DIAG
#include "sw_nor_flash_diag.h"
#endif

/* API */
const SwNorFlashConfig_t* SwNorFlashGetConfig(uint8_t num);
SwNorFlashHandle_t* SwNorFlashGetNode(uint8_t num);
bool SwNorFlashIsValidConfig(const SwNorFlashConfig_t* const Config);


bool sw_nor_flash_mcal_init(void);
bool sw_nor_flash_init_custom(void);
bool sw_nor_flash_init_one(uint8_t num);
bool sw_nor_flash_init_common(const SwNorFlashConfig_t* const Config,
                              SwNorFlashHandle_t* const Node);

bool sw_nor_flash_proc_one(uint8_t num);
bool sw_nor_flash_proc(void);
bool sw_nor_flash_erase_sector(uint8_t num, uint32_t phy_address);
bool sw_nor_flash_erase_block(uint8_t num, uint32_t phy_address);
bool sw_nor_flash_zero(uint8_t num, uint32_t phy_address, uint32_t size);

/*setters*/
bool sw_nor_flash_page_program(uint8_t num, uint32_t phy_address, const uint8_t* constdata, uint32_t array_len);
bool sw_nor_flash_write(uint8_t num, uint32_t phy_address, const uint8_t* const data, uint32_t array_len);
bool sw_nor_flash_erase_chip(uint8_t num);
bool sw_nor_flash_erase_mem(uint8_t num, uint32_t phy_address, uint32_t size);

/*getters*/
uint8_t sw_nor_flash_read_byte(uint8_t num, uint32_t phy_address);
bool sw_nor_flash_read(uint8_t num, uint32_t phy_address, uint8_t * const data, uint32_t array_len);
bool sw_nor_flash_verify(uint8_t num, uint32_t phy_address, const uint8_t* const data, uint32_t size) ;
bool sw_nor_flash_is_spare(uint8_t num, uint32_t phy_address, uint32_t size) ;
bool sw_nor_flash_is_valid_addr(uint8_t num, uint32_t phy_address);

#ifdef __cplusplus
}
#endif

#endif /* SW_NOR_FLASH_MCAL_H */



