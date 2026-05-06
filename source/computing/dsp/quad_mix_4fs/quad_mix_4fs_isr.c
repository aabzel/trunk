#include "quad_mix_4fs_isr.h"

#include "quad_mix_4fs.h"
#include "circular_buffer_index.h"

static bool quad_mix_4fs_push_ll(QuadMix4fsHandle_t *Node, QuadMix4fsSample_t in) {
    bool res = true;
    uint32_t index = circular_buffer_index_add(&Node->indexer);
    Node->x[index] = in;
    return res;
}

bool quad_mix_4fs_pop_ll(QuadMix4fsHandle_t *Node,
                             QuadMix4fsSample_t x0, QuadMix4fsSample_t *const out) {
    bool res = true;
    QuadMix4fsSample_t y = 0.0;
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

bool quad_mix_4fs_proc_in_out_ll(QuadMix4fsHandle_t *Node, QuadMix4fsSample_t x, QuadMix4fsSample_t *const y) {
    bool res = false;

    res = quad_mix_4fs_pop_ll(Node, x, y);
    if (res) {
        res = quad_mix_4fs_push_ll(Node, x);
        Node->proc_cnt++;
    }
    return res;
}


bool quad_mix_4fs_proc_in_out(uint8_t num, QuadMix4fsSample_t x, QuadMix4fsSample_t *const y) {
    bool res = false;
    QuadMix4fsHandle_t *Node = QuadMix4fsGetNode(num);
    if(Node) { // if can be commentes to boost code execution
        res = quad_mix_4fs_proc_in_out_ll(Node, x, y);
    }
    return res;
}

bool quad_mix_4fs_proc_in_out_array(uint8_t num, uint32_t size, const QuadMix4fsSample_t *const x,
        QuadMix4fsSample_t *const y) {
    bool res = false;
    QuadMix4fsHandle_t* Node = QuadMix4fsGetNode(num);
    uint32_t s = 0;
    for (s = 0; s < size; s++) {
        res = quad_mix_4fs_pop_ll(Node, x[s], &y[s]);
        if (res) {
            res = quad_mix_4fs_push_ll(Node, x[s]);
        }
    }
    return res;
}

