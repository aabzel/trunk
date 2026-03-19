#include "input_capture_diag.h"

#include <stdio.h>
#include <string.h>

#include "gpio_diag.h"
#include "input_capture_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "num_to_str.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

static const char* InputCaptureEdgeToStr(InputCapturePolarity_t polarity) {
    char* name = "?";
    switch((uint32_t)polarity) {
    case INPUT_CAPTURE_EDGE_FALING:
        name = "Fall";
        break;
    case INPUT_CAPTURE_EDGE_RISING:
        name = "Rise";
        break;
    case INPUT_CAPTURE_EDGE_BOTH:
        name = "Both";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* InputCaptureConfigToStr(const InputCaptureConfig_t* const Config) {
    static char text[80] = "";
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sEn:%u,", text, Config->on);
        snprintf(text, sizeof(text), "%sTim:%u,", text, Config->timer_num);
        snprintf(text, sizeof(text), "%sCh:%u,", text, Config->channel);
        snprintf(text, sizeof(text), "%sPol:%s,", text, InputCaptureEdgeToStr(Config->polarity));
        snprintf(text, sizeof(text), "%sPad:%s,", text, GpioPadToStr(Config->Pad));
    }
    return text;
}

bool InputCaptureDiagConfig(const InputCaptureConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(INPUT_CAPTURE, "%s", InputCaptureConfigToStr(Config));
        res = true;
    }
    return res;
}

bool input_capture_diag(char* key_word1, char* key_word2) {
    bool res = false;
    uint16_t cnt = 0;
    uint32_t qnt = input_capture_get_cnt();
    char temp_str[120] = {0};
    static const table_col_t cols[] = {{4, "No"}, {8, "Cnt"}, {5, "Tim"}, {7, "CH"}, {6, "Pad"}, {10, "name"}};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint16_t num = 0;
    for(num = 1; num <= qnt; num++) {
        const InputCaptureConfig_t* Config = InputCaptureGetConfig(num);
        if(Config) {

            InputCaptureHandle_t* Node = InputCaptureGetNode(num);
            if(Node) {

                uint32_t counter = 0;
                res = input_capture_counter_get(num, &counter);

                strcpy(temp_str, TSEP);
                snprintf(temp_str, sizeof(temp_str), "%s %02u " TSEP, temp_str, num);
                snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, counter);
                snprintf(temp_str, sizeof(temp_str), "%s T%02u " TSEP, temp_str, Node->timer_num);
                snprintf(temp_str, sizeof(temp_str), "%s CH_%02u " TSEP, temp_str, Node->channel);
                snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, GpioPadToStr(Node->Pad));
                snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, Config->name);
                res = is_contain(temp_str, key_word1, key_word2);
                if(res) {
                    cli_printf("%s" CRLF, temp_str);
                    cnt++;
                }
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
