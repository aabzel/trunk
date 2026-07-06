#include "iqueue_cli.h"

#include "array_diag.h"
#include "convert.h"
#include "iqueue.h"
#include "log.h"

bool iqueue_diag_cli(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = iqueue_diag();
    } else {
        LOG_ERROR(IQUEUE, "Usage: iqd");
    }

    return res;
}

bool iqueue_init_cli(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
    }

    if(res) {
        res = iqueue_mcal_init();
        log_res(IQUEUE, res, "Init");
    } else {
        LOG_ERROR(IQUEUE, "Usage: iqi");
    }
    return res;
}

bool iqueue_push_cli(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t TxData[IQUEUE_ELEMENT_MAX_SIZE] = {0};
    uint8_t num = 1;
    uint32_t size = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(IQUEUE, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], TxData, sizeof(TxData), &size);
        if(false == res) {
            LOG_WARNING(IQUEUE, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)TxData, sizeof(TxData), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = false;
        iQueueHandle_t* Node = iQueueGetNode(num);
        if(Node) {
            if(Node->pHandle->element_size <= IQUEUE_ELEMENT_MAX_SIZE) {
                i_status ret = iqueue_enqueue(Node->pHandle, (void*)TxData);
                res = iqueue_ret_res(ret);
            }
        }
    } else {
        LOG_ERROR(IQUEUE, "Usage: iqsh Num WriteData");
    }
    return res;
}

bool iqueue_pull_cli(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(IQUEUE, res, "Num");
    }

    if(res) {
        res = false;
        iQueueHandle_t* Node = iQueueGetNode(num);
        if(Node) {
            uint8_t rx_data[IQUEUE_ELEMENT_MAX_SIZE] = {0};
            if(Node->pHandle->element_size <= IQUEUE_ELEMENT_MAX_SIZE) {
                i_status ret = iqueue_dequeue(Node->pHandle, (void*)rx_data);
                res = iqueue_ret_res(ret);
                if(res) {
                    LOG_INFO(IQUEUE, "IQUEUE_%u,ReadData:%s", num, ArrayToStr(rx_data, Node->pHandle->element_size));
                }
            }
        }
    } else {
        LOG_ERROR(IQUEUE, "Usage: iqll Num");
    }

    return res;
}
