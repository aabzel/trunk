#include "test_parse_sd_card_regs.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse_sd_card_regs.h"
#include "sd_card_bits_offsets.h"
#include "str_ops.h"
#include "uTests.h"
#include "utils.h"

bool test_parse_reg_sd_card(void) {
  printf("\n\n\n%s()", __FUNCTION__);
  init_reg_map();
  int16_t ind = get_reg_ind(REG_OCR);
  EXPECT_EQ((int16_t)5, ind); // 1
  uint8_t reg = 0;
  reg = SdCardRegMap[get_reg_ind(REG_OCR)].reg8BitAddr;
  EXPECT_EQ((uint8_t)REG_OCR, reg);
  reg = SdCardRegMap[get_reg_ind(REG_CID)].reg8BitAddr;
  EXPECT_EQ((uint8_t)REG_CID, reg);
  return true;
}
