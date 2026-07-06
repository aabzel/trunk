#include "iqueue.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "iqueue.h"
#include "log.h"

COMPONENT_GET_NODE(iQueue, iqueue)
COMPONENT_GET_CONFIG(iQueue, iqueue)

iQueueHandle_t* iQueueInterfaceToNode(const InterfaceType_t Interface) {
    iQueueHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = iqueue_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(Interface.word == iQueueInstance[i].Interface.word) {
            if(iQueueInstance[i].valid) {
                Node = &iQueueInstance[i];
                break;
            }
        }
    }
    return Node;
}

/*ISO-26262 require verify configuration*/
bool iQueueIsValidConfig(const iQueueConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) { LOG_WARNING(IQUEUE, "%u,NameErr", Config->num); }

        ifn(Config->pHandle) {
            LOG_ERROR(IQUEUE, "%u,pHandle,Err", Config->num);
            res = false;
        }
#if 0
        ifn(Config->type) {
            LOG_ERROR(IQUEUE, "%u,type,Err", Config->num);
            res = false;
        }
#endif

        ifn(Config->storage) {
            LOG_ERROR(IQUEUE, "%u,NoMemoryForQueue,Err", Config->num);
            res = false;
        }

        ifn(0 < Config->element_cnt) {
            LOG_ERROR(IQUEUE, "%u,ElementCntZero,Err", Config->num);
            res = false;
        }

        ifn(0 < Config->element_size) {
            LOG_ERROR(IQUEUE, "%u,ElementSize,Err", Config->num);
            res = false;
        }

        ifn(Config->Interface.word) {
            LOG_ERROR(IQUEUE, "%u,Interface,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool iqueue_init_custom(void) {
    bool res = false;
    LOG_INFO(IQUEUE, "Version:%s", IQUEUE_VERSION);
    return res;
}

i_status iqueue_empty(iqueue_t* _queue, uint32_t* const cnt) {
    i_status out_ret = I_ERROR;
    if(_queue) {
        if(cnt) {
            (*cnt) = 0;
            if(_queue->element_size <= IQUEUE_ELEMENT_MAX_SIZE) {
                for(;;) {
                    uint8_t data_temp[IQUEUE_ELEMENT_MAX_SIZE] = {0};
                    i_status ret = iqueue_dequeue(_queue, (void*)data_temp);
                    if(I_OK == ret) {
                        (void)data_temp;
                        (*cnt)++;
                    } else if(I_EMPTY == ret) {
                        out_ret = I_OK;
                        break;
                    }
                }
            }
        }
    }
    return out_ret;
}

bool iqueue_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(IQUEUE, "Proc %u", i);
    iQueueHandle_t* Node = iQueueGetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

bool iqueue_init_common(const iQueueConfig_t* const Config, iQueueHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->pHandle = Config->pHandle;
            Node->storage = Config->storage;
            Node->element_size = Config->element_size;
            Node->element_cnt = Config->element_cnt;
            Node->Interface = Config->Interface;
#if 0
            Node->type = Config->type;
#endif
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool iqueue_ret_res(const i_status ret) {
    bool res = false;
    switch(ret) {
    case I_OK:
        res = true;
        break;
    case I_INVALID:
        res = false;
        break;
    case I_EXISTS:
        res = false;
        break;
    case I_NOTEXISTS:
        res = false;
        break;
    case I_FAILED:
        res = false;
        break;
    case I_EXPIRED:
        res = false;
        break;
    case I_UNKNOWN:
        res = false;
        break;
    case I_INPROGRESS:
        res = false;
        break;
    case I_IDLE:
        res = false;
        break;
    case I_FULL:
        res = false;
        break;
    case I_EMPTY:
        res = false;
        break;
    case I_YES:
        res = false;
        break;
    case I_NO:
        res = false;
        break;
    case I_SKIP:
        res = false;
        break;
    case I_DEBUG_01:
        res = false;
        break;
    case I_DEBUG_02:
        res = false;
        break;
    case I_DEBUG_03:
        res = false;
        break;
    case I_DEBUG_04:
        res = false;
        break;
    case I_DEBUG_05:
        res = false;
        break;
    case I_DEBUG_06:
        res = false;
        break;
    case I_DEBUG_07:
        res = false;
        break;
    case I_DEBUG_08:
        res = false;
        break;
    case I_DEBUG_09:
        res = false;
        break;
    case I_DEBUG_10:
        res = false;
        break;
    case I_DEBUG_11:
        res = false;
        break;
    case I_DEBUG_12:
        res = false;
        break;
    case I_DEBUG_13:
        res = false;
        break;
    case I_DEBUG_14:
        res = false;
        break;
    case I_DEBUG_15:
        res = false;
        break;
    case I_DEBUG_16:
        res = false;
        break;
    case I_MEMUNALIGNED:
        res = false;
        break;
    case I_NOTIMPLEMENTED:
        res = false;
        break;
    case I_ERROR:
        res = false;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

static bool iqueue_init_node(iQueueHandle_t* Node) {
    bool res = false;
    Node->valid = true;
    Node->spin = 0;
    memset(Node->pHandle, 0, sizeof(iqueue_t));
    i_status ret = iqueue_init(Node->pHandle, Node->element_cnt, Node->element_size, Node->storage);
    res = iqueue_ret_res(ret);
    if(res) {
        Node->init = true;
        LOG_INFO(IQUEUE, "IQUEUE_%u,Init,Ok", Node->num);
    }

    return res;
}

bool iqueue_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(IQUEUE, "IQUEUE%u", num);
    const iQueueConfig_t* Config = iQueueGetConfig(num);
    if(Config) {
        res = iQueueIsValidConfig(Config);
        if(res) {
#ifdef HAS_IQUEUE_DIAG
            LOG_WARNING(IQUEUE, "%s", iQueueConfigToStr(Config));
#endif
            iQueueHandle_t* Node = iQueueGetNode(num);
            if(Node) {
                res = iqueue_init_common(Config, Node);
                res = iqueue_init_node(Node);
            } else {
                LOG_ERROR(IQUEUE, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(IQUEUE, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(IQUEUE, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(IQUEUE, IQUEUE, iqueue)
COMPONENT_PROC_PATTERT(IQUEUE, IQUEUE, iqueue)
