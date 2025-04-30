#ifndef CROSS_DETECT_TYPES_H
#define CROSS_DETECT_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "cross_detect_const.h"
#include "gpio_types.h"

#if 0
typedef struct {
    Pad_t left;
    Pad_t right;
} PadPair_t;
#endif

typedef struct {
    uint16_t a;
    uint16_t b;
    uint16_t max;
} U16Pair_t;

typedef union {
    uint8_t fault_code;
    struct {
        uint8_t cross : 1;           /**/
        uint8_t left_short_gnd : 1;  /**/
        uint8_t left_short_vcc : 1;  /**/
        uint8_t right_short_gnd : 1; /**/
        uint8_t right_short_vcc : 1; /**/
        uint8_t res : 3;             /**/
    };
} CrossDetectFault_t;

#define CROSS_DETECT_PIN_COMMON_VARIABLES                                                                              \
    uint16_t num;                                                                                                      \
    uint16_t pin_num;                                                                                                  \
    bool valid;

typedef struct {
    CROSS_DETECT_PIN_COMMON_VARIABLES
    Pad_t pad;
} CrossDetectPinConfig_t;

typedef struct {
    // PadPair_t pair;
    CrossDetectFault_t Fault;
    CrossDetectFault_t FaultPrev;
    // CrossDetectStateMeasure_t measurements[9];
    uint32_t update_cnt;
} CrossDetectResult_t;

typedef struct {
    CrossDetectState_t state;
    CrossDetectGpioRead_t read;
} CrossDetectStateMeasure_t;

typedef struct {
    Pad_t left;
    Pad_t right;
    CrossDetectState_t state;
    CrossDetectSolution_t solution;
    // CrossDetectSolution_t prev_solution;
    uint32_t spin_cnt;
    uint32_t err_cnt;
    uint32_t time_start;
    uint32_t pause_ms;
    uint32_t fault_cnt;
    bool init;
    CrossDetectFault_t Fault;
    CrossDetectStateMeasure_t measurements[9];
} CrossDetectPairInfo_t;

#define CROSS_DETECT_COMMON_VARIABLES                                                                                  \
    uint8_t num;                                                                                                       \
    bool valid;

typedef struct {
    CROSS_DETECT_COMMON_VARIABLES
    char* name;
} CrossDetectConfig_t;

typedef struct {
    uint32_t transient_ms;
} CrossDetectGlobalConfig_t;

typedef struct {
    CROSS_DETECT_COMMON_VARIABLES
    CrossDetectPairInfo_t pair;
    bool init;
    uint16_t left_num;
    uint16_t right_num;
    bool on;
    uint16_t pair_cnt;
    uint32_t start_ms;
} CrossDetectHandle_t;

typedef bool (*CrossDetectHandler_t)(CrossDetectHandle_t* const Node);

/*Structure for LookUpTable*/
typedef struct {
    CrossDetectState_t state_new;
    GpioPullMode_t pull_left;
    GpioPullMode_t pull_right;
    CrossDetectHandler_t action;
} CrossDetectStateInfo_t;

typedef struct {
    CrossDetectState_t state;
    CrossDetectGpioRead_t read;
    ConfidenceLevel_t left_short_gnd;
    ConfidenceLevel_t left_short_vcc;
    ConfidenceLevel_t right_short_gnd;
    ConfidenceLevel_t right_short_vcc;
    ConfidenceLevel_t cross;
    ConfidenceLevel_t open;
    ConfidenceLevel_t error;
    ConfidenceLevel_t ok;
} CrossDetectSolutionInfo_t;

#endif /* CROSS_DETECT_TYPES_H  */
