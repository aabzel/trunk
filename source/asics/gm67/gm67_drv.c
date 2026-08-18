#include "gm67_drv.h"

#include <string.h>

#include "code_generator.h"
#include "data_utils.h"
#include "fifo_char.h"
#include "log.h"
#include "time_mcal.h"
#include "array_diag.h"

COMPONENT_GET_CONFIG(Gm67, gm67)

COMPONENT_GET_NODE(Gm67, gm67)

Gm67Handle_t* Gm67GetNodeByUart(uint8_t uart_num) {
    Gm67Handle_t* Node = NULL;
    uint32_t i = 0;
    for(i = 0; i < gm67_get_cnt(); i++) {
        if(uart_num == Gm67Instance[i].uart_num) {
            if(Gm67Instance[i].valid) {
                Node = &Gm67Instance[i];
                break;
            }
            break;
        }
    }
    return Node;
}

/*ISR_code*/
bool gm67_proc_byte_isr(uint8_t uart_num, uint8_t rx_byte) {
    bool res = false;
    Gm67Handle_t* Node = Gm67GetNodeByUart(uart_num);
    if(Node) {
        Node->rx_cnt++;
        Node->new_frame = true;
        Node->rx_time_ms = time_get_ms32();
        Node->DataCur[Node->i] = rx_byte;
        Node->i++;
        res = fifo_push(&Node->RxFifo, (char)rx_byte);
    }
    return res;
}

bool gm67_save_frame(Gm67Handle_t* Node){
    bool res = false ;
    if(Node) {
        cli_printf(CRLF);
        LOG_INFO(GM67, "%u,EndOfFrame,Rx:%u Byte", Node->num,Node->i);
        if(Node->i<GM_IN_BUFF_SIZE){
            Node->rx_size = Node->i;
            memcpy(Node->DataFixed, Node->DataCur, Node->i);
            print_mem(Node->DataFixed, Node->rx_size, true, true, true, true);
        }
        Node->unptoc_frame = true;
        Node->rx_frame_cnt++;
        Node->i=0;
        res = true;
    }
    return res;
}

/*0xFF 0xFF 0xFF byte 0x0D*/
bool gm67_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(GM67, "Proc:%u", num);
    Gm67Handle_t* Node = Gm67GetNode(num);
    if(Node) {
        char out_char = 0;
        res = fifo_pull(&Node->RxFifo, (uint8_t* )&out_char);
        if(res) {
            switch(out_char) {
                case CARRIAGE_RETURN: {
                    res = gm67_save_frame(Node);
                } break;
                default: {
                    cli_printf("%02X", out_char);
                } break;
            }
        }

        uint32_t time_ms = time_get_ms32();
        uint32_t diff_ms = 0;
        diff_ms = time_ms - Node->rx_time_ms;
        if(GM67_UPTIME_MS < diff_ms) {
            if(Node->new_frame) {
                LOG_DEBUG(GM67, "%u,TxTimeOut", num);
                Node->new_frame = false;
                Node->i=0;
                cli_printf(CRLF);
            }
        }
        res = true;
    }
    return res;
}

bool gm67_init_custom(void) {
    bool res = false;
    return res;
}

bool gm67_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(GM67, "Init");
    const Gm67Config_t* Config = Gm67GetConfig(num);
    if(Config) {
        LOG_WARNING(GM67, "%s", Gm67ConfigToStr(Config));
        Gm67Handle_t* Node = Gm67GetNode(num);
        if(Node) {
            Node->uart_num = Config->uart_num;
            Node->i = 0 ;
            memset(Node->DataCur,0,sizeof(Node->DataCur));
            memset(Node->DataFixed,0,sizeof(Node->DataFixed));
            Node->unptoc_frame = false ;
            Node->rx_size = 0 ;
            Node->rx_cnt = 0 ;
            Node->rx_frame_cnt = 0 ;
            memset(Node->DataFixed, 0, sizeof(Node->DataFixed));
            res = fifo_init(&Node->RxFifo, (uint8_t*)Config->RxArray, (uint32_t)Config->rx_array_size);
        } else {
            LOG_ERROR(GM67, "%u", num);
            res = false;
        }
    } else {
        LOG_DEBUG(GM67, "Conf %u Err", num);
    }

    return res;
}

COMPONENT_INIT_PATTERT(GM67, GM67, gm67)

COMPONENT_PROC_PATTERT(GM67, GM67, gm67)
