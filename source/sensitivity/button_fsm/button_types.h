#ifndef BUTTON_FSM_TYPES_H
#define BUTTON_FSM_TYPES_H

#include "std_includes.h"

#include "button_const.h"
#include "gpio_types.h"

typedef bool (*ButtonIsrHandler_t)(void);

#define BUTTON_COMMON_VARIABLES                \
    uint32_t num;                              \
    uint32_t debug_led_num;                    \
    bool valid;                                \
    Pad_t pad;                                 \
    GpioLogicLevel_t active;                                \
    ButtonIsrHandler_t proc_handler;  /*for backlight*/     \
    ButtonIsrHandler_t press_short_handler;    \
    ButtonIsrHandler_t press_long_handler;


#define BUTTON_NAME_SIZE 20
typedef struct {
    BUTTON_COMMON_VARIABLES
    char name[BUTTON_NAME_SIZE];
} ButtonConfig_t;

typedef struct {
    bool init;
    bool long_pressed;
    uint32_t time_ms;
    ButtonState_t state;
    ButtonInput_t input;
    ButtonState_t prev_state;
    uint32_t short_pres_cnt;
    uint32_t long_pres_cnt;
    uint32_t un_pres_cnt;
    uint32_t err_cnt;
    uint32_t handler_cnt;
    BUTTON_COMMON_VARIABLES
} ButtonHandle_t;

typedef bool (*ButtonActionHandler_t)(ButtonHandle_t* const Node);

#endif /* BUTTON_FSM_TYPES_H  */
