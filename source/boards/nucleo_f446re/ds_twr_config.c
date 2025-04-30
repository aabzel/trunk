#include "ds_twr_config.h"

#include "data_utils.h"

uint16_t KnownNodesArray[] = {0xAAAA}; /*Array Of known_id*/

const DsTwrConfig_t DsTwrConfig = {
#ifdef HAS_UWB
    .interface = IF_UWB,
#else
    .interface = IF_BLACK_HOLE,
#endif
    .num = 1,
    .decawave_num = 1,
    .valid = true,
    //  .id_def = 0x01,
    //.ant_delay_m = 154.199, // 154.215
    .timer_clock = 64000000000,
    .known_nodes = KnownNodesArray,
    .known_nodes_cnt = ARRAY_SIZE(KnownNodesArray),
};

DsTwr_t DsTwrItem = {
    .num = 1,
    .valid = true,
    .timer_clock = 64000000000,
};
