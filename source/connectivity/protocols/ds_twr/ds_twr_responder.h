#ifndef DS_TWR_RESPONDER_H
#define DS_TWR_RESPONDER_H

/*DS TWR stands for Double-Sided Two-Way Ranging*/

#include <stdbool.h>

#include "ds_twr_config.h"
#include "ds_twr_dependencies.h"
#ifdef HAS_DS_TWR_DIAG
#include "ds_twr_diag.h"
#endif
#include "ds_twr_types.h"

#ifdef HAS_DEBUG
#include "debug_info.h"
#endif

bool ds_twr_proc_idle_rx_time(DsTwr_t* const Node);
bool ds_twr_proc_rx_poll(DsTwr_t* const Node);
bool ds_twr_proc_responder_delay(DsTwr_t* const Node, uint32_t up_time_ms) ;
bool ds_twr_proc_responder_loop(DsTwr_t* const Node, uint32_t up_time_ms) ;
bool ds_twr_proc_done(DsTwr_t* const Node, uint32_t up_time_ms);
bool ds_twr_parse_pesponse(DsTwr_t* const Node, const uint8_t* const payload, uint16_t len);

#endif /* DS_TWR_RESPONDER_H  */
