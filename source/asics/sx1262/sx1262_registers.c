#include "sx1262_registers.h"

#include <stdlib.h>
#include <string.h>

#include "byte_utils.h"
#include "data_utils.h"
#include "sx1262_drv.h"
#include "spi_drv.h"
#include "none_blocking_pause.h"


#ifdef HAS_SX1262_DEBUG
const xSx1262Reg_t RegMap[] = {
   { 0x0385, "HoppingEnable"  },
   { 0x0386, "PacketLength"   },
   { 0x0387, "NbHoppingBlocks"},
   { 0x0388, "NbSymbols0"     },
   { 0x0389, "NbSymbols0"     },
   { 0x038A, "Freq0"          },
   { 0x038B, "Freq0"          },
   { 0x038C, "Freq0"          },
   { 0x0680, "TxBitBangA" },
   { 0x0587, "TxBitBangB" },
   { 0x038D, "Freq0"          },
   { 0x03E2, "NbSymbols15"    },
   { 0x03E3, "NbSymbols15"    },
   { 0x03E4, "Freq15"         },
   { 0x03E5, "Freq15"         },
   { 0x03E6, "Freq15"         },
   { 0x03E7, "Freq15"         },
   {0x08E2, "AnaLna"},
   {0x08E5, "DisMuxer"},
   {0x0749,"HeaderCodeRate"},
    {0x0580, "DIOxOutputEnable"},
    {0x0583, "DIOxInputEnable"},
    {0x0584, "DIOxPullUpControl"},
    {0x0585, "DIOxPullDownControl"},
    {0x06B8, "WhiteningInitValMSB"},
    {0x06B9, "WhiteningInitValLSB"},
    {0x06BC, "CRCMSBInitVal0"},
    {0x06BD, "CRCLSBInitVal1"},
    {0x06BE, "CRCMSBpolynomVal0"},
    {0x06BF, "CRCLSBpolynomVal1"},
    {SYNC_WORD_0, "SyncWord0"},
    {SYNC_WORD_1, "SyncWord1"},
    {SYNC_WORD_2, "SyncWord2"},
    {SYNC_WORD_3, "SyncWord3"},
    {SYNC_WORD_4, "SyncWord4"},
    {SYNC_WORD_5, "SyncWord5"},
    {SYNC_WORD_6, "SyncWord6"},
    {SYNC_WORD_7, "SyncWord7"},
    {REG_NODE_ADDR, "NodeAddr"},
    {REG_BROADCAST_ADDR, "BroadcastAddr"},
    {0x0736, "IQpolaritySetup"},
    {0x0740, "LoRaSyncWordMSB"},
    {0x0741, "LoRaSyncWordLSB"},
    {RAND_NUM_GEN_0, "RandNumGen0"},
    {RAND_NUM_GEN_1, "RandNumGen1"},
    {RAND_NUM_GEN_2, "RandNumGen2"},
    {RAND_NUM_GEN_3, "RandNumGen3"},
    {0x0889, "TxModulation"},
    {0x08AC, "RxGain"},
    {0x08D8, "TxClampConfig"},
    {0x08E7, "OCPConfig"},
    {0x0902, "RTCcontrol"},
    {0x0911, "XTAtrim"},
    {0x0912, "XTBtrim"},
    {0x0920, "DIO3outputVoltageControl"},
    {0x0944, "EventMask"},
};
#endif /*HAS_SX1262_DEBUG*/

uint32_t sx1262_get_reg_cnt(void){
    return ARRAY_SIZE(RegMap);
}

/*TODO: rewrite*/
#define READ_REG_HEADER_SZ 3
static bool sx1262_read_reg_proc(uint16_t reg_addr, uint8_t* reg_val) {
    bool res = false;
    if(NULL != reg_val) {
        res = true;
        *reg_val = 0xFF;
        uint8_t tx_array[4] = {0};
        memset(tx_array, 0x00, sizeof(tx_array));
        Type16Union_t temp_reg_val;
        temp_reg_val.u16 = 0;
        tx_array[0] = OPCODE_READ_REGISTER;
        uint16_t reg_addr_nbo = reverse_byte_order_uint16(reg_addr);
        memcpy(&tx_array[1], &reg_addr_nbo, sizeof(reg_addr_nbo));
        res = spi_write((SpiName_t)SX1262_SPI_NUM, tx_array, READ_REG_HEADER_SZ) && res;
        res = spi_read((SpiName_t)SX1262_SPI_NUM, (uint8_t*)&temp_reg_val.u16, sizeof(temp_reg_val.u16)) && res;
        temp_reg_val.u16 = reverse_byte_order_uint16(temp_reg_val.u16);
        *reg_val = temp_reg_val.u8[0];
    } else {
        res = false;
    }

    return res;
}

bool sx1262_read_reg(uint16_t reg_addr, uint8_t* reg_val) {
    bool res = false;
    SX1262_CHIP_SELECT(sx1262_read_reg_proc(reg_addr, reg_val));
    return res;
}

/*
  WriteRegister

  The command WriteRegister(...) allows writing a block of bytes in a data memory
  space starting at a specific address. The address is auto incremented after each
  data byte so that data is stored in contiguous memory locations. The SPI data
  transfer is described in the following table.
*/


#define WR_REG_PAYLOAD_SZ (3)
bool sx1262_write_reg(uint16_t reg_addr, uint8_t reg_val) {
    bool res = true;
    uint8_t tx_array[WR_REG_PAYLOAD_SZ];
    memset(tx_array, 0x00, sizeof(tx_array));
    uint16_t reg_addr_be = reverse_byte_order_uint16(reg_addr);
    memcpy(&tx_array[0], &reg_addr_be, sizeof(reg_addr_be));
    tx_array[2] = reg_val;
    res = sx1262_send_opcode(OPCODE_WRITE_REGISTER, tx_array, sizeof(tx_array), NULL, 0);
    return res;
}

bool sx1262_write_reg_lazy(uint16_t reg_addr, uint8_t reg_val) {
    bool res = false;
    uint8_t read_reg_val=0;
    res=sx1262_read_reg ( reg_addr, &read_reg_val);
    if(res){
        if(read_reg_val==reg_val){
            res = true;
        }else{
            res= sx1262_write_reg(reg_addr, reg_val);
        }
    }
    return res;
}


bool sx1262_set_tx_modulation(uint8_t tx_modulation){
    bool res = true;
    res= sx1262_write_reg(REG_TX_MODULATION ,  tx_modulation);
    return res;
}

bool sx1262_get_tx_modulation(uint8_t *tx_modulation){
    bool res = true;
    res = sx1262_read_reg(REG_TX_MODULATION , tx_modulation) ;
    return res;
}

bool sx1262_set_tx_clamp_config(uint8_t tx_clamp_config){
    bool res = true;
    res= sx1262_write_reg(REG_TX_CLAMP_CONFIG, tx_clamp_config);
    return res;
}

bool sx1262_get_tx_clamp_config(uint8_t *tx_clamp_config){
    bool res = true;
    res = sx1262_read_reg(REG_TX_CLAMP_CONFIG, tx_clamp_config) ;
    return res;
}

bool sx1262_get_rand(uint32_t* rand_num) {
    bool res = true;
    if(rand_num) {
        res = true;
        Type32Union_t var32bit = {0};
        res = sx1262_read_reg(RAND_NUM_GEN_0, &var32bit.u8[0]) && res;
        res = sx1262_read_reg(RAND_NUM_GEN_1, &var32bit.u8[1]) && res;
        res = sx1262_read_reg(RAND_NUM_GEN_2, &var32bit.u8[2]) && res;
        res = sx1262_read_reg(RAND_NUM_GEN_3, &var32bit.u8[3]) && res;
        *rand_num = var32bit.u32;
    } else {
        res = false;
    }
    return res;
}

bool sx1262_set_lora_sync_word(uint16_t sync_word) {
    bool res = true;
    Type16Union_t var16bit;
    var16bit.u16 = sync_word;
    var16bit.u16 = reverse_byte_order_uint16(var16bit.u16);
    res = sx1262_write_reg(LORA_SYNC_WORD_MSB, var16bit.u8[0]) && res;
    res = sx1262_write_reg(LORA_SYNC_WORD_LSB, var16bit.u8[1]) && res;
    return res;
}

bool sx1262_get_sync_word(uint64_t* sync_word) {
    bool res = true;
    if(sync_word) {
        res = true;
        Type64Union_t var64bit = {0};
        res = sx1262_read_reg(SYNC_WORD_0, &var64bit.u8[0]) && res;
        res = sx1262_read_reg(SYNC_WORD_1, &var64bit.u8[1]) && res;
        res = sx1262_read_reg(SYNC_WORD_2, &var64bit.u8[2]) && res;
        res = sx1262_read_reg(SYNC_WORD_3, &var64bit.u8[3]) && res;
        res = sx1262_read_reg(SYNC_WORD_4, &var64bit.u8[4]) && res;
        res = sx1262_read_reg(SYNC_WORD_5, &var64bit.u8[5]) && res;
        res = sx1262_read_reg(SYNC_WORD_6, &var64bit.u8[6]) && res;
        res = sx1262_read_reg(SYNC_WORD_7, &var64bit.u8[7]) && res;
        *sync_word = reverse_byte_order_uint64(var64bit.u64);
    } else {
        res = false;
    }
    return res;
}

bool sx1262_get_lora_sync_word(uint16_t* sync_word) {
    bool res = true;
    if(sync_word) {
        res = true;
        Type16Union_t var16bit = {0};
        res = sx1262_read_reg(LORA_SYNC_WORD_LSB, &var16bit.u8[1]) && res;
        res = sx1262_read_reg(LORA_SYNC_WORD_MSB, &var16bit.u8[0]) && res;

        *sync_word = reverse_byte_order_uint16(var16bit.u16);
    } else {
        res = false;
    }
    return res;
}



bool sx1262_set_sync_word(uint64_t sync_word) {
    bool res = true;
    Type64Union_t var64bit;
    var64bit.u64 = sync_word;
    var64bit.u64 = reverse_byte_order_uint64(var64bit.u64);
    res = sx1262_write_reg(SYNC_WORD_0, var64bit.u8[0]) && res;
    res = sx1262_write_reg(SYNC_WORD_1, var64bit.u8[1]) && res;
    res = sx1262_write_reg(SYNC_WORD_2, var64bit.u8[2]) && res;
    res = sx1262_write_reg(SYNC_WORD_3, var64bit.u8[3]) && res;
    res = sx1262_write_reg(SYNC_WORD_4, var64bit.u8[4]) && res;
    res = sx1262_write_reg(SYNC_WORD_5, var64bit.u8[5]) && res;
    res = sx1262_write_reg(SYNC_WORD_6, var64bit.u8[6]) && res;
    res = sx1262_write_reg(SYNC_WORD_7, var64bit.u8[7]) && res;
    return res;
}


bool sx1262_set_rx_gain(RxGain_t rx_gain){
    bool res = false;
    res = sx1262_write_reg_lazy(RX_GAIN, (uint8_t) rx_gain);
    return res;
}

bool sx1262_get_rx_gain(RxGain_t *rx_gain){
    bool res = false;
    if(rx_gain) {
        res = sx1262_read_reg(RX_GAIN,(uint8_t *) rx_gain);
    }
    return res;
}


bool sx1262_set_crc_poly(uint16_t polynomial){
    bool res = true;
    Type16Union_t var16bit;
    var16bit.u16 = polynomial;
    var16bit.u16 = reverse_byte_order_uint16(var16bit.u16);
    res = sx1262_write_reg(CRC_POLYNOMIAL_MSB, var16bit.u8[0]) && res;
    res = sx1262_write_reg(CRC_POLYNOMIAL_LSB, var16bit.u8[1]) && res;
    return res;
}

bool sx1262_set_crc_seed(uint16_t seed){
    bool res = true;
    Type16Union_t var16bit;
    var16bit.u16 = seed;
    var16bit.u16 = reverse_byte_order_uint16(var16bit.u16);
    res = sx1262_write_reg(CRC_INIT_MSB, var16bit.u8[0]) && res;
    res = sx1262_write_reg(CRC_INIT_LSB, var16bit.u8[1]) && res;
    return res;
}

bool sx1262_set_whitening_init_value(uint16_t value){
    bool res = true;
    Type16Union_t var16bit;
    var16bit.u16 = value;
    res = sx1262_write_reg(WHITENING_INITIAL_VALUE_LSB, var16bit.u8[0]) && res;
    res = sx1262_write_reg(WHITENING_INITIAL_VALUE_MSB, var16bit.u8[1]) && res;
    return res;
}

bool sx1262_get_whitening_init_value(uint16_t *value){
    bool res = false;
    if (value) {
        res = true;
        Type16Union_t var16bit = {0};
        res = sx1262_read_reg(WHITENING_INITIAL_VALUE_LSB, &var16bit.u8[0]) && res;
        res = sx1262_read_reg(WHITENING_INITIAL_VALUE_MSB, &var16bit.u8[1]) && res;
        *value = var16bit.u16;
    }
    return res;
}

bool sx1262_get_crc_poly(uint16_t *polynomial){
    bool res = false;
    if(polynomial) {
        res = true;
        Type16Union_t var16bit = {0};
        res = sx1262_read_reg(CRC_POLYNOMIAL_LSB, &var16bit.u8[0]) && res;
        res = sx1262_read_reg(CRC_POLYNOMIAL_MSB, &var16bit.u8[1]) && res;
        *polynomial = var16bit.u16;
    }
    return res;
}

bool sx1262_get_crc_seed(uint16_t *seed){
    bool res = false;
    if(seed){
        res = true;
        Type16Union_t var16bit = {0};
        res = sx1262_read_reg(CRC_INIT_LSB, &var16bit.u8[1]) && res;
        res = sx1262_read_reg(CRC_INIT_MSB, &var16bit.u8[0]) && res;

        *seed = reverse_byte_order_uint16(var16bit.u16);
    }
    return res;
}
