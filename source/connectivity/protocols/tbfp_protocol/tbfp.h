#ifndef TBFP_PROTOCOL_H
#define TBFP_PROTOCOL_H

/*TBFP Trivial Binary Frame Protocol*/
#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

#include "std_includes.h"
#include "system.h"
#include "tbfp_config.h"
#include "tbfp_types.h"

#ifdef HAS_TBFP_RE_TX
#include "tbfp_re_tx_ack_fsm.h"
#endif

#ifdef HAS_TBFP_DIAG
#include "tbfp_diag.h"
#endif


/*API*/
const TbfpConfig_t* TbfpGetConfig(uint8_t num);
TbfpHandle_t* TbfpGetNode(uint8_t num);
TbfpHandle_t* TbfpInterfaceToNode(const Interfaces_t inter_face);
TbfpHandle_t* TbfpGetNodeByUart(uint8_t uart_num);
bool tbfp_init_common(const TbfpConfig_t* const Config, TbfpHandle_t* const Node);


#ifdef HAS_TBFP_EXT
bool tbfp_heartbeat_proc(void);
bool tbfp_heartbeat_proc_one(uint32_t num);
#endif
bool tbfp_proc(void);
bool tbfp_proc_one(uint32_t num);
bool tbfp_proc_ping(uint8_t* ping_payload, uint16_t len, Interfaces_t inter_face) ;
bool tbfp_init_custom(void);
bool tbfp_init_one(uint32_t num);
bool tbfp_mcal_init(void);
bool tbfp_rx(uint8_t* const arr,
             uint32_t size,
             Interfaces_t inter_face);
bool tbfp_parser_init(TbfpHandle_t* Node, const TbfpConfig_t* Config);
bool tbfp_parser_reset_rx(TbfpHandle_t* Node, RxState_t state);

/*Tx API*/
bool tbfp_send_ack(uint16_t snum, Interfaces_t inter_face);
bool tbfp_send_text(uint8_t payload_id, uint8_t* tx_array, uint32_t len, Interfaces_t inter_face,
                           uint8_t lifetime, TbfpAck_t ack) ;

bool tbfp_send_payload(uint8_t* tx_array,
               uint32_t len,
               Interfaces_t inter_face,
               uint8_t lifetime,
               TbfpAck_t ack,
               TbfpPayloadId_t payload_id);
bool tbfp_send_frame(uint8_t num,  TbfpPayloadId_t payload_id, uint8_t* const payload,  uint16_t payload_size);
bool tbfp_compose_frame(const uint8_t* const payload, uint16_t payload_len ,
                        Interfaces_t inter_face,
                        TbfpPayloadId_t payload_id,
                        uint8_t* const buff,
                        uint32_t buff_len );

bool tbfp_compose_ping(uint8_t* out_frame, uint32_t* tx_frame_len,
                       TbfPingFrame_t* pingFrame, Interfaces_t inter_face);
bool tbfp_generate_frame(uint8_t* array, uint32_t len, Interfaces_t inter_face);
bool tbfp_send_chat(uint8_t* tx_array, uint32_t len, Interfaces_t inter_face, uint8_t lifetime, TbfpAck_t ack);
bool tbfp_send_cmd(uint8_t* tx_array, uint32_t len, Interfaces_t inter_face);
bool tbfp_send_ping(TbfpPayloadId_t payload_id, Interfaces_t inter_face);
bool tbfp_send_tunnel(uint8_t* tx_array, uint32_t len, Interfaces_t inter_face, TbfpAck_t ack);


/*Rx API*/
//bool tbfp_proc_full(uint8_t* const arr, uint16_t len, Interfaces_t inter_face);
IfRetx_t AckNeed2Retx(TbfpAck_t ack);
bool is_tbfp_protocol(uint8_t* arr, uint16_t len, Interfaces_t inter_face);
bool tbfp_proc_payload(TbfpHandle_t* Node, uint16_t len, TbfpPayloadId_t payload_id);
bool tbfp_calc_byte_rate(void);
bool tbfp_check(void);
bool tbfp_proc_xxx(uint8_t* arr, uint16_t len, Interfaces_t inter_face, bool is_reset);
bool tbfp_proc_byte(TbfpHandle_t* instance, uint8_t rx_byte);
bool wait_pong_loop_ms(uint32_t wait_pause_ms, Interfaces_t inter_face);

#ifdef __cplusplus
}
#endif

#endif /* TBFP_PROTOCOL_H */
