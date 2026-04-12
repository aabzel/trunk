#ifndef SW_NOR_FLASH_DIAG_H
#define SW_NOR_FLASH_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sw_nor_flash_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_SW_NOR_FLASH
#error "+HAS_SW_NOR_FLASH"
#endif /*HAS_SW_NOR_FLASH*/

#ifndef HAS_SW_NOR_FLASH_DIAG
#error "+HAS_SW_NOR_FLASH_DIAG"
#endif /*HAS_DIAG_SW_NOR_FLASH*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/


bool sw_nor_flash_diag(void);
const char* SwNorFlashConfigToStr(const SwNorFlashConfig_t* const Config);
const char* SwNorFlashNodeToStr(const SwNorFlashHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* SW_NOR_FLASH_DIAG_H  */
