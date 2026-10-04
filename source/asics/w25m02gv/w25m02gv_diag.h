#ifndef W25M02GV_DIAG_H
#define W25M02GV_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "w25m02gv_types.h"


#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_W25M02GV_DIAG
#error "+HAS_W25M02GV_DIAG"
#endif /*HAS_DIAG_W25M02GV*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/


bool W25m02gvDiagReg(W25m02gvRegAddr_t reg_addr, const W25m02gvRegUniversal_t* const Reg);
const char* W25m02gvJedecInfoToStr(const JedecInfo_t* const JedecInfo);
const char* W25m02gvConfigToStr(const W25m02gvConfig_t* const Config);
const char* W25m02gvNodeToStr(const W25m02gvHandle_t* const Node);
const char* W25m02gvRegAddrToName(W25m02gvRegAddr_t addr);
bool w25m02gv_diag_low_level(uint8_t num, const char* const key_word);
bool w25m02gv_diag_high_level(uint8_t num);
bool w25m02gv_reg_hazy(uint8_t num);
bool w25m02gv_reg_map_hidden_diag(uint8_t num);
bool w25m02gv_reg_map_diag(uint8_t num, char* key_word1, char* key_word2);

#endif /* W25M02GV_DIAG_H  */
