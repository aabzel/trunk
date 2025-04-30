#ifndef FLASH_MCAL_DIAG_H
#define FLASH_MCAL_DIAG_H


#include "std_includes.h"
#include "flash_types.h"

#ifdef HAS_FLASH_CUSTOM
#include "flash_custom_diag.h"
#endif

#ifndef HAS_FLASH
#error "+HAS_FLASH"
#endif

#ifndef HAS_FLASH_DIAG
#error "+HAS_FLASH_DIAG"
#endif

const char* FlashFsmOperationToStr(const FlashOperation_t operation);
const char* FlashFsmStateToStr(const FlashState_t state);
const char* FlashNodeToStr(const FlashHandle_t* const Node);
const char* FlashFsmInputToStr(const FlashInput_t input);
bool flash_region_print(uint32_t addr, uint32_t byte_size);
bool flash_diag_usage(uint32_t chank_size);
bool FlashDiagNode(const FlashHandle_t* const Node);
const char* MemContent2Str(MemContent_t code);
bool flash_scan_diag(uint32_t mem_start, uint32_t mem_size);

#endif /* FLASH_MCAL_DIAG_H  */
