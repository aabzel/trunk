#include "sd_card_crc16.h"

// Calculate CRC16 CCITT
/* It's a 16 bit CRC with polynomial x^16 + x^12 + x^5 + 1 */
// input:
//   crc16 - the CRC before (0 for rist step)
//   data - byte for CRC calculation
// return: the CRC16 value

static uint16_t calc_crc16_one(uint16_t crc16, uint8_t data) {
  crc16 = (uint8_t)(crc16 >> 8) | (crc16 << 8);
  crc16 ^= data;
  crc16 ^= (uint8_t)(crc16 & 0xff) >> 4;
  crc16 ^= (crc16 << 8) << 4;
  crc16 ^= ((crc16 & 0xff) << 4) << 1;

  return crc16;
}

uint16_t calc_crc16(const uint8_t *message, uint16_t len) {
  uint16_t crc16 = 0;

  while (len--) {
    crc16 = calc_crc16_one(crc16, *(message++));
  }

  return crc16;
}
