#include "adc_mcal.h"

#include "adc_const.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"
#include "microcontroller_const.h"
#include "std_includes.h"
#include "lib_iqueue.h"
#include "iqueue.h"

#include "dac_channel_mcal.h"

COMPONENT_GET_NODE(Adc, adc)
COMPONENT_GET_CONFIG(Adc, adc)

bool AdcIsValidConfig(const AdcConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;

        ifn(0.0f<Config->v_ref_voltage) {
            LOG_ERROR(LG_ADC, "ADC%u,v_ref_voltage,Err", Config->num);
            res = false;
        }
        ifn(Config->name) {
            LOG_ERROR(LG_ADC, "ADC%u,Name,Err", Config->num);
            res = false;
        }

        ifn(Config->RxSamples) {
            LOG_ERROR(LG_ADC, "ADC%u,RxSamples,Err", Config->num);
            res = false;
        }

        ifn(Config->move_mode) {
            LOG_ERROR(LG_ADC, "ADC%u,move_mode,Err", Config->num);
            res = false;
        }

        ifn(Config->SampleFifoMem) {
            LOG_ERROR(LG_ADC, "ADC%u,SampleFifoMem,Err", Config->num);
            res = false;
        }

        ifn(Config->RxSamplesCnt) {
            LOG_ERROR(LG_ADC, "ADC%u,RxSamplesCnt,Err", Config->num);
            res = false;
        }

        ifn(Config->SampleFifoMemCnt) {
            LOG_ERROR(LG_ADC, "ADC%u,SampleFifoMemCnt,Err", Config->num);
            res = false;
        }

        ifn(Config->trigger_source) {
            LOG_ERROR(LG_ADC, "ADC%u,trigger_source,Err", Config->num);
            res = false;
        }

        ifn(Config->resolution) {
            LOG_ERROR(LG_ADC, "ADC%u,resolution,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool adc_init_common(const AdcConfig_t* const Config, AdcHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->move_mode = Config->move_mode;
            Node->resolution = Config->resolution;
            Node->v_ref_voltage = Config->v_ref_voltage;
            Node->num = Config->num;
            Node->trigger_source = Config->trigger_source;
            Node->irq_priority = Config->irq_priority;

            Node->RxSamples = Config->RxSamples;
            Node->RxSamplesCnt = Config->RxSamplesCnt;

            Node->SampleFifoMem = Config->SampleFifoMem;
            Node->SampleFifoMemCnt = Config->SampleFifoMemCnt;

            res = true;
        }
    }
    return res;
}


_WEAK_FUN_
bool adc_set_vref(uint8_t adc_num, float v_ref_voltage) {
    bool res = false;
    return res;
}

/* 0 - 0.0 V
   4095 -3.3 V */
float AdcSample12ToVoltageVef3_3(const uint32_t sample) {
    float voltage_v = 0.0f;
    voltage_v = (3.3f *( (float) sample))/((float)ADC_MAX_VAL_12BIT);
    return voltage_v;
}


_WEAK_FUN_
bool adc_init_custom(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool adc_init_one(uint8_t num) {
    bool res = false;
    return res;
}

// TODO add UTEST
float AdcCode2Voltage(const int32_t code) {
    float voltage_v = -100.0;
#ifdef CROSS_CODE_VOLTAGE
    voltage_v = (CROSS_CODE_VOLTAGE * ((float)code));
#endif
    return voltage_v;
}

bool adc_wait_convert_done_ll(AdcHandle_t* Node, uint32_t time_out_ms) {
    bool res = true;
    uint32_t start_ms = time_get_ms32();
    uint32_t cur_ms = start_ms;
    uint32_t diff_ms = 0;
    while(false == Node->conv_done) {
        cur_ms = time_get_ms32();
        diff_ms = cur_ms - start_ms;
        if(time_out_ms < diff_ms) {
            res = false;
            LOG_ERROR(LG_ADC, "ADC%u ConvTimeOut %u ms", Node->num, time_out_ms);
            break;
        }
    }
    return res;
}

_WEAK_FUN_
bool adc_proc_one(uint8_t num) {
    bool res = false;
#ifdef HAS_ADC_DEBUG
    log_level_t ll = log_level_get(LG_ADC);
    AdcHandle_t* Node = AdcGetNode(num);
    if(Node) {
        i_status ret;
        size_t size = 0;
        ret = iqueue_size(&Node->iQueue, &size);
        if(I_OK==ret) {
            uint32_t i = 0;
            for(i=0; i<size; i++) {
                uint16_t sample = 0;
                ret = iqueue_dequeue(&Node->iQueue, (void*) &sample);
                if(I_OK == ret) {
                    if(LOG_LEVEL_DEBUG == ll) {
                        cli_printf("\rAdc,Code:%4u,%5.3f V", sample, AdcSample12ToVoltageVef3_3(sample));
                    }
                    DacChannelHandle_t* DacCh = DacChannelGetNodeV2(1, 1);
                    if(DacCh) {
                        sample *=16;//8.......
                        ret = iqueue_enqueue(&DacCh->iQueue, (void*) &sample);
                        if(I_OK != ret){
                            LOG_DEBUG(LG_ADC, "FiFoPush,Err:%u=%s", ret, iQueueStatusToStr(ret));
                        }
                    }
                }else{
                    LOG_ERROR(LG_ADC, "FiFoPull,Err:%u=%s", ret, iQueueStatusToStr(ret));
                }
            }
        }
    }
#endif
    return res;
}

COMPONENT_INIT_PATTERT(LG_ADC, ADC, adc)
COMPONENT_PROC_PATTERT(LG_ADC, ADC, adc)

