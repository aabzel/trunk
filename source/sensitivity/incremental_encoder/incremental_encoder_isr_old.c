#include "incremental_encoder_isr.h"

#include "incremental_encoder_mcal.h"
#include "gpio_mcal.h"
#include "ext_int_const.h"
#include "interrupt_mcal.h"

static bool incremental_encoder_ccw(IncrementalEncoderHandle_t* Node) {
    interrupt_control_all(false);
    Node->cnt--;

    return true;
}

static bool incremental_encoder_cw(IncrementalEncoderHandle_t* Node) {
    interrupt_control_all(false);
    Node->cnt++;

    return true;
}

static bool incremental_encoder_state_00_proc_input(IncrementalEncoderHandle_t* Node) {
    bool res = false;
    switch (Node->input) {
        case INC_ENCODER_INPUT_A_RISE: {
            res = incremental_encoder_ccw(Node);
        } break;
        case INC_ENCODER_INPUT_A_FALL: {
            Node->error_cnt++;
            res = false;
        } break;
        case INC_ENCODER_INPUT_B_RISE: {
            res=incremental_encoder_cw(Node);
        } break;
        case INC_ENCODER_INPUT_B_FALL: {
            Node->error_cnt++;
            res = false;
        } break;
        default: {
            Node->error_cnt++;
            res = false;
        } break;
    }
    return res;
}

static bool incremental_encoder_state_01_proc_input(IncrementalEncoderHandle_t *Node ){
    bool res = false;
    switch (Node->input) {
        case INC_ENCODER_INPUT_A_RISE: {
            res=incremental_encoder_cw(Node);
        } break;
        case INC_ENCODER_INPUT_A_FALL: {
            Node->error_cnt++;
            res = false;
        } break;
        case INC_ENCODER_INPUT_B_RISE: {
            Node->error_cnt++;
            res = false;
        } break;
        case INC_ENCODER_INPUT_B_FALL: {
            res = incremental_encoder_ccw(Node);
        } break;
        default: {
            Node->error_cnt++;
            res = false;
        } break;
    }
    return res;
}

static bool incremental_encoder_state_11_proc_input(IncrementalEncoderHandle_t *Node ){
    bool res = false;
    switch (Node->input) {
        case INC_ENCODER_INPUT_A_RISE: {
            Node->error_cnt++;
            res = false;
        } break;
        case INC_ENCODER_INPUT_A_FALL: {
            res = incremental_encoder_ccw(Node);
        } break;
        case INC_ENCODER_INPUT_B_RISE: {
            Node->error_cnt++;
            res = false;
        } break;
        case INC_ENCODER_INPUT_B_FALL: {
            res=incremental_encoder_cw(Node);
        } break;
        default: {
            Node->error_cnt++;
            res = false;
        } break;
    }
    return res;
}

static bool incremental_encoder_state_10_proc_input(IncrementalEncoderHandle_t *Node ){
    bool res = false;
    switch (Node->input) {
        case INC_ENCODER_INPUT_A_RISE: {
            Node->error_cnt++;
            res = false;
        } break;
        case INC_ENCODER_INPUT_A_FALL: {
            res=incremental_encoder_cw(Node);
        } break;
        case INC_ENCODER_INPUT_B_RISE: {
            res = incremental_encoder_ccw(Node);
        } break;
        case INC_ENCODER_INPUT_B_FALL: {
            Node->error_cnt++;
            res = false;
        } break;
        default: {
            Node->error_cnt++;
            res = false;
        } break;
    }
    return res;
}

static bool incremental_encoder_proc_input(IncrementalEncoderHandle_t *Node ) {
    bool res = false;
    IncrementalEncoderState_t read_state = incremental_encoder_read_state( Node);
    switch (read_state) {
        case INC_ENCODER_STATE_00:{
            res = incremental_encoder_state_00_proc_input(Node );
        } break;
        case INC_ENCODER_STATE_01:{
            res = incremental_encoder_state_01_proc_input(Node );
        } break;
        case INC_ENCODER_STATE_11:{
            res = incremental_encoder_state_11_proc_input(Node );
        } break;
        case INC_ENCODER_STATE_10:{
            res = incremental_encoder_state_10_proc_input(Node );
        } break;
        default:{
            Node->error_cnt++;
            res = false;
        } break;
    }
    return res;
}


bool incremental_encoder_proc_event(const Pad_t Pad, const PinIntEdge_t edge_effective) {
    bool res = false;
    interrupt_control_all(false);
    IncrementalEncoderHandle_t *Node = IncrementalEncoderPadToNode(Pad);
    if (Node) {
        Node->input = INC_ENCODER_INPUT_UNDEF;
        if (Node->PadA.byte == Pad.byte) {
            switch (edge_effective) {
                case PIN_INT_EDGE_FALLING: {
                    Node->input = INC_ENCODER_INPUT_A_FALL;
                    res = true;
                } break;
                case PIN_INT_EDGE_RISING: {
                    Node->input = INC_ENCODER_INPUT_A_RISE;
                    res = true;
                } break;
                default: {
                    Node->input = INC_ENCODER_INPUT_UNDEF;
                } break;
            }
        }

        if (Node->PadB.byte == Pad.byte) {
            switch (edge_effective) {
                case PIN_INT_EDGE_FALLING: {
                    Node->input = INC_ENCODER_INPUT_B_FALL;
                    res = true;
                } break;
                case PIN_INT_EDGE_RISING: {
                    Node->input = INC_ENCODER_INPUT_B_RISE;
                    res = true;
                } break;
                default: {
                    Node->input = INC_ENCODER_INPUT_UNDEF;
                } break;
            }
        }
        res = incremental_encoder_proc_input(Node);
    }
    interrupt_control_all(true);
    return res;
}

