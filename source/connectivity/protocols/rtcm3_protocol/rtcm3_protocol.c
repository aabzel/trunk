/*FSM for RTCM3 protocol*/
#include "rtcm3_protocol.h"

#include <string.h>

#include "byte_utils.h"
#include "crc24_q.h"
#include "data_utils.h"
#include "debug_info.h"
#ifdef HAS_LED
#include "led_drv.h"
#endif
#ifdef HAS_RADIO
#include "radio_drv.h"
#endif /*HAS_LORA*/
#ifdef HAS_LOG
#include "io_utils.h"
#include "log.h"
#include "system_diag.h"
#endif
#include "protocol_diag.h"

#ifdef X86_64
#include <stdio.h>
#endif

#ifdef HAS_TBFP
#include "tbfp_protocol.h"
#endif /*HAS_TBFP*/

#ifdef HAS_UART
#include "uart_drv.h"
#endif /*HAS_UART*/

#ifdef HAS_UBLOX
#include "ublox_driver.h"
#endif

#ifndef HAS_LORA
#define MAX_LORA_PAYLOAD_SIZE 250
#endif

Rtcm3Protocol_t Rtcm3Protocol[IF_CNT];

bool rtcm3_reset_rx(Rtcm3Protocol_t* instance, RxState_t rx_state) {
    bool res = false;
    if(instance) {
        res = true;
        LOG_DEBUG(RTCM, "ResetFsmIn: %s", RxState2Str(rx_state));
        instance->load_len = 0;
        instance->exp_len.len16 = 0;
        instance->rx_state = WAIT_PREAMBLE;
    }
    return res;
}

bool rtcm3_check(void) {
    bool res = true;
    Interfaces_t intf;
    for(intf = (Interfaces_t)0; intf < IF_CNT; intf++) {
        uint32_t diff = Rtcm3Protocol[intf].crc_err_cnt - Rtcm3Protocol[intf].crc_err_cnt_prev;
        Rtcm3Protocol[intf].crc_err_cnt_prev = Rtcm3Protocol[intf].crc_err_cnt;
        if(0 < diff) {
            res = false;
            LOG_ERROR(RTCM, "%s Crc24Err! %u times", InterfaceToStr(intf), diff);
        }
    }
    return res;
}

bool rtcm3_protocol_init(Rtcm3Protocol_t* instance, Interfaces_t interface, bool lora_fwd) {
    rtcm3_reset_rx(instance, WAIT_INIT);
    memset(instance, 0x0, sizeof(Rtcm3Protocol_t));
    memset(instance->fix_frame, 0x00, RTCM3_RX_MAX_FRAME_SIZE);
    memset(instance->rx_frame, 0x00, RTCM3_RX_MAX_FRAME_SIZE);

    instance->interface = interface;
#ifdef HAS_DEBUG
    instance->min_len = 0xFFFF;
    instance->forwarding[IF_LORA] = false;
#else
    instance->forwarding[IF_LORA] = lora_fwd;
#endif /*HAS_DEBUG*/
#ifdef HAS_LOG
    LOG_DEBUG(RTCM, "Init");
#endif
    return true;
}

static bool rtcm3_proc_wait_preamble(Rtcm3Protocol_t* instance, uint8_t rx_byte) {
    bool res = false;
    if((RTCM3_PREAMBLE == rx_byte) && (0 == instance->load_len)) {
        instance->rx_state = WAIT_LEN;
        instance->rx_frame[0] = rx_byte;
        instance->load_len = 1;
#ifdef HAS_DEBUG
        instance->preamble_cnt++;
#endif
#ifdef HAS_LOG
        LOG_DEBUG(RTCM, "Preamble");
#endif
        res = true;
    } else {
        rtcm3_reset_rx(instance, WAIT_PREAMBLE);
    }
    return res;
}

#ifdef HAS_DEBUG
static bool rtcm3_update_len_stat(Rtcm3Protocol_t* instance, uint16_t payload_len) {
    bool res = true;
    instance->max_len = max16u(instance->max_len, payload_len);
    instance->min_len = min16u(instance->min_len, payload_len);
    return res;
}
#endif /*HAS_DEBUG*/

static bool rtcm3_proc_wait_len(Rtcm3Protocol_t* instance, uint8_t rx_byte) {
    bool res = false;
    if(RTCM3_INX_LEN == instance->load_len) {
        instance->rx_frame[RTCM3_INX_LEN] = rx_byte;
        instance->exp_len.len8[RTCM3_INX_LEN] = rx_byte;
        instance->load_len = 2;
        instance->rx_state = WAIT_LEN;
        res = true;
    } else if((RTCM3_INX_LEN + 1) == instance->load_len) {
        instance->rx_frame[RTCM3_INX_LEN + 1] = rx_byte;
        instance->exp_len.len8[0] = rx_byte;
        instance->load_len = 3;
#ifdef HAS_LOG
        LOG_DEBUG(RTCM, "ExpLen %u", instance->exp_len.field.len);
#endif
        instance->rx_state = WAIT_PAYLOAD;
        res = true;
        if(RTCM3_RX_MAX_FRAME_SIZE < (instance->exp_len.field.len + RTCM3_OVERHEAD)) {
            res = false;
            instance->err_cnt++;
            LOG_ERROR(RTCM, "TooBigFrame:%u byte.Max:%u Byte", instance->exp_len.field.len + RTCM3_CRC24_SIZE,
                      RTCM3_RX_MAX_FRAME_SIZE);
            rtcm3_reset_rx(instance, WAIT_LEN);
        }
    } else {
        rtcm3_reset_rx(instance, WAIT_LEN);
    }
    return res;
}

bool rtcm3_proc_wait_payload(Rtcm3Protocol_t* instance, uint8_t rx_byte) {
    bool res = false;
    if(instance->load_len < (RTCM3_HEADER_SIZE + instance->exp_len.field.len - 1)) {
        instance->rx_frame[instance->load_len] = rx_byte;
        instance->load_len++;
        instance->rx_state = WAIT_PAYLOAD;
        res = true;
    } else if(instance->load_len == (RTCM3_HEADER_SIZE + instance->exp_len.field.len - 1)) {
        instance->rx_frame[instance->load_len] = rx_byte;
        instance->load_len++;
        instance->rx_state = WAIT_CRC;
        res = true;
    } else {
        rtcm3_reset_rx(instance, WAIT_PAYLOAD);
    }
    return res;
}

static bool rtcm3_proc_wait_crc24(Rtcm3Protocol_t* instance, uint8_t rx_byte) {
#ifdef X86_64
    LOG_PARN(RTCM, "ProcWaitCRC24 0x%02x", rx_byte);
#endif
    bool res = false;
    uint16_t crc24_index = RTCM3_HEADER_SIZE + instance->exp_len.field.len;
    if(crc24_index == instance->load_len) {
        instance->rx_frame[instance->load_len] = rx_byte;
        instance->load_len++;
        instance->rx_state = WAIT_CRC;
        res = true;
    } else if((crc24_index + 1) == instance->load_len) {
        instance->rx_frame[instance->load_len] = rx_byte;
        instance->load_len++;
        instance->rx_state = WAIT_CRC;
        res = true;
    } else if((crc24_index + 2) == instance->load_len) {
        instance->rx_frame[instance->load_len] = rx_byte;
        instance->load_len++;
        memcpy(&instance->read_crc, &instance->rx_frame[crc24_index], RTCM3_CRC24_SIZE);
        instance->read_crc = reverse_byte_order_uint24(instance->read_crc);
        uint16_t frame_length = instance->exp_len.field.len + RTCM3_HEADER_SIZE;
        res = crc24_q_check(&instance->rx_frame[0], frame_length, instance->read_crc);
        if(true == res) {
            res = true;
#ifdef HAS_LOG
            LOG_DEBUG(RTCM, "CRC24ok");
#endif
#ifdef HAS_DEBUG
            rtcm3_update_len_stat(instance, instance->exp_len.field.len);
#endif
            instance->rx_state = RX_DONE;
            instance->rx_pkt_cnt++;
            memcpy(instance->fix_frame, instance->rx_frame, RTCM3_RX_MAX_FRAME_SIZE);
            /*Send RTCM3 frame to LoRa*/
#ifdef HAS_LED
            led_blink(&Led[LED_INDEX_RED], 30);
#endif
            uint16_t packet_length = frame_length + RTCM3_CRC24_SIZE;
            instance->rx_byte += packet_length;
            if(MAX_LORA_PAYLOAD_SIZE < packet_length) {
                instance->jumbo_frame_cnt++;
                LOG_DEBUG(RTCM, "TooBigFrame %u byte", packet_length, MAX_LORA_PAYLOAD_SIZE);
            }
            switch(instance->interface) {
            case IF_UART1: {

                Interfaces_t interface = IF_NONE;
                for(interface = IF_LORA; interface <= IF_CNT; interface++) {
                    if(instance->forwarding[interface]) {
#if defined(HAS_TBFP) && defined(HAS_UBLOX)
                        /*Wrap to TBFP*/
                        if(FIX_TYPE_TIME_ONLY_FIX == NavInfo.FixType) {
                            res = tbfp_send(instance->fix_frame, frame_length + RTCM3_CRC24_SIZE, interface, 0,
                                            ACK_NO_NEED);
                            if(false == res) {
                                instance->lost_pkt_cnt[interface]++;
                                TbfpProtocol[interface].err_tx_cnt++;
                            }
                        }
#endif /*HAS_TBFP*/
                    }
                }
            } break;
            case IF_LORA:
            case IF_RS232:
            case IF_CAN: {
#ifdef HAS_UART1
                res = uart_send(UART_NUM_ZED_F9P, instance->fix_frame, frame_length + RTCM3_CRC24_SIZE, true);
                if(false == res) {
                    instance->uart_lost_pkt_cnt++;
                }
#endif /*HAS_UART1*/

            } break;
            }
#ifdef HAS_TBFP
            tbfp_parser_reset_rx(&TbfpProtocol[instance->interface], RX_DONE);
#endif
            rtcm3_reset_rx(instance, WAIT_CRC);
        } else {
#if defined(HAS_LOG) && defined(HAS_MCU)
            LOG_DEBUG(RTCM, "%s CrcErr", InterfaceToStr(instance->interface));
#endif
            instance->crc_err_cnt++;
            rtcm3_reset_rx(instance, WAIT_CRC);
        }
    } else {
        rtcm3_reset_rx(instance, WAIT_CRC);
    }
    return res;
}

bool rtcm3_proc_byte(Rtcm3Protocol_t* instance, uint8_t rx_byte) {
    bool res = false;
    switch(instance->rx_state) {
    case WAIT_PREAMBLE:
        res = rtcm3_proc_wait_preamble(instance, rx_byte);
        break;
    case WAIT_LEN:
        res = rtcm3_proc_wait_len(instance, rx_byte);
        break;
    case WAIT_PAYLOAD:
        res = rtcm3_proc_wait_payload(instance, rx_byte);
        break;
    case WAIT_CRC:
        res = rtcm3_proc_wait_crc24(instance, rx_byte);
        break;
    default:
        rtcm3_reset_rx(instance, WAIT_UNDEF);
        break;
    }
    return res;
}

bool rtcm3_generate_frame(uint8_t* arr, uint32_t size) {
    bool res = true;
    LOG_INFO(RTCM, "%s():", __FUNCTION__);
    Rtcm3Len_t ex_len;
    arr[0] = RTCM3_PREAMBLE;
    ex_len.field.len = size - RTCM3_CRC24_SIZE - RTCM3_HEADER_SIZE;
    arr[1] = ex_len.len8[1];
    arr[2] = ex_len.len8[0];
    uint16_t frame_length = size - RTCM3_CRC24_SIZE;
    Type32Union_t u32val;
    u32val.u32 = calc_crc24_q(arr, frame_length);
    LOG_INFO(RTCM, "CRC24 0x%x", u32val.u32);
    arr[size - RTCM3_CRC24_SIZE] = u32val.u8[2];
    arr[size - RTCM3_CRC24_SIZE + 1] = u32val.u8[1];
    arr[size - RTCM3_CRC24_SIZE + 2] = u32val.u8[0];
    LOG_INFO(RTCM, "%s()Done:", __FUNCTION__);
    return res;
}

bool is_rtcm3_frame(uint8_t* arr, uint16_t len) {
    bool res = true;
    LOG_DEBUG(RTCM, "IsRtcm3");
    Rtcm3Len_t ex_len;
    ex_len.len16 = 0;
    uint32_t read_crc24 = 0;
    uint16_t frame_length = 0;
    uint16_t crc24_index = 0;
    if((NULL == arr) || (0 == len)) {
        res = false;
    }

    if(res) {
        if(RTCM3_PREAMBLE != arr[0]) {
            LOG_DEBUG(RTCM, "PreErr");
            res = false;
        }
    }
    if(res) {
        ex_len.len8[0] = arr[2];
        ex_len.len8[1] = arr[1];
        if(0 == ex_len.field.len) {
            res = false;
        } else {
            frame_length = ex_len.field.len + RTCM3_HEADER_SIZE;
            LOG_DEBUG(RTCM, "PayLoadLen %u", ex_len.field.len);
        }
    }

    if(res) {
        crc24_index = RTCM3_HEADER_SIZE + ex_len.field.len;
        memcpy(&read_crc24, &arr[crc24_index], RTCM3_CRC24_SIZE);
        read_crc24 = reverse_byte_order_uint24(read_crc24);
        res = crc24_q_check(arr, frame_length, read_crc24);
    }

    return res;
}

bool rtcm3_proc_array(uint8_t* const payload, uint32_t size, Interfaces_t interface) {
    bool res = false;
#ifdef X86_64
    LOG_PARN(RTCM, "%s():", __FUNCTION__);
#endif
    if((NULL != payload) && (0 < size)) {
        uint32_t i = 0;
        rtcm3_reset_rx(&Rtcm3Protocol[interface], WAIT_INIT);
        uint32_t init_rx_pkt_cnt = Rtcm3Protocol[interface].rx_pkt_cnt;
        for(i = 0; i < size; i++) {
            res = rtcm3_proc_byte(&Rtcm3Protocol[interface], payload[i]);
        }
        if(init_rx_pkt_cnt < Rtcm3Protocol[interface].rx_pkt_cnt) {
            res = true;
        }
    }

    return res;
}

bool rtcm3_calc_byte_rate(void) {
    bool res = false;
    Interfaces_t interface;
    for(interface = (Interfaces_t)0; interface < ARRAY_SIZE(Rtcm3Protocol); interface++) {
        if(interface == Rtcm3Protocol[interface].interface) {
            Rtcm3Protocol[interface].rx_rate.cur =
                Rtcm3Protocol[interface].rx_byte - Rtcm3Protocol[interface].rx_byte_prev;
            Rtcm3Protocol[interface].rx_rate.min =
                min32u(Rtcm3Protocol[interface].rx_rate.cur, Rtcm3Protocol[interface].rx_rate.min);
            Rtcm3Protocol[interface].rx_rate.max =
                max32u(Rtcm3Protocol[interface].rx_rate.cur, Rtcm3Protocol[interface].rx_rate.max);
            Rtcm3Protocol[interface].rx_byte_prev = Rtcm3Protocol[interface].rx_byte;

            Rtcm3Protocol[interface].tx_rate.cur =
                Rtcm3Protocol[interface].tx_byte - Rtcm3Protocol[interface].tx_byte_prev;
            Rtcm3Protocol[interface].tx_rate.min =
                min32u(Rtcm3Protocol[interface].tx_rate.cur, Rtcm3Protocol[interface].tx_rate.min);
            Rtcm3Protocol[interface].tx_rate.max =
                max32u(Rtcm3Protocol[interface].tx_rate.cur, Rtcm3Protocol[interface].tx_rate.max);
            Rtcm3Protocol[interface].tx_byte_prev = Rtcm3Protocol[interface].tx_byte;
            res = true;
        }
    }
    return res;
}
