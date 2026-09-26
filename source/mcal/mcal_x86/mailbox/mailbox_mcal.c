#include "mailbox_mcal.h"

/*
 The Mailbox has the below features:
 - Implements the semaphores function and provides a mechanism to acquire "lock and unlock"
 - Support multiple channel communication between cores
 - Support sending short/long message
 - Support multiple interrupts, which can be triggered using a request or done event from channels


 The Mailbox (MB) provides the functionality for multiple cores to communicate
 and synchronize their activities.
 MB hardware is implemented using two structures: communication channels and interrupt channels.
 Specifically, there are 16 communication channels and 4 interrupt channels.

 */

#include <string.h>

#include "array_diag.h"
#include "code_generator.h"
#include "data_utils.h"
#include "log.h"
#include "mailbox_custom_diag.h"
#include "mailbox_custom_drv.h"
#include "mailbox_custom_isr.h"
#include "multicore_mcal.h"
#include "time_mcal.h"

static const MailBoxInfo_t MailBoxInfo[] = {
    {
        .num = 1,
        .MAILBOXx = 0x40058000,
        .irq_n = MB_IRQn,
        .valid = true,
    },

};
COMPONENT_GET_INFO(MailBox)

bool MailBoxStatusTypeToRes(const MB_StatusType ret) {
    bool res = false;
    switch(ret) {
    case MB_STATUS_SUCCESS:
        res = true;
        break;
    case MB_STATUS_FAILED:
        res = false;
        break;
    case MB_STATUS_PARAM_ERROR:
        res = false;
        break;
    case MB_STATUS_ALREADY_INITED:
        res = false;
        break;
    case MB_STATUS_UNINIT:
        res = false;
        break;
    case MB_STATUS_LOCKED:
        res = false;
        break;
    case MB_STATUS_NO_REQUEST:
        res = false;
        break;
    default:
        break;
    }
    return res;
}

bool mailbox_init_custom(void) {
    bool res = true;
    uint32_t cnt = mailbox_get_cnt();
    if(0 == cnt) {
        LOG_ERROR(MAILBOX, "Cnt:%u", cnt);
    }
    log_level_get_set(MAILBOX, LOG_LEVEL_INFO);
    return res;
}


static bool mailbox_proc_rx_data(MailBoxHandle_t* const Node, const MB_ReceiveType* const RxMesg) {
    bool res = false;
    if(Node) {
        Node->rx_done = false;
        Node->new_data = true;
        if(RxMesg) {
            LOG_INFO(MAILBOX, "RxCnt:%u,%s", Node->rx_cnt, MailBoxReceiveTypeToStr(RxMesg));
            if(Node->auto_release) {
                MB_StatusType ret = MB_ReleaseChannel(&(Node->Handle), (uint32_t)RxMesg->u8Channel);
                MailBoxStatusTypeDiagPrefix(ret, "ReleaseChannel");
            }
            res = true;
        }
    }
    return res;
}

bool mailbox_take_channel(uint32_t channel) {
    bool res = false;
    uint32_t start_ms = time_get_ms32();
    while(1) {
        MB_StatusType ret = MB_STATUS_FAILED;
        ret = MB_AcquireChannel(channel);
        if(MB_STATUS_SUCCESS == ret) {
            res = true;
            break;
        }
        res = time_wait_timeout(start_ms, MAILBOX_TAKE_TIMEOUT_MS);
    }
    return res;
}

bool mailbox_release_channel(uint8_t num, uint32_t channel) {
    bool res = false;
    MailBoxHandle_t* Node = MailBoxGetNode(num);
    if(Node) {
        MB_StatusType ret = MB_STATUS_FAILED;
        ret = MB_ReleaseChannel(&Node->Handle, channel);
        if(MB_STATUS_SUCCESS == ret) {
            res = true;
        } else {
            LOG_ERROR(MAILBOX, "%s", MailBoxStatusTypeToStr(ret));
        }
    }
    return res;
}

bool mailbox_done_channel(uint8_t num, uint32_t channel, uint8_t target_core_index) {
    bool res = false;
    MailBoxHandle_t* Node = MailBoxGetNode(num);
    if(Node) {
        MB_StatusType ret = MB_DoneChannel(&(Node->Handle), channel, target_core_index);
        res = MailBoxStatusTypeToRes(ret);
    }
    return res;
}
//
bool mailbox_channel_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(MAILBOX, "Proc,N:%u", num);
    MailBoxChannelHandle_t* Channel = MailBoxChannelGetNode(num);
    if(Channel) {
        MailBoxHandle_t* Node = MailBoxGetNode(num);
        if(Node) {
            if(Node->interrupt_on) {

            } else {
            }
        }
    }
    return res;
}

bool mailbox_channel_init_custom(void) {
    bool res = false;
    LOG_WARNING(MAILBOX, "InitChannel,CH:%u", MB_COM_CHANNEL_COUNT);
    return res;
}

bool mailbox_channel_init_one(uint8_t num) {
    bool res = false;
    const MailBoxChannelConfig_t* Config = MailBoxChannelGetConfig(num);
    if(Config) {
        MailBoxChannelHandle_t* Node = MailBoxChannelGetNode(num);
        if(Node) {
            Node->num = Config->num;
            Node->name = Config->name;
            Node->channel = Config->channel;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

static bool mailbox_unlock_all(void) {
    bool res = false;
    uint32_t ch = 0;
    for(ch = 0; ch < MB_COM_CHANNEL_COUNT; ch++) {
        MB_UnlockChannel(ch);
    }
    return res;
}

static bool mailbox_init_core(const MailBoxConfig_t* const Config, MailBoxHandle_t* const Node,
                              MB_InitType* const Init) {
    bool res = false;
    Init->u32EventMask = 0xFFFFFFFF;
    if(Config->interrupt_on) {
        Init->u32IntrMask = 0xFFFFFFFF;
        Init->pRequestCallback = MailBoxRequestCallback;
        Init->pDoneCallback = MailBoxDoneCallBack;
    } else {
        Init->pRequestCallback = NULL;
        Init->pDoneCallback = NULL;
        Init->u32IntrMask = MB_EVENT_NONE;
    }

    MB_Init(&(Node->Handle), Init);
    res = mailbox_unlock_all();
    return res;
}

bool mailbox_send_request(uint8_t num, uint8_t core_to, uint8_t channel, const uint8_t* const addr, uint32_t size) {
    bool res = false;
    MailBoxHandle_t* Node = MailBoxGetNode(num);
    if(Node) {
        if(Node->interrupt_on) {
            NVIC_EnableIRQ(MB_IRQn);
        }
        if(core_to <= CPU_CORE_COUNT) {
            MB_StatusType ret = MB_STATUS_SUCCESS;
            ret = MB_UnlockChannel(channel); // ???
            if(MB_STATUS_SUCCESS == ret) {
                res = true;
                uint8_t core_my = Cpm_HWA_GetCoreId();
                LOG_INFO(MAILBOX, "Send,Core:%u->%u,Ch%u,Size:%u,[%s]", core_my, core_to, channel, size,
                         ArrayToStr(addr, size));
                MB_RequestType Tx = {0};
                Tx.u8Channel = (uint8_t)channel;
                Tx.u8TargetCoreIndex = core_to;
                Tx.bAutoRelease = Node->auto_release;
                Tx.aData[0] = (uint32_t)addr;
                Tx.aData[1] = size;
                Node->new_data = false;
                ret = MB_SendRequest(&(Node->Handle), &Tx);
                // res = MailBoxStatusTypeToRes(ret);
                res = MailBoxStatusTypeDiag(ret);
                Node->channel = channel;
            }
        }
    }
    // MB_StatusType ret = MB_SendRequest(MB_HandleType *pMbHandle, MB_RequestType *pRequest);
    return res;
}

/*
    target_core_index - destination core (0; 1 or 2)
    channel - mail box channel (0....15)
    addr - pointer to tx data array
    size - the number of bytes to send
 */
bool mailbox_send_data(uint8_t num, const CpuCoreNumber_t target_core_index, const MailBoxChannel_t channel,
                       const uint8_t* const addr, const uint32_t size) {
    bool res = false;
    if(addr) {
        MailBoxHandle_t* Node = MailBoxGetNode(num);
        if(Node) {
            if(size < Node->TxData) {
                memcpy(Node->TxData, addr, size);
                /*There is only one MailBox in the system */
                res = mailbox_send_request(num, target_core_index, (uint8_t)channel, Node->TxData, size);
            }
        }
    }
    return res;
}

/*
    target_core_index - destination core (0; 1 or 2)
    addr - pointer to tx data array
    size - the number of bytes to send
 */
bool mailbox_send(uint8_t num, const CpuCoreNumber_t target_core_index, const uint8_t* const addr,
                  const uint32_t size) {
    bool res = false;
    if(addr) {
        MailBoxHandle_t* Node = MailBoxGetNode(num);
        if(Node) {
            if(size < Node->TxData) {
                memcpy(Node->TxData, addr, size);
                uint8_t core_my = Cpm_HWA_GetCoreId();
                /*There is only one MailBox in the system */
                res = mailbox_send_request(num, target_core_index, core_my, Node->TxData, size);
            }
        }
    }
    return res;
}

bool mailbox_init_one(uint8_t num) {
    bool res = false;
    log_level_get_set(MAILBOX, LOG_LEVEL_DEBUG);
    const MailBoxConfig_t* Config = MailBoxGetConfig(num);
    if(Config) {
        res = MailBoxIsValidConfig(Config);
        if(res) {
#ifdef HAS_MAILBOX_DIAG
            LOG_WARNING(MAILBOX, "%s", MailBoxConfigToStr(Config));
#endif
            MailBoxHandle_t* Node = MailBoxGetNode(num);
            if(Node) {
                res = mailbox_init_common(Config, Node);
                if(res) {
                    uint8_t core_my = Cpm_HWA_GetCoreId();
                    MB_InitType InitConfig = {0};
                    res = mailbox_init_core(Config, Node, &InitConfig);
                    LOG_INFO(MAILBOX, "Core:%u,%s", core_my, MailBoxInitTypeToStr(&InitConfig));
                    if(Config->interrupt_on) {
                        NVIC_EnableIRQ(MB_IRQn);
                    }
                    res = fifo_init(&Node->RxFifo, Config->RxData, Config->rx_data_size);
                    Node->init = true;
                }

#if 0
                MailBoxInfo_t* Info = MailBoxGetInfo(num);
                if(Info) {
                } else {
                    LOG_ERROR(MAILBOX, "MAILBOX%u InstErr", num);
                }
#endif
            } else {
                LOG_ERROR(MAILBOX, "MAILBOX%u NodeErr", num);
            }
        } else {
            LOG_ERROR(MAILBOX, "MAILBOX%u,ConfErr", num);
        }
    } else {
        LOG_DEBUG(MAILBOX, "MAILBOX%u,ConfErr", num);
    }
    log_level_get_set(MAILBOX, LOG_LEVEL_INFO);
    return res;
}

static bool mailbox_proc_isr_one_ll(MailBoxHandle_t* const Node) {
    bool res = false;
    uint8_t core_my = Cpm_HWA_GetCoreId();
    if(core_my == Node->it_core_num) {
        Node->it_core_num = 0xFF;
        if(Node->rx_done) {
            res = mailbox_proc_rx_data(Node, &Node->Rx);
        }

        if(Node->done_done) {
            Node->done_done = false;
            LOG_INFO(MAILBOX, "Done:%u", Node->done_cnt);
            LOG_INFO(MAILBOX, "DoneFlag:0x%08x", Node->done_flags);
        }

        if(Node->it_done) {
            Node->it_done = false;
            LOG_WARNING(MAILBOX, "ISR:%u", Node->it_cnt);
            res = true;
        }
    }
    return res;
}

/*
  Is Enable the request interrupt of mailbox interrupt channel

  u8CoreIndex the index of the core
  channel channel number
 */
bool MB_HWA_IsEnableIntrruptReq(uint8_t core_index, uint8_t channel) {
    bool res = false;
    uint32_t mask_req = MB_EVENT_REQ(channel);
    if(mask_req & (MB->INTR[core_index].MB_CCn_INTEN)) {
        res = true;
    }
    return res;
}

bool MB_HWA_IsEnableIntrruptDone(uint8_t core_index, uint8_t channel) {
    bool res = false;
    uint32_t mask_req = MB_EVENT_DONE(channel);
    if(mask_req & (MB->INTR[core_index].MB_CCn_INTEN)) {
        res = true;
    }
    return res;
}

static bool mailbox_proc_polling_one_ll(MailBoxHandle_t* const Node) {
    bool res = false;
    uint32_t done_flag = 0;
    uint8_t core_my = Cpm_HWA_GetCoreId();
    Node->Handle.tStatus.u8CoreIndex = core_my;
    done_flag = MB_PollDone(&(Node->Handle));
    if(done_flag) {
        LOG_WARNING(MAILBOX, "DoneFlag:0x%08x", done_flag);
        res = true;
    } else {
        Node->wait_cnt++;
        LOG_PARN(MAILBOX, "Wait");
    }

    if(0U == core_my) {
        /* Wait for Core B ready to receive*/
        uint32_t flag_Mask = 0;
        uint32_t ch_mask = 0;
        ch_mask = MB_EVENT_REQ(Node->channel);
        flag_Mask = MB_HWA_GetFlagMask(MB_CORE_INDEX_CORE_1, ch_mask);
        if(flag_Mask) {
            MultiCoreHandle_t* Core2 = MultiCoreGetNode(2);
            if(Core2) {
                if(false == Core2->ready) {
                    LOG_WARNING(MAILBOX, "Core1ReadyRx:0x%x", flag_Mask);
                    Core2->ready = true;
                }
            }
        }

        ch_mask = MB_EVENT_REQ(Node->channel);
        flag_Mask = MB_HWA_GetFlagMask(MB_CORE_INDEX_CORE_2, ch_mask);
        if(flag_Mask) {
            MultiCoreHandle_t* Core3 = MultiCoreGetNode(3);
            if(Core3) {
                if(false == Core3->ready) {
                    LOG_WARNING(MAILBOX, "Core2ReadyRx:0x%x", flag_Mask);
                    Core3->ready = true;
                }
            }
        }
    }

    MB_ReceiveType Rx = {0};
    Rx.u8Channel = (uint8_t)Node->channel;
    MB_StatusType ret = MB_ReceiveChannel(&(Node->Handle), &Rx);
    if(MB_STATUS_SUCCESS == ret) {
        res = mailbox_proc_rx_data(Node, &Rx);
    } else {
        MailBoxStatusTypeDiagPrefix(ret, "ReceiveChannel");
    }
    return res;
}

/*
  num - mailbox instance number
  data_out - array for storing received data
  size - size of array for storing received data
  rx_size - size of bytes actually received
 */
bool mailbox_read_data(uint8_t num, uint8_t* const data_out, const uint32_t size, uint32_t* const rx_size) {
    bool res = false;
    if(data_out) {
        if(size) {
            if(rx_size) {
                res = true;
            }
        }
    }

    MailBoxHandle_t* Node = MailBoxGetNode(num);
    if(res) {
        res = false;
        if(Node) {
            res = fifo_pull_array(&Node->RxFifo, data_out, size, rx_size);
        }
    }

    return res;
}

bool mailbox_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(MAILBOX, "Proc:%u", num);
    MailBoxHandle_t* Node = MailBoxGetNode(num);
    if(Node) {
        if(Node->interrupt_on) {
            res = mailbox_proc_isr_one_ll(Node);
        } else {
            res = mailbox_proc_polling_one_ll(Node);
        }

        uint8_t rxData[100] = {0};
        uint32_t real_rx = 0;
        res = mailbox_read_data( num, rxData, real_rx, &real_rx);
        if (res) {
            if(real_rx){
                LOG_INFO(MAILBOX, "MAILBOX%u,RxFiFo:%u byte",num, real_rx );
                print_hex(rxData, real_rx);
            }
        }

        Node->spin++;
    }
    return res;
}
