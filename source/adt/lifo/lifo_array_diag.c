#include "lifo_array_diag.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "array_diag.h"
#include "debug_info.h"
#include "lifo_array.h"
#include "log.h"
#include "log_utils.h"

#ifdef HAS_PROTOCOL_DIAG
#include "protocol_diag.h"
#endif

bool lifo_arr_peek(const LifoArray_t* const Node, Array_t* const node) {
    bool res = false;
    res = is_lifo_arr_valid(Node);
    if(res) {
        res = false;
        if(0u < Node->lifoState.count) {
            *node = Node->pDataArray[Node->lifoState.count - 1];
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

bool LivoIsValidItem(const  Array_t* const Item){
    bool res = false;
    if(Item) {
    	if(Item->size) {
    		if(Item->pArr) {
        	    LOG_DEBUG(LIFO,  "Size:%u byte,Mem:0x%p,%s",Item->size,Item->pArr,ArrayToStr(Item->pArr,Item->size));
    			res = true;
    		}else{
                LOG_ERROR(LIFO, "ErrMemPtr");
        	}
    	}else{
            LOG_ERROR(LIFO, "SizeErr");
    	}
    }else{
        LOG_ERROR(LIFO, "ErrNode");
	}
    return res;
}

bool lifo_arr_peek_num(const LifoArray_t* const Node, uint32_t num, Array_t* const node) {
    bool res = false;
    res = is_lifo_arr_valid(Node);
    if(res) {
        res = false;
        if(0u < Node->lifoState.count) {
            if(num < Node->lifoState.count) {
                *node = Node->pDataArray[Node->lifoState.count - 1 - num];
                res = true;
            }
        } else {
            res = false;
        }
    }
    return res;
}

bool lifo_arr_diag(const LifoArray_t* const Node) {
    bool res = false;
    res = is_lifo_arr_valid(Node);
    if(res) {
        int32_t i = 0;
        LOG_DEBUG(LIFO, "Cnt:%u", Node->lifoState.count);
        for(i = (Node->lifoState.count - 1); 0 <= i; i--) {
            Array_t node = Node->pDataArray[i];
            cli_printf(" %u ", i);
            print_mem_ascii(node.pArr, node.size);
            cli_printf(CRLF);
        }
    }
    return res;
}

bool LifoArrayDiag(const LifoArray_t* const Node, Protocol_t protocol) {
    bool res = false;
    if(Node) {
        char line[120] = "";
        uint32_t i = 0;
        log_level_t log_level = log_level_get(LIFO);

        snprintf(line, sizeof(line), "%s Cnt:%d,", line, Node->lifoState.count);
        LOG_DEBUG(LIFO, "%s", line);
        for(i = 0; i < Node->lifoState.count; i++) {
            Array_t Item = {0};
            res = lifo_arr_peek_num(Node, i, &Item);
            if(res) {
                strcpy(line, "");
                snprintf(line, sizeof(line), "%s %u ", line, i + 1);
                snprintf(line, sizeof(line), "%s %2u ", line, Item.size);
#ifdef HAS_PROTOCOL_DIAG
                snprintf(line, sizeof(line), "%s %s ", line, ProtocolFrame2Str(Item.pArr, Item.size, protocol));
#endif

                if(LOG_LEVEL_DEBUG == log_level) {
                    cli_printf("%s" CRLF, line);
                }
            }
        }
    }

    return res;
}
