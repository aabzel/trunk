#include "graphviz_to_tsort.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "win_utils.h"
#include "log.h"
#include "convert.h"
#include "str_utils_ex.h"
#include "file_pc.h"
#include "csv.h"
#include "str_utils_ex.h"

#if 0
bool gra_tsort_get_spare_line(GraphvizToTsortHandle_t* Node, uint32_t* spare){
    bool res = false ;
    if(Node) {
        if(spare) {
            uint32_t i = 0 ;
            for(i=0; i < MAX_COMP_CNT; i++) {
                uint32_t cnt = csv_cnt(&Node->AdjacencyList[i][0], ',');
                if(0==cnt) {
                    LOG_DEBUG(GRAPHVIZ_TO_TSORT,"cnt:%u",cnt);
                    *spare = i;
                    res = true;
                    break;
                }else{
                }
            }
        }
    }
    if(res){
        LOG_INFO(GRAPHVIZ_TO_TSORT,"spare:%u",spare);
    } else {
        LOG_ERROR(GRAPHVIZ_TO_TSORT,"GetSpareErr");
    }

    return res;
}
#endif

#if 0
bool gra_tsort_is_dest_known(GraphvizToTsortHandle_t* Node, uint32_t* line){
    uint32_t i = 0 ;
    bool res = false ;
    bool exist = false ;
    for(i=0; i<MAX_COMP_CNT; i++) {
        uint32_t cnt = csv_cnt(&Node->AdjacencyList[i][0],',');
        if(1 <= cnt) {
            uint32_t offset = 0;
            res = csv_fetch_text(&Node->AdjacencyList[i][0], DEP_CSV_SIZE, ',', 0, &offset);
            if(res) {
                uint32_t size = strlen(Node->Destination);
                int ret = strncmp(Node->Destination, &Node->AdjacencyList[i][0], size);
                if (0==ret) {
                    exist = true;
                    *line = i;
                    break;
                }
            }
        }
    }
    return exist;
}
#endif

static bool gra_tsort_insert(GraphvizToTsortHandle_t* Node){
    bool res = false ;
    if(Node){
        char text[80]={0};
        LOG_WARNING(GRAPHVIZ_TO_TSORT,"[%s]>[%s]", Node->Source, Node->Destination);
        snprintf(text,sizeof(text),"%s %s\n",Node->Destination,Node->Source);
        size_t size = strlen(text);
        res = file_pc_print_array(Node->tsort_file, (uint8_t*) text, size);

#if 0
        uint32_t line = 0 ;
        res = gra_tsort_is_dest_known(Node, &line);
        if(res) {
             LOG_INFO(GRAPHVIZ_TO_TSORT,"KnownNode");
            res = csv_add_back(&Node->AdjacencyList[line][0],',', Node->Source);
        }else{
            LOG_INFO(GRAPHVIZ_TO_TSORT,"NewNode");
            uint32_t spare = 0 ;
            res = gra_tsort_get_spare_line(Node, &spare);
            if(res){
                LOG_INFO(GRAPHVIZ_TO_TSORT,"spare:%u",spare);
                sprintf(&Node->AdjacencyList[spare][0],"%s,%s",Node->Destination,Node->Source);
            } else {
                LOG_ERROR(GRAPHVIZ_TO_TSORT,"GetSpareErr");
            }
        }
#endif

        memset(Node->Source,0,TOKEN_SIZE);
        memset(Node->Destination,0,TOKEN_SIZE);
        Node->s= 0 ;
        Node->d= 0 ;
        Node->state = GRA_TSORT_STATE_LINE_DONE;
        res= true;
    }
    return res;
}

static bool graphviz_to_tsort_reset(GraphvizToTsortHandle_t* Node){
    bool res = false ;
    if(Node){
        memset(Node->Source,0,TOKEN_SIZE);
        memset(Node->Destination,0,TOKEN_SIZE);
        Node->s= 0 ;
        Node->d= 0 ;
        Node->state = GRA_TSORT_STATE_IDLE;
        res= true;
    }
    return res;
}

static GraTsortInput_t  GraTsortLetterToInput(char letter){
    GraTsortInput_t input = GRA_TSORT_INPUT_UNDEF;

    switch(letter) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '_':{input=GRA_TSORT_INPUT_LETTER;} break;
        case ' ':{input=GRA_TSORT_INPUT_SPACE;} break;
        case '>':{input=GRA_TSORT_INPUT_RIGHT_ARROW;} break;
        case '\n':{input=GRA_TSORT_INPUT_END_OF_LINE;} break;
        case '\r':{input=GRA_TSORT_INPUT_END_OF_LINE;} break;
        case '-':{input=GRA_TSORT_INPUT_DASH;} break;
        default:{
            int ret = isalpha(letter);
            if(ret){
                input=GRA_TSORT_INPUT_LETTER;
            }else{
                input=GRA_TSORT_INPUT_REST;
            }
        } break;
    }

    return input;
}

bool  graphviz_to_tsort_proc_idle(GraphvizToTsortHandle_t* Node){
    bool res = false;

    switch(Node->input){
    case GRA_TSORT_INPUT_SPACE:{
       // memset(Node->Source,0,TOKEN_SIZE);
        //memset(Node->Destination,0,TOKEN_SIZE);
        res = true;
    } break;
    case GRA_TSORT_INPUT_LETTER:{
        memset(Node->Destination,0,TOKEN_SIZE);
        Node->state = GRA_TSORT_STATE_SOURCE;
        Node->Source[0] = Node->letter;
        Node->s=1;
    } break;
    case GRA_TSORT_INPUT_DASH:{
        res = false;
    } break;
    case GRA_TSORT_INPUT_RIGHT_ARROW:{
        res = false;
    } break;
    case GRA_TSORT_INPUT_END_OF_LINE:{
        res = true;
    } break;
    case GRA_TSORT_INPUT_REST:{
        res = true;
    } break;
    default:{res = false;} break;
    }
    return res;
}

bool  graphviz_to_tsort_proc_source(GraphvizToTsortHandle_t* Node){
    bool res = false;
    switch(Node->input){
    case GRA_TSORT_INPUT_LETTER:{
        Node->Source[Node->s] = Node->letter;
        Node->s++;
        res = true;
    } break;
    case GRA_TSORT_INPUT_SPACE:{
        Node->state = GRA_TSORT_STATE_WAIT_ARROW;
        res = true;
    } break;
    case GRA_TSORT_INPUT_DASH:{
        Node->state = GRA_TSORT_STATE_WAIT_ARROW;
        res = true;
    } break;
    case GRA_TSORT_INPUT_RIGHT_ARROW:{
        graphviz_to_tsort_reset(Node);
        LOG_ERROR(GRAPHVIZ_TO_TSORT,"ArrowFormatErr");
        res = false;
    } break;
    case GRA_TSORT_INPUT_END_OF_LINE:{
        graphviz_to_tsort_reset(Node);
        LOG_DEBUG(GRAPHVIZ_TO_TSORT,"EarlyLineBreakErr");
        res = false;
    } break;
    case GRA_TSORT_INPUT_REST:{
        res = true;
    } break;
    default:{res = false;} break;
    }

    return res;
}

static bool graphviz_to_tsort_proc_rx_arrow(GraphvizToTsortHandle_t* Node){
    bool res = false;
    switch(Node->input){
        case GRA_TSORT_INPUT_LETTER: {
            Node->Destination[0] = Node->letter;
            Node->d = 1;
            Node->state = GRA_TSORT_STATE_DESTINATION;
        } break;
        case GRA_TSORT_INPUT_SPACE: {
            res = true;
        } break;
        case GRA_TSORT_INPUT_DASH: {
            graphviz_to_tsort_reset(Node);
            LOG_ERROR(GRAPHVIZ_TO_TSORT,"DoubleArrowErr");
            res = false;
        } break;
        case GRA_TSORT_INPUT_RIGHT_ARROW: {
            graphviz_to_tsort_reset(Node);
            LOG_ERROR(GRAPHVIZ_TO_TSORT,"DoubleArrowErr");
            res = false;
        } break;
        case GRA_TSORT_INPUT_END_OF_LINE: {
            graphviz_to_tsort_reset(Node);
            LOG_ERROR(GRAPHVIZ_TO_TSORT,"NoDstErr");
            res = false;
        } break;
        case GRA_TSORT_INPUT_REST: {
            graphviz_to_tsort_reset(Node);
            LOG_ERROR(GRAPHVIZ_TO_TSORT,"SomeErr");
            res = false;
        } break;
        default:{res = false;} break;
    }
    return res;
}

bool graphviz_to_tsort_proc_wait_arrow(GraphvizToTsortHandle_t* Node){
    bool res = false;
    switch(Node->input){
    case GRA_TSORT_INPUT_LETTER: {
        graphviz_to_tsort_reset(Node);
    } break;
    case GRA_TSORT_INPUT_SPACE: {
        if('-'==Node->prev_letter){
            graphviz_to_tsort_reset(Node);
            res = false;
        }else{
             res = true;
        }
    } break;
    case GRA_TSORT_INPUT_DASH: {
        res = true;
    } break;
    case GRA_TSORT_INPUT_RIGHT_ARROW: {
        if('-'==Node->prev_letter) {
            Node->state = GRA_TSORT_STATE_RX_ARROW;
            Node->d = 0;
            memset(Node->Destination,0,sizeof(Node->Destination));
            res = true;
        } else {
            graphviz_to_tsort_reset(Node);
            res = false;
            LOG_ERROR(GRAPHVIZ_TO_TSORT,"ArrowStartErr");
        }
    } break;
    case GRA_TSORT_INPUT_END_OF_LINE: {
        graphviz_to_tsort_reset(Node);
        res = false;
        LOG_DEBUG(GRAPHVIZ_TO_TSORT,"EarlyLineBreakErr");
        Node->state = GRA_TSORT_STATE_IDLE;
        res = false;
    } break;
    case GRA_TSORT_INPUT_REST: {
        res = false;
    } break;
    default:{res = false;} break;
    }
    return res;
}



bool  graphviz_to_tsort_proc_destination(GraphvizToTsortHandle_t* Node){
    bool res = false;
    switch(Node->input){
        case GRA_TSORT_INPUT_LETTER: {
            Node->Destination[Node->d] = Node->letter;
            Node->d++;
            res = true;
        } break;
        case GRA_TSORT_INPUT_SPACE: {
            Node->state = GRA_TSORT_STATE_IDLE;
            res = true;
            res= gra_tsort_insert(Node);
        } break;
        case GRA_TSORT_INPUT_DASH: {
             res= gra_tsort_insert(Node);
            LOG_ERROR(GRAPHVIZ_TO_TSORT,"DoubleErrorErr");
             res = false;
        } break;
        case GRA_TSORT_INPUT_RIGHT_ARROW: {
             res= gra_tsort_insert(Node);
            LOG_ERROR(GRAPHVIZ_TO_TSORT,"FormatErrorErr");
             res = false;
        } break;
        case GRA_TSORT_INPUT_END_OF_LINE: {
            res= gra_tsort_insert(Node);
            Node->state =GRA_TSORT_STATE_IDLE;
            res = true;
        } break;
        case GRA_TSORT_INPUT_REST: {
            res= gra_tsort_insert(Node);
            res = true;
        } break;
        default:{res = false;} break;
    }
    return res;
}

bool graphviz_to_tsort_proc_line_done(GraphvizToTsortHandle_t* Node){
    bool res = false;
    switch(Node->input){
        case GRA_TSORT_INPUT_LETTER: {
            res = true;
        } break;
        case GRA_TSORT_INPUT_SPACE: {
            res = true;
        } break;
        case GRA_TSORT_INPUT_DASH: {
            res = true;
        } break;
        case GRA_TSORT_INPUT_RIGHT_ARROW: {
            res = true;
        } break;
        case GRA_TSORT_INPUT_END_OF_LINE: {
            Node->state = GRA_TSORT_STATE_IDLE;
            res = true;
        } break;
        case GRA_TSORT_INPUT_REST: {
            res = true;
        } break;
        default:{res = false;} break;
    }
    return res;
}

static bool graphviz_to_tsort_proc_letter(GraphvizToTsortHandle_t* Node, char letter) {
    bool res = false;
    Node->letter = letter;
    Node->input = GraTsortLetterToInput(letter);
    LOG_PARN(GRAPHVIZ_TO_TSORT,"%s",GraphvizToTsortDiagToStr(Node));
    switch(Node->state){
        case GRA_TSORT_STATE_IDLE:{
            res = graphviz_to_tsort_proc_idle(Node);
        } break;
        case GRA_TSORT_STATE_SOURCE:{
            res = graphviz_to_tsort_proc_source(Node);
        } break;


        case GRA_TSORT_STATE_WAIT_ARROW:{
            res = graphviz_to_tsort_proc_wait_arrow(Node);
        } break;

        case GRA_TSORT_STATE_RX_ARROW:{
            res = graphviz_to_tsort_proc_rx_arrow(Node);
        } break;

        case GRA_TSORT_STATE_DESTINATION:{
            res = graphviz_to_tsort_proc_destination(Node);
        } break;
        case GRA_TSORT_STATE_LINE_DONE:{
            res = graphviz_to_tsort_proc_line_done(Node);
        }break;
        default : res = false; break;
    }

    Node->prev_letter = letter;
    Node->char_cnt++;
    return res;
}


bool graphviz_to_tsort_proc_line(GraphvizToTsortHandle_t* Node, char* line) {
    bool res = false;
    if(Node){
        if(line){
            size_t len = strlen(line);
            LOG_DEBUG(GRAPHVIZ_TO_TSORT, "ProcLine,Len:%u,Line:[%s]",len,line);
            size_t  i = 0;
            for(i=0;i<len;i++){
                res = graphviz_to_tsort_proc_letter(Node, line[i]);
            }
        }
    }
    return res;
}

bool graphviz_to_tsort_sort(GraphvizToTsortHandle_t* Node){
    bool res = false ;
    char command[1000]={0};
    snprintf(command,sizeof(command),"sort -u %s -o %s",Node->tsort_file,Node->tsort_file);
    res=win_cmd_run(command);

    snprintf(command,sizeof(command),"cat %s | tr -d '\\r' > tsort_generated_clean.txt",Node->tsort_file);
    res=win_cmd_run(command);

    char init_file[500];
    strcpy(init_file,Node->GraphVizFile);
    res = replace_substring(init_file, "\.gv", "\.init") ;
    if(res){
        snprintf(command,sizeof(command),"tsort.exe tsort_generated_clean.txt | tac > %s",init_file);
        res = win_cmd_run(command);
    }
    return res;
}


bool graphviz_to_tsort_proc_gv( const char* const file_name){
    bool res = false;
    if(file_name) {
        strcpy(GraphvizToTsortInstance.GraphVizFile,file_name);
        LOG_INFO(GRAPHVIZ_TO_TSORT, "ProcFile:[%s]",file_name);
        FILE *FilePtr = NULL;
        FilePtr = fopen(file_name, "r");
        if(FilePtr) {
            LOG_INFO(GRAPHVIZ_TO_TSORT, "OpenOk,File:[%s]",file_name);
            //res = true;
            char line[500]={0};
            uint8_t line_num = 1;
            while (NULL != fgets(line, sizeof(line), FilePtr)) {
              LOG_DEBUG(GRAPHVIZ_TO_TSORT,"L:%u,[%s]",line_num, line);
              res = graphviz_to_tsort_proc_line(&GraphvizToTsortInstance, line);
              memset(line,0,sizeof(line));
              line_num++;
            }
            fclose(FilePtr);

            graphviz_to_tsort_sort(&GraphvizToTsortInstance);
            //graphviz_to_tsort_print(&GraphvizToTsortInstance);
        }else{
            LOG_ERROR(GRAPHVIZ_TO_TSORT, "OpenErr File:[%s]",file_name);
            res = false;
        }
    }
    return res;
}

static bool graphviz_to_tsort_init_ll(GraphvizToTsortHandle_t* const Node,
        const  GraphvizToTsortConfig_t* const Config) {
    bool res = false;
    if(Node){
        if(Config){
            Node->d=0;
            Node->s=0;
            memset(Node->Source,0,TOKEN_SIZE);
            memset(Node->Destination,0,TOKEN_SIZE);
            Node->gv_filename=Config->gv_filename;
            Node->tsort_file=Config->tsort_file;

            Node->char_cnt = 0;
            Node->state = GRA_TSORT_STATE_IDLE;


           res = true;
        }
    }
    return res;
}

bool graphviz_to_tsort_init(void) {
    bool res = false;
    //log_level_get_set(LINE,LOG_LEVEL_DEBUG);
    //log_level_get_set(GRAPHVIZ_TO_TSORT,LOG_LEVEL_DEBUG);

    res=graphviz_to_tsort_init_ll(&GraphvizToTsortInstance, &GraphvizToTsortConfig);

    LOG_INFO(GRAPHVIZ_TO_TSORT, "GRAPHVIZ_TO_TSORT_VERSION:%u",GRAPHVIZ_TO_TSORT_DRIVER_VERSION);
    res=graphviz_to_tsort_diag();

    log_level_get_set(LINE,LOG_LEVEL_INFO);
    log_level_get_set(GRAPHVIZ_TO_TSORT,LOG_LEVEL_INFO);
    return res;
}


bool graphviz_to_tsort_proc( void){
    bool res = false;
    res = graphviz_to_tsort_proc_gv(GraphvizToTsortConfig.gv_filename);
    if(res){
        LOG_WARNING( GRAPHVIZ_TO_TSORT,"Exit");
        exit(0);
    }
    return res;
}








