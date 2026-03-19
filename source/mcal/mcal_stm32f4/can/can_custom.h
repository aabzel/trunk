#ifndef CAN_STM32_CUSTOM_DRV_H
#define CAN_STM32_CUSTOM_DRV_H

#include "std_inc.h"
#include "microcontroller_const.h"
#include "can_mcal.h"
#include "can_core.h"
#include "can_custom_isr.h"
#include "can_custom_types.h"
#include "can_custom_diag.h"

/*getters*/
bool CanSegmentToStmSegment(const CanSegmentInfo_t* const Segment, CAN_InitTypeDef* const Init);
bool can_stm32_segment_info_calc(uint32_t bus_freq_hz, const uint32_t bit_rate_hz,
                                 CanSegmentInfo_t* const Segment);
CanIdentifier_t CanIDEtoIdentifierType(const uint32_t ide);
CanHandle_t* CanHandleToNode(const CAN_HandleTypeDef *const Handle);
uint8_t CanHandleToCanNum(const CAN_HandleTypeDef *const hcan);
int8_t can_filter_num_calc(const uint8_t can_num, const uint8_t filt_num) ;
const CanInfo_t* CanXToInfo(const CAN_TypeDef* const CANx);
uint32_t CanIdTypeToFiltIDE(const CanIdentifier_t id_type);
uint32_t can_get_spare_mail_box(const uint8_t num) ;

uint32_t can_segment_info_to_bitrate(const uint32_t base_clock_hz,
                                     const uint16_t brp,
                                     const uint8_t sjw,
                                     const uint8_t tseg1,
                                     const uint8_t tseg2) ;
/*setters*/

#endif /* CAN_STM32_CUSTOM_DRV_H  */
