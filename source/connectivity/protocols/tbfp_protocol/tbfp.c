#include "tbfp.h"

//#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "board_api.h"
#include "byte_utils.h"
#include "common_diag.h"
#include "common_functions.h"
#include "data_utils.h"
#include "interface_drv.h"
#include "protocol\protocol.h"

#ifdef HAS_LED
#include "led_drv.h"
#endif

#ifdef HAS_STORAGE
#include "storage.h"
#endif
//#include "debug_info.h"

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifdef HAS_ARRAY_DIAG
#include "array_diag.h"
#endif

#ifdef HAS_DS_TWR
#include "ds_twr.h"
#endif /*HAS_DS_TWR*/

#ifdef HAS_CLI
#include "cli_drv.h"
#include "writer_config.h"
#endif /*HAS_CLI*/

#ifdef HAS_KEYLOG
#include "keylog.h"
#endif

#ifdef HAS_DECAWAVE
#include "decawave.h"
#endif

#ifdef HAS_DECAWAVE_NATIVE
#include "decawave_native.h"
#endif

#ifdef HAS_DWM1000_DRV
#include "dwm1000_drv.h"
#ifdef HAS_DWM1000_RANGE
#include "dwm1000_range.h"
#endif /*HAS_DWM1000_RANGE*/
#endif /*HAS_DWM1000_DRV*/

#ifdef HAS_SUPER_CYCLE
#include "super_cycle.h"
#endif

#ifdef HAS_CALENDAR
#include "calendar.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_RADIO
#include "radio_drv.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif /*HAS_LOG*/

#ifdef HAS_CORE
#include "core_driver.h"
#endif /*HAS_CORE*/

#ifdef HAS_CRC
#include "crc8_sae_j1850.h"
#endif

#ifdef HAS_KEYBOARD
#include "keyboard.h"
#endif

#ifdef HAS_FLOAT
#include "float_utils.h"
#endif
#ifdef HAS_TIME
#include "none_blocking_pause.h"
#endif
#include "protocol_diag.h"

#ifdef HAS_FLASH_FS
#include "flash_fs.h"
#endif

#ifdef HAS_GNSS
#include "gnss_diag.h"
#include "gnss_utils.h"
#endif

#ifdef HAS_PARAM
#include "param_drv.h"
#endif /*HAS_PARAM*/

#ifdef HAS_RS232
#include "rs232_drv.h"
#endif /*HAS_RS232*/

#ifdef HAS_RTCM3
#include "rtcm3_protocol.h"
#endif /*HAS_RTCM3*/

#include "system.h"
#ifdef HAS_SYSTEM_DIAG
#include "system_diag.h"
#endif
#ifdef HAS_TBFP_RETX
#include "tbfp_re_tx_ack_fsm.h"
#endif

#ifdef HAS_GNSS
#include "gnss_diag.h"
#include "gnss_drv.h"
#endif

#ifdef X86_64
#include "log.h"
#include <stdio.h>
#endif

#ifndef HAS_TBFP
#error "That components needs HAS_TBFP macro define"
#endif

#include "code_generator.h"

COMPONENT_GET_NODE(Tbfp, tbfp)
COMPONENT_GET_CONFIG(Tbfp, tbfp)

#ifdef HAS_TBFP_EXT
/* 49 days max*/
/*none blocking wait for self test and polling*/
bool tbfp_wait_response_in_loop_ms(const TbfpHandle_t*const  Node, uint32_t wait_timeout_ms) {
    bool res = false;

#ifdef HAS_LOG
        LOG_PARN(TIME, "Pause %u ms", wait_timeout_ms);
#endif

#ifdef HAS_FREE_RTOS
        vTaskDelay(wait_timeout_ms / portTICK_RATE_MS);
        res = true;
#endif

        uint32_t start_ms = 0U;
        uint32_t curr_ms = 0U;
        start_ms = time_get_ms32();
        bool loop = true;

        while(loop) {
#ifdef HAS_SUPER_CYCLE
            super_cycle_iteration();
#endif
            curr_ms = time_get_ms32();
            if(wait_timeout_ms < (curr_ms - start_ms)) {
                res = false;
                loop = false;
                break;
            }

            if(Node->rx_done){
            	loop = false;
            	res = true;
            	break;
            }
        }

    return res;
}
#endif

#if 0
TbfpHandle_t* TbfpGetNode(uint32_t num) {
    TbfpHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = tbfp_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(TbfpInstance[i].num == num) {
            if(TbfpInstance[i].valid) {
                Node = &TbfpInstance[i];
            }
            break;
        }
    }
    return Node;
}
#endif

TbfpHandle_t* TbfpInterfaceToNode(const Interfaces_t inter_face) {
    TbfpHandle_t* Node = NULL;
#ifdef HAS_LOG
    LOG_PARN(TBFP, "%s():If:%u", __FUNCTION__,inter_face);
#endif
    uint32_t i = 0;
    uint32_t cnt = tbfp_get_cnt();
#ifdef HAS_LOG
    LOG_PARN(TBFP, "Cnt %u", cnt);
#endif
    for(i = 0; i < cnt; i++) {
    	tbfp_init_common(&TbfpConfig[i], &TbfpInstance[i]);
#ifdef HAS_LOG
        LOG_PARN( TBFP, "%u,%s", i, TbfpNodeToStr(&TbfpInstance[i])    );
#endif
        if(inter_face==TbfpInstance[i].inter_face ) {
            if(TbfpInstance[i].valid) {
                Node = &TbfpInstance[i];
                break;
            }
        }
    }
    return Node;
}

#if 0
const TbfpConfig_t* TbfpGetConfig(uint32_t num) {
    const TbfpConfig_t* Config = NULL;
    uint32_t i = 0;
    uint32_t cnt = tbfp_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(TbfpInstance[i].valid) {
            if(TbfpConfig[i].num == num) {
                Config = &TbfpConfig[i];
                break;
            }
        }
    }
    return Config;
}
#endif

// bool tbfp_protocol_init(TbfpHandle_t* Node, Interfaces_t inter_face, uint8_t preamble_val) {
#if 0
bool tbfp_protocol_init(void) {
    bool res = false;
#ifdef HAS_LOG
    set_log_level(TBFP, LOG_LEVEL_DEBUG);
#endif
    uint32_t cnt = tbfp_get_cnt();
#ifdef HAS_LOG
    LOG_INFO(TBFP, "Init Cnt:%u", cnt);
    LOG_INFO(TBFP, "MaxPayLoadSize: %u Byte", TBFP_MAX_PAYLOAD);
#endif
    uint32_t ok_cnt = 0;
    uint32_t i = 0;
    for(i = 0; i <= cnt; i++) {
        res = tbfp_protocol_init_one(i);
        if(res) {
            ok_cnt++;
        }
    }
    if(0 == ok_cnt) {
#ifdef HAS_LOG
        LOG_ERROR(TBFP, "InitErr");
#endif
        res = false;
    } else {
#ifdef HAS_LOG
        LOG_INFO(TBFP, "Init %u inst", ok_cnt);
#endif
        res = true;
    }
#ifdef HAS_LOG
    set_log_level(TBFP, LOG_LEVEL_INFO);
#endif
    return res;
}
#endif

#ifdef HAS_TBFP_EXT
bool is_tbfp_protocol(uint8_t* arr, uint16_t len, Interfaces_t inter_face) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(TBFP, "LOG_PARN len: %u", len);
#endif
    TbfpHeader_t header = {0};
    memcpy(&header, arr, sizeof(TbfpHeader_t));

    TbfpHandle_t* Node = TbfpInterfaceToNode(inter_face);
    if(Node) {
#ifdef HAS_LOG
        LOG_PARN(TBFP, "SpotNode");
#endif
        if(Node->preamble_val != header.preamble) {
#ifdef HAS_LOG
            LOG_ERROR(TBFP, "FramePreambleErr Exp:0x%x Real:0x%x", Node->preamble_val, header.preamble);
#endif
            res = false;
        } else {
            res = true;
        }
        if(res) {
            if(header.len < len) {
                res = true;
            } else {
                res = false;
#ifdef HAS_LOG
                LOG_ERROR(TBFP, "FrameLenErr", header.len);
#endif
            }
        }
        if(res) {
#ifdef HAS_CRC8
        	if(Node->crc_check_need) {
                uint32_t frame_len = sizeof(TbfpHeader_t) + header.len;
                uint8_t read_crc8 = arr[frame_len];
                uint8_t calc_crc8 = 0;

                res = crc8_sae_j1850_check(arr, frame_len, read_crc8, &calc_crc8);
#endif /*   HAS_CRC8 */
                if(res) {
#ifdef HAS_LOG
                  LOG_PARN(TBFP, "Crc8,OkRead:0x%02x", read_crc8);
#endif
                } else {
#ifdef HAS_LOG
                    LOG_ERROR(TBFP, "Crc8,ErrRead:0x%02x,Calc:0x%02x", read_crc8, calc_crc8);
#endif
                }
        	}
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(TBFP, "NodeErr");
#endif
    }

    return res;
}
#endif

static bool tbfp_make_header(uint8_t* out_array, uint32_t payload_size, Interfaces_t inter_face, uint8_t lifetime,
                             TbfpAck_t ack, TbfpPayloadId_t payload_id) {
    bool res = false;
    TbfpHandle_t* Node = TbfpInterfaceToNode(inter_face);
    if(Node) {
        if(payload_size < TBFP_MAX_PAYLOAD) {
            if(out_array) {
                TbfpHeader_t header;
                memset(&header, 0, sizeof(header));
                header.preamble = Node->preamble_val;
                header.payload_id = payload_id;
#ifdef HAS_TBFP_FLOW_CONTROL
                header.snum = Node->tx_sn;
                Node->expected_ser_num = header.snum;
                Node->tx_sn++;
#endif /*HAS_TBFP_FLOW_CONTROL*/

                header.flags.ack_need = ack;
                if(lifetime < 3) {
                    header.flags.lifetime = lifetime;
                }
                Node->tx_pkt_cnt++;
                header.len = (uint16_t)payload_size;
                memcpy(out_array, &header, sizeof(TbfpHeader_t));
                res = true;
            } else {
#ifdef HAS_LOG
                LOG_ERROR(TBFP, "NullPayLoad");
#endif
            }

        } else {
#ifdef HAS_LOG
            LOG_ERROR(TBFP, "TooBigPayload %u (Lim: %u)", payload_size, TBFP_MAX_PAYLOAD);
#endif
        }
    }
    return res;
}

#ifdef HAS_TBFP_RETX
IfRetx_t AckNeed2Retx(TbfpAck_t ack) {
    IfRetx_t retx = RETX_NO_NEED;
    switch(ack) {
    case ACK_NEED:
        retx = RETX_NEED;
        break;
    case ACK_NO_NEED:
        retx = RETX_NO_NEED;
        break;
    }
    return retx;
}
#endif

#ifdef HAS_TBFP_EXT
bool tbfp_storage_write_generate(const uint8_t tbfp_num, const uint32_t address,
		const uint8_t *const data, const uint16_t size) {
	bool res = false;
	TbfpHandle_t *Node = TbfpGetNode(tbfp_num);
	if (Node) {
		LOG_PARN(TBFP, "%s", TbfpNodeToStr(Node));
		if (Node->TxFrame) {
			uint32_t req_size = (     sizeof(TbfpHeader_t) + sizeof(StorageFrameHeader_t)     );
			if (req_size < Node->tx_array_size) {
				uint16_t payload_len = (uint16_t) sizeof(StorageFrameHeader_t)
						+ size;
				TbfpHeader_t Header = { 0 };
				(void) Header;
				Header.preamble = Node->preamble_val;
				Header.flags.ack_need = 1;
				Header.flags.crc_check_need = 1;
				Header.flags.lifetime = 1;
				Header.payload_id = FRAME_ID_STORAGE;
				Header.snum = 1;
				Header.len = payload_len;

				memcpy(Node->TxFrame, &Header, sizeof(TbfpHeader_t));
#if 1
                StorageFrameHeader_t StorageData;
                (void) StorageData;
                StorageData.address = address;
                StorageData.asic_num = 1;
                StorageData.operation = ACCESS_WRITE_ONLY;
                StorageData.size = size; /* Bytes to read */
                memcpy(&Node->TxFrame[sizeof(TbfpHeader_t)], &StorageData, sizeof(StorageFrameHeader_t));
                uint32_t data_index = sizeof(TbfpHeader_t) + sizeof(StorageFrameHeader_t);
                (void)data_index;
                //memcpy(&Node->TxFrame[data_index], data, size);

                uint16_t frame_len = payload_len + sizeof(TbfpHeader_t);
                Node->tx_size = frame_len + 1;
                Node->TxFrame[frame_len] = crc8_sae_j1850_calc(Node->TxFrame, frame_len);

                LOG_PARN(TBFP, "%s",TbfpSrorageWriteToStr(Node,address,size));
#endif
				res = true;
			}else{
	            LOG_ERROR(TBFP, "TxBuffSeizeErr %u",Node->tx_array_size);
	        }
		}else{
            LOG_ERROR(TBFP, "NoTxBuff Node:%u",tbfp_num);
        }
	}
	return res;
}
#endif

bool tbfp_send_payload(uint8_t* payload, uint32_t payload_size, Interfaces_t inter_face, uint8_t lifetime,
                       TbfpAck_t ack, TbfpPayloadId_t payload_id) {
    bool res = false;
#ifdef HAS_TBFP_DIAG
    LOG_PARN(TBFP, "TxSize:%u byte,IF:%s,PlID:%s", payload_size, InterfaceToStr(inter_face),
              TbfpPayloadIdToStr(payload_id));
#endif
    TbfpHandle_t* Node = TbfpInterfaceToNode(inter_face);
    if(Node) {
        IfRetx_t retx = RETX_NO_NEED;
#ifdef HAS_TBFP_RETX
        retx = AckNeed2Retx(ack);
#endif
        uint32_t tx_frame_len = 0;
        uint32_t frame_len = 0;
        if(payload && (0 < payload_size)) {
            tx_frame_len = payload_size + TBFP_SIZE_OVERHEAD;

            if(tx_frame_len < Node->tx_array_size) {
                frame_len = TBFP_SIZE_HEADER + payload_size;
                memset(Node->TxFrame, 0x00, Node->tx_array_size);
                res = tbfp_make_header(Node->TxFrame, payload_size, inter_face, lifetime, ack, payload_id);
                if(false == res) {
#ifdef HAS_LOG
                    LOG_ERROR(TBFP, "TooBigPayload cur: %u max: %u", payload_size, Node->tx_array_size);
#endif
                }
            } else {
                res = false;
#ifdef HAS_LOG
                LOG_ERROR(TBFP, "TooBigTxFrame cur: %u max: %u", tx_frame_len, Node->tx_array_size);
#endif
            }
        } else {
            res = false;
#ifdef HAS_LOG
            LOG_ERROR(TBFP, "PayErr");
#endif
        }

        if(res) {
            TbfpHeader_t OutHeader = {0};
            memcpy(&OutHeader, Node->TxFrame, sizeof(TbfpHeader_t));
            memcpy(&(Node->TxFrame[TBFP_INDEX_PAYLOAD]), payload, payload_size);
#ifdef HAS_CRC8
            Node->TxFrame[frame_len] = crc8_sae_j1850_calc(Node->TxFrame, frame_len);
#endif

#ifdef HAS_LOG
            LOG_PARN(TBFP, "%s Sent SN:%u=0x%04x Len:%u crc8 0x%02x", InterfaceToStr(inter_face), OutHeader.snum,
                      OutHeader.snum, OutHeader.len, Node->TxFrame[frame_len]);
#endif
            Node->tx_byte += frame_len + TBFP_SIZE_CRC;
            res = sys_send_if(Node->TxFrame, frame_len + TBFP_SIZE_CRC, inter_face, retx);
            if(false == res) {
#ifdef HAS_LOG
                LOG_ERROR(TBFP, "%s SysSendErr", InterfaceToStr(inter_face));
#endif
            } else {
#ifdef HAS_LOG
                LOG_PARN(TBFP, "%s SysSendOk", InterfaceToStr(inter_face));
#endif
            }
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(TBFP, "InvalIf %u %s", inter_face, InterfaceToStr(inter_face));
#endif
    }
    return res;
}

#ifdef HAS_TBFP_ACK
bool tbfp_send_ack(uint16_t snum, Interfaces_t inter_face) {
    bool res = false;
    TbfpHandle_t* Node = TbfpInterfaceToNode(inter_face);
    if(Node) {
        uint8_t payload[4] = "";
        memcpy(&payload[0], &snum, 2);
        res = tbfp_send_payload(payload, 3, inter_face, 0, ACK_NO_NEED, FRAME_ID_ACK);
#ifdef HAS_LOG
        log_res(TBFP, res, "SendAck");
#endif
        if(res) {
            Node->ack_tx_cnt++;
        } else {
            Node->err_tx_cnt++;
        }
    }
    return res;
}
#endif

#ifdef HAS_TBFP_EXT
bool tbfp_send_text(uint8_t payload_id, uint8_t* tx_array, uint32_t len, Interfaces_t inter_face, uint8_t lifetime,
                    TbfpAck_t ack) {
    bool res = false;
    uint8_t frame[256] = "";
#ifdef HAS_LOG
    LOG_PARN(TBFP, "%s SendText Ack:%u", InterfaceToStr(inter_face), ack);
#endif
    if(tx_array && (0 < len) && ((len + TBFP_SIZE_OVERHEAD + TBFP_SIZE_ID) < sizeof(frame))) {
        memcpy(&frame[0], tx_array, len);
        res = tbfp_send_payload(frame, len, inter_face, lifetime, ack, payload_id);
        if(false == res) {
#ifdef HAS_LOG
            LOG_ERROR(TBFP, "SendTextErr");
#endif
        }
    }
    return res;
}
#endif

#ifdef HAS_TBFP_EXT
bool tbfp_send_chat(uint8_t* tx_array, uint32_t len, Interfaces_t inter_face, uint8_t lifetime, TbfpAck_t ack) {
    bool res = false;
    res = tbfp_send_text(FRAME_ID_CHAT, tx_array, len, inter_face, lifetime, ack);
    return res;
}
#endif

#ifdef HAS_TBFP_EXT
bool tbfp_send_cmd(uint8_t* tx_array, uint32_t len, Interfaces_t inter_face) {
    bool res = false;
    res = tbfp_send_text(FRAME_ID_CMD, tx_array, len, inter_face, 0, ACK_NEED);
    return res;
}
#endif

#ifdef HAS_TBFP_EXT
bool tbfp_send_tunnel(uint8_t* tx_array, uint32_t len, Interfaces_t inter_face, TbfpAck_t ack) {
    bool res = false;
    res = tbfp_send_text(FRAME_ID_TUNNEL, tx_array, len, inter_face, 0, ack);
    return res;
}
#endif

#ifdef HAS_TBFP_EXT
static bool tbfp_is_ping_if(TbfpPayloadId_t payload_id) {
    bool res = false;
    switch((uint8_t)payload_id) {
    case FRAME_ID_PING:
    case FRAME_ID_PONG:
        res = true;
        break;
    }
    return res;
}
#endif

#ifdef HAS_TBFP_EXT
bool tbfp_send_ping(TbfpPayloadId_t payload_id, Interfaces_t inter_face) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(TBFP, "SendPing %s", InterfaceToStr(inter_face));
#endif
    res = tbfp_is_ping_if(payload_id);
    if(res) {
        TbfpHandle_t* Node = TbfpInterfaceToNode(inter_face);
        if(Node) {
            memset(Node->TxFrame, 0, Node->tx_array_size);
            TbfPingFrame_t pingFrame = {0};
            pingFrame.id = payload_id;
#ifdef HAS_TIME
            pingFrame.time_stamp = time_get_ms32();
#endif
            Node->rx_pong = false;
#ifdef HAS_MAC
            pingFrame.mac = get_ble_mac();
#endif /*HAS_MAC*/

#ifdef HAS_GNSS
            pingFrame.coordinate.phi = 99999.0;
            pingFrame.coordinate.lambda = 9999.0;
            res = is_valid_time(&Gnss.time_date);
            if(res) {
                pingFrame.time_stamp = TimeDateToSeconds(&Gnss.time_date);
            }
            pingFrame.height_m = Gnss.height_m;
            Node->rx_pong = false;
            res = is_valid_gnss_coordinates(Gnss.coordinate_cur);
            if(res) {
                pingFrame.coordinate = Gnss.coordinate_cur;
            } else {
                /*invalid coordinate*/
                pingFrame.coordinate.phi = 360.0;
                pingFrame.coordinate.lambda = 360.0;
            }
#endif /*HAS_GNSS*/
            memcpy(Node->TxFrame, &pingFrame, sizeof(TbfPingFrame_t));
            res = tbfp_send_payload(Node->TxFrame, sizeof(TbfPingFrame_t), inter_face, 0, ACK_NO_NEED, payload_id);
            if(false == res) {
                Node->err_send_cnt++;
#ifdef HAS_LOG
                LOG_ERROR(TBFP, "%s SendErr", InterfaceToStr(inter_face));
#endif /*HAS_LOG*/
            }
        }
    } else {
#ifdef HAS_LOG
        LOG_PARN(TBFP, "NotPingId %u", payload_id);
#endif
    }
    return res;
}
#endif

#ifdef HAS_TBFP_EXT
bool tbfp_proc_ping(uint8_t* ping_payload, uint16_t len, Interfaces_t inter_face) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(TBFP, "PingPayload");
#endif
    if(ping_payload) {
        TbfPingFrame_t pingFrame = {0};
        memcpy((void*)&pingFrame, (void*)ping_payload, sizeof(TbfPingFrame_t));
#ifdef HAS_TBFP_DIAG
        tbfp_print_ping_frame(&pingFrame);
        LOG_INFO(TBFP, "Proc %u=%s PayLoad: %s", inter_face, InterfaceToStr(inter_face),
                 TbfpPayloadIdToStr(pingFrame.id));
#endif /*HAS_TBFP_DIAG*/
        if(FRAME_ID_PING == pingFrame.id) {
#ifdef HAS_TIME
            wait_ms(1000); /*tranviver must go back to rx mode*/
#endif
            res = tbfp_send_ping(FRAME_ID_PONG, inter_face);
        }
#ifdef HAS_GNSS
        int32_t sec_diff = 0;
        res = is_valid_time(&Gnss.time_date);
        if(res) {
            uint32_t cur_ts = TimeDateToSeconds(&Gnss.time_date);
            sec_diff = abs(cur_ts - pingFrame.time_stamp);
            LOG_INFO(TBFP, "TimeDiff: %d s", sec_diff);
        }
        double cur_dist = 0.0;
        double azimuth = 0.0;
        if(is_valid_gnss_coordinates(pingFrame.coordinate)) {
            if(is_valid_gnss_coordinates(Gnss.coordinate_cur)) {
                cur_dist = gnss_calc_distance_m(Gnss.coordinate_cur, pingFrame.coordinate);
                azimuth = gnss_calc_azimuth_deg(Gnss.coordinate_cur, pingFrame.coordinate);
#ifdef HAS_LOG
                LOG_INFO(TBFP, "LinkDistance %3.3f m %4.1f deg=%s %d s", cur_dist, azimuth, BearingDeg2Str(azimuth),
                         sec_diff);
#ifdef HAS_PARAM
                gnss_update_link_info(Gnss.coordinate_cur, pingFrame.coordinate);
#endif /*HAS_PARAM*/
#endif /*HAS_LOG*/
            } else {
#ifdef HAS_LOG
                LOG_ERROR(TBFP, "InvalidLocalGNSSDot");
#endif /*HAS_LOG*/
            }
        } else {
#ifdef HAS_LOG
            LOG_ERROR(TBFP, "InvalidRemoteGNSSDot");
#endif /*HAS_LOG*/
        }
#endif /*HAS_GNSS*/

#if defined(HAS_LORA) && defined(HAS_GNSS)
        uint16_t file_len = 0;
#if defined(HAS_PARAM) && defined(HAS_FLASH_FS)
        res = mm_get(PAR_ID_MAX_LINK_DIST, (uint8_t*)&LoRaInterface.max_distance, sizeof(double), &file_len);
#endif /*HAS_PARAM && HAS_FLASH_FS*/
        if((LoRaInterface.max_distance < cur_dist) && res) {
#if defined(HAS_PARAM) && defined(HAS_FLASH_FS)
            res = mm_set(PAR_ID_MAX_LINK_DIST, (uint8_t*)&cur_dist, sizeof(double));
            if(false == res) {
#ifdef HAS_LOG
                LOG_ERROR(TBFP, "UpdateMaxDist");
#endif
            }
#endif /*HAS_PARAM && HAS_FLASH_FS*/
            LoRaInterface.max_distance = cur_dist;
        }

#endif /*HAS_LORA HAS_GNSS*/
    }
    return res;
}
#endif

#ifdef HAS_TBFP_EXT
static bool tbfp_proc_chat(uint8_t* payload, uint16_t len) {
    bool res = false;
    if((payload) && (0 < len)) {
        res = true;
#ifdef HAS_LOG
        res = print_mem(&payload[1], len - 1, false, true, true, true);
#endif
    }
    return res;
}
#endif

#ifdef HAS_TBFP_CMD
static bool tbfp_proc_cmd(uint8_t* payload, uint16_t len) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(TBFP, "CmdPayload");
#endif
    if((payload) && (0 < len) && (FRAME_ID_CMD == payload[0])) {
        res = false;
#if defined(HAS_CLI) && defined(HAS_LORA)
        curWriterPtr = &dbg_lora_o;
        payload[len] = 0x00;
        res = process_shell_cmd((char*)&payload[1]);
        curWriterPtr = &dbg_o;
#endif
    }
    return res;
}
#endif

bool tbfp_parser_reset_rx(TbfpHandle_t* Node, RxState_t state) {
    bool res = false;
    if(Node) {
        Node->rx_state = WAIT_PREAMBLE;
        Node->load_len = 0;
#ifdef HAS_PROTOCOL_DIAG
        LOG_PARN(TBFP, "ResetFsmIn: %s", ProtocolRxState2Str(state));
#endif
        res = true;
    }
    return res;
}

static bool tbfp_memory(const TbfpHandle_t* const Node) {
    bool res = false;
    if(Node) {
        res = storage_tbfp_memory(Node->num, &(Node->fix_frame[TBFP_INDEX_PAYLOAD]), Node->payload_size);
    }
    return res;
}

/*
 $A5$C1$01$00$04$00$01$00$00$00$80$E4
 */
static bool tbfp_jump(const TbfpHandle_t* const Node) {
    bool res = false;
    if(4 <= Node->payload_size) {
        // led_mono_ctrl(2, true);
        uint32_t base_address = 0;
        memcpy(&base_address, &(Node->fix_frame[TBFP_INDEX_PAYLOAD]), 4);
        res = application_launch(base_address);
    }
    return res;
}

//            //res = tbfp_proc_payload(&Node->fix_frame[TBFP_INDEX_PAYLOAD], inHeader.len, Node->inter_face,
//            inHeader.payload_id);
/*
 * len -
 * size - tbfp frame payload size
 * */
bool tbfp_proc_payload(TbfpHandle_t* Node, uint16_t len, TbfpPayloadId_t payload_id) {
    bool res = false;
    // code runs
    Node->payload_size = len;
    Node->rx_done = true;
#ifdef HAS_TBFP_DIAG
    LOG_PARN(TBFP, "%s,ProcPayloadID:0x%x=%s,Len:%u Byte", InterfaceToStr(Node->inter_face), payload_id,
              TbfpPayloadIdToStr(payload_id), len);
#endif
    // TbfpHandle_t* Node = TbfpInterfaceToNode(Node->inter_face);
    if(Node) {
        switch(payload_id) {

        case FRAME_ID_MEM: {
            res = tbfp_memory(Node);
#ifdef HAS_LOG
            log_res(TBFP, res, "Memory");
#endif
        } break;

        case FRAME_ID_JUMP: {
            // r
            res = tbfp_jump(Node);
#ifdef HAS_LOG
            log_res(TBFP, res, "JumpProc");
#endif
        } break;

#ifdef HAS_STORAGE
        case FRAME_ID_STORAGE: {
            // code runs
            res = storage_proc_cmd(Node->num, &(Node->fix_frame[TBFP_INDEX_PAYLOAD]), len);
#ifdef HAS_LOG
            log_parn_res(TBFP, res, "StoreProc");
#endif
        } break;
#endif

        case FRAME_ID_PING:
#ifdef HAS_TBFP_EXT
            Node->rx_ping = true;
            res = tbfp_proc_ping(&Node->fix_frame[TBFP_INDEX_PAYLOAD], len, Node->inter_face);
#endif
            break;

#ifdef HAS_KEYBOARD
        case FRAME_ID_KEYBOARD: {
            if(len == sizeof(KeyBoard_t)) {
                LOG_PARN(KEYLOG, "%s", KeyBoard2Str((KeyBoard_t*)&Node->fix_frame[TBFP_INDEX_PAYLOAD]));
#ifdef HAS_KEYLOG
                res = save_key((KeyBoard_t*)&Node->fix_frame[TBFP_INDEX_PAYLOAD]);
                if(res) {
                    LOG_PARN(KEYLOG, "SaveOk");
                } else {
                    LOG_ERROR(KEYLOG, "SaveErr");
                }
#endif /*HAS_KEYLOG*/
            } else {
                LOG_ERROR(KEYLOG, "KeySizeErr %u Byte", len);
            }
        } break;
#endif /*HAS_KEYLOG*/

        case FRAME_ID_ACK: {
#ifdef HAS_LOG
            LOG_PARN(TBFP, "RxAck");
#endif
            uint16_t ser_num = 0;
            memcpy(&ser_num, &Node->fix_frame[TBFP_INDEX_PAYLOAD + 1], 2);
#ifdef HAS_TBFP_RETX
            res = tbfp_retx_ack(Node, ser_num);
#endif
        } break;
        case FRAME_ID_TUNNEL: {
#ifdef HAS_LOG
            LOG_PARN(TBFP, "TBFP in TBFP"); /*matryoshka*/
#endif
        } break;
#ifdef HAS_RTCM3
        case FRAME_ID_RTCM3:
#ifdef HAS_LOG
            LOG_PARN(TBFP, "RTCMpayload");
#endif
            res = rtcm3_proc_array(&Node->fix_frame[TBFP_INDEX_PAYLOAD], len, Node->inter_face);
            break;
#endif /*HAS_RTCM3*/
        case FRAME_ID_CHAT:
#ifdef HAS_LOG
            LOG_PARN(TBFP, "ChatPayload");
#endif

#ifdef HAS_TBFP_EXT
            res = tbfp_proc_chat(&Node->fix_frame[TBFP_INDEX_PAYLOAD], len);
#endif
            break;
        case FRAME_ID_PONG:
            Node->rx_pong = true;
#ifdef HAS_LOG
            LOG_PARN(TBFP, "PongPayload");
#endif

#ifdef HAS_TBFP_EXT
            res = tbfp_proc_ping(&Node->fix_frame[TBFP_INDEX_PAYLOAD], len, Node->inter_face);
#endif
            break;
        case FRAME_ID_UNDEF:
            res = true;
            break;

#if 0
        case FRAME_ID_T_DELAY:
            DsTwrItem.start_ms = time_get_ms32();
            LOG_PARN(TBFP, "SignalTDelay");
            Dwm1000Instance.ranging = true;
            res = dwm1000_range_proc_t_delay(&Dwm1000Instance, &Node->fix_frame[TBFP_INDEX_PAYLOAD], len);
            break;
#endif

#ifdef HAS_DECAWAVE
        case FRAME_ID_DECAWAVE: {
            res = decawave_proc(1, &Node->fix_frame[TBFP_INDEX_PAYLOAD], len);
        } break;
#endif /*HAS_DECAWAVE*/

#ifdef HAS_DECAWAVE_NATIVE
        case FRAME_ID_DECAWAVE_NATIVE: {
            res = decawave_native_proc(1, &Node->fix_frame[TBFP_INDEX_PAYLOAD], len);
        } break;
#endif

#if 0
        case FRAME_ID_PESPONSE: {
            DsTwrItem.start_ms = time_get_ms32();
            LOG_PARN(TBFP, "SignalRxResp in State %s", DsTwrState2Str(DsTwrItem.state));
            res = ds_twr_parse_pesponse(&DsTwrItem, &Node->fix_frame[TBFP_INDEX_PAYLOAD], len);
        } break;
#endif /*HAS_DS_TWR*/

        case FRAME_ID_CMD:
#ifdef HAS_TBFP_CMD
            res = tbfp_proc_cmd(&Node->fix_frame[TBFP_INDEX_PAYLOAD], len);
#endif
            break;
        default:
#ifdef HAS_LOG
            LOG_ERROR(TBFP, "IF:%s,UndefPayloadID:0x%02x", InterfaceToStr(Node->inter_face), payload_id);
#endif
            res = false;
            break;
        }
    }
    return res;
}

#if 0
/*One array   can contain several TBFP frames*/
bool tbfp_proc_xxx(uint8_t* arr, uint16_t len, Interfaces_t inter_face, bool is_reset_parser) {
    bool res = true;
#ifdef HAS_LOG
    LOG_PARN(TBFP, "IF:%s,Proc %u Byte ResetParser %s", InterfaceToStr(Node->inter_face), len, OnOff2Str(is_reset_parser));
#endif
    TbfpHandle_t* Node = TbfpInterfaceToNode(Node->inter_face);
    if(Node) {
        uint32_t cur_rx_prk = 0;
        uint32_t init_rx_prk = Node->rx_pkt_cnt;
        if(is_reset_parser) {
            res = tbfp_parser_reset_rx(Node, WAIT_INIT);
        }
        uint32_t i = 0, ok_cnt = 0, err_cnt = 0;
        for(i = 0; i < len; i++) {
            res = tbfp_proc_byte(Node, arr[i]);
            if(res) {
                ok_cnt++;
            } else {
                err_cnt++;
#ifdef HAS_LOG
                LOG_ERROR(TBFP, "Arr[%u]=0x%x", i, arr[i]);
#endif
            }
        }

        cur_rx_prk = Node->rx_pkt_cnt - init_rx_prk;

        if(0 < cur_rx_prk) {
#ifdef HAS_LOG
            LOG_PARN(TBFP, "%s %u Packets in %u byte", InterfaceToStr(Node->inter_face), cur_rx_prk, len);
#endif /*HAS_LOG*/
        } else {
            if(is_reset_parser) {
                Node->lack_frame_in_data++;
#ifdef HAS_LOG
                LOG_PARN(TBFP, "%s LackPktInFrame:%u ", InterfaceToStr(Node->inter_face), len);
#endif /*HAS_LOG*/
            }

#ifdef TBFP_DIAG

            if(Node->debug) {
                print_mem(arr, len, true, false, true, true);
            }
#endif /*TBFP_DIAG*/
        }
        if(len == ok_cnt) {
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_ERROR(TBFP, "ProcErr %u!=%u", ok_cnt, len);
#endif /*HAS_LOG*/
            res = false;
        }
    }

    return res;
}
#endif

/*
  size       1        1     2     2     N      1
  field    PREAMBLE|RETX|SER_NUM|LEN|PAYLOAD|CRC8
 */

bool tbfp_send_frame(uint8_t num, TbfpPayloadId_t payload_id, uint8_t* const payload, uint16_t payload_size) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(STORAGE, "TrySend:%u", num);
#endif
    TbfpHandle_t* Node = TbfpGetNode(num);
    if(Node) {
        TbfpHeader_t Header = {0};
        Header.preamble = Node->preamble_val;
        Header.flags.ack_need = 0;
        Header.flags.crc_check_need = 0;
        Header.flags.lifetime = 15;
        Header.len = payload_size;
        Header.snum = Node->tx_sn;
        Header.payload_id = payload_id;
        memcpy(Node->TxFrame, Header.buff, sizeof(TbfpHeader_t));
        memcpy(&Node->TxFrame[sizeof(TbfpHeader_t)], payload, payload_size);

        uint16_t frame_len = payload_size + sizeof(TbfpHeader_t);
#ifdef HAS_CRC8
        Node->TxFrame[frame_len] = crc8_sae_j1850_calc(Node->TxFrame, frame_len);
#endif

        res = sys_send_if(Node->TxFrame, frame_len + TBFP_SIZE_CRC, Node->inter_face, RETX_NO_NEED);
#ifdef HAS_LOG
        log_res(TBFP, res, "SendIf");
#endif
    }
    return res;
}

/*
  size       1        1     2     2     N      1
  field    PREAMBLE|RETX|SER_NUM|LEN|PAYLOAD|CRC8
 */
#ifdef HAS_TBFP_EXT
bool tbfp_compose_frame(const uint8_t* const payload, uint16_t payload_size, Interfaces_t inter_face,
                        TbfpPayloadId_t payload_id, uint8_t* const buff, uint32_t buff_len) {
    bool res = false;
    if(payload) {
        if(payload_size) {
            if(buff) {
                if((payload_size + sizeof(TbfpHeader_t)) < buff_len) {
                    TbfpHandle_t* Node = TbfpInterfaceToNode(inter_face);
                    TbfpHeader_t* Header = (TbfpHeader_t*)buff;

                    Node->tx_pkt_cnt++;
                    Header->preamble = Node->preamble_val;
                    Header->payload_id = payload_id;
                    Header->len = payload_size;
                    Header->snum = Node->tx_pkt_cnt;
                    Header->flags.ack_need = 0;
                    Header->flags.lifetime = 1;

                    memcpy(buff + sizeof(TbfpHeader_t), payload, payload_size);
                    uint16_t frame_len = payload_size + sizeof(TbfpHeader_t);
                    buff[frame_len] = crc8_sae_j1850_calc(buff, frame_len);
                    // print_mem(buff, frame_len + 1, true, false, true, false);
                    res = true;
                }
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_TBFP_EXT
bool tbfp_generate_frame(uint8_t* const buff, uint32_t buff_len, Interfaces_t inter_face) {
    bool res = false;
    TbfpHandle_t* Node = TbfpInterfaceToNode(inter_face);
    if(buff && (TBFP_OVERHEAD_SIZE <= buff_len)) {
        uint16_t snum = 0;
        uint16_t payload_size = buff_len - TBFP_OVERHEAD_SIZE;
        buff[TBFP_INDEX_PREAMBLE] = Node->preamble_val;
        buff[TBFP_INDEX_RETX] = 0;
        memcpy(&buff[TBFP_INDEX_SER_NUM], &snum, TBFP_SIZE_SN);
        memcpy(&buff[TBFP_INDEX_LEN], &payload_size, TBFP_SIZE_SN);
        uint32_t i = 0;
        for(i = 0; i < payload_size; i++) {
            buff[TBFP_INDEX_PAYLOAD + i] = i;
        }
        uint16_t frame_len = payload_size + sizeof(TbfpHeader_t);
        buff[frame_len] = crc8_sae_j1850_calc(buff, frame_len);
        print_mem(buff, frame_len + 1, true, false, true, false);

        res = true;
    }
    return res;
}
#endif

#ifdef HAS_TBFP_EXT
bool tbfp_check(void) {
    bool res = true;
    uint32_t cnt = tbfp_get_cnt();
    uint32_t i = 0;
    for(i = (Interfaces_t)0; i < cnt; i++) {
        TbfpHandle_t* Node = TbfpGetNode(i);
        if(Node) {
            uint32_t diff = Node->silence_cnt - Node->silence_cnt_prev;
            if(0 < diff) {
                res = false;
#ifdef HAS_LOG
                LOG_PARN(HMON, "%s LackOfAck %u times", InterfaceToStr(Node->inter_face), diff);
#endif
            }
            Node->silence_cnt_prev = Node->silence_cnt;

            diff = Node->crc_err_cnt - Node->crc_err_cnt_prev;
            if(0 < diff) {
                res = false;
#ifdef HAS_LOG
                LOG_PARN(HMON, "%s CrcErr %u times", InterfaceToStr(Node->inter_face), diff);
#endif
            }
            Node->crc_err_cnt_prev = Node->crc_err_cnt;
#ifdef HAS_TBFP_FLOW_CONTROL
            diff = Node->Flow.torn_cnt - Node->Flow.torn_cnt_prev;
            if(0 < diff) {
                res = false;
#ifdef HAS_LOG
                LOG_PARN(HMON, "%s FlowTorn %u times", InterfaceToStr(Node->inter_face), diff);
#endif
            }
            Node->Flow.torn_cnt_prev = Node->Flow.torn_cnt;
#endif

            diff = Node->err_tx_cnt - Node->err_tx_cnt_prev;
            if(0 < diff) {
                res = false;
#ifdef HAS_LOG
                LOG_PARN(HMON, "IF:%s,TxErr:%u times", InterfaceToStr(Node->inter_face), diff);
#endif
            }
            Node->err_tx_cnt_prev = Node->err_tx_cnt;
        }
    }
    return res;
}
#endif


TbfpHandle_t* TbfpGetNodeByUart(uint8_t uart_num) {
    TbfpHandle_t* Node = NULL;
    uint32_t i = 0;
    for(i = 0; i < tbfp_get_cnt(); i++) {
        if(uart_num == TbfpInstance[i].uart_num) {
            if(TbfpInstance[i].valid) {
                Node = &TbfpInstance[i];
                break;
            }
            break;
        }
    }
    return Node;
}

#ifdef HAS_TBFP_EXT
bool tbfp_calc_byte_rate(void) {
    bool res = true;
    uint32_t cnt = tbfp_get_cnt();
    uint32_t i = 0;
    for(i = (Interfaces_t)0; i < cnt; i++) {
        TbfpHandle_t* Node = TbfpGetNode(i);
        if(Node) {
            DATA_UPDATE(Node->rx_rate, Node->rx_byte - Node->rx_byte_prev);
            // Node->rx_rate.cur = Node->rx_byte - Node->rx_byte_prev;
            // Node->rx_rate.min = MIN(Node->rx_rate.cur, Node->rx_rate.min);
            // Node->rx_rate.max = MAX(Node->rx_rate.cur, Node->rx_rate.max);
            Node->rx_byte_prev = Node->rx_byte;

            DATA_UPDATE(Node->tx_rate, Node->tx_byte - Node->tx_byte_prev);
            // Node->tx_rate.cur = Node->tx_byte - Node->tx_byte_prev;
            // Node->tx_rate.min = MIN(Node->tx_rate.cur, Node->tx_rate.min);
            // Node->tx_rate.max = MAX(Node->tx_rate.cur, Node->tx_rate.max);
            Node->tx_byte_prev = Node->tx_byte;
            res = true;
        }
    }
    return res;
}
#endif

#ifdef HAS_TBFP_EXT
bool wait_pong_loop_ms(uint32_t wait_timeout_ms, Interfaces_t inter_face) {
    bool res = false;
    TbfpHandle_t* Node = TbfpInterfaceToNode(inter_face);
    if(Node) {

#ifdef HAS_NORTOS
        uint32_t start_ms = 0U;
        uint32_t curr_ms = 0U;
        start_ms = time_get_ms32();
        bool loop = true;
        while(loop) {
#ifdef HAS_SUPER_CYCLE
            super_cycle_iteration();
#endif /*HAS_SUPER_CYCLE*/
            if(Node->rx_pong) {
                res = true;
                loop = false;
                break;
            }

            curr_ms = time_get_ms32();
            if(wait_timeout_ms < (curr_ms - start_ms)) {
                res = false;
                loop = false;
                break;
            }
        }
#endif /*HAS_NORTOS*/
    }
    return res;
}
#endif


/*
 * Load RAW bytes to FSM parser
 */
bool tbfp_rx(uint8_t* const arr, uint32_t size, Interfaces_t inter_face) {
    bool res = false;
    TbfpHandle_t* Node = TbfpInterfaceToNode(inter_face);
    uint32_t ok = 0;
#ifdef HAS_LOG
    LOG_PARN(TBFP, "Size:%u byte", size);
#endif
    if(Node) {
        uint32_t i = 0;
        for(i = 0; i < size; i++) {
#ifdef HAS_LOG
            LOG_PARN(TBFP, "[%u]=0x%02x", i, arr[i]);
#endif
            res = tbfp_proc_byte(Node, arr[i]);
            if(res) {
                ok++;
            }
        }
    }

    if(ok == size) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

#ifdef HAS_TBFP_EXT
bool tbfp_heartbeat_proc_one(uint32_t num) {
    bool res = false;
    TbfpHandle_t* Node = TbfpGetNode(num);
    if(Node) {
        if(Node->heartbeat) {
            res = tbfp_send_ping(FRAME_ID_PONG, Node->inter_face);
        }
    }
    return res;
}
#endif

bool tbfp_proc_one(uint32_t num) {
    bool res = false;
    TbfpHandle_t* Node = TbfpGetNode(num);
    if(Node) {
        res = true;
        uint32_t i = 0;
        for(i = 0; i < 512; i++) {
            char out_char = 0;
            res = fifo_pull(&Node->RxFifo, &out_char);
            if(res) {
                Node->rx_time_stamp_iteration = Node->iteration;
                res = tbfp_proc_byte(Node, (uint8_t)out_char);
            } else {
                break;
            }
        }

#ifdef HAS_TIME
        uint32_t up_time_ms = time_get_ms32();
        uint32_t diff_ms = up_time_ms - Node->rx_time_stamp_ms;
        if(TBFP_RX_TIME_OUT_MS < diff_ms) {
            Node->rx_time_stamp_ms = time_get_ms32();
            res = tbfp_parser_reset_rx(Node, Node->rx_state);
        }
#else
        uint32_t up_time_iteration = Node->iteration;
        uint32_t diff_iteration = 0;

        diff_iteration = up_time_iteration - Node->rx_time_stamp_iteration;
        if(TBFP_RX_TIME_OUT_ITER < diff_iteration) {
            //  Node->rx_time_stamp_iteration = Node->iteration;
            res = tbfp_parser_reset_rx(Node, Node->rx_state);
        }
#endif
        Node->iteration++;
    }
    return res;
}

bool tbfp_init_custom(void) {
    bool res = true;
    return res;
}

bool tbfp_init_common(const TbfpConfig_t* const Config, TbfpHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->inter_face = Config->inter_face;
            Node->heartbeat = Config->heartbeat;
            Node->fix_frame = Config->fix_frame;
            Node->tx_array_size = Config->tx_array_size;
            Node->TxFrame = Config->TxFrame;
            Node->rx_frame = Config->rx_frame;
            Node->uart_num = Config->uart_num;
            Node->RxArray = Config->RxArray;
            Node->rx_array_size = Config->rx_array_size;
            Node->crc_check_need = Config->crc_check_need;
            Node->preamble_val = Config->preamble_val;
            Node->num = Config->num;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

bool tbfp_init_one(uint32_t num) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(TBFP, "%u Init", num);
#endif
    const TbfpConfig_t* Config = TbfpGetConfig(num);
    if(Config) {
#ifdef HAS_LOG
        LOG_INFO(TBFP, "SpotConfig %u", num);
#endif
        TbfpHandle_t* Node = TbfpGetNode(num);
        if(Node) {
            res = tbfp_init_common(Config, Node);
#ifdef HAS_LOG
            LOG_INFO(TBFP, "SpotNode %u", num);
#endif

            Node->tx_sn = 0;
            Node->proc_done = false;
            res = tbfp_parser_init(Node, Config);
#ifdef HAS_TBFP_FLOW_CONTROL
            res = protocol_flow_init(&Node->Flow);
#endif /*HAS_TBFP_FLOW_CONTROL*/

#ifdef HAS_TBFP_DIAG
            Node->max_len = 0;
            Node->min_len = 0xFFFF;
#endif /*HAS_TBFP_DIAG*/
            res = fifo_init(&Node->RxFifo, (char*)Config->RxArray, (FifoIndex_t)Config->rx_array_size);
            Node->rx_pkt_cnt = 0;
            res = true;
#ifdef HAS_TBFP_RETX
            res = tbfp_retx_init(Node);
#endif
        } else {
#ifdef HAS_LOG
            LOG_ERROR(TBFP, "NodeErr %u", num);
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_PARN(TBFP, "NoConfig %u", num);
#endif
    }

    return res;
}

COMPONENT_INIT_PATTERT_CNT(TBFP, TBFP, tbfp, 1)

bool tbfp_proc(void) {
    bool res = true;
    uint32_t ok = 0;
    uint32_t num = 0;
    for(num = 0; num <= 1; num++) {
        res = tbfp_proc_one(num);
        if(res) {
            ok++;
        } else {
        }
    }
    if(ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

#ifdef HAS_TBFP_EXT
bool tbfp_heartbeat_proc(void) {
    bool res = true;
    uint32_t ok = 0;
    uint32_t num = 0;
    // uint32_t cnt = tbfp_get_cnt();
    for(num = 0; num <= 10; num++) {
        res = tbfp_heartbeat_proc_one(num);
        if(res) {
            ok++;
        } else {
        }
    }
    if(ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif
