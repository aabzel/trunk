#ifndef I2S_ZEPHYR_CONST_H
#define I2S_ZEPHYR_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "i2s_const.h"

typedef enum {
	I2S_0=0,
	I2S_UNFED=1
}I2sNum_t;

#define INITIAL_BLOCKS      1
#define BLOCK_COUNT (INITIAL_BLOCKS + 1)

#define I2S_MAX_TXBUFF (40*K_BYTES)
#define BYTES_PER_SAMPLE    sizeof(int32_t)
#define SAMPLE_FREQUENCY    I2S_AUDIO_FREQ_41K
#define NUMBER_OF_CHANNELS  2
#define SAMPLES_PER_BLOCK   ((SAMPLE_FREQUENCY / 10) * NUMBER_OF_CHANNELS)
#define I2S_BLOCK_SIZE  (BYTES_PER_SAMPLE * SAMPLES_PER_BLOCK)

#ifdef __cplusplus
}
#endif

#endif /* I2S_ZEPHYR_CONST_H  */
