
#ifndef SW_NOR_FLASH_CONFIG_H
#define SW_NOR_FLASH_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sw_nor_flash_types.h"

#ifndef HAS_SW_NOR_FLASH
#error  "+HAS_SW_NOR_FLASH"
#endif /*HAS_SW_NOR_FLASH*/

//#define SW_NOR_FLASH_ID 1

//extern uint8_t SwNorFlashMem[SW_NOR_FLASH_FLASH_SIZE];

#ifdef __cplusplus
}
#endif

#endif /*SW_NOR_FLASH_CONFIG_H*/
