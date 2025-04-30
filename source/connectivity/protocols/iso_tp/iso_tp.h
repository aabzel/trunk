#ifndef ISO_TP_PROTOCOL_H
#define ISO_TP_PROTOCOL_H

/*ISO_TP Trivial Binary Frame Protocol*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "iso_tp_config.h"
#include "iso_tp_types.h"
#include "system.h"
#ifdef HAS_ISO_TP_DIAG
#include "iso_tp_diag.h"
#endif

IsoTpHandle_t* IsoTpGetNode(uint8_t num);
IsoTpHandle_t* IsoTpIfToNode(Interfaces_t interface);
const IsoTpConfig_t* IsoTpGetConfig(uint8_t num);

bool iso_tp_check(void);
bool iso_tp_proc_rx(uint8_t num, uint16_t feame_id, IsoTpFrame_t* const RxFrame);
bool iso_tp_init_one(uint8_t num);
bool iso_tp_if_sent_ll(IsoTpHandle_t* Node);
bool iso_tp_proc_one(uint8_t num);
bool iso_tp_proc(void);
bool iso_tp_init_custom(void);
bool iso_tp_send(uint8_t num, const uint8_t* const data, size_t size);
bool iso_tp_mcal_init(void);
double SepTime2Val(uint8_t sep_time);

#ifdef __cplusplus
}
#endif

#endif /* ISO_TP_PROTOCOL_H */
