#ifndef PARSE_SD_CARD_REGS_H
#define PARSE_SD_CARD_REGS_H

#include "custom_type.h"
#include "parse_regs.h"
#include "sd_card_bits_offsets.h"

#include <stdio.h>

typedef union {
    uint32_t reg_32_bit_val;
    uint16_t reg_16_bit_val[2];
    uint8_t reg_8_bit_val[4];
    uint8_t *reg_array_ptr;
} RegData_t;

typedef struct  {
  uint8_t reg8BitAddr;
  // uint32_t reg_32_bit_val;
  RegData_t reg_data;
  bool valid;
  // uint8_t *reg_array_ptr;
  uint32_t reg_bitness;
  uint32_t reg_array_len;
  char *regName;
} SdReg32bit_t;

extern SdReg32bit_t SdCardRegMap[NUM_OF_REGISTERS + 1];

extern uint8_t procRegCnd;

bool init_reg_map(void);
int16_t get_reg_ind(uint8_t reg_addr);
bool parse_sd_card_regs_file(char *inFileName, char *outFileName);
// bool parse_sd_card_reg (uint8_t regAddr, FILE *outFilePrt);
// bool load_sd_card_reg (uint8_t regAddr, uint32_t regVal);

#endif /* PARSE_SD_CARD_REGS_H */
