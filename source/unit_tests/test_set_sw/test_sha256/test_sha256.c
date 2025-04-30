#include "test_sha256.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//#include "custom_type.h"
#include "log.h"
#include "sha256.h"

// "hello"
unsigned char hello_hashed[] = {0x2c, 0xf2, 0x4d, 0xba, 0x5f, 0xb0, 0xa3, 0x0e, 0x26, 0xe8, 0x3b,
                                0x2a, 0xc5, 0xb9, 0xe2, 0x9e, 0x1b, 0x16, 0x1e, 0x5c, 0x1f, 0xa7,
                                0x42, 0x5e, 0x73, 0x04, 0x33, 0x62, 0x93, 0x8b, 0x98, 0x24};

// ""
unsigned char empty_hashed[] = {0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14, 0x9a, 0xfb, 0xf4,
                                0xc8, 0x99, 0x6f, 0xb9, 0x24, 0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b,
                                0x93, 0x4c, 0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55};

bool test_sha256(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    int cmpres;
    unsigned char out_buf[32] = {0};

    sha256_hash(out_buf, (unsigned char*)"hello", 5);

    cmpres = memcmp(out_buf, hello_hashed, 32);
    if(0 != cmpres) {
        return false;
    }
    LOG_INFO(TEST, "should hash correctly");

    sha256_hash(out_buf, (unsigned char*)"", 0);

    cmpres = memcmp(out_buf, empty_hashed, 32);
    LOG_INFO(TEST, "empty should hash correctly");
    if(0 != cmpres) {
        return false;
    }

    return true;
}
