#include "test_dds.h"

#include "std_includes.h"
#include "data_utils.h"
#include "dds_drv.h"
#include "log.h"
#include "unit_test_check.h"
#include "time_mcal.h"

#ifdef HAS_DFT
#include "complex_diag.h"
#include "dft.h"
#endif

#define DDS_CHIRP_NUM 1
#define DDS_MAX_SAMPLE_ARRAY 200
#define CHIRP_DURATION_MS 30
const InterfaceType_t playerWav={ .interface_name=INTERFACE_NAME_WAV, .num=1, };


bool test_dds_sin(void) {
    bool res = true;
    res = dds_play1khz(DDS_NUM_SIN, 1000, 0, 0);
    ASSERT_TRUE( wait_in_loop_ms(1000) );
    res = dds_stop(DDS_NUM_SIN);
    ASSERT_TRUE(res);
    return res;
}
/*
 tsr dds_chirp
 */
bool test_dds_chirp(void) {
    bool res = true;
    // log_level_get_set(DDS,LOG_LEVEL_DEBUG);
    ASSERT_TRUE( dds_set_chirp(DDS_CHIRP_NUM,MSEC_2_SEC(CHIRP_DURATION_MS),450,10000));
    ASSERT_TRUE( dds_set_array(DDS_CHIRP_NUM, 0, MSEC_2_NSEC(CHIRP_DURATION_MS*3)));
    ASSERT_TRUE( dds_shift_signal(DDS_CHIRP_NUM, MSEC_2_SEC(CHIRP_DURATION_MS)));
    ASSERT_TRUE( dds_play(DDS_CHIRP_NUM  , 100));
    // log_level_get_set(DDS,LOG_LEVEL_INFO);
    return res;
}


/*
 tsr dds_chirp_wav
 */
bool test_dds_chirp_wav(void) {
    bool res = true;
    // log_level_get_set(DDS,LOG_LEVEL_DEBUG);
    ASSERT_TRUE( dds_set_chirp(DDS_CHIRP_NUM,MSEC_2_SEC(CHIRP_DURATION_MS),450,10000));

    ASSERT_TRUE( dds_player_set(DDS_CHIRP_NUM, playerWav));
    ASSERT_TRUE( dds_set_array(DDS_CHIRP_NUM, 0, MSEC_2_NSEC(CHIRP_DURATION_MS*4)));
    ASSERT_TRUE( dds_shift_signal(DDS_CHIRP_NUM, MSEC_2_SEC(CHIRP_DURATION_MS)));
    ASSERT_TRUE( dds_play(DDS_CHIRP_NUM, MSEC_2_NSEC(CHIRP_DURATION_MS*3)));

    // log_level_get_set(DDS, LOG_LEVEL_INFO);
    return res;
}



/*
 tsr dds_chirp_wav
 */
bool test_dds_chirp_30ms_wav(void) {
    bool res = true;
    uint32_t dutation_ms = 30;
    // log_level_get_set(DDS,LOG_LEVEL_DEBUG);
    ASSERT_TRUE( dds_set_chirp(DDS_CHIRP_NUM,MSEC_2_SEC(dutation_ms),450,10000));

    ASSERT_TRUE( dds_player_set(DDS_CHIRP_NUM, playerWav));
    ASSERT_TRUE( dds_set_array(DDS_CHIRP_NUM, 0, MSEC_2_NSEC(dutation_ms*4)));
    ASSERT_TRUE( dds_shift_signal(DDS_CHIRP_NUM, MSEC_2_SEC(dutation_ms)));
    ASSERT_TRUE( dds_play(DDS_CHIRP_NUM, MSEC_2_NSEC(dutation_ms*3)));

    DdsHandle_t* Node = DdsGetNode(  DDS_CHIRP_NUM);
    ASSERT_NE(NULL, Node);

#ifdef HAS_DFT
    double complex Spectr[DDS_MAX_SAMPLE_ARRAY]={0};
    double sampling_period_s = 1.0/((double) Node->sample_per_second);
    ASSERT_TRUE(  dft_calc(Node->sample_array,   Node->sample_cnt, (double complex* const) &Spectr,   sampling_period_s));
    uint32_t order = Node->sample_cnt/2;

    ASSERT_TRUE(   complex_array_print_csv((const double complex* const )&Spectr,   Node->sample_cnt,   sampling_period_s,   order));
#endif

    // log_level_get_set(DDS, LOG_LEVEL_INFO);
    return res;
}


