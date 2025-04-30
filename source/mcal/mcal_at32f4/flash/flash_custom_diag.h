#ifndef FLASH_CUSTOM_DIAG_H
#define FLASH_CUSTOM_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "flash_const.h"
#include "flash_diag.h"
#include "artery_at32f4xx.h"

bool flash_raw_reg_diag(void);
bool flash_parse_sr(uint32_t reg_val);
bool flash_parse_acr(uint32_t reg_val);
bool diag_flash_usage(char* keyWord1, char* keyWord2);
bool diag_flash_prot(char* key_word1, char* key_word2);
const char* FlashStatusToStr(flash_status_type code);

#endif /* FLASH_CUSTOM_DIAG_H  */
