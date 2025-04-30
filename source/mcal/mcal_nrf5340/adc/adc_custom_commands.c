#include "adc_custom_commands.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#ifdef HAS_ADC_DIAG
#include "adc_custom_diag.h"
#endif
#include "adc_drv.h"
#include "log.h"

bool adc_custom_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";

    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }

    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(res) {
#ifdef HAS_ADC_DIAG
        res = adc_custom_diag(keyWord1, keyWord2);
#endif

    } else {
        LOG_ERROR(LG_ADC, "Usage: adc keyWord");
    }
    return res;
}
