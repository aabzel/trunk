#ifndef DS_TWR_INITIATOR_H
#define DS_TWR_INITIATOR_H

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

bool ds_twr_calibrate(DsTwr_t* const TwrNode, double real_dist_m);
bool ds_twr_init_distances(const DsTwrConfig_t* const Config, DsTwr_t* const Node);
bool ds_twr_start_ll(DsTwr_t* const Node);
bool ds_twr_send_poll(DsTwr_t* const Node);
bool ds_twr_enable_continuous(DsTwr_t* const Node, bool on_off);
bool ds_twr_proc_initiator_loop(DsTwr_t* const Node, uint32_t up_time_ms);
bool ds_twr_proc_initiator_delay(DsTwr_t* const Node, uint32_t up_time_ms);
bool ds_twr_proc_wait_timings(DsTwr_t* const Node, uint32_t up_time_ms);

#endif /* DS_TWR_INITIATOR_H  */
