#include "led_diag.h"

#include "data_utils.h"
#include "gpio_diag.h"
#include "table_utils.h"
#include "writer_config.h"
#ifdef HAS_LED_MONO
#include "led_mono_drv.h"
#endif

const char* LedMode2Str(LedMode_t mode) {
    const char* name = "?";
    switch((uint8_t)mode) {
    case LED_MODE_NONE:
        name = "None";
        break;
    case LED_MODE_PWM:
        name = "PWM";
        break;
    case LED_MODE_ON:
        name = "On";
        break;
    case LED_MODE_OFF:
        name = "Off";
        break;
    case LED_MODE_BLINK:
        name = "Blink";
        break;
    }
    return name;
}

static const table_col_t cols[] = {{6, "pad"}, {7, "mode"}, {6, "period"}, {5, "duty"}, {6, "phase"}, {7, "name"}};

bool LedTableHeaderPrint(void) {
    bool res = true;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
bool LedTableTailPrint(void) {
    bool res = true;
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

const char* Color2Str(Color_t color) {
    const char* name = "?";
    switch((uint32_t)color) {
    case COLOR_BLACK:
        name = "Black";
        break;
    case COLOR_RED:
        name = "Red";
        break;
    case COLOR_YELLOW:
        name = "Yellow";
        break;
    case COLOR_GREEN:
        name = "Green";
        break;
    case COLOR_BLUE:
        name = "Blue";
        break;
    case COLOR_CYANIC:
        name = "Cyanic";
        break;
    case COLOR_PURPLE:
        name = "Purpul";
        break;
    case COLOR_WHITE:
        name = "White";
        break;
    }
    return name;
}
