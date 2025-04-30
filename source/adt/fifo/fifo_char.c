#include "fifo_char.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef HAS_FIFO_EXT
static bool is_fifo_valid(FifoChar_t* const Node) {
    bool res = false;
    if(NULL != Node) {
        if(Node->initDone && (0u < Node->fifoState.size)) {
            if(Node->fifoState.count <= Node->fifoState.size) {
                if(NULL != Node->array) {
                    res = true;
                }
            }
        }
    }
    return res;
}
#endif

/*Array is given outside because dynamic memory prohibited*/
bool fifo_init(FifoChar_t* const Node, char* const data, uint16_t capacity) {
    bool res = false;
    if(NULL != Node) {
        if(data) {
            if(0u < capacity) {
                fifo_index_init(&(Node->fifoState), capacity);
                (void)memset(data, 0x00, capacity);
                Node->array = data;
                Node->initDone = true;
                res = true;
            }
        }
    }
    return res;
}

bool fifo_reset(FifoChar_t* const Node) {
    // bool res = is_fifo_valid(Node);
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
    res = is_fifo_valid(Node);
#endif
    FifoIndex_t i = 0;
    char out_char = 0x00;
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
bool fifo_push(FifoChar_t* Node, char inChar) {
    bool res = true;
#ifdef HAS_FIFO_EXT
    res = is_fifo_valid(Node);
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
    return res;
}

bool has_fifo_valid_data(FifoChar_t* const Node) {
    bool res = true;
#ifdef HAS_FIFO_EXT
    res = is_fifo_valid(Node);
#endif
    if(res) {
        res = false;
        if(0u < Node->fifoState.size) {
            if(0u < Node->fifoState.count) {
                uint32_t i = 0u;
                char ch = (char)0;
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

bool fifo_pull(FifoChar_t* Node, char* const out_char) {
    bool res = true;
#ifdef HAS_FIFO_EXT
    res = is_fifo_valid(Node);
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
    return res;
}

#ifdef HAS_FIFO_EXT
bool fifo_peek(FifoChar_t* Node, char* const out_char) {
    bool res = true;
    res = is_fifo_valid(Node);
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
bool fifo_push_array(FifoChar_t* Node, char* const inArr, FifoIndex_t arr_len) {
    bool res = is_fifo_valid(Node);
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
    return res;
}
#endif

#ifdef HAS_FIFO_EXT
bool fifo_pull_array(FifoChar_t* Node, char* outArr, size_t arr_size, FifoIndex_t* const out_len) {
    bool res = is_fifo_valid(Node);
    if((NULL != outArr) && (NULL != out_len) && (res)) {
        res = false;
        bool loop = true;
        (*out_len) = 0u;
        while(loop) {
            if(0u < Node->fifoState.count) {
                char out_char = (char)0;
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
    return res;
}
#endif

#ifdef HAS_FIFO_EXT
bool fifo_peek_array(FifoChar_t* Node, char* outArr, FifoIndex_t* const out_len) {
    bool res = is_fifo_valid(Node);
    if(res) {
        res = false;
        if((NULL != outArr) && (NULL != out_len)) {
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

FifoIndex_t fifo_get_count(FifoChar_t* const Node) {
    FifoIndex_t ret = 0;
    if(Node) {
        ret = Node->fifoState.count;
    }
    return ret;
}

FifoIndex_t fifo_get_size(FifoChar_t* const Node) {
    FifoIndex_t ret;
    ret = fifo_index_get_size(&(Node->fifoState));
    return ret;
}

FifoIndex_t fifo_get_spare(FifoChar_t* const Node) {
    FifoIndex_t spare;
    spare = fifo_index_get_spare(&Node->fifoState);
    return spare;
}

bool fifo_free(FifoChar_t* Node, FifoIndex_t size) { return fifo_index_free(&Node->fifoState, size); }
