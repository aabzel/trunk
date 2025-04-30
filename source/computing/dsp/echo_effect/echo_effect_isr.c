#include "echo_effect_isr.h"

#include "circular_buffer_word.h"
#include "echo_effect.h"


bool echo_effect_proc_sample_volume(uint8_t num,
        SampleType_t sample_in,
        SampleType_t* const sample_out) {
    bool res = false;
    EchoEffectHandle_t* Node = EchoEffectGetNode(num);
    if(Node) {
         int32_t old_part = (Node->numerator * sample_in) / (Node->denominator);// ?
         *sample_out = ((int16_t)old_part) ;
         res = true;
    }

    return res;
}

bool echo_effect_proc_sample(uint8_t num, SampleType_t sample_in, SampleType_t* const sample_out) {
    bool res = false;
    EchoEffectHandle_t* Node = EchoEffectGetNode(num);
    if(Node) {
        int16_t old_word = 0;
        res = circular_buffer_word_pull(&Node->CircularBuffer, &old_word);
        if(res) {
            int32_t old_part = (Node->numerator * old_word) / (Node->denominator);// ?
            *sample_out = ((int16_t)old_part) + sample_in;
            res = circular_buffer_word_push(&Node->CircularBuffer, (int16_t)*sample_out);
        }
    }

    return res;
}
