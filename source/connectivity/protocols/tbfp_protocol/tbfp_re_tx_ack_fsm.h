#ifndef TBFP_RETX_ACK_FSM_H
#define TBFP_RETX_ACK_FSM_H

/*TBFP Trivial Binary Frame Protocol*/
#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "system.h"
#include "tbfp_types.h"

bool is_tbfp_retx_idle(TbfpHandle_t* instance);
bool tbfp_retx_start(TbfpHandle_t* instance, uint8_t* array, uint32_t len);
bool tbfp_retx_tx_done(Interfaces_t interface);
bool tbfp_retx_ack(TbfpHandle_t* instance, uint16_t sn);
bool tbfp_retx_proc(void);
bool tbfp_retx_init(TbfpHandle_t* instance);

#ifdef __cplusplus
}
#endif

#endif /* TBFP_RETX_ACK_FSM_H */
