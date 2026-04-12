#include "median_filter.h"

#include <stdlib.h>

#include "circular_buffer_float.h"
#include "code_generator.h"
#include "float_utils.h"
#include "log.h"
#include "utils_math.h"

COMPONENT_GET_NODE(MedianFilter, median_filter)
COMPONENT_GET_CONFIG(MedianFilter, median_filter)

static bool median_filter_init_custom(void) {
    bool res = true;
    LOG_INFO(MEDIAN_FILTER, "CustomInit");
    return res;
}

static bool median_filter_init_common(const MedianFilterConfig_t* Config, MedianFilterHandle_t* Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->sample_rate_hz = Config->sample_rate_hz;
            Node->num = Config->num;
            Node->size = Config->size;
            Node->temp = Config->temp;
            Node->max_size = Config->max_size;
            // Node->CircularBuffer.array = Config->x;
            uint32_t i = 0;
            for(i = 0; i < Node->size; i++) {
                // Node->x[i] = 0.0;
                Node->temp[i] = 0.0;
            }
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

static bool MedianFilterIsValidConfig(const MedianFilterConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(1 <= Config->size) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER, "Order,Err,Size:%u", Config->size);
        }

        ifn(Config->size <= Config->max_size) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER, "OrderErr,Order:%u,Max:%u", Config->size, Config->max_size);
        }

        ifn(0 < Config->sample_rate_hz) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER, "SampleRateErr");
        }

        ifn(Config->temp) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER, "Temp,Err");
        }

        ifn(Config->x) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER, "xErr");
        }

        ifn(Config->valid) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER, "ValidErr");
        }

        ifn(Config->name) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER, "NameErr");
        }
    }

    return res;
}

int32_t median_of_3_if(const int32_t a, const int32_t b, const int32_t c) {
    int32_t median;

    if((a >= b && a <= c) || (a <= b && a >= c)) {
        median = a;
    } else if((b >= a && b <= c) || (b <= a && b >= c)) {
        median = b;
    } else {
        median = c;
    }

    LOG_DEBUG(MEDIAN_FILTER, "%d,%d,%d->%d", a, b, c, median);
    return median;
}

#if 0

/*
 *
 * a=80,b=6,c=2->      6
 * */
int32_t median_of_3_if(const int32_t a, const int32_t b, const int32_t c) {
    int32_t middle = 0;

    if(a<=b) {
        if(b<=c){
            middle = b;
        }else{
            middle = c;
        }
    }else{
        //
        if(b<=c){
            middle = (a<=c ) ? a : b;
        }else{
            middle = (a<=c ) ? a : b;
        }
    }

    if(a<=c){
        if(b<=c){
            middle = (a<=b ) ? a : b;
        }else{
            middle = (a<=b ) ? a : b;
        }
    }else{
        // c < a
        if(b<=c){
            middle = (a<=b ) ? a : b;
        }else{
            middle = (a<=b ) ? a : b;
        }
    }



    if(b<=c){
        if(a<=c){
            middle = (a<=b ) ? a : b;
        }else{
            middle = (a<=b ) ? a : b;
        }
    }else{
        //
        if(a<=c){
            middle = (a<=b ) ? a : b;
        }else{
            middle = (a<=b ) ? a : b;
        }
    }





    return middle;
}
#endif

static int compare_int32(const void* x1, const void* x2) { return (*(int32_t*)x1 - *(int32_t*)x2); }

int32_t median_of_3_sort(const int32_t a, const int32_t b, const int32_t c) {
    int32_t array[3] = {a, b, c};
    qsort(array, 3, sizeof(int32_t), compare_int32);
    int32_t middle = array[1];
    LOG_DEBUG(MEDIAN_FILTER, "%d,%d,%d->%d", a, b, c, middle);
    return middle;
}

static bool median_filter_init_window(MedianFilterHandle_t* const Node) {
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < Node->size; i++) {
        float out_val = 0.0;
        res = median_filter_proc_in_out(Node->num, (float)0, &out_val);
    }
    return res;
}

bool median_filter_init_one(uint8_t num) {
    bool res = false;
    const MedianFilterConfig_t* Config = MedianFilterGetConfig(num);
    if(Config) {
        LOG_WARNING(MEDIAN_FILTER, "%s", MedianFilterConfigToStr(Config));
        res = MedianFilterIsValidConfig(Config);
        if(res) {
            MedianFilterHandle_t* Node = MedianFilterGetNode(num);
            if(Node) {
                res = median_filter_init_common(Config, Node);
                Node->parity = math_calc_parity(Node->size);
                res = circular_buffer_float_init(&Node->CircularBuffer, Config->x, Config->size);
                if(res) {
                    Node->init = true;
                    res = median_filter_init_window(Node);
                    LOG_INFO(MEDIAN_FILTER, "InitOk:%u", num);
                }
            } else {
                LOG_ERROR(MEDIAN_FILTER, "NodeErr:%u", num);
                res = false;
            }
        } else {
            LOG_ERROR(MEDIAN_FILTER, "ConfigAbsurdErr:%u", num);
            res = false;
        }
    } else {
        LOG_ERROR(MEDIAN_FILTER, "ConfErr:%u", num);
        res = false;
    }

    return res;
}

COMPONENT_INIT_PATTERT(MEDIAN_FILTER, MEDIAN_FILTER, median_filter)
