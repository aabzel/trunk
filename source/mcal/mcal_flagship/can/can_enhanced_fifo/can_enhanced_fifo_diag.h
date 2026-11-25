#ifndef CAN_ENHANCED_FIFO_DIAG_H
#define CAN_ENHANCED_FIFO_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_types.h"
#include "mcal_types.h"
#include "can_enhanced_fifo_types.h"

bool can_diag_enhanced_rx_fifo_filter(uint8_t num);
bool can_diag_enhanced_rx_fifo_filter_std(uint8_t num);
bool can_diag_enhanced_rx_fifo_filter_ext(uint8_t num);
bool can_diag_enhanced_fifo_parse(uint8_t num);
bool can_diag_enhanced_fifo_region(uint8_t num, uint32_t size);
bool can_enhanced_id_check_all(const uint8_t num);

bool can_ext_id_check_all(const uint8_t num);
bool can_std_id_check_all(const uint8_t num);

const char* CanFilterSchemeToStr(const CanFSCH_t filter_scheme);
const char* CanExtFilterElementToStr(const CanExtFiltElement_t* const Node);
const char* CanStdFilterElementToStr(const CanStdFiltElement_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* CAN_ENHANCED_FIFO_DIAG_H */


