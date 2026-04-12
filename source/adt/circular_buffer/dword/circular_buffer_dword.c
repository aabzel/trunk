#include "circular_buffer_dword.h"

#include <string.h>

#include "log.h"
#include "std_includes.h"

static bool is_circular_buffer_valid(CircularBufferDword_t* const Node) {
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
bool circular_buffer_dword_init(CircularBufferDword_t* const Node, int32_t* const inArray, uint32_t capacity) {
    bool res = false;
    if(Node) {
        if(capacity) {
            (void)memset(inArray, 0x00, capacity * sizeof(int32_t));
            res = circular_buffer_index_init(&(Node->state), capacity);
            if(res) {
                Node->array = inArray;
                Node->init_done = true;
            }
        }
    }
    return res;
}

bool circular_buffer_dword_reset(CircularBufferDword_t* const Node) {
    // bool res = is_circular_buffer_valid(Node);
    /*FiFo may be corrupted in run-time*/
    bool res = false;
    if(Node) {
        uint32_t size_bytes = Node->state.size * sizeof(int32_t);
        (void)memset(Node->array, 0x00, size_bytes);
        Node->state.cur = 0u;
        res = true;
    }
    return res;
}

bool circular_buffer_dword_clean(CircularBufferDword_t* Node) {
    bool res = false;
    if(Node) {
        uint32_t i = 0;
        for(i = 0; i < Node->state.size; i++) {
            int32_t out_element = 0x00;
            res = circular_buffer_dword_pull(Node, &out_element);
            if(false == res) {
                res = true;
                break;
            }
        }
    }
    return res;
}

bool circular_buffer_dword_push(CircularBufferDword_t* Node, int32_t in_dword) {
    bool res = is_circular_buffer_valid(Node);
    if(res) {
        uint32_t idx = circular_buffer_index_add(&(Node->state));
        Node->array[idx] = in_dword;
        res = true;
    } else {
        Node->err_cnt++;
        res = circular_buffer_dword_reset(Node);
    }
    return res;
}

bool circular_buffer_dword_pull(CircularBufferDword_t* Node, int32_t* const out_dword) {
    bool res = is_circular_buffer_valid(Node);
    if(res) {
        uint32_t phy_i = circular_buffer_index_get(&(Node->state));
        int32_t val = 0;
        val = Node->array[phy_i];
        (*out_dword) = val;

        if(Node->state.size <= Node->state.add_cnt) {
            /*shift register is full*/
            res = true;
        } else {
            res = false;
        }
    } else {
        Node->err_cnt++;
    }
    return res;
}

bool circular_buffer_push_pull(CircularBufferDword_t* Node, const int32_t x, int32_t* const out_dword) {
    bool res = false;
    res = circular_buffer_dword_push(Node, x);
    //  log_res(MEDIAN_FILTER_FAST,res,"PushInShiftReg");

    res = circular_buffer_dword_pull(Node, out_dword);
    return res;
}

/*
 shift register
 */
bool circular_buffer_dword_get(CircularBufferDword_t* const Node, int32_t const need, int32_t* const sample) {
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

bool circular_buffer_dword_peek(CircularBufferDword_t* Node, int32_t* const out_dword) {
    bool res = circular_buffer_dword_pull(Node, out_dword);
    return res;
}

uint32_t circular_buffer_dword_get_size(CircularBufferDword_t* const Node) {
    uint32_t ret;
    ret = circular_buffer_index_get_size(&(Node->state));
    return ret;
}
