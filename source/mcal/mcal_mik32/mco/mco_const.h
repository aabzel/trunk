#ifndef MCO_CONST_H
#define MCO_CONST_H

typedef enum {
    MCO_1 = 1,
    MCO_2 = 2,

    MCO_UNDEF = 0,
} McoChannel_t;

typedef enum {
    FREQ_SRC_LSE = 1,
    FREQ_SRC_HSE = 2,
    FREQ_SRC_HSI = 3,
    FREQ_SRC_PLL = 4,

    FREQ_SRC_UNDEF = 0,
} FrequencySource_t;

#endif /* MCO_CONST_H  */
