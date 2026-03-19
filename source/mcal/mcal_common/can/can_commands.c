#include "can_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "array_diag.h"
#include "can_mcal.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#include "ostream.h"
#include "string_reader.h"
#include "table_utils.h"
#include "writer_config.h"
#ifdef HAS_TEST_CAN
#include "test_can.h"
#endif


/*
 1 0xc2 2 0x556644
 */
bool can_parse_mesg(int32_t argc, char* argv[], const int32_t start, CanMessage_t * const Message) {
    bool res = false;
    LOG_INFO(CAN, "argc:%u,Start:%u", argc,start);

    uint32_t array_len = 8;
    uint8_t id_type = 0;

    if((start+1) <= argc) {
        /* The CAN bus number this package came from*/
        res = try_str2int8(argv[start+0], &Message->can_bus_num);
        log_res(CAN, res, "CANn");
    }

    if((start+2) <= argc) {
        res = try_str2uint32(argv[start+1], &Message->identifier.extended);
        log_res(CAN, res, "Id");
    }

    if((start+3 )<= argc) {
        res = try_str2uint8(argv[start+2], &id_type);
        log_res(CAN, res, "idType");
    }

    if((start+4) <= argc) {
        LOG_INFO(CAN, "Data [%s]", argv[start+3]);
        /* contains the transmit data. it ranges from 0 to 0xFF. */
        array_len = 0;
        res = try_str2array(argv[start+3], Message->data, sizeof(Message->data), &array_len);
        if(res) {
            LOG_WARNING(CAN, "SpotHexSize:%u Byte", array_len);
        } else {
            LOG_WARNING(CAN, "ExtractHexArrayErr  [%s]", argv[start+3]);
            snprintf((char*)Message->data, sizeof(Message->data), "%s", argv[start+3]);
            array_len = strlen(argv[start+3]);
            res = true;
        }
    }

    if(res) {
        LOG_INFO(CAN, "SpotSize:%u Byte,idType:%u", array_len,id_type);
        Message->id_type = (CanIdentifier_t) id_type;
        if(array_len <= 8) {
            Message->frame_type = CAN_TX_FRAME_DATA;
            Message->size = array_len;
            LOG_INFO(CAN, "Mesg:[%s]",  CanMessageToStr(Message));
            res = true;
        }else {
            LOG_ERROR(CAN, "DataSize:%u",array_len);
        }
    } else {
        LOG_ERROR(CAN, "ParseError");
    }
    return res;
}


bool can_rx_frame_manual_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t array_len = 0;
    CanMessage_t RxMessage = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &RxMessage.identifier.extended);
        log_res(CAN, res, "Id");
    }

    if(3 <= argc) {
        res = try_str2array(argv[2], RxMessage.data, sizeof(RxMessage.data), &array_len);
        if(false == res) {
            LOG_WARNING(CAN, "ExtractHexArrayErr [%s]", argv[2]);
            snprintf((char*)RxMessage.data, sizeof(RxMessage.data), "%s", argv[2]);
            array_len = strlen(argv[2]);
            res = true;
        } else {
            LOG_WARNING(CAN, "SpotSize:%u Byte", array_len);
        }
    }

    if(res) {
        if(array_len <= 8) {
            RxMessage.id_type = can_id_val_to_id_type(RxMessage.identifier.extended);
            RxMessage.size = array_len;
            RxMessage.frame_type = CAN_TX_FRAME_DATA;
            res = can_rx_frame_manual(num, &RxMessage);
            log_res(CAN, res, "RxFrameManual");
        }
    } else {
        LOG_ERROR(CAN, "Usage: crfm instance Id hex_string");
    }

    return res;
}

/*
  ll can debug
    cse 1 0x555555 0x5555555555555555
    cse 2 0x555555 0x5555555555555555
 * */
bool can_send_ext_command(int32_t argc, char* argv[]) {
    bool res = false;
    CanMessage_t Message = {0};
    uint32_t array_len = 0;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &Message.identifier.extended);
        log_res(CAN, res, "Id");
    }

    if(3 <= argc) {
        res = try_str2array(argv[2], Message.data, sizeof(Message.data), &array_len);
        if(false == res) {
            LOG_WARNING(CAN, "ExtractHexArrayErr  [%s]", argv[2]);
            snprintf((char*)Message.data, sizeof(Message.data), "%s", argv[2]);
            array_len = strlen(argv[2]);
            res = true;
        } else {
            LOG_WARNING(CAN, "SpotSize:%u Byte", array_len);
        }
    }

    if(res) {
        if(array_len <= 8) {
            Message.id_type = CAN_FRAME_ID_EXTENDED;
            Message.size = array_len;
            Message.can_bus_num = num;
            Message.frame_type = CAN_TX_FRAME_DATA;
            res = can_mcal_transmit_message(num, &Message);
            if(res) {
                print_hex(Message.data, array_len);
                LOG_INFO(CAN, "%u ExtSendOk %u byte", num, array_len);
                cli_printf(CRLF);
            } else {
                LOG_ERROR(CAN, "%u ExtSendErr", num);
            }
        }
    } else {
        LOG_ERROR(CAN, "Usage: cse instance ExtId hex_string");
        LOG_INFO(CAN, "instance [1...%u]", CAN_COUNT);
        LOG_INFO(CAN, "hex_string 0x[0...F]+");
    }
    return res;
}


/*
  cs 1 1 0x5555555555555555

    cs 2 1 0x5555555555555555
 cs 1 1 0x55AA
 cs 0 1 0x55AA
  cs 0 2 0x55AA
*/
bool can_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    CanMessage_t Message = {0};
    uint32_t array_len = 0;

    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &Message.identifier.extended);
        log_res(CAN, res, "Id");
    }

    if(3 <= argc) {
        res = try_str2array(argv[2], Message.data, sizeof(Message.data), &array_len);
        if(false == res) {
            LOG_WARNING(CAN, "ExtractHexArrayErr  [%s]", argv[2]);
            snprintf((char*)Message.data, sizeof(Message.data), "%s", argv[2]);
            array_len = strlen(argv[2]);
            res = true;
        } else {
            LOG_WARNING(CAN, "SpotSize:%u Byte", array_len);
        }
    }

    if(res) {
        if(array_len <= 8) {
            Message.id_type = can_id_val_to_id_type(Message.identifier.extended);
            Message.size = array_len;
            Message.frame_type = CAN_TX_FRAME_DATA;
            res = can_mcal_transmit_message(num, &Message);
            if(res) {
                print_hex(Message.data, array_len);
                LOG_INFO(CAN, "%u SendOk %u byte", num, array_len);
                cli_printf(CRLF);
            } else {
                LOG_ERROR(CAN, "%u SendErr", num);
            }
        }
    } else {
        LOG_ERROR(CAN, "Usage: cs instance Id hex_string");
        LOG_INFO(CAN, "instance [1...%u]", CAN_COUNT);
        LOG_INFO(CAN, "hex_string 0x[0...F]+");
    }
    return res;
}

bool can_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }
    if(res) {
        if(1 == argc) {
            res = can_init_one(num);
            log_res(CAN, res, "InitOne");
        } else {
            res = can_mcal_init();
            log_res(CAN, res, "Init");
        }
    } else {
        LOG_ERROR(CAN, "Usage: ci instance");
        LOG_INFO(CAN, "instance [1...%u]", CAN_COUNT);
        LOG_INFO(CAN, "bit_rate");
    }
    return res;
}

/*
 cb 0 500000
 */
bool can_bit_rate_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t bit_rate = 0;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &bit_rate);
        log_res(CAN, res, "BitRate");
    }

    if(res) {
        switch(argc) {
        case 1: {
            res = can_mcal_baudrate_get(num, &bit_rate);
            if(res) {
                LOG_INFO(CAN, "BitRate:%u bit/s", bit_rate);
            } else {
                LOG_ERROR(CAN, "BitRateGetErr");
            }

        } break;

        case 2: {
            res = can_mcal_baudrate_set(num, bit_rate);
            if(res) {
                LOG_INFO(CAN, "SetBaudRate:%u bit/s Ok", bit_rate);
            }

        } break;
        default:
            res = false;
            break;
        }
    }
    return res;
}

bool can_diag_interrupt_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = can_diag_interrupt();
    log_res(CAN, res, "DiagInterrupts");
    return res;
}

bool can_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = can_diag();
    log_res(CAN, res, "Diag");
    return res;
}

#ifdef HAS_CAN_FD
bool can_fd_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = can_fd_diag();
    log_res(CAN, res, "FdDiag");
    return res;
}
#endif

#ifdef HAS_CAN_FD
bool can_fd_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    CanMessage_t Message = {0};
    uint8_t num = 0;
    uint32_t array_len = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "ParseNum");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &Message.identifier.extended);
        log_res(CAN, res, "ParseID");
    }

    if(3 <= argc) {
        res = try_str2array(argv[2], Message.data, sizeof(Message.data), &array_len);
        log_res(CAN, res, "ParseHexArray");
        if(false == res) {
            LOG_WARNING(CAN, "ExtractHexArrayErr  [%s]", argv[2]);
            snprintf((char*)Message.data, sizeof(Message.data), "%s", argv[2]);
            array_len = strlen(argv[2]);
            res = true;
        } else {
            LOG_WARNING(CAN, "SpotSize:%u Byte", array_len);
        }
    }

    if(res) {
        Message.id_type = CAN_FRAME_ID_STANDARD;
        Message.size = array_len;
        res = can_fd_send(num, &Message);
        log_res(CAN, res, "FdSend");
        if(res) {
            print_hex(Message.data, array_len);
            LOG_INFO(CAN, "CAN%u,SendOk,Size:%u byte", num, array_len);
            cli_printf(CRLF);
        } else {
            LOG_ERROR(CAN, "CAN%u,SendErr", num);
        }
    } else {
        LOG_ERROR(CAN, "Usage: cfs Num Id HexString");
        LOG_INFO(CAN, "instance [1...%u]", CAN_COUNT);
        LOG_INFO(CAN, "hex_string 0x[0...F]+");
    }
    return res;
}
#endif

bool can_mesg_buff_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint8_t num = 0;
    uint8_t mb_idx = 4;
    uint32_t can_id = 4;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "ParseCan");
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &mb_idx);
        log_res(CAN, res, "ParseMbIdx");
    }
    if(3 <= argc) {
        res = try_str2uint32(argv[2], &can_id);
        log_res(CAN, res, "ParseId");
    }

    if(res) {
        res = can_mesg_buff_rx(num, mb_idx, can_id);
        log_res(CAN, res, "Rx");
    } else {
        LOG_ERROR(CAN, "Usage: cmb Num Mb Id");
    }
    return res;
}

bool can_loopback_command(int32_t argc, char* argv[]) {
    bool res = false;
#ifdef HAS_TEST_CAN
    uint32_t can_id = 4;
    uint8_t num_tx = 2;
    uint8_t num_rx = 3;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num_tx);
        log_res(CAN, res, "Tx");
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[0], &num_rx);
        log_res(CAN, res, "Rx");
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &can_id);
        log_res(CAN, res, "Id");
    }

    if(res) {
        res = test_can_loopback_pair(num_tx, num_rx, can_id);
        log_res(CAN, res, "Forward");
        res = test_can_loopback_pair(num_rx, num_tx, can_id);
        log_res(CAN, res, "Backward");
    } else {
        LOG_ERROR(CAN, "Usage: clb TxNum RxNum Id");
    }
#endif
    return res;
}

/*
  ccbr 24000000  100 1 3 3 3
  ccbr 24000000  100 1 2 3 3

  ccbr 24000000  4 3 7 7 7 250000
  ccbr 24000000  4 2 7 7 7 260869
  ccbr 24000000  4 1 7 7 7 272727
  ccbr 24000000  4 0 7 7 7 285714

  preDiv:4,JumpWidth:2,PropSeg:7,PhaSeg1:7,PhaSeg2:7
  */
bool can_calc_bit_rate_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t clk_freq_hz = 24000000;
    CanSegmentInfo_t TimeSeg = {0};

    if(6 <= argc) {
        res = try_str2uint32(argv[0], &clk_freq_hz);
        log_res(CAN, res, "Id");
        res = try_str2uint32(argv[1], &TimeSeg.prescaler);
        log_res(CAN, res, "prescaler");
        res = try_str2uint32(argv[2], &TimeSeg.synchronization);
        log_res(CAN, res, "synchronization");
        res = try_str2uint32(argv[3], &TimeSeg.propagation);
        log_res(CAN, res, "propagation");
        res = try_str2uint32(argv[4], &TimeSeg.phase_1);
        log_res(CAN, res, "phase_1");
        res = try_str2uint32(argv[5], &TimeSeg.phase_2);
        log_res(CAN, res, "phase_2");
    }

    if(res) {
        uint32_t bit_rate_real = can_time_seg_to_bit_rate(clk_freq_hz, &TimeSeg);
        LOG_INFO(CAN, "BaseClock:%7u Hz,%s,RateReal:%7u bit/s", clk_freq_hz, CanSegmentInfoToStr(&TimeSeg),
                 bit_rate_real);
    } else {
        LOG_ERROR(CAN, "Usage: ccbr ClkFreqHz TqPsc sync  propag pha1 pha2");
    }

    return res;
}

bool can_loopback_mode_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = 0;

    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
        log_res(CAN, res, "OnOff");
    }

    if(res) {
        switch(argc) {
        case 1: {
            res = can_loopback_get(num, &on_off);
            log_res(CAN, res, "Get");
            LOG_INFO(CAN, "CAN%u,LoopBack,Get:%u", num, on_off);
        } break;
        case 2: {
            LOG_INFO(CAN, "CAN%u,LoopBack,Set:%u", num, on_off);
            res = can_loopback_set(num, on_off);
            log_res(CAN, res, "Set");
        } break;
        default: {
            res = false;
        } break;
        }
    }
    return res;
}

bool can_test_loopback_id_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t id = 0x55;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &id);
        log_res(CAN, res, "Id");
    }
#ifdef HAS_TEST_CAN

    if(res) {
        res = test_can_loop_back_send(num, id);
        log_res(CAN, res, "LoopBack");
    } else {
        LOG_ERROR(CAN, "Usage: clbm Num Id");
    }
#endif
    return res;
}

bool can_is_my_id_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t id = 0x55;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &id);
        log_res(CAN, res, "Id");
    }

    if(res) {
        switch(argc) {
        case 1: {
            res = can_show_my_id(num);
            log_res(CAN, res, "ShowMyID");
        } break;
        case 2: {
            res = can_is_my_id(num, id);
            if(res) {
                LOG_INFO(CAN, "CAN%u,ID:0x%08x,isMy", num, id);
            } else {
                LOG_ERROR(CAN, "CAN%u,ID:0x%08x,ignored", num, id);
            }

        } break;
        default:
            break;
        }
    } else {
        LOG_ERROR(CAN, "Usage: cimid Num Id");
    }
    return res;
}

/*
  cshl 1 500 50 0x55
 */
bool can_send_hi_load_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint32_t frame_cnt = 1000;
    uint32_t id = 1000;
    uint32_t pause_ms = 100;

    if(0 <= argc) {
        num = 1;
        pause_ms = 100;
        frame_cnt = 9999;
        res = false;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &frame_cnt);
        log_res(CAN, res, "frameCnt");
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &pause_ms);
        log_res(CAN, res, "PauseMs");
    }

    if(4 <= argc) {
        res = try_str2uint32(argv[3], &id);
        log_res(CAN, res, "ID");
    }


    if(res) {
        res = can_std_send_hi_load(num, frame_cnt, pause_ms, id);
        log_res(CAN, res, "SendHiLoad");
    } else {
        LOG_ERROR(CAN, "Usage: cshl Num Cnt duration ID");
    }
    return res;
}

bool can_filter_id_mask_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint32_t filter_id = 0;
    uint32_t filter_mask = 0;

    if(0 <= argc) {
        res = true;
        filter_id = 0x00000100;
        filter_mask = 0xFFFFF7F8;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &filter_id);
        log_res(CAN, res, "FiltId");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &filter_mask);
        log_res(CAN, res, "FiltMask");
    }

    if(res) {
        uint32_t ok = can_filter_id_mask_diag(filter_id, filter_mask);
        LOG_INFO(CAN, "OK:%u", ok);
    } else {
        LOG_ERROR(CAN, "Usage: cfim ID Mask");
    }

    return res;
}

/*
  cfims 2 13 0x005500 0x00FF00; cdf
 | CAN1 |  13 |  0 | FIFO0 |  16 | IdMask | 0xa8380fa6 | 0x3b014b3c | (StdID1:0x007d,MASK1:0x0541);(StdID2:0x0259,MASK2:0x01d8) |
  */
bool can_filter_set_command(int32_t argc, char *argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t filt_num = 0;
    uint32_t filter_id = 0;
    uint32_t filter_mask = 0;

    if (1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if (2 <= argc) {
        res = try_str2uint8(argv[1], &filt_num);
        log_res(CAN, res, "FiltNum");
    }

    if (3 <= argc) {
        res = try_str2uint32(argv[2], &filter_id);
        log_res(CAN, res, "FiltId");
    }

    if (4 <= argc) {
        res = try_str2uint32(argv[3], &filter_mask);
        log_res(CAN, res, "FiltMask");
    }

    if (res) {
        res = can_mcal_filter_id_mask_set(num, filt_num, CAN_FRAME_ID_EXTENDED, filter_id, filter_mask);
        log_res(CAN, res, "filter_id_mask_set");
    } else {
        LOG_ERROR(CAN, "Usage: cfims CanNum FiltNum ID Mask");
    }

    return res;
}

bool can_rx_all_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    if (1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if (res) {
        res = can_rx_all(num);
        log_res(CAN, res, "RxAll");
    } else {
        LOG_ERROR(CAN, "Usage: cra CanNum");
    }
    return res;
}
