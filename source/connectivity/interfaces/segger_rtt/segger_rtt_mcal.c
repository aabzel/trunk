#include "segger_rtt_mcal.h"

#include "SEGGER_RTT.h"
#include "array_diag.h"
#include "cli_drv.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"
#include "array_diag.h"

#ifdef HAS_STRING_READER
#include "string_reader.h"
#endif

COMPONENT_GET_NODE(SeggerRtt, segger_rtt)
COMPONENT_GET_CONFIG(SeggerRtt, segger_rtt)

bool segger_rtt_writer(const uint8_t num) {
    bool res = false;
    InterfaceType_t interface_if;
    interface_if.num = num;
    interface_if.interface_name = INTERFACE_NAME_SEGGER_RTT;
    res = writer_interface_set(interface_if);
    return res;
}

void segger_rtt1_puts(void* stream_ptr, const char* str, int32_t len) {
    SeggerRttHandle_t* Node = SeggerRttGetNode(1);
    if(Node) {
        if(str) {
            if(len) {
                unsigned tx_cnt = SEGGER_RTT_Write(Node->BufferIndex, (void*)str, (unsigned)len);
                (void)tx_cnt;
                // fifo_push_array(&Node->TxFifo, (uint8_t*)str, (uint32_t)len);
            }
        }
    }
}

void segger_rtt1_putc(void* stream_ptr, char ch) {
    SeggerRttHandle_t* Node = SeggerRttGetNode(1);
    if(Node) {
        unsigned tx_cnt = SEGGER_RTT_Write(Node->BufferIndex, (void*)&ch, (unsigned)1);
        (void)tx_cnt;
        // fifo_push(&Node->TxFifo, (uint8_t)ch);
    }
}

// bool uart_writer_transmit(struct sWriterHandle_t* Node) {
bool segger_rtt1_writer_transmit(void* base) {
    bool res = false;
    WriterHandle_t* Node = (WriterHandle_t*)base;
    if(Node) {
        strcpy((char*)Node->data, "");
        uint32_t out_len = 0;
        Node->in_transmit = 0;
        res = fifo_pull_array(&Node->fifo, Node->data, 200, &out_len);
        if(false == res) {
            Node->fifo.err_cnt++;
        } else {
            Node->in_transmit = out_len;
        }

        if(0 < Node->in_transmit) {
            Node->tx_cnt += Node->in_transmit;
            if(Node->enable) {
                SeggerRttHandle_t* SeggerRtt = SeggerRttGetNode(1);
                if(SeggerRtt) {
                    unsigned tx_cnt =
                        SEGGER_RTT_Write(SeggerRtt->BufferIndex, (void*)Node->data, (unsigned)Node->in_transmit);
                    if(tx_cnt) {
                        res = true;
                    }
                    // res = fifo_push_array(&SeggerRtt->TxFifo, (uint8_t*)Node->data, (uint32_t)Node->in_transmit);
                }
            }
            Node->in_transmit = 0;
        }
    }
    return res;
}

/*ISO-26262 require verify configuration*/
bool SeggerRttIsValidConfig(const SeggerRttConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(SEGGER_RTT, "SEGGER_RTT_%u,Name,Err", Config->num);
            res = false;
        }

        ifn(Config->RxBuffer) {
            LOG_ERROR(SEGGER_RTT, "SEGGER_RTT_%u,RxBuffer,Err", Config->num);
            res = false;
        }
        ifn(Config->buffer_size) {
            LOG_ERROR(SEGGER_RTT, "SEGGER_RTT_%u,buffer_size,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool segger_rtt_init_custom(void) {
    bool res = false;
    LOG_INFO(SEGGER_RTT, "Version:%u", SEGGER_RTT_VERSION);
    SeggerInit();
    return res;
}

bool segger_rtt_write(uint8_t num, char* data) {
    bool res = false;
    SeggerRttHandle_t* Node = SeggerRttGetNode(num);
    if(Node) {
        if(data) {
            unsigned tx_data = SEGGER_RTT_WriteString(Node->BufferIndex, data);
            if(tx_data) {
                res = true;
            }
        }
    }
    return res;
}

bool segger_rtt_init_common(const SeggerRttConfig_t* const Config, SeggerRttHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->RxBuffer = Config->RxBuffer;
            Node->BufferIndex = Config->BufferIndex;
            Node->buffer_size = Config->buffer_size;
            res = true;
        }
    }
    return res;
}

InterfaceType_t RttNumToInterface(uint8_t num) {
    InterfaceType_t inter_face;
    inter_face.interface_name = INTERFACE_NAME_SEGGER_RTT;
    inter_face.num = num;
    return inter_face;
}

bool segger_rtt_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(SEGGER_RTT, "RTT%u,Proc", num);
    SeggerRttHandle_t* Node = SeggerRttGetNode(num);
    if(Node) {
        if(Node->RxBuffer) {
            if(Node->buffer_size) {
                unsigned rx_byte = SEGGER_RTT_Read(Node->BufferIndex, (void*)Node->RxBuffer, Node->buffer_size);
                if(rx_byte) {
                    LOG_DEBUG(SEGGER_RTT, "RxData:[%s]=[%s],rxByteCnt:%u Bytes", ArrayToStr(Node->RxBuffer, rx_byte),
                              ArrayToAsciiStr(Node->RxBuffer, rx_byte), rx_byte);
                    InterfaceType_t interface_if = RttNumToInterface(Node->num);
                    res = segger_rtt_writer(num);
                    uint32_t i = 0;
                    for(i = 0; i < Node->buffer_size; i++) {
#ifdef HAS_STRING_READER
                        res = string_reader_rx_byte(interface_if, (uint8_t)Node->RxBuffer[i]);
#endif
                    }
                    memset(Node->RxBuffer, 0, rx_byte);
                }
            }
        }
        Node->spin++;
    }
    return res;
}

bool segger_rtt_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SEGGER_RTT, "SEGGER_RTT_%u", num);
    const SeggerRttConfig_t* Config = SeggerRttGetConfig(num);
    if(Config) {
        res = SeggerRttIsValidConfig(Config);
        if(res) {
#ifdef HAS_SEGGER_RTT_DIAG
            LOG_WARNING(SEGGER_RTT, "%s", SeggerRttConfigToStr(Config));
#endif
            SeggerRttHandle_t* Node = SeggerRttGetNode(num);
            if(Node) {
                res = segger_rtt_init_common(Config, Node);
                res = segger_rtt_writer(1);
                Node->valid = true;
                Node->init = true;
            } else {
                LOG_ERROR(SEGGER_RTT, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(SEGGER_RTT, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(SEGGER_RTT, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(SEGGER_RTT, SEGGER_RTT, segger_rtt)
COMPONENT_PROC_PATTERT(SEGGER_RTT, SEGGER_RTT, segger_rtt)
