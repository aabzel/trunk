#include "iir_isr.h"

#include "circular_buffer_index.h"
#include "iir.h"
#include "log.h"

/*
 *Node
 *x0
 *out_val
 */
static bool iir_pop_ll(IirHandle_t* const Node, IirSample_t x0, IirSample_t* const out_val) {
    bool res = false;
    if(Node) {
        if(out_val) {
            /* I don't check pointers (Node and out_val)  for zero deliberately
               on purpose to increase performance! It is hi-load code! */
            uint32_t cb_i = 0;
            int32_t i = 0;

            IirSample_t feed_forward = 0.0; // feed forward shift register
            IirSample_t feed_back = 0.0;    // feed back shift register
            feed_forward += x0 * Node->b[0];
            for(i = 1; i < (Node->size); i++) {
                // i: 1 2 3
                // feed forward chain
                cb_i = circular_buffer_index_get_i(&Node->xIndexer, -i);
                feed_forward += Node->b[i] * Node->x[cb_i];

                // feed back chain
                // cb_i = circular_buffer_index_get_i(&Node->yIndexer, -i);
                feed_back += Node->a[i] * Node->y[cb_i];
            }

            *out_val = feed_forward - feed_back;
            LOG_DEBUG(IIR, "Pop,FILTER:%u,X_0:%f,Y_0:%f", Node->num, x0, *out_val);
            res = true;
        }
    }

    return res;
}

/*
 * charge the IIR filter
 * load samples into IIR shift registers
 *
 * in_sample  x0
 * out_sample y0
 */
static bool iir_push_ll(IirHandle_t* Node, IirSample_t in_sample, IirSample_t out_sample) {
    bool res = true;
    // I don't check pointers (Node )  for zero deliberately
    // on purpose to increase performance! It is hi-load code!
    if(Node) {
        uint32_t index = 0;
        index = circular_buffer_index_add(&Node->xIndexer);
        Node->x[index] = in_sample;

        // index = circular_buffer_index_add(&Node->yIndexer);
        Node->y[index] = out_sample;
        res = true;
    }

    return res;
}

/* Proc one tact of digital IIR filter
 *
 * num - IIR logic num
 * x0  - IIR input value
 * y   - IIR output value
 *
 * res - exe result
 */

bool iir_proc_fast_in_out(uint8_t num, IirSample_t x0, IirSample_t* const y) {
    bool res = false;
    IirHandle_t* Node = IirGetNode(num);
    if(Node) {
        LOG_DEBUG(IIR, "FILTER:%u,X:%f", num, x0);
        /* I don't check pointers (y )  for zero deliberately
        in order to increase performance! It is hi-load code! */
        res = iir_pop_ll(Node, x0, y);
        if(res) {
            res = iir_push_ll(Node, x0, *y);
        } else {
            res = false;
        }
        LOG_DEBUG(IIR, "FILTER:%u,X:%f,Y:%f", num, x0, *y);
    }
    return res;
}

IirSample_t iir_slow(uint8_t num, IirSample_t NewSample) {
    IirHandle_t* Node = IirGetNode(num);
    if(Node) {
        int n;
        // shift the old samples
        // new
        //\/
        // 2 3 4 5 6 7 8 9
        // 1 2 3 4 5 6 7 8
        for(n = (Node->size - 1); n > 0; n--) {
            Node->x[n] = Node->x[n - 1]; // input samples
            Node->y[n] = Node->y[n - 1]; // output samples
        }

        // Calculate the new output
        Node->x[0] = NewSample;
        Node->y[0] = Node->b[0] * Node->x[0];
        for(n = 1; n <= (Node->size - 1); n++) {
            Node->y[0] += Node->b[n] * Node->x[n] - Node->a[n] * Node->y[n];
        }
        LOG_DEBUG(IIR, "IIR%u,X:%f,Y:%f", num, NewSample, Node->y[0]);
    }

    return Node->y[0];
}

bool iir_proc_in_out(uint8_t num, IirSample_t x0, IirSample_t* const y) {
    bool res = false;
    if(y) {
#if 0
    	res = true;
        IirSample_t out = iir_slow(  num,   x0);
        *y = out;
#else
        res = iir_proc_fast_in_out(num, x0, y);
#endif
    }
    return res;
}
