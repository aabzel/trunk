#include "graphviz_to_tsort_commands.h"

#include "graphviz_to_tsort.h"
#include "graphviz_to_tsort_diag.h"
#include "convert.h"
#include "log.h"

bool cmd_graphviz_to_tsort_diag(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res){
        res = graphviz_to_tsort_diag();
    } else {
        LOG_ERROR(GRAPHVIZ_TO_TSORT, "Usage: gtd");
    }
    return res;
}

bool cmd_graphviz_to_tsort_proc(int32_t argc, char* argv[]) {
    bool res = false;
    char file_name[1000]="";
    if(1 <= argc) {
        res = true;
        strcpy(file_name,argv[0]);
    }

    if(res){
        res = graphviz_to_tsort_proc_gv(file_name);
        if(res){
        	LOG_INFO(GRAPHVIZ_TO_TSORT, "Proc,Ok,[%s]",file_name);
        }else{
        	LOG_ERROR(GRAPHVIZ_TO_TSORT, "Proc,Err,[%s]",file_name);
        }
    }else {
        LOG_ERROR(GRAPHVIZ_TO_TSORT, "Usage: gts");
    }
    return res;
}


