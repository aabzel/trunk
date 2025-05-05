#include "end_of_block_diag.h"

#include <stdio.h>
#include <string.h>

#include "end_of_block.h"
#include "log.h"

const char* EndOfBlockDiagToStr(const EndOfBlockHandle_t* const Node){
    char* name = "?";
    return name;
}

bool EndOfBlockDiag(const EndOfBlockHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(END_OF_BLOCK, "%s", EndOfBlockDiagToStr(Node));
        res = true;
    }
    return res;
}

bool end_of_block_diag(void){
    bool res = true;
    res = EndOfBlockDiag(&EndOfBlockInstance);
    return res;
}

const char* BraceInfoToStr(const  BraceInfo_t* const Node){
    static char text[100];
    if(Node) {
        strcpy(text,"");
        snprintf(text,sizeof(text),"%sCode:0x%02x,",text,Node->code);
        snprintf(text,sizeof(text),"%sDir:%u,",text,Node->dir);
        snprintf(text,sizeof(text),"%sLine:%u",text,Node->line_number);
    }
    return text;
}


const char* EndOfBlockNodeReportToStr(const EndOfBlockHandle_t* const Node){
    static char text[200];
    if(Node){
        strcpy(text,"");
        snprintf(text,sizeof(text),"%s%s,",text,Node->fileShortName);
        if(Node->violation_counter){
            snprintf(text,sizeof(text),"%s"VT_SETCOLOR_RED"Err:%u line,"VT_SETCOLOR_GREEN ,text,Node->violation_counter);
        }
        snprintf(text,sizeof(text),"%sOk:%u line,",text,Node->ok_counter);
        snprintf(text,sizeof(text),"%sPair:%u," ,text,Node->pair_cnt);
        snprintf(text,sizeof(text),"%sTotal:%u line,",text,Node->cur_line);
        snprintf(text,sizeof(text),"%sTr:%u lines,",text,Node->line_threshold);
    }
    return text;
}

const char* EndOfBlockBugInfoToStr(const EndOfBlockHandle_t* const Node){
    static char text[200]={0};
    if(Node) {
        strcpy(text,"");
        snprintf(text,sizeof(text),"%s%s,",text,Node->fileShortName);
        snprintf(text,sizeof(text),"%sL:   %u   ,",text,Node->cur_line);
        snprintf(text,sizeof(text),"%sErr:%u ,",text,Node->violation_counter);
        snprintf(text,sizeof(text),"%slack[ // end of xxx() ] ,",text);
    }
    return text;
}

