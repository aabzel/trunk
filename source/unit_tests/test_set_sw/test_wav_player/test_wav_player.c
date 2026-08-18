#include "test_wav_player.h"


#include <stdio.h>
#include <string.h>

#include "std_includes.h"
#include "wav_player_mcal.h"
#include "log.h"
#include "time_mcal.h"
#include "unit_test_check.h"
#include "utils_math.h"
#include "test_i2s.h"
#include "test_dds.h"
#include "test_wm8731.h"
#include "test_sdio.h"

#ifdef HAS_FAT_FS_TEST
#include "test_fat_fs.h"
#endif

/*
 tr wav_player_proc
 */
bool test_wav_player_deps(void) {
    LOG_INFO(WAV_PLAYER, "%s():", __FUNCTION__);
    bool res = true;

    WavPlayerHandle_t* Node = WavPlayerGetNode(1);
    ASSERT_NE(NULL, Node);

    res =  test_i2s_dma_half_write(Node->i2s_num  );
    ASSERT_TRUE(res);

    res =  test_i2s_dma_done_write(Node->i2s_num  );
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

#ifdef HAS_FAT_FS_TEST
    res = test_fat_fs_read();
    ASSERT_TRUE(res);
#endif

    return res;
}

bool test_wav_player_types(void) {
    bool res = true;
    LOG_INFO(WAV_PLAYER, "%s():", __FUNCTION__);
    WavPlayerHandle_t* Node = WavPlayerGetNode(1);
    ASSERT_NE(NULL, Node);

    return res;
}

bool test_wav_player_play(void) {
    bool res = true;
    LOG_INFO(WAV_PLAYER, "%s():", __FUNCTION__);

    WavPlayerHandle_t* Node = WavPlayerGetNode(1);
    ASSERT_NE(NULL, Node);

    res = wav_player_play_file(1, TEST_WAV_NAME);
    ASSERT_TRUE(res);
    ASSERT_NE(WAV_PLAYER_STATE_IDLE, Node->state);
    ASSERT_TRUE(wait_in_loop_ms(5000));
    ASSERT_EQ(WAV_PLAYER_STATE_IDLE,Node->state);

    return res;
}
