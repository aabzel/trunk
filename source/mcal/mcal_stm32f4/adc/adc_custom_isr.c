#include "adc_custom_isr.h"

#include "adc_mcal.h"
#include "dma_channel_config_adc.h"
#include "lib_iqueue.h"
#include "iqueue.h"

#ifdef HAS_ADC_FIFO
static bool load_samples_to_fifo( AdcHandle_t* Node, uint32_t start, uint32_t end){
    bool res = false ;
    uint32_t i = 0 ;
    for(i=start;i<end;i++){
        i_status ret = iqueue_enqueue(&Node->iQueue, &Node->RxSamples[i]);
        if(I_OK!=ret){
            Node->err_cnt++;
        }
    }
    return res;
}
#endif

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc) {
    uint8_t adc_num = ADC_HandleTypeDefToNum(hadc);
    AdcHandle_t* Node = AdcGetNode(adc_num);
    if(Node) {
        Node->half_cplt_done = true;
        Node->half_cplt_done_cnt++;
        //CallBackHalfAdc1();
#ifdef HAS_ADC_FIFO
#error rerer
        load_samples_to_fifo(Node,0, Node->RxSamplesCnt/2);
#endif
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    AdcHandle_t* Node = NULL;
    Node = AdcHalHandle2Handle(hadc);
    if(Node) {
       // Node->code = HAL_ADC_GetValue(&Node->adc_h);
        Node->it_cnt++;
        Node->conv_done = true;
        Node->chan_conv_end = true;
        Node->chan_conv_end_cnt++;
        //CallBackDoneAdc1();
#ifdef HAS_ADC_FIFO
        load_samples_to_fifo(Node, Node->RxSamplesCnt/2, Node->RxSamplesCnt);
#endif
    }
}


void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc) {
    uint8_t adc_num = ADC_HandleTypeDefToNum(hadc);
    AdcHandle_t* Node = AdcGetNode(adc_num);
    if(Node) {
        Node->level_out_window_done = true;
        Node->level_out_window_done_cnt++;
    }
}

void HAL_ADC_ErrorCallback(ADC_HandleTypeDef* hadc) {
    uint8_t adc_num = ADC_HandleTypeDefToNum(hadc);
    AdcHandle_t* Node = AdcGetNode(adc_num);
    if(Node) {
        Node->error_done = true;
        Node->error_done_cnt++;
    }
}
