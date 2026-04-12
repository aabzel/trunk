#include "circular_buffer_float.h"

#include <string.h>

#include "log.h"
#include "std_includes.h"

static bool is_circular_buffer_valid(CircularBufferFloat_t* const Node) {
    bool res = false;
    if(Node) {
        if(Node->init_done) {
            if(Node->state.size) {
                if(Node->array) {
                    res = true;
                }
            }
        }
    }
    return res;
}

/*Array is given outside because dynamic memory prohibited*/
bool circular_buffer_float_init(CircularBufferFloat_t* const Node, float* const inArray, uint32_t capacity) {
    bool res = false;
    if(Node) {
        if(capacity) {
            (void)memset(inArray, 0x00, capacity * sizeof(float));
            res = circular_buffer_index_init(&(Node->state), capacity);
            if(res) {
                Node->array = inArray;
                Node->init_done = true;
                LOG_INFO(CIRCULAR_BUFFER, "InitOk:Size%u", capacity);
            }
        }
    }
    return res;
}

bool circular_buffer_float_reset(CircularBufferFloat_t* const Node) {
    // bool res = is_circular_buffer_valid(Node);
    /*FiFo may be corrupted in run-time*/
    bool res = false;
    if(Node) {
        uint32_t size_bytes = Node->state.size * 2;
        (void)memset(Node->array, 0x00, size_bytes);
        Node->state.cur = 0u;
        res = true;
    }
    return res;
}

bool circular_buffer_float_clean(CircularBufferFloat_t* Node) {
    bool res = false;
    if(Node) {
        uint32_t i = 0;
        float out_element = 0x00;
        for(i = 0; i < Node->state.size; i++) {
            res = circular_buffer_float_pull(Node, &out_element);
            if(false == res) {
                res = true;
                break;
            }
        }
    }
    return res;
}

bool circular_buffer_float_push(CircularBufferFloat_t* Node, float in_float) {
    LOG_DEBUG(CIRCULAR_BUFFER, "Push:%f", in_float);
    bool res = is_circular_buffer_valid(Node);
    if(res) {
        uint32_t idx = circular_buffer_index_add(&(Node->state));
        LOG_DEBUG(CIRCULAR_BUFFER, "Wr,idx:%u", idx);
        Node->array[idx] = in_float;
        res = true;
    } else {
        LOG_ERROR(CIRCULAR_BUFFER, "Error");
        Node->err_cnt++;
        res = circular_buffer_float_reset(Node);
    }
    return res;
}

bool circular_buffer_float_pull(CircularBufferFloat_t* Node, float* const out_float) {
    bool res = is_circular_buffer_valid(Node);
    if(res) {
        uint32_t phy_i = circular_buffer_index_get(&(Node->state));
        float val = 0;
        val = Node->array[phy_i];
        (*out_float) = val;
        res = true;
    } else {
        Node->err_cnt++;
    }
    return res;
}

/*
 * shift register
 * */
bool circular_buffer_float_get(CircularBufferFloat_t* const Node, int32_t need, float* const sample) {
    bool res = false;
    if(sample) {
        int32_t phy_index =
            circular_buffer_index_calc_phy_index(Node->state.size, (int32_t)Node->state.cur, (int32_t)need - 1);
        if(phy_index < Node->state.size) {
            *sample = Node->array[phy_index];
            res = true;
        } else {
            LOG_ERROR(CIRCULAR_BUFFER, "Error");
        }
    }
    return res;
}

bool circular_buffer_float_peek(CircularBufferFloat_t* Node, float* const out_float) {
    bool res = circular_buffer_float_pull(Node, out_float);
    return res;
}

uint32_t circular_buffer_float_get_size(CircularBufferFloat_t* const Node) {
    uint32_t ret;
    ret = circular_buffer_index_get_size(&(Node->state));
    return ret;
}
