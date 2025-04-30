/*UBX is a little-endian protocol*/

#include "ubx_protocol.h"

#include <string.h>

#include "data_utils.h"
#include "debug_info.h"
#ifdef HAS_MCU
#include "clocks.h"
#include "common_functions.h"
#include "task_info.h"
#include "time_mcal.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif
#include "ublox_driver.h"
#include "ubx_diag.h"

UbloxProtocol_t UbloxProtocol = {0};
StatClass_t tableRxClass[UBX_CLA_CNT] = {0};

bool ubx_reset_rx(void) {
    UbloxProtocol.load_len = 0;
    UbloxProtocol.exp_len = 0;
    UbloxProtocol.rx_state = UBX_WAIT_SYC0;
    return true;
}

bool ublox_protocol_init(void) {
    ubx_reset_rx();
    UbloxProtocol.diag = false;
    UbloxProtocol.rx_pkt_cnt = 0;
    UbloxProtocol.ack_cnt = 0;
#ifdef HAS_DEBUG
    UbloxProtocol.min_len = 0xffff;
    UbloxProtocol.max_len = 0;
#endif
    UbloxProtocol.unproc_frame = false;
    memset(UbloxProtocol.fix_frame, 0x00, UBX_RX_FRAME_SIZE);
    memset(tableRxClass, 0x00, sizeof(tableRxClass));
    return true;
}

uint16_t ubx_calc_crc16(uint8_t* const array, uint16_t len) {
    uint16_t crc16 = 0U;
    uint8_t crc_a = 0, crc_b = 0;
    uint16_t i = 0;
    for(i = 0; i < len; i++) {
        crc_a = crc_a + array[i];
        crc_b = crc_b + crc_a;
    }
    crc16 = (((uint16_t)crc_b) << 8) | ((uint16_t)crc_a);
    return crc16;
}

static bool proc_ublox_wait_sync0(uint8_t rx_byte) {
    bool res = false;
    if(UBX_SYN_0 == rx_byte) {
        UbloxProtocol.rx_state = UBX_WAIT_SYC1;
        UbloxProtocol.rx_frame[0] = rx_byte;
        UbloxProtocol.load_len = 1;
        res = true;
    } else {
        ubx_reset_rx();
    }
    return res;
}

static bool proc_ublox_wait_sync1(uint8_t rx_byte) {
    bool res = false;
    if(UBX_SYN_1 == rx_byte) {
        UbloxProtocol.rx_state = UBX_WAIT_CLASS;
        UbloxProtocol.rx_frame[1] = rx_byte;
        UbloxProtocol.load_len = 2;
#ifdef HAS_DEBUG
        UbloxProtocol.sync_cnt++;
#endif
        res = true;
    } else {
        ubx_reset_rx();
    }
    return res;
}

static bool proc_ublox_wait_calss(uint8_t rx_byte) {
    UbloxProtocol.rx_frame[2] = rx_byte;
    UbloxProtocol.load_len = 3;
    UbloxProtocol.rx_state = UBX_WAIT_ID;
    return true;
}

static bool proc_ublox_wait_id(uint8_t rx_byte) {
    UbloxProtocol.rx_frame[3] = rx_byte;
    UbloxProtocol.load_len = 4;
    UbloxProtocol.rx_state = UBX_WAIT_LEN;
    return true;
}

static bool proc_ublox_wait_len(uint8_t rx_byte) {
    bool res = false;
    if(4 == UbloxProtocol.load_len) {
        UbloxProtocol.rx_frame[4] = rx_byte;
        UbloxProtocol.load_len = 5;
        UbloxProtocol.rx_state = UBX_WAIT_LEN;
        res = true;
    } else if(5 == UbloxProtocol.load_len) {
        UbloxProtocol.rx_frame[5] = rx_byte;
        UbloxProtocol.load_len = 6;
        memcpy(&UbloxProtocol.exp_len, &UbloxProtocol.rx_frame[4], UBX_LEN_SIZE);
#ifdef HAS_DEBUG
        UbloxProtocol.min_len = min16u(UbloxProtocol.min_len, UbloxProtocol.exp_len);
        UbloxProtocol.max_len = max16u(UbloxProtocol.max_len, UbloxProtocol.exp_len);
#endif /*HAS_DEBUG*/
        UbloxProtocol.rx_state = UBX_WAIT_PAYLOAD;
        res = true;
        if(UBX_RX_FRAME_SIZE < UbloxProtocol.exp_len) {
            ubx_reset_rx();
        }
    } else {
        ubx_reset_rx();
    }
    return res;
}

bool proc_ublox_wait_payload(uint8_t rx_byte) {
    bool res = false;
    if(UbloxProtocol.load_len < (UBX_HEADER_SIZE + UbloxProtocol.exp_len - 1)) {
        UbloxProtocol.rx_frame[UbloxProtocol.load_len] = rx_byte;
        UbloxProtocol.load_len++;
        UbloxProtocol.rx_state = UBX_WAIT_PAYLOAD;
        res = true;
    } else if(UbloxProtocol.load_len == (UBX_HEADER_SIZE + UbloxProtocol.exp_len - 1)) {
        UbloxProtocol.rx_frame[UbloxProtocol.load_len] = rx_byte;
        UbloxProtocol.load_len++;
        UbloxProtocol.rx_state = UBX_WAIT_CRC;
        res = true;
    } else {
        ubx_reset_rx();
    }
    return res;
}

static bool proc_ublox_wait_crc(uint8_t rx_byte) {
    bool res = false;
    uint16_t calc_crc = 0;
    uint16_t crc_index = UBX_HEADER_SIZE + UbloxProtocol.exp_len;
    if(crc_index == UbloxProtocol.load_len) {
        UbloxProtocol.rx_frame[UbloxProtocol.load_len] = rx_byte;
        UbloxProtocol.load_len++;
        UbloxProtocol.rx_state = UBX_WAIT_CRC;
        res = true;
    } else if((crc_index + 1) == UbloxProtocol.load_len) {
        UbloxProtocol.rx_frame[UbloxProtocol.load_len] = rx_byte;
        UbloxProtocol.load_len++;
        memcpy(&UbloxProtocol.read_crc, &UbloxProtocol.rx_frame[crc_index], UBX_LEN_SIZE);
        uint16_t len = UbloxProtocol.exp_len + 4;
        calc_crc = ubx_calc_crc16(&UbloxProtocol.rx_frame[2], len);
        if(calc_crc == UbloxProtocol.read_crc) {
            UbloxProtocol.rx_state = UBX_RX_DONE;
            UbloxProtocol.rx_pkt_cnt++;
            memcpy(UbloxProtocol.fix_frame, UbloxProtocol.rx_frame, UBX_RX_FRAME_SIZE);
            UbloxProtocol.unproc_frame = true;
#ifdef HAS_MCU
            UbloxProtocol.rx_time_stamp = get_time_ms32();
#endif /*HAS_MCU*/
#ifdef HAS_LOG
            LOG_DEBUG(UBX, "RxFrameClassId: %s len:%u Crc16 Ok!",
                      ClassId2str(UbloxProtocol.fix_frame[UBX_INDEX_CLS], UbloxProtocol.fix_frame[UBX_INDEX_ID]), len);
#endif
#ifdef HAS_MCU
            res = ubx_proc_frame(&UbloxProtocol);
#ifdef HAS_LOG
            if(res) {
                LOG_DEBUG(UBX, "RxProcDone");
            }
#endif
#endif /*HAS_MCU*/
            ubx_reset_rx();
            res = true;
        } else {
            UbloxProtocol.crc_err_cnt++;
            ubx_reset_rx();
        }
    } else {
        ubx_reset_rx();
    }
    return res;
}

bool ubx_proc_byte(uint8_t rx_byte) {
    bool res = false;
    switch(UbloxProtocol.rx_state) {
    case UBX_WAIT_SYC0:
        res = proc_ublox_wait_sync0(rx_byte);
        break;
    case UBX_WAIT_SYC1:
        res = proc_ublox_wait_sync1(rx_byte);
        break;
    case UBX_WAIT_CLASS:
        res = proc_ublox_wait_calss(rx_byte);
        break;
    case UBX_WAIT_ID:
        res = proc_ublox_wait_id(rx_byte);
        break;
    case UBX_WAIT_LEN:
        res = proc_ublox_wait_len(rx_byte);
        break;
    case UBX_WAIT_PAYLOAD:
        res = proc_ublox_wait_payload(rx_byte);
        break;
    case UBX_WAIT_CRC:
        res = proc_ublox_wait_crc(rx_byte);
        break;
    default:
        ubx_reset_rx();
        break;
    }
    return res;
}

bool ubx_update_stat(uint8_t val_class) {
    bool res = false;
    bool inc = false;
    uint8_t i;
    for(i = 0; i < ARRAY_SIZE(tableRxClass); i++) {
        if(val_class == tableRxClass[i].class_val) {
            tableRxClass[i].cnt++;
            res = true;
            inc = true;
            break;
        }
    }

    if(false == inc) {
        for(i = 0; i < ARRAY_SIZE(tableRxClass); i++) {
            if(0x00 == tableRxClass[i].class_val) {
                tableRxClass[i].class_val = val_class;
                tableRxClass[i].cnt = 1;
                res = true;
                inc = true;
                break;
            }
        }
    }

    return res;
}

/*see Page 176 */
uint8_t ubx_key_len_2bytes(uint8_t code) {
    uint8_t bytes = 0;
    switch(code) {
    case 1:
    case 2:
        bytes = 1;
        break;
    case 3:
        bytes = 2;
        break;
    case 4:
        bytes = 4;
        break;
    case 5:
        bytes = 8;
        break;
    default:
        bytes = 0;
        break;
    }
    return bytes;
}

uint8_t ubx_keyid_2len(uint32_t key_id) {
    uint8_t bytes = 0;
    ConfigurationKeyID_t KeyId;
    KeyId.word = key_id;
    bytes = ubx_key_len_2bytes(KeyId.size);
    return bytes;
}

#ifdef HAS_UART
bool ubx_wait_ack(uint32_t wait_pause_ms) {
    bool res = false, loop = true;
    uint32_t start_ms = 0U, curr_ms = 0U, diff_ms = 0;
    start_ms = get_time_ms32();
    uint64_t loop_start_time_us = 0;
    while(loop) {
        if(true == UbloxProtocol.ack) {
            res = true;
            loop = false;
        }
        if(false == res) {
            loop_start_time_us = get_time_us();
            super_loop(loop_start_time_us);

            curr_ms = get_time_ms32();
            diff_ms = curr_ms - start_ms;
            if(wait_pause_ms < diff_ms) {
                res = false;
                loop = false;
            }
        }
    }
    return res;
}
#endif
