#ifndef TBFP_RETX_DIAG_H
#define TBFP_RETX_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "tbfp_re_tx_ack_fsm_types.h"

const char* tbfp_retx_in2str(TbfpReTxInput_t in);
const char* tbfp_retx_state2str(TbfpReTxState_t state);
bool tbfp_diag_retx(void) ;

#ifdef __cplusplus
}
#endif

#endif /* TBFP_RETX_DIAG_H */
