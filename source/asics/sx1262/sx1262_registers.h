#ifndef SX1262_REGISTERS_H
#define SX1262_REGISTERS_H

#include <stdbool.h>
#include <stdint.h>


#ifdef HAS_FREE_RTOS
#include <FreeRTOS.h>
#include <semphr.h>
#endif


#include "sx1262_constants.h"
#include "sx1262_types.h"

/* Register Table */
/* Regiser Name     Address*/
#define CRC_INIT_MSB 0x06BC
#define CRC_INIT_LSB 0x06BD
#define CRC_POLYNOMIAL_MSB 0x06BE
#define CRC_POLYNOMIAL_LSB 0x06BF

#define WHITENING_INITIAL_VALUE_MSB 0x06B8
#define WHITENING_INITIAL_VALUE_LSB 0x06B9

#define SYNC_WORD_0 0x06C0
#define SYNC_WORD_1 0x06C1
#define SYNC_WORD_2 0x06C2
#define SYNC_WORD_3 0x06C3
#define SYNC_WORD_4 0x06C4
#define SYNC_WORD_5 0x06C5
#define SYNC_WORD_6 0x06C6
#define SYNC_WORD_7 0x06C7

#define  REG_TX_MODULATION 0x0889
#define  REG_TX_CLAMP_CONFIG 0x08D8

#define RAND_NUM_GEN_0 0x0819
#define RAND_NUM_GEN_1 0x081A
#define RAND_NUM_GEN_2 0x081B
#define RAND_NUM_GEN_3 0x081C

#define LORA_SYNC_WORD_MSB 0x0740
#define LORA_SYNC_WORD_LSB 0x0741
#define RX_GAIN            0x08AC

#define REG_NODE_ADDR   0x06CD
#define REG_BROADCAST_ADDR 0x06CE

#define OCP_CONFIGURATION 0x08E7
#define XTB_TRIM 0x0912

#ifdef HAS_SX1262_DEBUG
extern const xSx1262Reg_t RegMap[];
#endif

bool sx1262_get_crc_poly(uint16_t *polynomial);
bool sx1262_get_crc_seed(uint16_t *seed);
bool sx1262_get_lora_sync_word(uint16_t* sync_word);
bool sx1262_get_rand(uint32_t* rand_num);
bool sx1262_get_rx_gain(RxGain_t *rx_gain);
bool sx1262_get_sync_word(uint64_t* sync_word);
bool sx1262_get_tx_clamp_config(uint8_t *tx_clamp_config);
bool sx1262_get_tx_modulation(uint8_t *tx_modulation);
bool sx1262_get_whitening_init_value(uint16_t *value);
bool sx1262_read_reg(uint16_t reg_addr, uint8_t* reg_val);
bool sx1262_set_crc_poly(uint16_t polynomial);
bool sx1262_set_crc_seed(uint16_t seed);
bool sx1262_set_lora_sync_word(uint16_t sync_word);
bool sx1262_set_rx_gain(RxGain_t rx_gain);
bool sx1262_set_sync_word(uint64_t sync_word) ;
bool sx1262_set_tx_clamp_config(uint8_t tx_clamp_config);
bool sx1262_set_tx_modulation(uint8_t tx_modulation);
bool sx1262_set_whitening_init_value(uint16_t value);
bool sx1262_write_reg(uint16_t reg_addr, uint8_t reg_val);
bool sx1262_write_reg_lazy(uint16_t reg_addr, uint8_t reg_val);
uint32_t sx1262_get_reg_cnt(void);


#endif /* SX1262_REGISTERS_H  */
