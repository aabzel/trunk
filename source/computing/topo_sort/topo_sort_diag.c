#include "topo_sort_diag.h"

#include <stdio.h>
#include <string.h>

#include "num_to_str.h"
#include "log.h"

const char* TopoSortConfigToStr(const TopoSortConfig_t* const Config){
	static char text[250] = "";
    if(Config) {
    	strcpy(text,"");
        snprintf(text, sizeof(text), "%sN:%u,", text,Config->num);
    }
    return text;
}


const char* TopoSortNodeToStr(const TopoSortHandle_t* const Node){
	static char text[350] = "";
    if(Node){
    	strcpy(text,"");
        snprintf(text, sizeof(text), "%sN:%u Hz,", text,Node->num);
        //snprintf(text, sizeof(text), "%sSamTime:%f s,", text,Node->sample_time_s);
    }
    return text;
}


bool topo_sort_diag(uint8_t num){
	return false;
}
