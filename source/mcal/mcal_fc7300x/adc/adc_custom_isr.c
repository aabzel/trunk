#include "adc_custom_isr.h"

#include "adc_mcal.h"

bool AdcIRQHandler(uint8_t num) {
    bool res = false;
    AdcHandle_t* Node = AdcGetNode(num);
    if(Node) {
        Node->it_cnt++;
        Node->it = true;
        flag_status ret = 0;
        /* ordinary channel conversion overflow flag */
        ret = adc_interrupt_flag_get(Node->ADCx, ADC_OCCO_FLAG);
        if(ret != RESET) {
            adc_flag_clear(Node->ADCx, ADC_OCCO_FLAG);
            Node->overflow_cnt++;
            Node->overflow = true;
        }

        /* ordinary channels conversion end flag */
        ret = adc_interrupt_flag_get(Node->ADCx, ADC_OCCE_FLAG);
        if(ret != RESET) {
            adc_flag_clear(Node->ADCx, ADC_OCCE_FLAG);
            Node->chan_conv_end_cnt++;
            Node->chan_conv_end = true;
            Node->data_valid = true;
        }

        /* voltage monitoring out of range flag */
        ret = adc_interrupt_flag_get(Node->ADCx, ADC_VMOR_FLAG);
        if(ret != RESET) {
            adc_flag_clear(Node->ADCx, ADC_VMOR_FLAG);
            Node->vmor_flag_cnt++;
            Node->vmor = true;
        }

        /* preempt channels conversion end flag */
        ret = adc_interrupt_flag_get(Node->ADCx, ADC_PCCE_FLAG);
        if(ret != RESET) {
            adc_flag_clear(Node->ADCx, ADC_PCCE_FLAG);
            Node->preempt_chan_conv_end_cnt++;
            Node->preempt_chan_conv_end = true;
        }

        /* preempt channel conversion start flag */
        ret = adc_interrupt_flag_get(Node->ADCx, ADC_PCCS_FLAG);
        if(ret != RESET) {
            adc_flag_clear(Node->ADCx, ADC_PCCS_FLAG);
            Node->preempt_chan_conv_start_cnt++;
            Node->preempt_chan_conv_start = true;
        }

        /* ordinary channel conversion start flag */
        ret = adc_interrupt_flag_get(Node->ADCx, ADC_OCCS_FLAG);
        if(ret != RESET) {
            adc_flag_clear(Node->ADCx, ADC_OCCS_FLAG);
            Node->conversion_start_cnt++;
            Node->conversion_start = true;
        }

        /* adc ready to conversion flag */
        ret = adc_interrupt_flag_get(Node->ADCx, ADC_RDY_FLAG);
        if(ret != RESET) {
            adc_flag_clear(Node->ADCx, ADC_RDY_FLAG);
            Node->ready_cnt++;
            Node->ready = true;
        }
        Node->is_idle = false;
    }
    return res;
}
