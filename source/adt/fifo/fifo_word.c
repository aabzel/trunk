#include "fifo_word.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static bool is_fifo_valid(FifoWord_t* const Node) {
    bool res = false;
    if(Node) {
        if((true == Node->init_done) && (0u < Node->state.size)) {
            if(Node->state.count <= Node->state.size) {
                if(NULL != Node->array) {
                    res = true;
                }
            }
        }
    }
    return res;
}

/*Array is given outside because dynamic memory prohibited*/
bool fifo_word_init(FifoWord_t* const Node, int16_t* const inArray, uint16_t capacity) {
    bool res = false;
    if((NULL != Node) && (0u < capacity)) {
        (void)memset(inArray, 0x00, (size_t)capacity*2);
        fifo_index_init(&(Node->state), capacity);
        Node->array = inArray;
        Node->init_done = true;
        res = true;
    }
    return res;
}

bool fifo_word_reset(FifoWord_t* const Node) {
    //bool res = is_fifo_valid(Node);
    /*FiFo may be corrupted in run-time*/
    bool  res = true;
    (void)memset(Node->array, 0x00,(size_t) Node->state.size*2);
    Node->state.count = 0u;
    Node->state.start = 0u;
    Node->state.end = 0u;
    return res;
}

bool fifo_word_clean(FifoWord_t* Node) {
    bool res = is_fifo_valid(Node);
    FifoIndex_t i = 0;
    int16_t out_element = 0x00;
    for(i = 0; i < Node->state.size; i++) {
        res = fifo_word_pull(Node, &out_element);
        if(false == res) {
            res = true;
            break;
        }
    }
    return res;
}

bool fifo_word_push(FifoWord_t* Node, int16_t in_word) {
    bool res = is_fifo_valid(Node);
    if(res) {
        res = false;
        if((Node->state.count < Node->state.size)) {
            Node->array[Node->state.end] = in_word;
            (void)fifo_index_add(&(Node->state));
            res = true;
        }
    }else{
        Node->err_cnt++;
        res= fifo_word_reset(Node);
    }
    return res;
}

bool fifo_word_pull(FifoWord_t* Node, int16_t* const out_word) {
    bool res = is_fifo_valid(Node);
    if(res) {
        res = false;
        if(0u < Node->state.count) {
            (*out_word) = Node->array[Node->state.start];
            Node->array[Node->state.start] = (uint16_t)0x00;
            (void)fifo_index_get(&(Node->state));
            res = true;
        }
    }
    return res;
}

bool fifo_word_peek(FifoWord_t* Node, int16_t* const out_word) {
    bool res = is_fifo_valid(Node);
    if(res) {
        res = false;
        if(0u < Node->state.count) {
            *out_word = Node->array[Node->state.start];
            res = true;
        }
    }
    return res;
}

FifoIndex_t fifo_word_get_count(FifoWord_t* const Node) {
    FifoIndex_t ret;
    ret = Node->state.count;
    return ret;
}

FifoIndex_t fifo_word_get_size(FifoWord_t* const Node) {
    FifoIndex_t ret;
    ret = fifo_index_get_size(&(Node->state));
    return ret;
}

FifoIndex_t fifo_word_get_spare(FifoWord_t* const Node) {
    FifoIndex_t spare;
    spare  = fifo_index_get_spare(&Node->state);
    return spare;
}

bool fifo_word_free(FifoWord_t* Node, FifoIndex_t size) {
    return fifo_index_free(&Node->state, size);
}
