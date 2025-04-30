#include "test_sd_card_crc.h"

#include "sd_card_crc.h"
#include "sd_card_crc16.h"
#include "unit_test_check.h"

bool test_crc16(void) {
  LOG_INFO(TEST,"%s()", __FUNCTION__);

  uint16_t crc16;
  uint8_t message[512] = {0xFF};
  memset(message, 0xFF, sizeof(message));
  crc16 = calc_crc16(message, sizeof(message));
  ASSERT_EQ((uint16_t)0x7FA1, crc16);

  return true;
}

bool test_crc7(void) {
	  LOG_INFO(TEST,"%s()", __FUNCTION__);
  uint8_t crc;
  uint8_t message40[] = {0x40, 0x00, 0x00, 0x00, 0x00};
  crc = calc_crc7(message40, sizeof(message40));
  ASSERT_EQ(0x4A, crc);

  uint8_t message51[] = {0x51, 0x00, 0x00, 0x00, 0x00};
  crc = calc_crc7(message51, sizeof(message51));
  ASSERT_EQ(0x2A, crc);

  uint8_t message11[] = {0x11, 0x00, 0x00, 0x09, 0x00};
  crc = calc_crc7(message11, sizeof(message11));
  ASSERT_EQ(0x33, crc);

  return true;
}

