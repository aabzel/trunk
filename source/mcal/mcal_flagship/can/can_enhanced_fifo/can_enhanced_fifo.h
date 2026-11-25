#ifndef CAN_ENHANCED_FIFO_H
#define CAN_ENHANCED_FIFO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "module_driver_flexcan.h"
#include "can_enhanced_fifo_types.h"
#include "can_enhanced_fifo_diag.h"
#include "can_types.h"

/*API*/
bool can_config_enhanced_fifo_init(const CanConfig_t* const Config, FLEXCAN_InitType* const Init) ;
bool can_init_rx_fifo_enhanced_default(FLEXCAN_InitType* const pInit) ;

/*setters*/
bool can_filter_ctrl(uint8_t num, uint32_t can_id, CanFilterIdAccess_t accsess_cmd);

/*getters*/
uint8_t can_std_id_filter_element_cnt_get(uint8_t num);
uint8_t can_ext_id_filter_element_cnt_get(uint8_t num);
uint32_t can_enhanced_watermark_get(uint32_t num);
bool can_is_mode_enhanced_fifo(const uint8_t num);
bool can_is_valid_std_id(const uint32_t id, const uint32_t filter);
bool can_is_valid_ext_id(const uint32_t id, const uint64_t filter);
bool can_enhanced_id_check_std(uint8_t num, const uint32_t can_id);
bool can_enhanced_id_check_ext(uint8_t num, const uint32_t can_id);
bool can_enhanced_id_check(uint8_t num, const uint32_t can_id);

bool can_proc_erfsr(CanHandle_t* Node);
bool can_enhanced_watermark_set(uint32_t num, uint32_t watermark);

#ifdef __cplusplus
}
#endif

#endif /* CAN_ENHANCED_FIFO_H  */




