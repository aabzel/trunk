#include "fir_config.h"

#include "data_utils.h"
#include "fir_types.h"

#define FIR_MAX_ORDER 100000

static FirSample_t StaticX1[FIR_MAX_ORDER] = {0};
static FirSample_t StaticB1[FIR_MAX_ORDER] = {0};

static FirSample_t StaticX2[FIR_MAX_ORDER] = {0};
static FirSample_t StaticB2[FIR_MAX_ORDER] = {0};

static FirSample_t StaticX3[FIR_MAX_ORDER] = {0};
static FirSample_t StaticB3[FIR_MAX_ORDER] = {0};

static FirSample_t StaticX4[FIR_MAX_ORDER] = {0};
static FirSample_t StaticB4[FIR_MAX_ORDER] = {0};

static FirSample_t StaticX5[FIR_MAX_ORDER] = {0};
static FirSample_t StaticB5[FIR_MAX_ORDER] = {0};

static FirSample_t StaticX6[FIR_MAX_ORDER] = {0};
static FirSample_t StaticB6[FIR_MAX_ORDER] = {0};

static FirSample_t StaticX7[FIR_MAX_ORDER] = {0};
static FirSample_t StaticB7[FIR_MAX_ORDER] = {0};


static FirSample_t StaticX8[FIR_MAX_ORDER] = {0};
static FirSample_t StaticB8[FIR_MAX_ORDER] = {0};

const FirConfig_t FirConfig[] = {
    {
        .num = 1,
        .valid = true,
        .file_name_out = "out.csv",
        .cut_off_freq_hz = 10,
        .sample_rate_hz = 96000.0,
        .max_size = FIR_MAX_ORDER, /*filter Order M */
        .size = 400,               /*filter Order M */
        .name = "PhaseDetector",
        .x = StaticX1,
        .b = StaticB1,
        .mode = FIR_MODE_CLASSIC,
    },

    {
        .num = 2,
        .valid = true,
        .cut_off_freq_hz = 4000,
        .sample_rate_hz = 44100.0,
        .max_size = FIR_MAX_ORDER, /*filter Order M */
        .size = 800,               /*filter Order M */
        .name = "FIR_I",
        .x = StaticX2,
        .file_name_out = "out.csv",
        .b = StaticB2,
        .mode = FIR_MODE_CLASSIC,
    },

    {
        .num = 3,
        .valid = true,
        .cut_off_freq_hz = 4000,
        .sample_rate_hz = 44100.0,
        .max_size = FIR_MAX_ORDER, /*filter Order M */
        .size = 800,               /*filter Order M */
        .name = "FIR_Q",
        .x = StaticX3,
        .file_name_out = "out.csv",
        .b = StaticB3,
        .mode = FIR_MODE_CLASSIC,
    },

    {
        .num = 4,
        .valid = true,
        .cut_off_freq_hz = 6,
        .sample_rate_hz = 44100.0,
        .max_size = FIR_MAX_ORDER, /*filter Order M */
        .size = 800,               /*filter Order M */
        .name = "FIR_Phase",
        .file_name_out = "out.csv",
        .x = StaticX4,
        .b = StaticB4,
        .mode = FIR_MODE_CLASSIC,
    },

    {
        .num = 5,
        .valid = true,
        .cut_off_freq_hz = 10,
        .sample_rate_hz = 44100.0,
        .max_size = FIR_MAX_ORDER, /*filter Order M */
        .size = 800,               /*filter Order M */
        .name = "FIR_I",
        .x = StaticX5,
        .file_name_out = "out.csv",
        .b = StaticB5,
        .mode = FIR_MODE_CLASSIC,
    },

    {
        .num = 6,
        .valid = true,
        .cut_off_freq_hz = 10,
        .sample_rate_hz = 44100.0,
        .max_size = FIR_MAX_ORDER, /*filter Order M */
        .size = 800,               /*filter Order M */
        .name = "FIR_Q",
        .x = StaticX6,
        .b = StaticB6,
        .file_name_out = "out.csv",
        .mode = FIR_MODE_CLASSIC,
    },

    {
        .num = FIR_MUN_CHIRP_CORRELATION,
        .valid = true,
        .cut_off_freq_hz = 10,
        .sample_rate_hz = 44100.0,
        .max_size = FIR_MAX_ORDER, /*filter Order M */
        .size = 800,               /*filter Order M */
        .name = "Chirp",
        .mode = FIR_MODE_CORRELATION,
        .file_name_out = "out.csv",
        .x = StaticX7,
        .b = StaticB7,
    },

    {
        .num = FIR_MUN_SOUND_DIR,
        .valid = true,
        .cut_off_freq_hz = 1.0,
        .sample_rate_hz = 96000.0,
        .max_size = FIR_MAX_ORDER, /*filter Order M */
        .size = 90000,               /*filter Order M */
        .name = "SoundDir",
        .file_name_out = "out2.csv",
        .x = StaticX8,
        .b = StaticB8,
        .mode = FIR_MODE_CLASSIC,
    },

};

FirHandle_t FirInstance[] = {
    {        .num = 1,        .valid = true,        .init = false,    },
    {        .num = 2,        .valid = true,        .init = false,    },
    {        .num = 3,        .valid = true,        .init = false,    },
    {        .num = 4,        .valid = true,        .init = false,    },
    {        .num = 5,        .valid = true,        .init = false,    },
    {        .num = 6,        .valid = true,        .init = false,    },
    {        .num = FIR_MUN_CHIRP_CORRELATION,        .valid = true,        .init = false,    },
    {        .num = FIR_MUN_SOUND_DIR,        .valid = true,        .init = false,    },
};

uint32_t fir_get_cnt(void) {
    uint8_t cnt = 0;
    cnt = ARRAY_SIZE(FirConfig);
    return cnt;
}
