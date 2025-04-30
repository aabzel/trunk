#ifndef TEST_SD_CARD_H
#define TEST_SD_CARD_H

#include <stdbool.h>
#include <stdint.h>

#include "test_sd_card_crc.h"

bool test_sd_card_write_read(void);
bool test_sd_card_read(void);
bool test_sd_card_gpio(void);
bool test_sd_card_write(void);
bool test_sd_card_init(void);
bool test_sd_card_types(void);
bool test_sd_card_frame(void);

#define TEST_SUIT_SD_CARD  TEST_SUIT_SD_CARD_CRC \
        {"sd_card_types", test_sd_card_types}, \
        {"sd_card_gpio", test_sd_card_gpio}, \
        {"sd_card_frame", test_sd_card_frame}, \
        {"sd_card_read", test_sd_card_read}, \
        {"sd_card_write", test_sd_card_write}, \
        {"sd_card_write_read", test_sd_card_write_read}, \
        {"sd_card_init", test_sd_card_init},


#endif /* TEST_SD_CARD_H */
