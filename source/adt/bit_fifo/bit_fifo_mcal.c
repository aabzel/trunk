#include "bit_fifo_mcal.h"

#include "array_diag.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(BitFifo, bit_fifo)
COMPONENT_GET_CONFIG(BitFifo, bit_fifo)

/* Helper: get a single bit from the byte buffer */
static uint8_t get_bit(const uint8_t *buf, uint32_t bit_index) {
    uint32_t byte_index = bit_index >> 3;// divide by 8
    uint32_t bit  = bit_index & 7; // 7=0b0111
    return (buf[byte_index] >> bit) & 1u;
}

/* Helper: set a single bit inside the byte buffer */
static void set_bit(uint8_t *buf, uint32_t bit_index, uint8_t bit_value) {
    uint32_t byte = bit_index >> 3;   // divide by 8
    uint32_t bit  = bit_index & 7;    // modulo 8
    if (bit_value) {
        buf[byte] |= (1u << bit);
    } else {
        buf[byte] &= ~(1u << bit);
    }
}

/*ISO-26262 require verify configuration*/
static bool BitFifoIsValidConfig(const BitFifoConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(BIT_FIFO, "%u,Name,Err", Config->num);
            res = false;
        }

        ifn(Config->buffer) {
            LOG_ERROR(BIT_FIFO, "%u,buffer,Err", Config->num);
            res = false;
        }

        ifn(Config->size) {
            LOG_ERROR(BIT_FIFO, "%u,capacity_bits,Err", Config->num);
            res = false;
        }
    }
    return res;
}

static bool bit_fifo_init_custom(void) {
    bool res = false;
    LOG_INFO(BIT_FIFO, "Version:%u", BIT_FIFO_VERSION);
    return res;
}

static bool bit_fifo_init_common(const BitFifoConfig_t* const Config, BitFifoHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->buffer = Config->buffer;
            Node->size = Config->size;
            res = true;
        }
    }
    return res;
}

static bool bit_fifo_init_node(BitFifoHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->valid = true;
        Node->write_bit = 0;
        Node->read_bit = 0;
        Node->overflow_cnt = 0;
        res = true;
    }
    return res;
}

bool bit_fifo_init(BitFifoHandle_t* const Node,  uint8_t* const buffer, const uint32_t buffer_bytes) {
    bool res = false;
    if(Node) {
        if(buffer) {
            if(buffer_bytes) {
                // Cast away const because we will write into the buffer later (push operations)
                memset(buffer,0,buffer_bytes);
                Node->buffer = (uint8_t*) buffer;
                Node->capacity_bits = buffer_bytes * 8;
                Node->size = buffer_bytes;
                Node->init = true;
                Node->write_bit = 0;
                Node->read_bit = 0;
                Node->overflow_cnt = 0;
                res = true;
            }
        }
    }

    return res;
}

bool bit_fifo_push(BitFifoHandle_t* const Node, const uint8_t bit) {
    bool res = false; // will be false if no overflow occurred
    if(Node) {
        if(Node->init) {
            if(Node->buffer ) {
                res = true;
                uint32_t used = Node->write_bit - Node->read_bit;
                bool was_full = (used == Node->capacity_bits);

                if(was_full) {
                    // Overwrite the oldest bit: advance read pointer
                    // Node->read_bit++;
                    Node->overflow_cnt++;
                    LOG_ERROR(BIT_FIFO,"overflow:%u",Node->overflow_cnt);
                    res = false ;
                }else{
                    uint32_t write_pos = Node->write_bit % Node->capacity_bits;
                    set_bit(Node->buffer, write_pos, bit & 1u);
                    Node->write_bit++;
                }
            }
        }
    }

    LOG_DEBUG(BIT_FIFO,"Push:%u,%s",bit,BitFifoNodeToStr(Node));
    return res;
}

bool bit_fifo_pull(BitFifoHandle_t* const Node, uint8_t* const bit) {
    bool res = false;
    if(Node) {
        if(bit) {
            if(Node->buffer) {
                if(Node->init) {
                    if(Node->write_bit != Node->read_bit) {
                        uint32_t read_pos = Node->read_bit % Node->capacity_bits;
                        *bit = get_bit(Node->buffer, read_pos);
                        Node->read_bit++;
                        res = true;
                    }
                }
            }
        }
    }
    LOG_DEBUG(BIT_FIFO,"Pull:%u,%s",*bit,BitFifoNodeToStr(Node));
    return res;
}

int32_t bit_fifo_get_count(const BitFifoHandle_t* const Node) {
    int32_t count = -1; // default error value
    if(Node) {
        if(Node->init) {
            // Number of bits currently stored is always non-negative and fits in int32_t
            count = (int32_t) (Node->write_bit - Node->read_bit);
        }
    }
    LOG_DEBUG(BIT_FIFO,"%s",BitFifoNodeToStr(Node));
    return count;
}

bool bit_fifo_peek(const BitFifoHandle_t* const Node, uint8_t* const bit) {
    bool res = false;
    if(Node) {
        if(bit) {
            if(Node->init) {
                if(Node->buffer != NULL) {
                    if(Node->write_bit != Node->read_bit) {
                        uint32_t read_pos = Node->read_bit % Node->capacity_bits;
                        *bit = get_bit(Node->buffer, read_pos);
                        res = true;
                    }
                }
            }
        }
    }
    LOG_DEBUG(BIT_FIFO,"%s",BitFifoNodeToStr(Node));
    return res;
}

static bool bit_fifo_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(BIT_FIFO, "BIT_FIFO%u", num);
    const BitFifoConfig_t* Config = BitFifoGetConfig(num);
    if(Config) {
        res = BitFifoIsValidConfig(Config);
        if(res) {
#ifdef HAS_BIT_FIFO_DIAG
            LOG_WARNING(BIT_FIFO, "Config:%s", BitFifoConfigToStr(Config));
#endif
            BitFifoHandle_t* Node = BitFifoGetNode(num);
            if(Node) {
                res = bit_fifo_init_common(Config, Node);
                res = bit_fifo_init_node(Node);
                res = bit_fifo_init(Node, Config->buffer, Config->size);
                Node->valid = true;
                Node->init = true;
                LOG_INFO(BIT_FIFO, "Init,Ok,%u", num);
            } else {
                LOG_ERROR(BIT_FIFO, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(BIT_FIFO, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(BIT_FIFO, "ConfigErr %u", num);
    }
    return res;
}

bool bit_fifo_push_array(BitFifoHandle_t* const Node,
                         uint8_t* const bit_stream,
                         const uint32_t samples) {
    bool res = false;
    if(Node) {
        if(bit_stream) {
            if(samples) {
                LOG_DEBUG(BIT_FIFO,"PushSam:[%s]", ArrayToStr(bit_stream,samples));
                res = true;
                uint32_t i = 0;
                for (i = 0; i < samples; i++) {
                    res = bit_fifo_push(Node, bit_stream[i]) && res;
                }
            }
        }
    }
    return res;
}

bool bit_fifo_pull_array(const BitFifoHandle_t* const Node,
                         uint8_t* const outArr,
                         const uint32_t arr_size,
                         uint32_t* const outLen) {
    bool res = false;
    if(outLen) {
        uint32_t i = 0;
        uint32_t rx_len = 0;
        for (i = 0; i < arr_size; i++) {
            res = bit_fifo_pull(Node, &outArr[i]);
            if(res) {
                rx_len++;
            } else {
                break;
            }
        }

        if(0 < rx_len) {
            *outLen = rx_len;
            res = true;
            LOG_DEBUG(BIT_FIFO,"PullSam:[%s]", ArrayToStr(outArr,rx_len));
        }
    }
    return res;
}

bool bit_fifo_peek_array(BitFifoHandle_t* const Node, uint8_t* const outArr, uint32_t* const outLen){
    bool res = false ;
    return res;
}



COMPONENT_INIT_PATTERT(BIT_FIFO, BIT_FIFO, bit_fifo)
