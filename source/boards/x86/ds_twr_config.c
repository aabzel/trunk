#include "ds_twr_config.h"

#include "data_utils.h"

uint16_t KnownNodesArray[] = {0x02}; /*Array Of known_id*/

const DsTwrConfig_t DsTwrConfig = {
    .interface = IF_BLACK_HOLE,
    .num = 1,
    .decawave_num = 1,
    .valid = true,
    .timer_clock = 64000000000,
    .known_nodes = KnownNodesArray,
    .known_nodes_cnt = ARRAY_SIZE(KnownNodesArray),
};

DsTwr_t DsTwrItem = {
    .num = 1,
    .valid = true,
    .timer_clock = 64000000000,
};
