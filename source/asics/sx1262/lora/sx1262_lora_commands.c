#include "sx1262_lora_commands.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "bit_utils.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "gpio_mcal.h"
#include "cli_utils.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "spi_drv.h"
#include "str_utils.h"
#include "sx1262_diag.h"
#include "sx1262_drv.h"
#include "system_diag.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_SX1262_EX_DEBUG
bool sx1262_set_packet_param_command(int32_t argc, char* argv[]) {
    bool res = false;
    PacketParam_t packetParam;
    packetParam.packet_type = PACKET_TYPE_LORA;
    packetParam.proto.lora.preamble_length = 8;
    packetParam.proto.lora.header_type = LORA_VAR_LEN_PACT;
    packetParam.proto.lora.payload_length = 255;
    packetParam.proto.lora.crc_type = LORA_CRC_ON;
    packetParam.proto.lora.invert_iq = IQ_SETUP_STANDARD;
    if(0 == argc) {
        res = true;
        packetParam.packet_type = PACKET_TYPE_LORA;
        packetParam.proto.lora.preamble_length = 8;
        packetParam.proto.lora.header_type = LORA_VAR_LEN_PACT;
        packetParam.proto.lora.payload_length = 255;
        packetParam.proto.lora.crc_type = LORA_CRC_ON;
        packetParam.proto.lora.invert_iq = IQ_SETUP_STANDARD;
    }

    if(0 < argc) {
        LOG_ERROR(LORA, "Usage: sxpp preamble_length header_type payload_length crc_type invert_iq");
    }
    if(res) {
        res = sx1262_set_packet_params(&packetParam);
        if(res) {
            LOG_INFO(LORA, "Set packet param OK");
        } else {
            LOG_ERROR(LORA, "Set packet param error");
        }
    }
    return res;
}
#endif

bool sx1262_set_modulation_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t modulation_number = 0;
    if(1 == argc) {
        res = try_str2uint16(argv[0], &modulation_number);
        if(false == res) {
            LOG_ERROR(LORA, "ParseErr %s", argv[0]);
        }
        res = true;
    } else {
        LOG_ERROR(LORA, "Usage: sxl mod_num");
    }
    if(res) {
        res = false;
#ifdef HAS_PARAM
        res = sx1262_set_modulation(modulation_number);
#endif
    }
    return res;
}


bool sx1262_set_lora_sync_word_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t lora_sync_word = 0;
    if(1 == argc) {
        res = try_str2uint16(argv[0], &lora_sync_word);
        if(false == res) {
            LOG_ERROR(LORA, "ParseLoraSyncWordErr %s", argv[0]);
        }
    } else {
        LOG_ERROR(LORA, "Usage: sxslsw sync_word16bit");
    }
    if(res) {
        res = sx1262_set_lora_sync_word(lora_sync_word);
        if(res) {
            LOG_INFO(LORA, "SetLoRaSyncWordOk");
        } else {
            LOG_ERROR(LORA, "SetLoRaSyncWordErr");
        }
    }
    return res;
}

#ifdef HAS_SX1262_EX_DEBUG
bool sx1262_set_cad_params_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t cad_det_peak =0;
    uint8_t cad_det_min = 0;
    CadExtMode_t cad_exit_mode= CAD_RX;
	CadNunSym_t cad_symbol_num;
    uint32_t cad_timeout = 0;
	if(1<=argc){
        res = try_str2uint8(argv[0],(uint8_t*) &cad_symbol_num);
        if(false == res) {
            LOG_ERROR(LORA, "SymbolNumErr %s", argv[0]);
        }
    }
    if(2<=argc){
        res = try_str2uint8(argv[1], &cad_det_peak);
        if(false == res) {
            LOG_ERROR(LORA, "CadDetPeakErr %s", argv[1]);
        }
    }
    if(3<=argc){
        res = try_str2uint8(argv[2], &cad_det_min);
        if(false == res) {
            LOG_ERROR(LORA, "CadDetMinErr %s", argv[2]);
        }
    }
    if(4<=argc){
        res = try_str2uint8(argv[3], (uint8_t*) &cad_exit_mode);
        if(false == res) {
            LOG_ERROR(LORA, "ExitModeErr %s", argv[3]);
        }
    }
    if(5<=argc){
        res = try_str2uint32(argv[4], &cad_timeout);
        if(false == res) {
            LOG_ERROR(LORA, "TimeOutErr %s", argv[4]);
        }
    }

    if(res){
        res= sx1262_set_cad_params(cad_symbol_num,
                           cad_det_peak,
                           cad_det_min,
                           cad_exit_mode, 
                           cad_timeout
                              ); 
    } else {
        LOG_ERROR(SX1262, "Usage: sxcp SymbolNum DetPeak DetMin ExitMode Timeout");
    }
    return res;
}
#endif /*HAS_SX1262_EX_DEBUG*/

#ifdef HAS_SX1262_EX_DEBUG
bool sx1262_set_cad_command(int32_t argc, char* argv[]){
    bool res = false;

    if(0 == argc) {
        res = sx1262_set_cad();
        if(res){
            LOG_INFO(SX1262, "CAD Ok!");
        }
    } else {
        LOG_ERROR(SX1262, "Usage: sxa");
    }
    return res;
}
#endif /*HAS_SX1262_EX_DEBUG*/
