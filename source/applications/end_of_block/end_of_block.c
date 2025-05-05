#include "end_of_block.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "file_pc.h"
#include "lifo_array.h"
#include "lifo_array_diag.h"
#include "str_utils_ex.h"
#include "csv.h"


bool end_of_block_mcal_init(void) {
    bool res = true;
    log_level_get_set(LINE, LOG_LEVEL_INFO);
    log_level_get_set(END_OF_BLOCK, LOG_LEVEL_INFO);
    LOG_INFO(END_OF_BLOCK, "END_OF_BLOCK_VERSION:%u", END_OF_BLOCK_DRIVER_VERSION);
    return res;
}

static bool end_of_block_proc_brace_open(EndOfBlockHandle_t *const Node) {
    bool res = false;
    //push to stack
    BraceInfo_t* Brace = (BraceInfo_t*) malloc(sizeof(BraceInfo_t));
    if(Brace) {
        Brace->dir = BRACE_DIR_OPEN;
        Brace->line_number = Node->cur_line;
        Brace->code = END_OF_BLOCK_ID;

        Array_t Elem = {0};
        Elem.pArr = (uint8_t*)Brace;
        Elem.size = sizeof(BraceInfo_t);
        res = lifo_arr_push(&(Node->LifoArray), Elem);
        if(res){
            LOG_DEBUG(END_OF_BLOCK, "Line:  %7u  ,LifoArrayPush {",Node->cur_line);
        }else{
            LOG_ERROR(END_OF_BLOCK,"ErrPush");
        }
    }else{
        LOG_ERROR(END_OF_BLOCK,"ErrMalloc");
    }
    return res;
}

static bool EndOfBlockIsValidBrace(BraceInfo_t* Node) {
    bool res = false;
    if(Node) {
        if((BRACE_DIR_CLOSE==Node->dir) || (BRACE_DIR_OPEN==Node->dir))
        {
            if(0<Node->line_number){
                if(END_OF_BLOCK_ID==Node->code){
                    res = true;
                }else{
                    LOG_ERROR(END_OF_BLOCK,"NoCodeID");
                }
            }else{
                LOG_ERROR(END_OF_BLOCK,"NotLine");
            }
        }else{
            LOG_ERROR(END_OF_BLOCK,"NotBrase");
        }
    }

    if(false==res){
        LOG_ERROR(END_OF_BLOCK,"%s",BraceInfoToStr(Node));
    }
    return res;
}

bool end_of_block_try_reduce(EndOfBlockHandle_t *const Node) {
    bool res = false;
    LOG_DEBUG(END_OF_BLOCK,  "TryReduce");
    Array_t PrevNode={0};
    res = lifo_arr_peek_num(&(Node->LifoArray),   0, &PrevNode);
    if(res) {
        res = LivoIsValidItem(&PrevNode);

        BraceInfo_t PrevBrace={0};
        PrevBrace =    *((BraceInfo_t*)     PrevNode.pArr);

        Array_t PrevPrevNode={0};
        res = lifo_arr_peek_num(&(Node->LifoArray),   1, &PrevPrevNode);
        if (res) {
            res = LivoIsValidItem(&PrevPrevNode);

            BraceInfo_t PrevPrevBrace;
            PrevPrevBrace =    *((BraceInfo_t*)     PrevPrevNode.pArr);
            //memcpy((void *)&PrevPrevBrace,(void *)PrevPrevNode.pArr,sizeof(BraceInfo_t));

            res = EndOfBlockIsValidBrace(&PrevBrace);
            res = EndOfBlockIsValidBrace(&PrevPrevBrace);

            if(BRACE_DIR_CLOSE==PrevBrace.dir) {
                if(BRACE_DIR_OPEN==PrevPrevBrace.dir) {
                    LOG_DEBUG(END_OF_BLOCK,  "Spot{} pair");
                    Node->pair_cnt++;
                    uint32_t line_diff = PrevBrace.line_number - PrevPrevBrace.line_number;
                    if (Node->line_threshold < line_diff) {
                        char* subStr = strstr(Node->curLine,"end of");
                        if(subStr) {
                            res = true;
                            Node->ok_counter++;
                        } else {
                            Node->violation_counter++;
                            char* text = EndOfBlockBugInfoToStr(Node);
                            LOG_ERROR(END_OF_BLOCK,"%s",text);
                            res = file_pc_print_line(Node->ReportFileName , text, strlen(text) );
                        }
                    }
                    res = lifo_arr_delete_cnt(&(Node->LifoArray), 2) ;
                }
            }
        }else{
            LOG_ERROR(END_OF_BLOCK,"PeekErr");
        }
    }else{
        LOG_ERROR(END_OF_BLOCK,"PeekErr");
    }
    return res;
}

static bool end_of_block_proc_brace_close(EndOfBlockHandle_t *const Node) {
    bool res = false;
    //push to stack
    BraceInfo_t *Brace = (BraceInfo_t*) malloc(sizeof(BraceInfo_t));
    if(Brace) {
        Brace->dir = BRACE_DIR_CLOSE;
        Brace->line_number = Node->cur_line;
        Brace->code = END_OF_BLOCK_ID;

        Array_t Elem;
        Elem.pArr = (uint8_t*)Brace;
        Elem.size = sizeof(BraceInfo_t);

        res = lifo_arr_push(&(Node->LifoArray), Elem);
        if(res){
            LOG_DEBUG(END_OF_BLOCK,  "Line:%3u,LifoArrayPush }",Node->cur_line);
            res = end_of_block_try_reduce(Node);
        }else{
            LOG_ERROR(END_OF_BLOCK,"ErrPush");
        }
    }else{
        LOG_ERROR(END_OF_BLOCK,"ErrMalloc");
    }
    return res;
}

static bool end_of_block_proc_byte(EndOfBlockHandle_t* Node, char letter) {
    bool res = false ;
    switch(letter){
        case '{': {
            res = end_of_block_proc_brace_open(Node);
        } break;
        case '}': {
            res = end_of_block_proc_brace_close(Node);
            //try reduce
            res = true;
        } break;
        case '\n': {res = true;} break;
        case '\r': {res = true;} break;
        default: {res = true;} break;
    }
    return res;
}

static bool end_of_block_proc_line(EndOfBlockHandle_t* Node){
    bool res = true;
    uint32_t len=strlen(Node->curLine);
    uint32_t i = 0 ;
    uint32_t ok_cnt = 0 ;
    for(i=0; i<len; i++) {
        res = end_of_block_proc_byte(Node, Node->curLine[i]);
        if (res) {
            ok_cnt++;
        } else {
            LOG_ERROR(END_OF_BLOCK, "ProcByteErr:[%c]",Node->curLine[i]);
        }
    }
    if(len==ok_cnt) {
        res = true;
    }else{
        LOG_ERROR(END_OF_BLOCK, "ProcLineErr:[%s]",Node->curLine);
        res = false;
    }
    return res;
}

bool end_of_block_check(const char *const file_name_c, uint32_t lines ) {
    bool res = false;
    if (file_name_c) {
        if( 0 < lines) {
            EndOfBlockHandle_t EndOfBlock={0};
            EndOfBlock.line_threshold = lines;
            res = file_pc_realpath(file_name_c, EndOfBlock.fileNameC);
            if(res) {
                Array_t LifoArray[800] = {0};
                res = csv_parse_last_text(EndOfBlock.fileNameC, '/',
                                          EndOfBlock.fileShortName,
                                          sizeof(EndOfBlock.fileShortName) );
                if(res) {
                    res = csv_parse_text(EndOfBlock.fileShortName,
                                         '.',
                                         0,
                                         EndOfBlock.ReportFileName,
                                         sizeof(EndOfBlock.ReportFileName));
                    if(res) {
                        snprintf(EndOfBlock.ReportFileName,
                                 sizeof(EndOfBlock.ReportFileName),
                                 "%s_eof_report.txt",
                                 EndOfBlock.ReportFileName);

                        file_pc_delete(EndOfBlock.ReportFileName);
                    }

                    res = lifo_arr_init(&EndOfBlock.LifoArray, LifoArray, ARRAY_SIZE(LifoArray));
                    log_res(END_OF_BLOCK, res, "LiFoInit");
                    if(res) {
                        LOG_DEBUG(END_OF_BLOCK, "CheckEndOfBlockCommentIn:[%s]", EndOfBlock.fileNameC);
                        EndOfBlock.filePtr = fopen(EndOfBlock.fileNameC, "r");
                        if(EndOfBlock.filePtr) {
                            LOG_DEBUG(END_OF_BLOCK, "OpenOkFile:[%s]", EndOfBlock.fileNameC);
                            while(NULL != fgets(EndOfBlock.curLine, END_OF_BLOCK_MAX_LINE_SIZE, EndOfBlock.filePtr)) {
                                EndOfBlock.cur_line++;
                                LOG_PARN(END_OF_BLOCK, "%u,%s",EndOfBlock.cur_line, EndOfBlock.curLine);
                                res = end_of_block_proc_line(&EndOfBlock);
                                if(res) {
                                    EndOfBlock.ok_cnt++;
                                }else{
                                    EndOfBlock.err_cnt++;
                                }
                            }
                            fclose(EndOfBlock.filePtr);
                        }
                    }
                }

            }else{
                LOG_ERROR(END_OF_BLOCK, "OpenFileErr:[%s]", EndOfBlock.fileNameC);
            }

            if(0==EndOfBlock.err_cnt) {
                res = true;
            } else {
                LOG_ERROR(END_OF_BLOCK, "Err:%u", EndOfBlock.err_cnt);
            }

            LOG_INFO(END_OF_BLOCK, "%s", EndOfBlockNodeReportToStr(&EndOfBlock));
        }
    }
    return res;
}



