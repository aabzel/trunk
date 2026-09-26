#ifndef EXT_INT_MCAL_ISR_H
#define EXT_INT_MCAL_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ext_int_types.h"

#ifdef HAS_EXT_INT_CUSTOM
#include "ext_int_custom_isr.h"
#endif

PinIntDrop_t ExtIntEdgeToDrop(const PinIntEdge_t edge_effective);
bool ext_int_irq_handler(const uint8_t pin_num, const uint32_t timestamp_us);
//bool ExtIntRisingCallBack(ExtIntHandle_t* const Node);
//bool ExtIntFallingCallBack(ExtIntHandle_t* const Node);
//bool ext_int_proc_egde(ExtIntHandle_t* Node) ;

#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_MCAL_ISR_H */
