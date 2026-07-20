#include "test_loopback_audio.h"


#include <stdio.h>
#include <string.h>

#include "std_includes.h"
#include "loopback_audio_mcal.h"
#include "log.h"
#include "time_mcal.h"
#include "i2s_mcal.h"
#include "unit_test_check.h"
#include "utils_math.h"
#include "test_fat_fs.h"
#include "audio.h"
#include "test_i2s.h"
#include "test_dds.h"
#include "wav.h"
#include "test_wm8731.h"
#include "test_sdio.h"

/*
 tr loopback_audio_proc
 */
bool test_loopback_audio_deps(void) {
    LOG_INFO(LOOPBACK_AUDIO, "%s():", __FUNCTION__);
    bool res = true;

    uint8_t i2s_num = loopback_audio_i2s_num_get(1);
    res = i2s_is_valid_num(i2s_num);
    ASSERT_TRUE(res);

    LoopbackAudioHandle_t* Node = LoopbackAudioGetNode(1);
    ASSERT_NE(NULL, Node);

    res =  test_i2s_dma_half_write(i2s_num  );
    ASSERT_TRUE(res);

    res =  test_i2s_dma_done_write(i2s_num );
    ASSERT_TRUE(res);

    res =  test_i2s_dma_half_read(i2s_num  );
    ASSERT_TRUE(res);

    res =  test_i2s_dma_done_read(i2s_num );
    ASSERT_TRUE(res);


    res= test_wm8731_hashset();
    ASSERT_TRUE(res);

    res= test_wm8731_sidetone();
    ASSERT_TRUE(res);

    res= test_wm8731_set_vol();
    ASSERT_TRUE(res);

    res= test_wm8731_reinit();
    ASSERT_TRUE(res);

    res = test_dds_sin();
    ASSERT_TRUE(res);

    res = test_wm8731_types();
    ASSERT_TRUE(res);

    res = test_wm8731_play();
    ASSERT_TRUE(res);

    res = test_sdio_read_dma();
    ASSERT_TRUE(res);

    res = test_fat_fs_read();
    ASSERT_TRUE(res);

    return res;
}

bool test_loopback_audio_types(void) {
    bool res = true;
    LOG_INFO(LOOPBACK_AUDIO, "%s():", __FUNCTION__);
    LoopbackAudioHandle_t* Node = LoopbackAudioGetNode(1);
    ASSERT_NE(NULL, Node);
    return res;
}

bool test_loopback_audio_rec_play_one(uint8_t num, const  char* const PlayFileName) {
    bool res = true;
    LOG_INFO(LOOPBACK_AUDIO, "%s():Play:[%s]", __FUNCTION__,PlayFileName);


    float rec_duration_s = wav_read_file_duration(PlayFileName);
    ASSERT_GR(0, rec_duration_s);
    float rec_duration_ms = SEC_2_MSEC(rec_duration_s);
    uint32_t time_out_ms =(uint32_t) (1.5f*rec_duration_ms);

    char recFile[80] = {0};
    res =  wav_file_name_generate(recFile,
                                  sizeof(recFile),
                                  LOOPBACK_MEM_SAM_CNT,
                                  rec_duration_s);
    ASSERT_TRUE(res);

    LoopbackAudioHandle_t* Node = LoopbackAudioGetNode(1);
    ASSERT_NE(NULL, Node);

    res = loopback_audio_play_rec_file(num, PlayFileName, recFile) ;
    ASSERT_TRUE(res);
    ASSERT_TRUE(wait_in_loop_ms(time_out_ms));

    res = loopback_audio_play_file(num, recFile);
    ASSERT_TRUE(res);
    ASSERT_TRUE(wait_in_loop_ms(time_out_ms));

    return res;
}

bool test_loopback_audio_rec_play(void) {
    bool res = true;
    LOG_INFO(LOOPBACK_AUDIO, "%s()", __FUNCTION__);
    res = test_loopback_audio_rec_play_one(1, TEST_WAV_PLAY);
    ASSERT_TRUE(res);
    return res;
}


bool test_loopback_audio_play(void){
    bool res = true;
    LOG_INFO(LOOPBACK_AUDIO, "%s()", __FUNCTION__);
    res = loopback_audio_play_file(1, TEST_WAV_PLAY);
    ASSERT_TRUE(res);
    return res;
}

