#ifndef SI4737_DIAG_H
#define SI4737_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "si4737_types.h"

#ifndef HAS_SI4737
#error "+HAS_SI4737"
#endif /*HAS_SI4737*/

const char* OutModeToStr(uint8_t code);
const char* OutMonoToStr(uint8_t code);
const char* OutFallToStr(uint8_t out_fall);
const char* SeekDirToStr(uint8_t SeekDir);
const char* SeekEndToStr(uint8_t SeekEnd);
const char* parse_rds_block_corr_err(uint8_t byte, RdsBlock_t rds_block);
const char* SiPropertyToStr(uint16_t id);

#endif /* SI4737_DIAG_H  */
