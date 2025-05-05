#include "circular_buffer_word.h"

#include <string.h>

#include "log.h"
#include "std_includes.h"

static bool is_circular_buffer_valid(CircularBufferWord_t* const Node) {
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
bool circular_buffer_word_init(CircularBufferWord_t* const Node, int16_t* const inArray, uint32_t capacity) {
    bool res = false;
    if(Node) {
        if(capacity) {
            (void)memset(inArray, 0x00, capacity * sizeof(int16_t));
            res = circular_buffer_index_init(&(Node->state), capacity);
            if(res) {
                Node->array = inArray;
                Node->init_done = true;
            }
        }
    }
    return res;
}

bool circular_buffer_word_reset(CircularBufferWord_t* const Node) {
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

bool circular_buffer_word_clean(CircularBufferWord_t* Node) {
    bool res = false;
    if(Node) {
        uint32_t i = 0;
        int16_t out_element = 0x00;
        for(i = 0; i < Node->state.size; i++) {
            res = circular_buffer_word_pull(Node, &out_element);
            if(false == res) {
                res = true;
                break;
            }
        }
    }
    return res;
}

bool circular_buffer_word_push(CircularBufferWord_t* Node, int16_t in_word) {
    bool res = is_circular_buffer_valid(Node);
    if(res) {
        uint32_t idx = circular_buffer_index_add(&(Node->state));
        Node->array[idx] = in_word;
        res = true;
    } else {
        Node->err_cnt++;
        res = circular_buffer_word_reset(Node);
    }
    return res;
}

bool circular_buffer_word_pull(CircularBufferWord_t* Node, int16_t* const out_word) {
    bool res = is_circular_buffer_valid(Node);
    if(res) {
        uint32_t phy_i = circular_buffer_index_get(&(Node->state));
        int16_t val = 0;
        val = Node->array[phy_i];
        (*out_word) = val;
        res = true;
    } else {
        Node->err_cnt++;
    }
    return res;
}

/*
 * shift register
 * */
bool circular_buffer_word_get(CircularBufferWord_t* const Node, int32_t need, int16_t* const sample) {
    bool res = false;
    if(sample) {
        int32_t phy_index =
            circular_buffer_index_calc_phy_index(Node->state.size, (int32_t)Node->state.cur, (int32_t)need - 1);
        if(phy_index < Node->state.size) {
            *sample = Node->array[phy_index];
            res = true;
        } else {
            LOG_ERROR(SYS, "Error");
        }
    }
    return res;
}

bool circular_buffer_word_peek(CircularBufferWord_t* Node, int16_t* const out_word) {
    bool res = circular_buffer_word_pull(Node, out_word);
    return res;
}

uint32_t circular_buffer_word_get_size(CircularBufferWord_t* const Node) {
    uint32_t ret;
    ret = circular_buffer_index_get_size(&(Node->state));
    return ret;
}
