#include "gps_config.h"

#include "common_const.h"
#include "data_utils.h"

/*that is sat for source2.bin 28 5 14 20 30 */
static GpsSat_t SatArray[] = {
    {
        .valid = true, .prn = 5, .doppler_offset_hz = 900, .if_seek_step_hz = 100, .doppler_range_hz = 10000,
        //  .if_hz = IF_FREQ_HZ,
    },

    {
        // tracking 0.39 %
        .valid = true,
        .prn = 14,
        .doppler_offset_hz = 4240,     // 4100 4240 4325  4336 4330
        .init_prn_phase_sample = 8595, // 1 byte - one sample 8596 8594
        .if_seek_step_hz = 100,
        // .if_hz = IF_FREQ_HZ,
    },

    {
        .valid = true, .prn = 20, .doppler_offset_hz = -1000, .if_seek_step_hz = 100,
        // .if_hz = IF_FREQ_HZ,
    },
    {
        .valid = true, .prn = 30, .doppler_offset_hz = 2000, .if_seek_step_hz = 100,
        // .if_hz = IF_FREQ_HZ,
    },
    {
        .valid = true,
        .prn = 13,
        .init_prn_phase_sample = 4959, // 4900 4963
        .doppler_offset_hz = 4200,     //
        .if_seek_step_hz = 100,
        // .if_hz = IF_FREQ_HZ,
    },
};

const GpsConfig_t GpsConfig[] = {
    {
        // visible sats: 5 14 30  13 15 20 28
        .num = 1,
        .valid = true,
        .histogram_num = 1,
        .gnss_front_end_lo_freq_hz = 1571328000.0,
        .adc_sample_rate_hz = 16368000.0,
        .SatS = SatArray,
        .sat_cnt = ARRAY_SIZE(SatArray),
        .step_samples = 2, // PRN phase seek step samples
        .file_name = "byte_stream_i8.bin",
    },

    {
        /*visible sats:  17 28 1 32 11 23 4 6 */
        .num = 2,
        .valid = true,
        .gnss_front_end_lo_freq_hz = 1571328000.0,
        .adc_sample_rate_hz = 16368000.0,
        .SatS = NULL,
        .sat_cnt = 0,
        .step_samples = 8,            //
        .file_name = "gn3sv3_l1.bin", /*  */
    },

};

GpsHandle_t GpsInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },
};

uint32_t gps_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(GpsInstance);
    cnt2 = ARRAY_SIZE(GpsConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
