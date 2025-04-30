#ifndef SD_CARD_CRC16_H
#define SD_CARD_CRC16_H

#include <stdint.h>

uint16_t calc_crc16(const uint8_t *message, uint16_t len);

#endif /* SD_CARD_CRC16_H */
