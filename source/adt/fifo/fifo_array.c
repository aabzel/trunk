#include "fifo_array.h"

#include <stdlib.h>
#include <string.h>

static bool is_fifo_arr_valid(FifoArray_t* const Node) {
    bool res = false;
    if(Node) {
        if(Node->init_done) {
            res = fifo_index_valid(&(Node->fifoState));
        }
    }
    return res;
}

bool fifo_arr_init(FifoArray_t* const Node, Array_t* const heap, FifoIndex_t capacity) {
    bool res = false;
    if(NULL != Node) {
        if(heap) {
            if(0 < capacity) {
                (void)memset(heap, 0x00, capacity * (sizeof(Array_t)));
                fifo_index_init(&(Node->fifoState), capacity);
                Node->pDataArray = heap;
                Node->init_done = true;
                res = true;
            }
        }
    }
    return res;
}

FifoIndex_t fifo_arr_get_count(FifoArray_t* const Node) {
    FifoIndex_t ret;
    ret = Node->fifoState.count;
    return ret;
}

FifoIndex_t fifo_arr_get_size(FifoArray_t* const Node) {
    FifoIndex_t ret;
    ret = Node->fifoState.size;
    return ret;
}

bool fifo_arr_push(const FifoArray_t* const Node, Array_t Item) {
    bool res = false;
    res = is_fifo_arr_valid(Node);

    if(res) {
        if(Node->fifoState.count < Node->fifoState.size) {
            res = true;
        } else {
            res = false;
        }
    }

    if(res) {
        if(Node->fifoState.end < Node->fifoState.size) {
            Node->pDataArray[Node->fifoState.end] = Item;
            (void)fifo_index_add(&(Node->fifoState));
        } else {
            res = false;
        }
    }
    return res;
}

bool fifo_arr_pull(FifoArray_t* const Node, Array_t* const ArrayItem) {
    bool res = false;
    res = is_fifo_arr_valid(Node);

    if(res) {
        if(0u < Node->fifoState.count) {
            res = true;
        } else {
            res = false;
        }
    }
    if(res) {
        *ArrayItem = Node->pDataArray[Node->fifoState.start];
        memset(&Node->pDataArray[Node->fifoState.start], 0x00, sizeof(Array_t));
        (void)fifo_index_get(&(Node->fifoState));
    }
    return res;
}

bool fifo_arr_peek(FifoArray_t* const Node, Array_t* const ArrayItem) {
    bool res = false;
    res = is_fifo_arr_valid(Node);
    if(res) {
        if(0u < Node->fifoState.count) {
            *ArrayItem = Node->pDataArray[Node->fifoState.start];
        } else {
            res = false;
        }
    }
    return res;
}

bool fifo_arr_del_first(FifoArray_t* const Node) {
    bool res = false;
    Array_t Item = {0};
    res = fifo_arr_pull(Node, &Item);
    if(res) {
        res = false;
        if(Item.pArr) {
            res = true;
            /*TODO Is Item.pArr in heap memory*/
#ifdef HAS_MCU
            // free(Item.pArr); /*????*/
#endif
        }
    }
    return res;
}

bool fifo_arr_pack_frame(uint8_t* out_buf, uint32_t buf_size, FifoArray_t* const Node, uint32_t* buff_len) {
    bool res = false;
    if(out_buf && (0 < buf_size) && Node) {
        uint32_t rem_size = buf_size;
        uint32_t frame_cnt = 0;
        uint32_t index = 0;
        Array_t Item = {.size = 0, .pArr = NULL};
        do {
            res = fifo_arr_peek(Node, &Item);
            if(res) {
                if(Item.pArr) {
                    if(Item.size < rem_size) {
                        memcpy(&out_buf[index], Item.pArr, Item.size);
                        frame_cnt++;
                        index += Item.size;
                        rem_size -= Item.size;
                        res = fifo_arr_del_first(Node);
                    } else {
                        break;
                    }
                } else {
                    res = false;
                }
            } else {
                res = true;
                break;
            }
        } while(0 < rem_size);
        if(buff_len) {
            *buff_len = buf_size - rem_size;
        }
    }
    return res;
}
