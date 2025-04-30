#include "quadrature_mixer_isr.h"

#include "quadrature_mixer.h"
#include "circular_buffer_index.h"

static bool quadrature_mixer_push_ll(QuadratureMixerHandle_t *Node, QuadratureMixerSample_t in) {
    bool res = true;
    uint32_t index = circular_buffer_index_add(&Node->indexer);
    Node->x[index] = in;
    return res;
}

bool quadrature_mixer_pop_ll(QuadratureMixerHandle_t *Node,
                             QuadratureMixerSample_t x0, QuadratureMixerSample_t *const out) {
    bool res = true;
    QuadratureMixerSample_t y = 0.0;
    uint32_t cb_i = 0;

    y += x0 * Node->b[0];
    uint32_t i = 0;
    for (i = 1; i < (Node->size); i++) {
        cb_i = circular_buffer_index_get_i(&Node->indexer, i-1);
        y += Node->b[i] * Node->x[cb_i];
    }

    *out = y;
    return res;
}

bool quadrature_mixer_proc_in_out_ll(QuadratureMixerHandle_t *Node, QuadratureMixerSample_t x, QuadratureMixerSample_t *const y) {
    bool res = false;

    res = quadrature_mixer_pop_ll(Node, x, y);
    if (res) {
        res = quadrature_mixer_push_ll(Node, x);
        Node->proc_cnt++;
    }
    return res;
}


bool quadrature_mixer_proc_in_out(uint8_t num, QuadratureMixerSample_t x, QuadratureMixerSample_t *const y) {
    bool res = false;
    QuadratureMixerHandle_t *Node = QuadratureMixerGetNode(num);
    if(Node) { // if can be commentes to boost code execution
        res = quadrature_mixer_proc_in_out_ll(Node, x, y);
    }
    return res;
}

bool quadrature_mixer_proc_in_out_array(uint8_t num, uint32_t size, const QuadratureMixerSample_t *const x,
        QuadratureMixerSample_t *const y) {
    bool res = false;
    QuadratureMixerHandle_t* Node = QuadratureMixerGetNode(num);
    uint32_t s = 0;
    for (s = 0; s < size; s++) {
        res = quadrature_mixer_pop_ll(Node, x[s], &y[s]);
        if (res) {
            res = quadrature_mixer_push_ll(Node, x[s]);
        }
    }
    return res;
}

