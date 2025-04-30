#include "i2c_nrf_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "i2c_config.h"
#include "i2c_drv.h"
#include "i2c_nrf_diag.h"
#include "i2c_nrf_types.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "table_utils.h"
#include "writer_config.h"
#include "nrfx_irqs_nrf5340_application.h"
#include "nrfx_timer.h"


static bool i2c_diag_low_level(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"},    {5, "sta"}, {6, "Mode"}, {5, "ErrIt"}, {5, "EntIt"}, {5, "BufIt"},
        {5, "DmaIt"}, {5, "MHz"}, {5, "role"}, {5, "state"}, {5, "dir"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i2c_num = 0;
  //  char temp_str[120] = "";
    for(i2c_num = 0; i2c_num <= I2C_COUNT; i2c_num++) {

    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool i2c_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        LOG_INFO(I2C, "TIMER0_IRQHandler: 0x%p",nrfx_timer_0_irq_handler);
        LOG_INFO(I2C, "TIMER0_IRQHandler: 0x%p",TIMER0_IRQHandler);
        res = i2c_diag_low_level();
    } else {
        LOG_ERROR(I2C, "Usage: i2dl");
    }
    return res;
}
