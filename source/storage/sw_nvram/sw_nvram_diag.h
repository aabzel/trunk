#ifndef SW_NVRAM_DIAG_H
#define SW_NVRAM_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "sw_nvram_types.h"

#ifndef HAS_DIAG
#error  "+HAS_DIAG"
#endif /*HAS_DIAG*/

#ifndef HAS_SW_NVRAM
#error  "+HAS_SW_NVRAM"
#endif /*HAS_SW_NVRAM*/

#ifndef HAS_SW_NVRAM_DIAG
#error  "+HAS_SW_NVRAM_DIAG"
#endif /*HAS_SW_NVRAM_DIAG*/

bool SwNvramDiagPages(const NvRamPageConfig_t* const page);
bool sw_nvram_capacity(uint8_t nvram_num);
bool sw_nvram_draw_tree_compose(char* name);
bool entry_graphiz(NvRamItem_t* Node, NvRamHeader_t* Header, uint32_t base);
bool sw_nvram_diag(void) ;
bool sw_nvram_final_diag(void);
bool SwNvramDiag(const NvRamConfig_t* const Config);

#endif /*NVRAM_DIAG_H*/
