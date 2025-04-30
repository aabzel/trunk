#include "test_fifo_char.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "fifo_char.h"
#include "unit_test_check.h"

#define STRING19 "123456789"

bool test_fifo_2(void) {
#ifdef X86_64
    printf("\n%s():", __FUNCTION__);
#endif
    FifoChar_t FifiObj;
    char FiFoHeap[6] = "";
    ASSERT_TRUE(fifo_init(&FifiObj, FiFoHeap, sizeof(FiFoHeap)));
    ASSERT_EQ(0, fifo_get_count(&FifiObj));

    return true;
}

bool test_fifo_char_array_overrun(void) {
#ifdef X86_64
    printf("\n%s():", __FUNCTION__);
#endif
    FifoChar_t FifiObj;
    char peek_ch = '0';
    char FiFoHeap[6] = "";
    fifo_init(&FifiObj, FiFoHeap, sizeof(FiFoHeap));
    ASSERT_FALSE(fifo_push_array(&FifiObj, STRING19, strlen(STRING19)));

    ASSERT_TRUE(fifo_peek(&FifiObj, &peek_ch));
    ASSERT_EQ('1', peek_ch);

    uint16_t outLen = 0;
    char outArray[100] = "";
    ASSERT_TRUE(fifo_pull_array(&FifiObj, outArray, sizeof(outArray), &outLen));
    ASSERT_EQ(6, outLen);
    ASSERT_STREQ("123456", outArray);
    return true;
}

bool test_fifo_char_array(void) {
#ifdef X86_64
    printf("\n%s():", __FUNCTION__);
#endif
    FifoChar_t FifiObj;
    char FiFoHeap[10] = "";
    char outArray[100] = "";
    char peek_ch = '0';
    uint16_t outLen = 0;
    ASSERT_TRUE(fifo_init(&FifiObj, FiFoHeap, sizeof(FiFoHeap)));

    ASSERT_TRUE(fifo_push_array(&FifiObj, "12345", 5));

    ASSERT_TRUE(fifo_peek(&FifiObj, &peek_ch));
    ASSERT_EQ('1', peek_ch);

    ASSERT_TRUE(fifo_pull_array(&FifiObj, outArray, sizeof(outArray), &outLen));

    ASSERT_EQ(5, outLen);

    ASSERT_STREQ("12345", outArray);

    return true;
}

bool test_fifo_char_overrun(void) {
#ifdef X86_64
    printf("\n%s():", __FUNCTION__);
#endif
    FifoChar_t FifiObj;
    char FiFoHeap[5] = "";

    char outChar = '0';
    char peek_ch = '0';
    fifo_init(&FifiObj, FiFoHeap, sizeof(FiFoHeap));

    ASSERT_TRUE(fifo_push(&FifiObj, '1'));
    ASSERT_TRUE(fifo_peek(&FifiObj, &peek_ch));
    ASSERT_EQ('1', peek_ch);
    ASSERT_TRUE(fifo_push(&FifiObj, '2'));
    ASSERT_TRUE(fifo_peek(&FifiObj, &peek_ch));
    ASSERT_EQ('1', peek_ch);
    ASSERT_TRUE(fifo_push(&FifiObj, '3'));
    ASSERT_TRUE(fifo_peek(&FifiObj, &peek_ch));
    ASSERT_EQ('1', peek_ch);
    ASSERT_TRUE(fifo_push(&FifiObj, '4'));
    ASSERT_TRUE(fifo_peek(&FifiObj, &peek_ch));
    ASSERT_EQ('1', peek_ch);
    ASSERT_TRUE(fifo_push(&FifiObj, '5'));
    ASSERT_TRUE(fifo_peek(&FifiObj, &peek_ch));
    ASSERT_FALSE(fifo_push(&FifiObj, '6'));

    ASSERT_TRUE(fifo_peek(&FifiObj, &peek_ch));
    ASSERT_EQ('1', peek_ch);
    ASSERT_TRUE(fifo_pull(&FifiObj, &outChar));
    ASSERT_EQ('1', outChar);

    ASSERT_TRUE(fifo_peek(&FifiObj, &peek_ch));
    ASSERT_EQ('2', peek_ch);
    ASSERT_TRUE(fifo_pull(&FifiObj, &outChar));
    ASSERT_EQ('2', outChar);

    ASSERT_TRUE(fifo_peek(&FifiObj, &peek_ch));
    ASSERT_EQ('3', peek_ch);
    ASSERT_TRUE(fifo_pull(&FifiObj, &outChar));
    ASSERT_EQ('3', outChar);

    ASSERT_TRUE(fifo_peek(&FifiObj, &peek_ch));
    ASSERT_EQ('4', peek_ch);
    ASSERT_TRUE(fifo_pull(&FifiObj, &outChar));
    ASSERT_EQ('4', outChar);

    ASSERT_TRUE(fifo_peek(&FifiObj, &peek_ch));
    ASSERT_EQ('5', peek_ch);
    ASSERT_TRUE(fifo_pull(&FifiObj, &outChar));
    ASSERT_EQ('5', outChar);

    ASSERT_FALSE(fifo_pull(&FifiObj, &outChar));

    return true;
}
