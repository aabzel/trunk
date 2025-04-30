#include "fifo_index.h"

#include "std_includes.h"

bool fifo_index_init(fifo_index_info_t* Node, FifoIndex_t size) {
    bool res = false;
    if((NULL != Node) && (0 < size)) {
        res = true;
        Node->size = size;
        Node->count = 0U;
        Node->start = 0U;
        Node->end = 0U;
        Node->errors = false;
    }
    return res;
}

bool fifo_index_valid(const fifo_index_info_t* Node) {
    bool valid = true;
    if(Node->errors) {
        valid = false;
    }
    if(Node->count > Node->size) {
        valid = false;
    }
    if(Node->start >= Node->size) {
        valid = false;
    }
    if(Node->end >= Node->size) {
        valid = false;
    }
    if(valid) {
        FifoIndex_t idx_start = Node->start;
        FifoIndex_t idx_end = Node->end;
        if(idx_end > idx_start) {
            if((idx_end - idx_start) != Node->count) {
                valid = false;
            }
        } else {
            FifoIndex_t v_count = (idx_end + Node->size) - idx_start;
            if((v_count != (Node->count + Node->size))) {
                if(v_count != Node->count) {
                    valid = false;
                }
            }
        }
    }
    return valid;
}

FifoIndex_t fifo_index_add(fifo_index_info_t* Node) {
    FifoIndex_t ret_add = RING_INVALID_INDEX;
    if(Node->count < Node->size) {
        ret_add = Node->end;
        Node->end++;
        if(Node->size <= Node->end) {
            Node->end = 0U;
        }
        Node->count++;
    }
    return ret_add;
}

FifoIndex_t fifo_index_get(fifo_index_info_t* Node) {
    FifoIndex_t ret_get = RING_INVALID_INDEX;
    if(0U != Node->count) {
        ret_get = Node->start;
        Node->start++;
        if(Node->start >= Node->size) {
            Node->start = 0U;
        }
        Node->count--;
    }
    return ret_get;
}

bool fifo_index_free(fifo_index_info_t* Node, FifoIndex_t size_free) {
    bool res = false;
    if(size_free <= Node->count) {
        FifoIndex_t s = size_free;
        FifoIndex_t count_before_wrap = Node->size - Node->start;
        Node->count -= s;
        if(s >= count_before_wrap) {
            s -= count_before_wrap;
            Node->start = 0U;
        }
        if(0U != s) {
            Node->start += s;
        }
        res = true;
    } else {
        Node->errors = true;
        res = false;
    }
    return res;
}

FifoIndex_t fifo_index_continuus_used_size(const fifo_index_info_t* Node) {
    FifoIndex_t ret_cus = Node->size - Node->start;
    if(ret_cus > Node->count) {
        ret_cus = Node->count;
    }
    return ret_cus;
}

double fifo_index_get_used_pp(const fifo_index_info_t* Node) {
    double precent = 0.0;
    if(Node) {
        precent = 100.0 * ((double)Node->count) / ((double)Node->size);
    }
    return precent;
}

FifoIndex_t fifo_index_get_used(const fifo_index_info_t* Node) { return Node->count; }

FifoIndex_t fifo_index_get_size(const fifo_index_info_t* Node) { return Node->size; }

FifoIndex_t fifo_index_get_spare(const fifo_index_info_t* Node) { return Node->size - Node->count; }
