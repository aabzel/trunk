#include "sliding_integral.h"

//#include <complex.h>
//#include <stddef.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

//#include "array.h"
#include "circular_buffer_index.h"
#include "code_generator.h"
//#include "sliding_integral_diag.h"
//#include "float_utils.h"
#include "log.h"
//#include "table_utils.h"
//#include "utils_math.h"
//#include "debug_info.h"

COMPONENT_GET_NODE(SlidingIntegral, sliding_integral)
COMPONENT_GET_CONFIG(SlidingIntegral, sliding_integral)


static bool sliding_integral_init_common(const SlidingIntegralConfig_t* const Config,
                                         SlidingIntegralHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->max_size = Config->max_size;
            Node->size = Config->size;
            Node->x = Config->x;
            Node->sample_rate_hz = Config->sample_rate_hz;
            Node->size = Config->size;
            res = true;
        }
    }
    return res;
}


static bool sliding_integral_init_custom(void) {
    bool res = true;
    return res;
}

bool sliding_integral_reset_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SLIDING_INTEGRAL, "SLIDING_INTEGRAL%u,ResetMem", num);
    SlidingIntegralHandle_t* Node = SlidingIntegralGetNode(num);
    if(Node) {
        if(Node->x) {
            LOG_INFO(SLIDING_INTEGRAL, "ZeroMem,%s", SlidingIntegralNodeToStr(Node));
            uint32_t i = 0;
            for(i = 0; i < Node->size; i++) {
                Node->x[i] = 0;
                res = true;
            }
        }
    } else {
        LOG_ERROR(SLIDING_INTEGRAL, "NodeErr");
    }
    return res;
}

static bool sliding_integral_push_ll(SlidingIntegralHandle_t* const Node, const int32_t sample) {
    bool res = true;
    uint32_t index = circular_buffer_index_add(&Node->indexer);
    Node->x[index] = sample;
    return res;
}

static bool sliding_integral_is_valid_config(const SlidingIntegralConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->size <= Config->max_size) {
            res = false;
            LOG_ERROR(SLIDING_INTEGRAL, "SizeErr");
        }

        ifn(2 < Config->size) {
            res = false;
            LOG_ERROR(SLIDING_INTEGRAL, "MinSizeErr");
        }

        ifn(0 < Config->sample_rate_hz) {
            res = false;
            LOG_ERROR(SLIDING_INTEGRAL, "SampeReteErr");
        }

        ifn(Config->x) {
            res = false;
            LOG_ERROR(SLIDING_INTEGRAL, "XErr");
        }

        ifn(Config->name) {
            LOG_ERROR(SLIDING_INTEGRAL, "NameErr");
        }
    }

    return res;
}

int32_t sliding_integral_order_get(uint8_t num) {
    int32_t order = 0;
    SlidingIntegralHandle_t* Node = SlidingIntegralGetNode(num);
    if(Node) {
        order = Node->size;
    }
    return order;
}

/*Hi load */
#if 0
static bool sliding_integral_pull_ll(SlidingIntegralHandle_t* const Node, int32_t* const out) {
    bool res = true;
    *out =  Node->sum;
    return res;
}
#endif

/*Hi load */
inline bool sliding_integral_proc_in_out_ll(SlidingIntegralHandle_t* Node, const int32_t x, int32_t* const y) {
    bool res = false;
    if (y) {
        uint32_t old_index = circular_buffer_index_get(&Node->indexer);
        Node->sum -= Node->x[old_index];
        Node->sum += x;
        *y = Node->sum;
        res = sliding_integral_push_ll(Node, x);
#ifdef HAS_SLIDING_INTEGRAL_DEBUG
        Node->proc_cnt++;
        LOG_DEBUG(SLIDING_INTEGRAL, "x:%d->y:%d", x, *y);
#endif
    }
    return res;
}

bool sliding_integral_proc_in_out_array(uint8_t num,
                                        uint32_t size,
                                        const int32_t* const x,
                                        int32_t* const y) {
    bool res = false;
    SlidingIntegralHandle_t *Node = SlidingIntegralGetNode(num);
    if (Node) {
        uint32_t s = 0;
        for (s = 0; s < size; s++) {
            res = sliding_integral_proc_in_out_ll(Node, x[s], &y[s]);
#if 0
            uint32_t old_index = circular_buffer_index_get(&Node->indexer);
            Node->sum -= Node->x[old_index];
            Node->sum +=x;
            y[s] = Node->sum;
            res = sliding_integral_push_ll(Node, x[s]);
#endif
        }
    }
    return res;
}

bool sliding_integral_proc_in_out(uint8_t num, int32_t x, int32_t* const y) {
    bool res = false;
    SlidingIntegralHandle_t* Node = SlidingIntegralGetNode(num);
    if(Node) { // if(Node)  can be commentes to boost code execution
        res = sliding_integral_proc_in_out_ll(Node, x, y);
    }
    return res;
}

bool sliding_integral_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SLIDING_INTEGRAL, "%u,Init", num);
    const SlidingIntegralConfig_t *Config = SlidingIntegralGetConfig(num);
    res = sliding_integral_is_valid_config(Config);
    if (res) {
#ifdef HAS_SLIDING_INTEGRAL_DIAG
        LOG_WARNING(SLIDING_INTEGRAL, "%s", SlidingIntegralConfigToStr(Config));
#endif
        SlidingIntegralHandle_t *Node = SlidingIntegralGetNode(num);
        if (Node) {
            res = sliding_integral_init_common(Config, Node);
            res = sliding_integral_reset_one(num);
            Node->valid = true;
            Node->sum = 0;
            res = circular_buffer_index_init(&Node->indexer, Config->size);
        } else {
            LOG_ERROR(SLIDING_INTEGRAL, "NodeErr");
        }
    } else {
        LOG_ERROR(SLIDING_INTEGRAL, "ConfNodeErr");
    }
    return res;
}


COMPONENT_INIT_PATTERT(SLIDING_INTEGRAL, SLIDING_INTEGRAL, sliding_integral)
