#include "correlator_s16_config.h"

#include "data_utils.h"
#include "correlator_s16_types.h"

#define CORRELATOR_S16_MAX_ORDER 5000
static int16_t StaticX7[CORRELATOR_S16_MAX_ORDER] = {0};
static int16_t StaticB7[CORRELATOR_S16_MAX_ORDER] = {0};

const CorrelatorS16Config_t CorrelatorS16Config[] = {
    {
        .num = CORRELATOR_S16_MUN_CHIRP_CORRELATION,
        .valid = true,
        .sample_rate_hz = 48000.0,
        .max_size = CORRELATOR_S16_MAX_ORDER, /* filter Order M */
        .size = 2880,                         /* filter Order M */
        .name = "Chirp",
        .file_name_in = "in.csv",
        .file_name_out = "out.csv",
        .x = StaticX7,
        .ReferenceSignal = StaticB7,
    },
};

CorrelatorS16Handle_t CorrelatorS16Instance[] = {
    {        .num = CORRELATOR_S16_MUN_CHIRP_CORRELATION,  .valid = true,  .init = false,    },
};


COMPONENT_GET_CNT(CorrelatorS16, correlator_s16)

