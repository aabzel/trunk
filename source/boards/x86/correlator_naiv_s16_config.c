#include "correlator_naiv_s16_config.h"

#include "data_utils.h"
#include "correlator_naiv_s16_types.h"

#define CORRELATOR_NAIV_S16_MAX_ORDER 5000
static int16_t StaticX7[CORRELATOR_NAIV_S16_MAX_ORDER] = {0};
static int16_t StaticB7[CORRELATOR_NAIV_S16_MAX_ORDER] = {0};

static int16_t StaticXm[CORRELATOR_NAIV_S16_MAX_ORDER] = {0};
static int16_t StaticBm[CORRELATOR_NAIV_S16_MAX_ORDER] = {0};


const CorrelatorNaivS16Config_t CorrelatorNaivS16Config[] = {
    {
        .num = CORRELATOR_NAIV_S16_MUN_M_SEC,
        .valid = true,
        .sample_rate_hz = 1,
        .max_size = CORRELATOR_NAIV_S16_MAX_ORDER, /*filter Order M */
        .size = ARRAY_SIZE(StaticXm),              /*filter Order M */
        .name = "Chirp",
        .file_name_in = "in.csv",
        .file_name_out = "out.csv",
        .x = StaticXm,
        .ReferenceSignal = StaticBm,
    },

    {
        .num = CORRELATOR_NAIV_S16_MUN_CHIRP_CORRELATION,
        .valid = true,
        .sample_rate_hz = 48000,
        .max_size = CORRELATOR_NAIV_S16_MAX_ORDER, /*filter Order M */
        .size = 2880,              /*filter Order M */
        .name = "Chirp",
        .file_name_in = "in.csv",
        .file_name_out = "out.csv",
        .x = StaticX7,
        .ReferenceSignal = StaticB7,
    },
};

CorrelatorNaivS16Handle_t CorrelatorNaivS16Instance[] = {
    {        .num = CORRELATOR_NAIV_S16_MUN_M_SEC,  .valid = true,  .init = false,    },
    {        .num = CORRELATOR_NAIV_S16_MUN_CHIRP_CORRELATION,  .valid = true,  .init = false,    },
};


COMPONENT_GET_CNT(CorrelatorNaivS16, correlator_naiv_s16)

