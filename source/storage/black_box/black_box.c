#include "black_box.h"

#include <stdio.h>
#include <string.h>

#include "code_generator.h"
#include "log.h"
#include "tbfp_diag.h"
#include "fat_fs_drv.h"

COMPONENT_GET_NODE(BlackBox, black_box)

COMPONENT_GET_CONFIG(BlackBox, black_box)

static bool black_box_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(BLACK_BOX, "Proc %u", num);
    BlackBoxHandle_t* Node = BlackBoxGetNode(num);
    if(Node) {
        LOG_PARN(BLACK_BOX, "Spot %u", num);

        TbfpProtocol_t* TbfpNode=TbfpNum2Node(1);
        if(TbfpNode) {
        	if(false==TbfpNode->proc_done) {
        		if(TbfpNode->Flow.torn) {
                    char text[100] = "";
                    memset(text, 0, sizeof(text));
                    snprintf(text,sizeof(text),"%s",TbfpNode2Str(TbfpNode));
                    res = fat_fs_write("ContFlow.csv", text);
                    if (res) {
                        LOG_DEBUG(BLACK_BOX,"ContFlow[%s]",text);
                    }
        		} else {
        			LOG_DEBUG(BLACK_BOX,"FlowOK!");

        		}
                TbfpNode->proc_done = true;
        	}
        }

        res = true;

    }
    return res;
}

COMPONENT_PROC_PATTERT(BLACK_BOX, BLACK_BOX, black_box)


static bool black_box_init_one(uint8_t num) {
    bool res = false;
    const BlackBoxConfig_t* Config = BlackBoxGetConfig(num);
    if(Config) {
        BlackBoxHandle_t* Node = BlackBoxGetNode(num);
        if(Node) {
            LOG_WARNING(BLACK_BOX, "BLACK_BOX_%u Init", num);
            res = true;
        } else {
            LOG_ERROR(BLACK_BOX, "%u NodeErr", num);
        }
    } else {
        LOG_DEBUG(BLACK_BOX, "%u NoConf", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(BLACK_BOX, BLACK_BOX, black_box)
