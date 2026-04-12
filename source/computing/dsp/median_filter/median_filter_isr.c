#include "median_filter_isr.h"

#include <stdlib.h>
#include <string.h>

#include "array_diag.h"
#include "circular_buffer_float.h"
#include "circular_buffer_index.h"
#include "log.h"
#include "math_diag.h"
#include "median_filter.h"

/* Proc one tact of digital MEDIAN_FILTER filter
 *
 * num - MEDIAN_FILTER logic num
 * x0  - MEDIAN_FILTER input value
 * y   - MEDIAN_FILTER output value
 *
 * res - exe result
 */

bool median_filter_proc_fast_in_out(uint8_t num, float x0, float* const y) {
    bool res = false;
    MedianFilterHandle_t* Node = MedianFilterGetNode(num);
    if(Node) {
    }
    return res;
}

static int real_comparator(const void* const x1, const void* const x2) {
    int ret = 0;
    float* a = x1;
    float* b = x2;
    float diff = (*a) - (*b);
    if(0 < diff) {
        ret = 1;
    } else {
        ret = -1;
    }
    return ret;
}

static float median_filter_fetch_middle(const float* const array, const uint32_t size, const MathParity_t parity) {
    float median = 0.0;
#ifdef HAS_MED_FILT_DEBUG
    LOG_DEBUG(MEDIAN_FILTER, "Parity:%u=%s", parity, MathParityToStr(parity));
#endif
    switch(parity) {
    case MATH_PARITY_ODD: {
        uint32_t mid_index = size / 2;
        median = array[mid_index];
    } break;
    case MATH_PARITY_EVEN: {
        uint32_t mid_index1 = (size / 2) - 1; // 2/2-1 = 0
        uint32_t mid_index2 = size / 2;       //
#ifdef HAS_MED_FILT_DEBUG
        LOG_DEBUG(MEDIAN_FILTER, "Arr[%u]=%f", mid_index1, array[mid_index1]);
        LOG_DEBUG(MEDIAN_FILTER, "Arr[%u]=%f", mid_index2, array[mid_index2]);
#endif
        median = (array[mid_index1] + array[mid_index2]) / 2.0;
    } break;
    default:
        break;
    }
#ifdef HAS_MED_FILT_DEBUG
    LOG_DEBUG(MEDIAN_FILTER, "median=%f", median);
#endif
    return median;
}

bool median_filter_proc_in_out(uint8_t num, const float in_sample, float* const out_sample) {
    bool res = false;
#ifdef HAS_MED_FILT_DEBUG
    log_level_t ll = log_level_get(MEDIAN_FILTER);
    LOG_DEBUG(MEDIAN_FILTER, "Proc:%f", in_sample);
#endif
    MedianFilterHandle_t* Node = MedianFilterGetNode(num);
    if(Node) {
        res = circular_buffer_float_push(&Node->CircularBuffer, in_sample);
        if(res) {
            res = false;
            memcpy(Node->temp, Node->CircularBuffer.array, (Node->size) * sizeof(float));
#ifdef HAS_MED_FILT_DEBUG
            if(LOG_LEVEL_DEBUG == ll) {
                array_float_print(Node->temp, Node->size);
            }
#endif
            qsort(Node->temp, Node->size, sizeof(float), real_comparator);
#ifdef HAS_MED_FILT_DEBUG
            if(LOG_LEVEL_DEBUG == ll) {
                array_float_print(Node->temp, Node->size);
            }
#endif
            // MathParity_t parity=math_calc_parity(Node->size);
        }

        if(out_sample) {
            *out_sample = median_filter_fetch_middle(Node->temp, Node->size, Node->parity);
            res = true;
        }
#ifdef HAS_MED_FILT_DEBUG
        LOG_DEBUG(MEDIAN_FILTER, "%f->%f", in_sample, *out_sample);
#endif

        // float last_element = 0.0;
        // res = circular_buffer_float_pull( &Node->CircularBuffer, &last_element)&&res;
    }
    return res;
}
