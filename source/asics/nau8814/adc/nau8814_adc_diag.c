#include "nau8814_adc_diag.h"

#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "log.h"
#include "nau8814_drv.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool nau8814_adc_diag(uint8_t num) {
    bool res = false;
    Nau8814Handle_t* Node = Nau8814GetNode(num);
    if(Node) {
        res = nau8814_p_mic_gain_get(num, &Node->p_mic_gain);
        res = nau8814_aux_gain_get(num, &Node->aux_gain);
        res = nau8814_pga_gain_get(num, &Node->pga_gain);
        res = nau8814_adc_get(num, &Node->adc_on);
    }
    return res;
}
