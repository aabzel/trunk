#ifndef SD_CARD_CRC_H
#define SD_CARD_CRC_H

#include <stdint.h>

void print_crc_table(void);

#if 0
void generate_crc7_table(void);
#endif

uint8_t calc_crc7(uint8_t const* const message, uint32_t length);

#endif /* SD_CARD_CRC_H */
