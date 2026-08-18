#ifndef TCAN4550_DIAG_H
#define TCAN4550_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "tcan4550_types.h"

char* can_mode2str(uint8_t code);
const char* lec2str(uint8_t lec);

bool tcan4550_parse_reg_proto_state(uint32_t reg_val);
bool tcan4550_parse_reg_revision(uint32_t reg_val);
bool tcan4550_parse_reg_dev_id0(uint32_t reg_val);
bool tcan4550_parse_reg_dev_id1(uint32_t reg_val);
bool tcan4550_parse_reg_status(uint32_t reg_val);
bool tcan4550_parse_reg_mode_op_cfg(uint32_t reg_val);
bool tcan4550_parse_reg_interrupt_flags(uint32_t reg_val);
bool tcan4550_parse_reg_bit_timing(uint32_t reg_val);

#ifdef __cplusplus
}
#endif

#endif /* TCAN4550_DIAG_H  */
