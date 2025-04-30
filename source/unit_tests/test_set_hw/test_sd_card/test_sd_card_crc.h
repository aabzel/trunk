#ifndef TEST_SD_CARD_CRC_H
#define TEST_SD_CARD_CRC_H

#include <stdbool.h>


bool test_crc16(void);
bool test_crc7(void);


#define TEST_SUIT_SD_CARD_CRC  \
    {"sd_card_crc16", test_crc16}, \
    {"sd_card_crc7", test_crc7},



#endif /* TEST_SD_CARD_CRC_H */
