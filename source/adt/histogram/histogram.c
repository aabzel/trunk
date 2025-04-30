#include "histogram.h"

#include <stdbool.h>
#include <string.h>


#include "log.h"
#include "histogram_types.h"
#include "code_generator.h"

COMPONENT_GET_NODE(Histogram, histogram)
COMPONENT_GET_CONFIG(Histogram, histogram)


bool histogram_add_ll(HistogramHandle_t* const Node, int32_t value) {
    bool res = false;
    if(Node) {
        if(value <= Node->max_val) {
            if(Node->min_val<=value) {
                int32_t i =0;//???
                Node->sum += (int64_t) value;
                Node->in_cnt++;
                /*In whitch bin do I need to put that value*/
                i = value/Node->resolution;
                if(i<Node->size) {
                    LOG_DEBUG(HISTOGRAM, "Add %d In[%d]",value, i);
                    Node->frequency[i]++;
                    res = true;
                }
            }
        }
    }
    return res;
}

bool histogram_add(uint8_t num, int32_t value) {
    bool res = false;
    HistogramHandle_t* Node = HistogramGetNode(num);
    if(Node) {
        res = histogram_add_ll(Node, value);
    } else {
        LOG_ERROR(HISTOGRAM, "NodeErr %u", num);
    }
    return res;
}

bool histogram_get_max(uint8_t num, HistogramItem_t* const Item) {
    bool res = true;
    HistogramHandle_t* Node = HistogramGetNode(num);
    if (Node) {
        if(Item) {
            HistogramItem_t MaxBin = {0};
            MaxBin.expected_value = Node->sum/Node->in_cnt;

            uint32_t i = 0 ;
            for(i=0; i<Node->size; i++) {
                if(MaxBin.frequency < Node->frequency[i]) {
                    MaxBin.frequency = Node->frequency[i];
                    MaxBin.index = i;
                    res = true;
                }
            }
            *Item = MaxBin;
        }
    }
    return res;
}

bool histogram_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(HISTOGRAM, "Init", num);
    const HistogramConfig_t* Config = HistogramGetConfig(num);
    if(Config) {
        HistogramHandle_t* Node = HistogramGetNode(num);
        if(Node) {
            Node->resolution = Config->resolution;
            Node->min_val = Config->min_val;
            Node->max_val = Config->max_val;
            Node->frequency = Config->frequency;
            Node->size = Config->size;
            Node->range=Node->max_val-Node->min_val;
            Node->bin_cnt =Node->range/Node->resolution;

            memset(Node->frequency,0,Node->size*sizeof(uint32_t));

            Node->sum = 0;
            Node->in_cnt=0;

            Node->err_cnt =0;
            Node->add_cnt =0;
            Node->init =true;
            LOG_INFO(HISTOGRAM,"%s",HistogramNodeToStr(Node));
            log_level_get_set(HISTOGRAM, LOG_LEVEL_INFO);
            res = true;

        }
    }
    return res;
}

bool histogram_init_custom(void){
    bool res = true;
    log_level_get_set(HISTOGRAM, LOG_LEVEL_INFO);
    return res;
}

COMPONENT_INIT_PATTERT(HISTOGRAM, HISTOGRAM, histogram)
