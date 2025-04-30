#include "fir_isr.h"

#include "circular_buffer_index.h"
#include "fir.h"
#include "log.h"

static bool fir_push_ll(FirHandle_t* Node, FirSample_t in) {
    bool res = true;
    uint32_t index = circular_buffer_index_add(&Node->indexer);
    Node->x[index] = in;
    return res;
}

bool fir_pop_ll(FirHandle_t* Node, FirSample_t x0, FirSample_t* const out) {
    bool res = true;
    FirSample_t y = 0.0;
    uint32_t cb_i = 0;

    y += x0 * Node->b[0];
    int32_t i = 0;
    for(i = 1; i < (Node->size); i++) {
        cb_i = circular_buffer_index_get_i(&Node->indexer, -i);
        y += Node->b[i] * Node->x[cb_i];
    }

    *out = y;
    return res;
}

bool fir_proc_in_out_ll(FirHandle_t* Node, FirSample_t x, FirSample_t* const y) {
    bool res = false;

    res = fir_pop_ll(Node, x, y);
    if(res) {
        res = fir_push_ll(Node, x);
        Node->proc_cnt++;
    }
    LOG_DEBUG(FIR,"%f->%f",x,*y);
    return res;
}


bool fir_proc_in_out_array(uint8_t num, uint32_t size, const FirSample_t* const x, FirSample_t* const y) {
    bool res = false;
    FirHandle_t* Node = FirGetNode(num);
    uint32_t s = 0;
    for(s = 0; s < size; s++) {
        res = fir_pop_ll(Node, x[s], &y[s]);
        if(res) {
            res = fir_push_ll(Node, x[s]);
        }
    }
    return res;
}

bool fir_proc_in_out(uint8_t num, FirSample_t x, FirSample_t* const y) {
    bool res = false;
    FirHandle_t* Node = FirGetNode(num);
    if(Node) { // if(Node)  can be commentes to boost code execution
        res = fir_proc_in_out_ll(Node, x, y);
    }
    return res;
}
