#include "graphviz_to_tsort_diag.h"

#include <stdio.h>
#include <string.h>

#include "csv.h"
#include "graphviz_to_tsort.h"
#include "log.h"

const char*  GraphvizToTsortStateToStr(GraTsortState_t state){
	const char* name = "?";
	switch(state){
	    case GRA_TSORT_STATE_IDLE:name = "Idle"; break;
	    case GRA_TSORT_STATE_SOURCE:name = "Src"; break;
	    case GRA_TSORT_STATE_WAIT_ARROW:name = "WaitArrow"; break;
	    case GRA_TSORT_STATE_RX_ARROW:name = "RxArrow"; break;
	    case GRA_TSORT_STATE_DESTINATION:name = "Dest"; break;
	    case GRA_TSORT_STATE_LINE_DONE:name = "LineDone"; break;
	    default : break;
	}
	return name;
}


const char* GraphvizToTsortInputToStr(    GraTsortInput_t input){
	const char* name = "?";
	switch(input){
	case GRA_TSORT_INPUT_LETTER:name = "Letter"; break;
	case GRA_TSORT_INPUT_DASH:name = "-"; break;
	case GRA_TSORT_INPUT_RIGHT_ARROW:name = ">"; break;
	case GRA_TSORT_INPUT_END_OF_LINE:name = "EndOfLine"; break;
	case GRA_TSORT_INPUT_SPACE:name = " "; break;
	case GRA_TSORT_INPUT_REST:name = "REST"; break;
	default : break;
	}
	return name;
}

const char* GraphvizToTsortDiagToStr(const GraphvizToTsortHandle_t* const Node){
    static char text[120]="";
    strcpy(text,"");
    snprintf(text,sizeof(text),"%sState:%s,",text, GraphvizToTsortStateToStr(Node->state));
    snprintf(text,sizeof(text),"%sIn:%s,",text, GraphvizToTsortInputToStr(Node->input));
    snprintf(text,sizeof(text),"%s[%s]->[%s],",text, Node->Source, Node->Destination);
    snprintf(text,sizeof(text),"%ss:%u,",text, Node->s);
    snprintf(text,sizeof(text),"%sd:%u,",text, Node->d);
    snprintf(text,sizeof(text),"%sWindow:[%c%c],",text, Node->prev_letter,Node->letter);
    return text;
}

bool GraphvizToTsortDiag(const GraphvizToTsortHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(GRAPHVIZ_TO_TSORT, "%s", GraphvizToTsortDiagToStr(Node));
        res = true;
    }
    return res;
}

bool graphviz_to_tsort_diag(void){
    bool res = true;
    res = GraphvizToTsortDiag(&GraphvizToTsortInstance);
    return res;
}

#if 0
bool graphviz_to_tsort_print(const GraphvizToTsortHandle_t* const Node){
    bool res = false;
	uint32_t i = 0;
    for(i=0; i<MAX_COMP_CNT; i++) {
    	uint32_t cnt = csv_cnt(&Node->AdjacencyList[i][0],',');
    	if(cnt) {
    		LOG_INFO(GRAPHVIZ_TO_TSORT, "i:%u,N:%u,%s",i ,cnt,&Node->AdjacencyList[i][0]);
    		res = true;
    	}
    }
    return res;
}
#endif
