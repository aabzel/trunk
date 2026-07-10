#include "test_sound_recorder.h"


#include <stdio.h>
#include <string.h>

#include "std_includes.h"
#include "sound_recorder_mcal.h"
#include "log.h"
#include "time_mcal.h"
#include "unit_test_check.h"
#include "utils_math.h"
#include "test_fat_fs.h"
#include "i2s_mcal.h"
#include "test_i2s.h"
#include "test_i2s_dma.h"
#include "test_dds.h"
#include "test_wm8731.h"
#include "test_sdio.h"
#include "fat_fs.h"

static uint8_t chunk[SAVE_PART_SIZE+1]={0};

/*
 tr sound_recorder_proc
 */
bool test_sound_recorder_deps(void) {
    LOG_INFO(SOUND_RECORDER, "%s():", __FUNCTION__);
    bool res = true;

    SoundRecorderHandle_t* Node = SoundRecorderGetNode(1);
    ASSERT_NE(NULL, Node);

    res = i2s_audio_set_data_dirrection(Node->i2s_num, INTERFACE_OPERATION_RECEPTION);
    ASSERT_TRUE(res);

    res = i2s_gpio_set_read(Node->i2s_num);
    ASSERT_TRUE(res);


    res =  test_i2s_dma_half_read(Node->i2s_num  );
    ASSERT_TRUE(res);

    res =  test_i2s_dma_done_read(Node->i2s_num  );
    ASSERT_TRUE(res);

    res= test_wm8731_hashset();
    ASSERT_TRUE(res);

#if 0
    res= test_wm8731_sidetone();
    ASSERT_TRUE(res);

    res= test_wm8731_reinit();
    ASSERT_TRUE(res);
#endif

    res = test_wm8731_types();
    ASSERT_TRUE(res);

    return res;
}

bool test_sound_recorder_save_perf(void) {
    LOG_INFO(SOUND_RECORDER, "%s():", __FUNCTION__);
    bool res = true;

    res = test_fat_fs_perf_write();
    ASSERT_TRUE(res);

    return res;
}


bool test_sound_recorder_types(void) {
    bool res = true;
    LOG_INFO(SOUND_RECORDER, "%s():", __FUNCTION__);
    SoundRecorderHandle_t* Node = SoundRecorderGetNode(1);
    ASSERT_NE(NULL, Node);
    return res;
}

bool test_sound_recorder_rec(void) {
    bool res = true;
    LOG_INFO(SOUND_RECORDER, "%s():", __FUNCTION__);

    SoundRecorderHandle_t* Node = SoundRecorderGetNode(1);
    ASSERT_NE(NULL, Node);

    res = sound_recorder_start(1, WAV_REC_FILE, 3.5);
    ASSERT_TRUE(res);
    ASSERT_NE(SOUND_RECORDER_STATE_IDLE, Node->state);
    ASSERT_TRUE(wait_in_loop_ms(5000));
    ASSERT_EQ(SOUND_RECORDER_STATE_IDLE,Node->state);

    return res;
}


static bool test_sound_recorder_write_perf_one( const uint32_t one_write_timeout_us) {
    LOG_INFO(TEST, "%s():TimeOut:%u us", __FUNCTION__,one_write_timeout_us);
    bool res = true;
    static uint32_t sn = 0;
    FRESULT ret = FR_OK;
    sn++;
    char file_name[80] = "";
    snprintf(file_name, sizeof(file_name),"TWP%u.bin", sn);

    FIL File = {0};
    ASSERT_TRUE( fat_fs_open_force(&File, file_name));

    uint32_t total_size = 0;
    memset(chunk, 0x5A, sizeof(chunk));
    uint32_t i = 0;
    for(i=0;total_size < TEST_WAV_FILE_SIZE;i++) {
        UINT written = 0;
        uint32_t start_save_us = time_get_us32();
        ret = f_write(&File, chunk, SAVE_PART_SIZE, &written);
        uint32_t end_save_us = time_get_us32();

        uint32_t diff_us = end_save_us-start_save_us;
        EXPECT_GR( diff_us, one_write_timeout_us);

        if(one_write_timeout_us < diff_us) {
            LOG_ERROR(TEST,"LongWrite,I:%u,Duration:%u us",i, diff_us);
        }

        EXPECT_EQ(FR_OK, ret);
        EXPECT_EQ(SAVE_PART_SIZE, written);
        if( FR_OK != ret ) {
            LOG_ERROR(TEST,"%u,WrError:%s",i, FatFsResToStr(ret ));
            break;
        }
        if(SAVE_PART_SIZE!=written) {
            break;
        }
        total_size += written;
    }

    ret = f_close(&File);
    LOG_INFO(TEST,"CloseCode:%s " , FatFsResToStr(ret ));
    ASSERT_EQ(FR_OK, ret);
    LOG_INFO(TEST,"totalSize:%u Byte", total_size );
    EXPECT_EQ(TEST_WAV_FILE_SIZE, total_size);
    return res;
}

/*
tr sound_recorder_write_perf
 */
bool test_sound_recorder_write_perf(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true ;
    ASSERT_TRUE(test_sound_recorder_write_perf_one( REC_PART_32K_TIMEOUT_US) );
    ASSERT_TRUE(test_sound_recorder_write_perf_one( REC_PART_48K_TIMEOUT_US) );
    ASSERT_TRUE(test_sound_recorder_write_perf_one( REC_PART_88K_TIMEOUT_US) );
    ASSERT_TRUE(test_sound_recorder_write_perf_one( REC_PART_96K_TIMEOUT_US) );
    return res;
}


