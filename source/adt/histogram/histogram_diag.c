#include "histogram_diag.h"

#include <inttypes.h>
#include <string.h>
#include <stdio.h>

const char* HistogramNodeToStr(const HistogramHandle_t* const Node){
    static char name[180]="";
    if(Node) {
    	strcpy(name,"");
    	snprintf(name,sizeof(name),"%sMin:%d,",name,Node->min_val);
    	snprintf(name,sizeof(name),"%sMax:%d,",name,Node->max_val);
    	snprintf(name,sizeof(name),"%sRange:%d,",name,Node->range);
    	snprintf(name,sizeof(name),"%sResol:%d,",name,Node->resolution);
    	snprintf(name,sizeof(name),"%sCnt:%d,",name,Node->add_cnt);
    	snprintf(name,sizeof(name),"%sBins:%d,",name,Node->bin_cnt);
    	snprintf(name,sizeof(name),"%sSize:%d,",name,Node->size);
    }
    return name;
}

const char* HistogramItemToStr(const HistogramItem_t* const Node){
    static char name[180]="";
    if(Node) {
    	strcpy(name,"");
    	snprintf(name,sizeof(name),"%sIndex:%d,",name,Node->index);
    	snprintf(name,sizeof(name),"%sValue:%d,",name,Node->frequency);
    	snprintf(name,sizeof(name),"%sExpValue:%"PRId64 "",name,Node->expected_value);
    }
    return name;
}

