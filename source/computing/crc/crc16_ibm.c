#include "crc16_ibm.h"

// CRC-16-IBM with polynomial 0x8005, initial value 0x4F4E
uint16_t crc16_ibm_calc(const uint8_t* const data, const uint32_t len) {
    uint16_t crc = 0x4F4E; // Initial value as per datasheet page 31
    uint16_t polynomial = 0x8005;

    for(uint32_t i = 0; i < len; i++) {
        crc ^= (uint16_t)data[i] << 8;
        for(int bit = 0; bit < 8; bit++) {
            if(crc & 0x8000) {
                crc = (crc << 1) ^ polynomial;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}
