#include "i2s_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2s.h>
#include <zephyr/kernel.h>
#include <zephyr/zephyr.h>

#include "i2s_config.h"
#include "i2s_zephyr_types.h"
#include "macro_utils.h"

#ifdef HAS_SW_DAC
#include "sw_dac_drv.h"
#endif /*HAS_SW_DAC*/

#ifdef HAS_DIAG
#include "zephyr_diag.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif /*HAS_LOG*/

#ifndef HAS_ZEPHYR
#error "+HAS_ZEPHYR"
#endif

static const I2sInfo_t I2sInfoLut[] = {
#ifdef HAS_I2S0
    {
        .i2s_num = I2S_0,
        .I2sDev = DEVICE_DT_GET(DT_NODELABEL(i2s0)),
    },
#endif

#ifdef HAS_I2S1
    {
        .i2s_num = I2S_1,
        .I2sDev = DEVICE_DT_GET(DT_NODELABEL(i2s1)),
    },
#endif
};

struct device* I2sNumToI2sDevPtr(I2sNum_t i2s_num) {
    struct device* DevNode = NULL;
    uint32_t cnt = ARRAY_SIZE(I2sInfoLut);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(I2sInfoLut[i].i2s_num == i2s_num) {
            DevNode = I2sInfoLut[i].I2sDev;
            break;
        }
    }
    return DevNode;
}

bool i2s_dma_stop(uint8_t i2s_num){
    bool res = false;
    struct device* I2sDev = I2sNumToI2sDevPtr((I2sNum_t)i2s_num);
    int ret = i2s_trigger(I2sDev, I2S_DIR_TX, I2S_TRIGGER_STOP);
    if(0==ret) {
        res = true;
    }else {
        LOG_ERROR(I2S, "%u TrigStopErr %d=%s", i2s_num, ret, ErrNo2Str(ret));
    }
    return res;
}
#error Do not compile that

bool i2s_api_write(uint8_t i2s_num, uint16_t* array, size_t size){
    bool res = false;
    if(array && size) {
        struct device* I2sDev = I2sNumToI2sDevPtr((I2sNum_t)i2s_num);
        int ret = i2s_write(I2sDev, (void *) array, (size_t) size);
        if(0==ret) {
            res = true;
        } else {
            LOG_ERROR(I2S, "%u WriteErr %d=%s", i2s_num, ret, ErrNo2Str(ret));
            res = false;
        }
    }
    return res;
}

static enum i2s_trigger_cmd OnOffToI2sTrig(bool status){
    enum i2s_trigger_cmd val=0;
    switch(status){
    case true:  val=I2S_TRIGGER_START; break;
    case false: val=I2S_TRIGGER_STOP; break;
    }
    return val;
}

bool i2s_play_tx(uint8_t i2s_num,uint8_t dac_num , bool status){
    bool res = false;
    int ret = 0;
    struct device* I2sDev = I2sNumToI2sDevPtr((I2sNum_t)i2s_num);
      SwDac_t* DacNode = sw_dac_get_node(dac_num);
    if(I2sDev ) {
#ifdef HAS_SW_DAC
        if(DacNode) {
            if(DacNode->tx_sample_array) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(LG_DAC, "TrackArrayErr");
            }
            if(DacNode->sample_cnt) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(LG_DAC, "TrackSampleCntErr");
            }
        }
#endif /*HAS_SW_DAC*/
    }else {
        LOG_ERROR(I2S, "%u DevErr", i2s_num);
        res = false;
    }

    if(res) {
          LOG_DEBUG(I2S, "SpotRecord %u", dac_num);
          LOG_INFO(I2S, "Play %u Samples", DacNode->sample_cnt);
          res = i2s_api_write(i2s_num, (uint16_t*)&DacNode->tx_sample_array[0], DacNode->sample_cnt);
          enum i2s_trigger_cmd trig = OnOffToI2sTrig(status);
          ret = i2s_trigger(I2sDev, I2S_DIR_TX, trig);
          if(0==ret) {
              res = true;
          } else {
              LOG_ERROR(I2S, "%u TrigErr %d=%s", i2s_num, ret, ErrNo2Str(ret));
          }
      } else {
        LOG_ERROR(LG_DAC, "TrackErr");
    }
    return res;
}

bool i2s_send(uint8_t i2s_num, bool status){
    bool res = false;
    int ret = 0;
    struct device* I2sDev = I2sNumToI2sDevPtr((I2sNum_t)i2s_num);
    if(I2sDev) {
    	  if(status){
              LOG_INFO(I2S, "Send");
    	  }else{
    		  LOG_INFO(I2S, "Stop");
    	  }
          enum i2s_trigger_cmd trig = OnOffToI2sTrig(status);
          ret = i2s_trigger(I2sDev, I2S_DIR_TX, trig);
          if(0==ret) {
              res = true;
          } else {
              LOG_ERROR(I2S, "%u TrigErr %d=%s", i2s_num, ret, ErrNo2Str(ret));
              res = false;
          }
    }else {
        LOG_ERROR(I2S, "%u DevErr", i2s_num);
        res = false;
    }

    return res;
}


bool i2s_read_write(uint8_t i2s_num, uint32_t tx_sample){
    bool res = false;
    struct device* I2sDev = I2sNumToI2sDevPtr((I2sNum_t)i2s_num);
    int ret = i2s_trigger(I2sDev, I2S_DIR_BOTH, I2S_TRIGGER_START);
    if(0==ret) {
        res = true;
    }else {
        LOG_ERROR(I2S, "%u TrigErr %d=%s", i2s_num, ret, ErrNo2Str(ret));
    }
    return res;
}

bool i2s_read_sample(uint8_t i2s_num, size_t size){
    bool res = false;
    struct device* I2sDev = I2sNumToI2sDevPtr((I2sNum_t)i2s_num);
    if(I2sDev) {
        uint8_t* mem_block=NULL;
        int ret = i2s_read(I2sDev, &mem_block, (size_t*) &size);
        if(0==ret) {
            if(mem_block) {
                res = true;
            }else{
                LOG_ERROR(I2S, "NoData");
                res = false;
            }
        }else{
            LOG_ERROR(I2S, "%u ReadErr %d=%s", i2s_num, ret, ErrNo2Str(ret));
        }
    }
    return res;
}

uint32_t i2s_get_sample_rate(uint8_t i2s_num){
    uint32_t sample_rate=0;
    struct device* I2sDev = I2sNumToI2sDevPtr((I2sNum_t)i2s_num);
    const struct i2s_config* Config = i2s_config_get(I2sDev, I2S_DIR_TX);
    if(Config) {
        sample_rate = Config->frame_clk_freq;
    }
    return sample_rate;
}


bool i2s_api_read(uint8_t i2s_num, uint16_t* array, size_t size){
    bool res = false;
    if(array && size) {
        struct device* I2sDev = I2sNumToI2sDevPtr((I2sNum_t)i2s_num);
        uint8_t *mem_block = NULL;
        int ret = i2s_read(I2sDev, (void **) &mem_block, &size);
        if(0==ret) {
            if(mem_block) {
                res = true;
                memcpy(array,mem_block,size);
            } else {
                res = false;
                LOG_ERROR(I2S, "%u ReadDataErr", i2s_num);
            }
        } else {
            LOG_ERROR(I2S, "%u ReadErr %d=%s", i2s_num, ret, ErrNo2Str(ret));
        }
    }
    return res;
}

static enum i2s_dir I2sModeToDir(I2sMode_t i2s_mode){
    enum i2s_dir dir=0;
    switch((uint32_t )i2s_mode){
        case I2SMODE_SLAVE_TX  :{  dir=I2S_DIR_BOTH; }break;
        case I2SMODE_SLAVE_RX  :{  dir=I2S_DIR_RX;   }break;
        case I2SMODE_SLAVE     :{  dir=I2S_DIR_RX;   }break;
        case I2SMODE_MASTER    :{  dir=I2S_DIR_TX;   }break;
        case I2SMODE_MASTER_TX :{  dir=I2S_DIR_TX;   }break;
        case I2SMODE_MASTER_RX :{  dir=I2S_DIR_BOTH; }break;
        default:
            dir=I2S_DIR_TX;
            break;
    }
    return dir;
}

bool i2s_test(uint8_t i2s_num) {
    bool res = false;
    res = i2s_play_tx(i2s_num, 1 , true);
    if(res) {
        LOG_INFO(I2S, "%u playOk", i2s_num);
    }else {
        LOG_ERROR(I2S, "%u PlayErr", i2s_num);
    }
    return res;
}


static char tx_buffer[I2S_MAX_TXBUFF];
bool i2s_config_tx(uint8_t i2s_num, uint8_t word_size_bits,
		uint8_t channels ,uint32_t audio_freq) {
    bool res = true;
    LOG_INFO(I2S, "%u Config WordSize %u Byte Chan %u Freq %u Hz",
    		i2s_num,
			word_size_bits,
			channels,
			audio_freq);
    uint32_t samples_per_block  = 128;
    size_t block_size = samples_per_block*channels*(word_size_bits/8);
    LOG_INFO(I2S, "BlockSize: %u",block_size);
    if(sizeof(tx_buffer)<(block_size*BLOCK_COUNT)  ) {
    	LOG_ERROR(I2S, "HeapErr Limit:%u Needed %u byte",sizeof(tx_buffer),(block_size*BLOCK_COUNT));
    	res = false;
    }

    if(res){
        struct device* I2sDev = I2sNumToI2sDevPtr((I2sNum_t)i2s_num);
        if(I2sDev) {
            static struct k_mem_slab i2s_tx_mem_slab;
            k_mem_slab_init(&i2s_tx_mem_slab, tx_buffer, block_size, BLOCK_COUNT);
            //K_MEM_SLAB_DEFINE_STATIC(i2s_tx_mem_slab, block_size, BLOCK_COUNT, 4);
            static struct i2s_config cfg;

              cfg.word_size= word_size_bits; //
              cfg.channels=channels; //2
              cfg.format=I2S_FMT_DATA_FORMAT_I2S;
              cfg.options= I2S_OPT_BIT_CLK_CONT|I2S_OPT_BIT_CLK_MASTER | I2S_OPT_FRAME_CLK_MASTER;
              cfg.frame_clk_freq= audio_freq; /*Ok*/
              cfg.mem_slab=&i2s_tx_mem_slab;
              cfg.block_size=block_size;
              cfg.timeout=SYS_FOREVER_MS; /*milliseconds*/


            int ret = i2s_configure(I2sDev,I2S_DIR_TX,&cfg);
            if (0==ret) {
                res = true;
                LOG_INFO(I2S, "%u ConfigOk",i2s_num);
            } else {
                res = false;
                LOG_ERROR(I2S, "%u ConfigErr %d=[%s]", i2s_num, ret, ErrNo2Str(ret));
            }
        }else{
            LOG_ERROR(I2S, "%u DevErr",i2s_num);
            res = false;
        }
    }


    return res;
}


bool i2s_init_ll(uint8_t i2s_num) {
    bool res = true;
    LOG_INFO(I2S, "%u Init ", i2s_num);
    I2sHandle_t* I2sNode = I2sGetNode(i2s_num);
    const I2sConfig_t* I2sConfigNode = NULL;
    I2sConfigNode = I2sGetConfNode(i2s_num);
    if(I2sNode) {
        if(I2sConfigNode) {
            struct device* I2sDev = I2sNumToI2sDevPtr((I2sNum_t)i2s_num);
            if(I2sDev) {
            	K_MEM_SLAB_DEFINE_STATIC(MemSlab, I2S_BLOCK_SIZE, BLOCK_COUNT, 4);
                enum i2s_dir dir=I2sModeToDir(  I2sConfigNode->mode);
                LOG_INFO(I2S, "%u BlockSize: %u", I2S_BLOCK_SIZE);
                const struct i2s_config cfg ={
                  .word_size= I2sConfigNode->data_format,
                  .channels=NUMBER_OF_CHANNELS,
                  .format=I2S_FMT_DATA_FORMAT_I2S,
                  .options=I2S_OPT_BIT_CLK_CONT| I2S_OPT_BIT_CLK_MASTER | I2S_OPT_FRAME_CLK_MASTER,
                  .frame_clk_freq= I2sConfigNode->audio_freq,
                  .mem_slab=&MemSlab,
                  .block_size=I2S_BLOCK_SIZE,
                  .timeout=SYS_FOREVER_MS, /*milliseconds*/
                };

                int ret = i2s_configure(I2sDev,dir,&cfg);
                if (0==ret) {
                    res = true;
                    LOG_INFO(I2S, "%u ConfigOk",i2s_num);
                } else {
                    res = false;
                    LOG_ERROR(I2S, "%u ConfigErr %d=[%s]", i2s_num, ret, ErrNo2Str(ret));
                }
            }else{
                LOG_ERROR(I2S, "%u DevErr",i2s_num);
            }
        }else{
            LOG_ERROR(I2S, "%u StaticConfigErr",i2s_num);
        }
    } else {
        LOG_ERROR(I2S, "%u HandleErr",i2s_num);
        res = false;
    }
    return res;
}


bool i2s_init(void) {
    bool res = true;
    uint8_t cnt = 0;
#ifdef HAS_LOG
    LOG_INFO(I2S, "Init");
#endif

#ifdef HAS_I2S0
    cnt += (uint8_t)i2s_init_ll(0);
#endif /*HAS_I2S0*/

#ifdef HAS_I2S1
    cnt += (uint8_t)i2s_init_ll(1);
#endif /*HAS_I2S1*/

    if(cnt) {
        LOG_INFO(I2S, "Init %u I2Ss", cnt);
        res = true;
    } else {
        LOG_ERROR(I2S, "NoI2S init");
        res = false;
    }

    return res;
}


