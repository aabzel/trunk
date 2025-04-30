#ifndef DS_TWR_DRV_H
#define DS_TWR_DRV_H

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

bool ds_twr_proc_timeout(DsTwr_t* const Node);
bool ds_twr_proc_error_input(DsTwr_t* const Node);
bool ds_twr_send_poll(DsTwr_t* const Node);
// bool ds_twr_dist_get(const DsTwr_t* const Node, double* const dist);
// bool ds_twr_parse_responder_timings(DsTwr_t* const Node, const uint8_t* const payload, uint16_t len);
bool ds_twr_init(void);
bool ds_twr_enable_continuous(DsTwr_t* const Node, bool on_off);
bool ds_twr_init_one(const DsTwrConfig_t* const Config, DsTwr_t* const Node);
bool ds_twr_parse_pesponse(DsTwr_t* const Node, const uint8_t* const payload, uint16_t len);
bool ds_twr_proc_one(DsTwr_t* const Node);
bool ds_twr_proc(void);
bool ds_twr_proc_tx_time(DsTwr_t* ds_twr, uint64_t tx_stamp);
bool ds_twr_proc_rx_time(DsTwr_t* ds_twr, uint64_t rx_stamp);
bool ds_twr_reset(DsTwr_t* const Node);
bool ds_twr_start(DsTwr_t* const Node);

#endif /* DS_TWR_DRV_H  */
