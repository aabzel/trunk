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

    res = test_fat_fs_write();
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
