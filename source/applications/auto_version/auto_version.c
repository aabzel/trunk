#include "auto_version.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "convert.h"
#include "str_utils_ex.h"
#include "file_pc.h"

//http://all-ht.ru/inf/prog/c/func/strncmp.html

bool auto_version_proc_line(AutoVersionHandle_t* Node, char* line) {
    bool res = false;
    if(Node){
        if(line){
            size_t len = strlen(line);
            LOG_INFO(AUTO_VERSION, "ProcLine,Len:%u,Line:[%s]",len,line);
            int ret = strncmp(PREFIX, line,strlen(PREFIX));
            if(0==ret){
                LOG_WARNING(AUTO_VERSION, "SpotVerLine,Len:%u,Line:[%s]",len,line);
                char out_text[80]={0};
                uint16_t ret_len =0;
                res =  parse_text_after_prefix(line,len, out_text, &ret_len, PREFIX,' ');
                if(res) {
                    LOG_WARNING(AUTO_VERSION, "SpotValueLine,Len:%u,Line:[%s]",ret_len,out_text);
                    res = try_str2uint32(out_text, &Node->number_of_builds);
                    if(res){
                        LOG_DEBUG(AUTO_VERSION, "ParseOk,Num:%u",Node->number_of_builds);
                        Node->number_of_builds_new = Node->number_of_builds+1;
                        Node->spot_version = true;
                    }else{
                        LOG_ERROR(AUTO_VERSION, "ParseNumErr[%s]",out_text);
                    }
                }
            }else{
                LOG_DEBUG(AUTO_VERSION, "NoPrefix[%s]",PREFIX);
            }
            res = true;
        }
    }
    return res;
}

bool auto_version_proc_headr( const char* const file_name){
    bool res = false;
    if(file_name) {
        LOG_INFO(AUTO_VERSION, "ProcFile:[%s]",file_name);
        FILE *FilePtr = NULL;
        FilePtr = fopen(file_name, "r");
        if(FilePtr) {
            LOG_INFO(AUTO_VERSION, "OpenOk File:[%s]",file_name);
            //res = true;
            char line[500]={0};
            uint8_t line_num = 0;
            while (NULL != fgets(line, sizeof(line), FilePtr)) {
              LOG_DEBUG(AUTO_VERSION,"%s", line);
              res = auto_version_proc_line(&AutoVersionInstance, line);
              memset(line,0,sizeof(line));
              line_num++;
            }

            fclose(FilePtr);
            char prev_str[80]={0};
            char new_str[80]={0};
            if(AutoVersionInstance.spot_version) {
                snprintf(prev_str,sizeof(prev_str),"%s%u",PREFIX,AutoVersionInstance.number_of_builds);
                snprintf(new_str,sizeof(new_str),"%s%u",PREFIX,AutoVersionInstance.number_of_builds_new);
            }else {
                LOG_WARNING(AUTO_VERSION, "NoPrevVersionInFile:[%s]",file_name);
                snprintf(prev_str,sizeof(prev_str),"#define AUTO_VERSION_H");
                snprintf(new_str,sizeof(new_str),"#define AUTO_VERSION_H%s%s%s1",CRLF_2,CRLF_2,PREFIX);
            }
            res = file_pc_replace_substr(file_name,prev_str ,new_str);
        }else{
            LOG_ERROR(AUTO_VERSION, "OpenErr File:[%s]",file_name);
            res = false;
        }
    }
    return res;
}

bool auto_version_init(void) {
    bool res = false;
    log_level_get_set(LINE,LOG_LEVEL_DEBUG);
    log_level_get_set(AUTO_VERSION,LOG_LEVEL_DEBUG);
    res=auto_version_diag();
    LOG_INFO(AUTO_VERSION, "AUTO_VERSION_VERSION:%u",AUTO_VERSION_DRIVER_VERSION);
    AutoVersionInstance.number_of_builds=0;
    AutoVersionInstance.spot_version=false;
    return res;
}


bool auto_version_proc( void){
    bool res = false;
    res = auto_version_proc_headr( AutoVersionConfig.filename);
    if(res){
        LOG_WARNING( AUTO_VERSION,"Exit");
        exit(0);
    }
    return res;
}








