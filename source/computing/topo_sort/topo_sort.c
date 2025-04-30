#include "topo_sort.h"

#include <math.h>
#include <math.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "csv.h"

/*TOPO_SORT receiver invariant component*/
#include "str_utils_ex.h"
#include "str_utils.h"
#include "topo_sort_diag.h"
#include "log.h"
#include "code_generator.h"
#include "csv.h"

COMPONENT_GET_NODE(TopoSort, topo_sort)
COMPONENT_GET_CONFIG(TopoSort, topo_sort)


bool topo_sort_init_custom(void) {
    bool res = true ;
    log_level_get_set(LINE, LOG_LEVEL_INFO  );
    log_level_get_set(TOPO_SORT, LOG_LEVEL_INFO  );
    return res;
}

static DepNode_t* TopoSortNameToDep(TopoSortHandle_t* Node, char* name){
    DepNode_t*  Dep = NULL;
    uint32_t i = 0 ;
    bool res = false;
    uint32_t cnt = MAX_DEP_LIST;
    for(i=0;i<cnt;i++) {
        if(Node->DepArray[i].valid) {
            char node_name[100]={0};
            res = csv_parse_text(Node->DepArray[i].name, ',', 0, node_name, sizeof(node_name));
            if(res) {
                int ret = 0;
                ret=strcmp(name,node_name);
                if(0==ret){
                    Dep=&Node->DepArray[i];
                }
            }
        }
    }
    return Dep;
}

bool csv_delete_duplicat_left(char * csv_text){
    bool res = false ;
    if(csv_text) {
        uint32_t node_cnt = 0;
        LOG_WARNING(TOPO_SORT, "DelDupLeft");
        node_cnt = csv_cnt(csv_text, ',');
        uint32_t i = 0;
        for(i=0; i<node_cnt; i++) {
            LOG_PARN(TOPO_SORT, "%u:Text[%s]",i, csv_text);
            char node_name[100] = {0};
            res = csv_parse_text(csv_text, ',', i, node_name, sizeof(node_name));
            if(res) {
                int ret = 0 ;
                ret = strcmp("",node_name);
                if(0!=ret) {
                    uint32_t dup_cnt = csv_count_node(csv_text, ',' ,node_name);
                    if(1 < dup_cnt) {
                        LOG_DEBUG(TOPO_SORT, "%u:Duplicant:[%s][%u]",i, node_name,dup_cnt);
                        uint32_t d=0;
                        for(d=1 ; d<=(dup_cnt-1); d++){
                            char temp[200] = {0};
                            snprintf(temp,sizeof(temp),",%s,",node_name);
                            LOG_DEBUG(TOPO_SORT, "%d/%d,TryDel[%s]",d,dup_cnt,temp);
                            //str_del_substr_inplace_firts(csv_text, temp);
                            //res = replace_substring_first( csv_text, temp, ",") ;
                              replaceFirstOccurrence( csv_text, temp, ",") ;
                             i=0;
                        }
                    }
                }
            } else {
                LOG_ERROR(TOPO_SORT, "%u:NoNode",i);
            }
            node_cnt = csv_cnt(csv_text, ',');
            cli_printf( "\rProgress:%2u/%2u ",i, node_cnt);
        }
    }
    return res;
}

bool topo_sort_proc_ll(TopoSortHandle_t* Node){
    bool res = false ;
    if(Node) {
        LOG_DEBUG(TOPO_SORT, "Proc:");
        strcpy(Node->result2,"");
        memset(Node->result2,0,sizeof(Node->result2));
        uint32_t node_cnt = csv_cnt(Node->result, ',');
        LOG_DEBUG(TOPO_SORT, "SwCnt:[%u]", node_cnt);
        uint32_t i = 0;
        for(i=0;i<node_cnt;i++) {
            char node_name[200] = {0};
            res = csv_parse_text(Node->result, ',', i, node_name, sizeof(node_name));
            if(res) {
               // find in dep
               if(strcmp("",node_name)) {
                   DepNode_t* DepNode=TopoSortNameToDep(Node, node_name);
                   if(DepNode) {
                       LOG_DEBUG(TOPO_SORT, "i:%u,+Deps[%s]", i, DepNode->name);
                       //size_t end = strlen(Node->result2);
                       //memset(&Node->result2[end],',',1);
                       //memcpy(&Node->result2[end+1],DepNode->name,DepNode->size);
                       if(0<i) {
                           sprintf(Node->result2,"%s,%s",Node->result2,DepNode->name);
                       } else {
                    	   sprintf(Node->result2,"%s",DepNode->name);
                       }
                       //char *strcat (Node->result2, DepNode->name);
                       LOG_PARN(TOPO_SORT, "%u,Raw[%s]",i, Node->result2);
                   }else{
                       LOG_ERROR(TOPO_SORT, "NoDeps:i:%u,[%s]", i,node_name);
                   }
               }
            }else{
                LOG_ERROR(TOPO_SORT, "Err:i:%u", i);
            }
        }

        LOG_DEBUG(TOPO_SORT, "Raw[%s]", Node->result2);
        /*Delete duplicat from left*/
        res = csv_delete_duplicat_left(Node->result2);
        LOG_WARNING(TOPO_SORT, "-Dups[%s]", Node->result2);

        memset(Node->result,0,sizeof(Node->result));
        memcpy(Node->result, Node->result2, sizeof(Node->result2));
       // res = csv_delete_duplicat_left(Node->result);
    }
    return res;
}

bool topo_sort_load_dep(uint8_t num,  char* const sw_dep){
    bool res = false ;
    LOG_WARNING(TOPO_SORT, "LoadDep:[%s]", sw_dep);
    TopoSortHandle_t* Node=TopoSortGetNode(num);
    if(Node){
         strcpy(Node->result, "");
         strcpy(Node->result2, "");
         FILE* FilePrt = NULL;
         char str_line[1000] = {0};
         FilePrt = fopen(sw_dep, "r");
         uint32_t cnt=0;

         if(FilePrt) {
             strcpy(str_line, "");
             LOG_INFO(TOPO_SORT, "File [%s] OpenOk", sw_dep);
             while(NULL != fgets(str_line, sizeof(str_line), FilePrt)) {
                 size_t len=strlen(str_line);
                 if(len){

                     uint32_t node_cnt = csv_cnt(str_line, ',');
                     LOG_INFO(TOPO_SORT, "+L:%u,[%s]%u],DepCnt:[%u]",cnt,str_line,len, node_cnt);
                     str_del_char_inplace(str_line, '\n');
                     str_del_char_inplace(str_line, '\r');
                     memset(Node->DepArray[cnt].name,0,sizeof(Node->DepArray[cnt].name));
                     memcpy(Node->DepArray[cnt].name,str_line,len-1);
                     Node->DepArray[cnt].size = len-1;
                     Node->DepArray[cnt].valid = true;
                     Node->DepArray[cnt].child_cnt=node_cnt;

                     char node_name[100]={0};
                         res = csv_parse_text(str_line, ',', 0, node_name, sizeof(node_name));
                         if(res){
                             LOG_INFO(TOPO_SORT, "%u,SwCom:[%s]Child:%u",cnt, node_name,node_cnt-1);
                             res = true;
                         }else{
                             res = false;
                             LOG_ERROR(TOPO_SORT, "GetErr:%u",cnt);
                    }
                 }


            strcpy(str_line, "");
            cnt++;
        }
        fclose(FilePrt);
    }else{
          LOG_ERROR(TOPO_SORT, "FileOpenErr");
    }
    }
    return res;
}

bool topo_sort_run(uint8_t num, char* const sw_comps, char* const sw_dep){
    bool res = false ;

    TopoSortHandle_t* Node=TopoSortGetNode(num);
    if(Node) {
        strcpy(Node->result, "");

        LOG_WARNING(TOPO_SORT, "GenerateInit:[%s]Dep:[%s]", sw_comps,sw_dep);
        res = topo_sort_load_dep(num, sw_dep);
        FILE* FilePrt = NULL;
        char csv_line[1000] = {0};
        FilePrt = fopen(sw_comps, "r");
        uint32_t cnt = 1;
        if(FilePrt) {
            LOG_INFO(TOPO_SORT, "File [%s] OpenOk", sw_comps);
            strcpy(csv_line, "");
            while(NULL != fgets(csv_line, sizeof(csv_line), FilePrt)) {
                uint32_t node_cnt = csv_cnt(csv_line, ',');
                LOG_INFO(TOPO_SORT, "Line:%u,SwComCnt:[%u]",cnt, node_cnt);
                uint32_t i = 0 ;
                for(i=0;i<node_cnt;i++){
                    char node_name[100] = {0};
                    res = csv_parse_text(csv_line, ',',   i, node_name, sizeof(node_name));
                    if (res) {
                        LOG_DEBUG(TOPO_SORT, "%u,SwCom:[%s]",i, node_name);
                        if(0<cnt){
                            snprintf(Node->result,RES_SIZE,"%s,%s",Node->result,node_name);
                        }else{
                            snprintf(Node->result,RES_SIZE,"%s",node_name);
                        }
                        uint32_t cnt = csv_cnt(Node->result, ',');
                        LOG_DEBUG(TOPO_SORT, "+Set:%u:[%s]",cnt, Node->result);
                    } else {
                        LOG_ERROR(TOPO_SORT, "GetErr:%u",i);
                    }
                }

                res = true;

                strcpy(csv_line, "");
                cnt++;
            }
            fclose(FilePrt);
        }else{
              LOG_ERROR(TOPO_SORT, "FileOpenErr");
        }

        uint32_t i=0;
        for(i=0;i<15;i++) {
            LOG_INFO(TOPO_SORT, "Iter:%u,Set:[%s]",i,Node->result);
            topo_sort_proc_ll(Node);
        }

        res = csv_print(Node->result, ',', CSV_ORVER_REVERSE);
    }
    return res;
}

bool topo_sort_init_one(uint8_t num) {
    LOG_WARNING(TOPO_SORT, "INIT:%u", num);
    bool res = false;
    const TopoSortConfig_t* Config = TopoSortGetConfig(num);
    if(Config) {
        LOG_WARNING(TOPO_SORT, "%s", TopoSortConfigToStr(Config));
        TopoSortHandle_t* Node = TopoSortGetNode(num);
        if(Node) {
            Node->num = Config->num;
            Node->valid = true;

            memset(Node->result2, 0, sizeof(Node->result2));
            memset(Node->result, 0, sizeof(Node->result));
            strcpy(Node->result2,"");
            strcpy(Node->result,"");
            log_level_get_set(TOPO_SORT, LOG_LEVEL_INFO  );
            log_level_get_set(LINE, LOG_LEVEL_INFO  );
            res = true;
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(TOPO_SORT, TOPO_SORT, topo_sort)
