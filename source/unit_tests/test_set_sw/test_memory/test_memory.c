#include "test_memory.h"

#include <stdlib.h>

#include "sys_config.h"
#include "unit_test_check.h"

static double byte2Mbyte(double byte) {
    double mByte = byte / (1024.0f * 1024.0f);
    return mByte;
}

/*Long test*/
bool test_heap(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    bool res = false;
    uint32_t byte = 3;
    uint32_t mult = 3;
    uint32_t div = 2;
    uint8_t patt = 0x00;
    while(1) {
        char* ptr = NULL;
        if(byte < RAM_SIZE) {
            ptr = (char*)malloc(byte);
            if(ptr) {
                LOG_INFO(SYS, "can malloc %u bytes %u kBytes %f MBytes Ok", byte, byte / 1024, byte2Mbyte(byte));
                memset(ptr, patt, byte);
                byte = (byte * mult) / div;
                res = true;
                // print_bytes (byte);
                free(ptr);
            } else {
                break;
            }
        } else {
            LOG_WARNING(SYS,
                        "NoMoreRam Try:%u kBytes"
                        "          Max:%u kBytes",
                        byte / 1024, RAM_SIZE);
            break;
        }
        patt++;
    }
    /* PC:  2,094,737,251 byte */
    LOG_INFO(SYS, "can malloc %u bytes %u kBytes %f MBytes", byte, byte / 1024, byte2Mbyte(byte));
    /* MCU: can malloc 46875 bytes 45,77 kBytes */
    /*        can malloc 1875 bytes 1 kBytes IAR*/
    return res;
}

bool test_malloc_zero(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = false;
    char* ptr = malloc(0);
#ifdef HAS_MICROCONTROLLER
    ASSERT_EQ_CONST(NULL, ptr);
#endif

#ifdef HAS_X86
    ASSERT_NE(NULL, ptr);
    free(ptr);
#endif
    return res;
}
