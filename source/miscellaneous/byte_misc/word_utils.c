#include "word_utils.h"

#include <string.h>

uint16_t copy_and_rev16(const uint8_t* const array) {
    uint16_t value16b = 0;
    memcpy(&value16b, array, 2);
    value16b = reverse_byte_order_uint16(value16b);
    return value16b;
}



uint16_t reverse_byte_order_uint16(const uint16_t in2byteVal) {
    uint16_t swapped = 0;
    swapped = (in2byteVal >> 8) | (in2byteVal << 8);
    return swapped;
}

bool insert_big_endian_word(const uint16_t word, uint8_t* const array ) {
    bool res = false;
    if(array) {
        uint16_t word_be = reverse_byte_order_uint16(word);
        memcpy(array,&word_be,2);
        res = true;
    }
    return res;
}
