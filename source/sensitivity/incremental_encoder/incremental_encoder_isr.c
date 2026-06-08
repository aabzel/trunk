#include "incremental_encoder_isr.h"

#include "incremental_encoder_mcal.h"
#include "gpio_mcal.h"
#include "ext_int_const.h"
#include "iqueue.h"

static inline IncrementalEncoderInput_t incremental_encoder_spot_event( IncrementalEncoderHandle_t *Node,
        const Pad_t Pad,
        const PinIntEdge_t edge_effective){
    IncrementalEncoderInput_t input = INC_ENCODER_INPUT_UNDEF;
    if (Node->PadB.byte == Pad.byte) {
        switch (edge_effective) {
            case PIN_INT_EDGE_FALLING: {
                input  = INC_ENCODER_INPUT_B_FALL;
            } break;
            case PIN_INT_EDGE_RISING: {
                input  = INC_ENCODER_INPUT_B_RISE;
            } break;
            default: {
                input = INC_ENCODER_INPUT_UNDEF;
            } break;
        }
    }

    if (Node->PadA.byte == Pad.byte) {
        switch (edge_effective) {
            case PIN_INT_EDGE_FALLING: {
                input = INC_ENCODER_INPUT_A_FALL;
            } break;
            case PIN_INT_EDGE_RISING: {
                input = INC_ENCODER_INPUT_A_RISE;
            } break;
            default: {
                input = INC_ENCODER_INPUT_UNDEF;
            } break;
        }
    }
    return input;
}

bool incremental_encoder_proc_event(const Pad_t Pad, const PinIntEdge_t edge_effective) {
    bool res = false;
    IncrementalEncoderHandle_t *Node = IncrementalEncoderPadToNode(Pad);
    if (Node) {
        IncrementalEncoderEvent_t Event = {0};
        Event.state = incremental_encoder_read_state(Node);
        Event.timestamp_us = time_get_us32();
        Event.input = INC_ENCODER_INPUT_UNDEF;
        Event.input = (IncrementalEncoderInput_t) incremental_encoder_spot_event(Node, Pad, edge_effective);

#ifdef HAS_IQUEUE
        // Push Event to event fifo
        i_status ret = iqueue_enqueue(&Node->iQueue, (void*) &Event);
        res = iqueue_ret_res(ret );
#endif
        //res = incremental_encoder_proc_input(Node);
    }
    return res;
}

//bool CallBackBFalling (void);
//bool CallBackAFalling (void);
