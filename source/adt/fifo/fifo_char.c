#include "fifo_char.h"

#include <string.h>

#include "std_includes.h"

#ifdef HAS_INTERRUPT
#include "interrupt_mcal.h"
#endif

#ifdef HAS_FIFO_EXT
static bool fifo_is_valid(FifoChar_t* const Node) {
    bool res = false;
    if(Node) {
        if(Node->init_done) {
            if(0u < Node->fifoState.size) {
                if(Node->array) {
                    if(Node->fifoState.count <= Node->fifoState.size) {
                        res = true;
                    }
                }
            }
        }
    }
    return res;
}
#endif

/*Array is given outside because dynamic memory prohibited*/
bool fifo_init(FifoChar_t* const Node, uint8_t* const data, uint32_t capacity) {
    bool res = false;
#ifdef HAS_INTERRUPT
    interrupt_control_all(false);
#endif
    if(Node) {
        if(data) {
            if(0u < capacity) {
                fifo_index_init(&(Node->fifoState), capacity);
                (void)memset(data, 0x00, capacity);
                Node->array = data;
                Node->init_done = true;
                res = true;
            }
        }
    }
#ifdef HAS_INTERRUPT
    interrupt_control_all(true);
#endif
    return res;
}

bool fifo_reset(FifoChar_t* const Node) {
    // bool res = fifo_is_valid(Node);
    /*FiFo may be corrupted in run-time*/
    bool res = false;
    if(Node) {
        if(Node->array) {
            if(Node->fifoState.size) {
                (void)memset(Node->array, 0x00, Node->fifoState.size);
            }
        }
        Node->fifoState.count = 0u;
        Node->fifoState.start = 0u;
        Node->fifoState.end = 0u;
        res = true;
    }

    return res;
}

bool fifo_clean(FifoChar_t* Node) {
    bool res = true;
#ifdef HAS_FIFO_EXT
    res = fifo_is_valid(Node);
#endif
    uint32_t i = 0;
    uint8_t out_char = 0x00;
    for(i = 0; i < Node->fifoState.size; i++) {
        res = fifo_pull(Node, &out_char);
        if(false == res) {
            res = true;
            break;
        }
    }
    return res;
}
/*called from ISR*/
bool fifo_push(FifoChar_t* Node, uint8_t inChar) {
    bool res = true;
#ifdef HAS_INTERRUPT
    interrupt_control_all(false);
#endif
#ifdef HAS_FIFO_EXT
    res = fifo_is_valid(Node);
#endif
    if(res) {
        res = false;
        if((Node->fifoState.count < Node->fifoState.size)) {
            Node->array[Node->fifoState.end] = inChar;
            (void)fifo_index_add(&(Node->fifoState));
            res = true;
        }
    } else {
        Node->err_cnt++;
        res = fifo_reset(Node);
    }
#ifdef HAS_INTERRUPT
    interrupt_control_all(true);
#endif
    return res;
}

bool has_fifo_valid_data(FifoChar_t* const Node) {
    bool res = true;
#ifdef HAS_FIFO_EXT
    res = fifo_is_valid(Node);
#endif
    if(res) {
        res = false;
        if(0u < Node->fifoState.size) {
            if(0u < Node->fifoState.count) {
                uint32_t i = 0u;
                uint8_t ch = (char)0;
                for(i = 0u; i < Node->fifoState.size; i++) {
                    ch = Node->array[i];
                    if((char)0 != ch) {
                        res = true;
                        break;
                    }
                }
            }
        }
    }
    return res;
}

bool fifo_pull(FifoChar_t* Node, uint8_t* const out_char) {
    bool res = true;
#ifdef HAS_INTERRUPT
    interrupt_control_all(false);
#endif
#ifdef HAS_FIFO_EXT
    res = fifo_is_valid(Node);
#endif
    if(res) {
        res = false;
        if(0u < Node->fifoState.count) {
            (*out_char) = Node->array[Node->fifoState.start];
            Node->array[Node->fifoState.start] = (char)0x00;
            (void)fifo_index_get(&(Node->fifoState));
            res = true;
        }
    }
#ifdef HAS_INTERRUPT
    interrupt_control_all(true);
#endif
    return res;
}

#ifdef HAS_FIFO_EXT
bool fifo_peek(FifoChar_t* Node, uint8_t* const out_char) {
    bool res = true;
    res = fifo_is_valid(Node);
    if(res) {
        res = false;
        if(0u < Node->fifoState.count) {
            *out_char = Node->array[Node->fifoState.start];
            res = true;
        }
    }
    return res;
}
#endif

#ifdef HAS_FIFO_EXT
bool fifo_push_array(FifoChar_t* Node, uint8_t* const inArr, uint32_t arr_len) {
    bool res = fifo_is_valid(Node);
#ifdef HAS_INTERRUPT
    interrupt_control_all(false);
#endif
#ifdef DEBUG_FIFO_CHAR
    LOG_DEBUG(FIFO, "%s [%s] size %d" CRLF, __FUNCTION__, inArr, arr_len);
#endif
    if(res && (0u < arr_len)) { /*Spare exist*/
        uint32_t spare = fifo_get_spare(Node);
        if(arr_len <= spare) {
            res = true;
        } else {
            Node->err_cnt++;
        }

        uint16_t i = 0;
        for(i = 0u; i < arr_len; i++) {
            if(res) {
                res = fifo_push(Node, inArr[i]);
                if(false == res) {
                    Node->err_cnt++;
                }
            }
        }

#ifdef DEBUG_FIFO_CHAR
        LOG_DEBUG(FIFO, "%s filo len [%d]", __FUNCTION__, Node->fifoState.size);
#endif
    }
#ifdef HAS_INTERRUPT
    interrupt_control_all(true);
#endif
    return res;
}
#endif

#ifdef HAS_FIFO_EXT
bool fifo_pull_array(FifoChar_t* Node, uint8_t* outArr, uint32_t arr_size, uint32_t* const out_len) {
    bool res = fifo_is_valid(Node);
#ifdef HAS_INTERRUPT
    interrupt_control_all(false);
#endif
    if((outArr) && (out_len) && (res)) {
        res = false;
        bool loop = true;
        (*out_len) = 0u;
        while(loop) {
            if(0u < Node->fifoState.count) {
                uint8_t out_char = (char)0;
                if((*out_len) < (arr_size)) {
                    res = fifo_pull(Node, &out_char);
                    if(res) {
                        outArr[(*out_len)] = out_char;
                        (*out_len)++;
                    } else {
                        loop = false;
                    }
                } else {
                    /*Lack of space to store */
                    // outArr[(*out_len)] = '\0';
                    loop = false;
                    res = true;
                } /**/
            } else {
                // outArr[(*out_len)] = '\0';
                loop = false;
                res = true;
            }
        }
    } else {
        res = false;
    }
#ifdef HAS_INTERRUPT
    interrupt_control_all(true);
#endif
    return res;
}
#endif

#ifdef HAS_FIFO_EXT
bool fifo_peek_array(FifoChar_t* Node, uint8_t* outArr, uint32_t* const out_len) {
    bool res = fifo_is_valid(Node);
    if(res) {
        res = false;
        if((outArr) && (out_len)) {
            (*out_len) = 0u;
            if(true == fifo_index_valid(&(Node->fifoState))) {
                if(0u < Node->fifoState.count) {
                    uint16_t i = 0u;
                    uint16_t run = Node->fifoState.start;
                    for(i = 0; i < Node->fifoState.count; i++) {
                        outArr[i] = Node->array[run];
                        if(run < Node->fifoState.size) {
                            run++;
                        } else {
                            run = 0;
                        }
                    }
                    (*out_len) = Node->fifoState.count;
                    outArr[i] = '\0';
                    res = true;
                }
            }
        }
    }
    return res;
}
#endif

uint32_t fifo_get_count(FifoChar_t* const Node) {
    uint32_t ret = 0;
    if(Node) {
        if(Node->fifoState.count <= Node->fifoState.size) {
            ret = Node->fifoState.count;
        } else {
            /*Fix Error*/
            Node->fifoState.count = 0;
        }
    }
    return ret;
}

uint32_t fifo_get_size(FifoChar_t* const Node) {
    uint32_t ret;
    ret = fifo_index_get_size(&(Node->fifoState));
    return ret;
}

uint32_t fifo_get_spare(FifoChar_t* const Node) {
    uint32_t spare;
    spare = fifo_index_get_spare(&Node->fifoState);
    return spare;
}

bool fifo_free(FifoChar_t* Node, uint32_t size) { return fifo_index_free(&Node->fifoState, size); }
