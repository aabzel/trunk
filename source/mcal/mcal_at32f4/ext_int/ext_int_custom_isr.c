#include "ext_int_custom_isr.h"

#include "ext_int_custom_drv.h"
#include "ext_int_mcal.h"
#include "microcontroller_const.h"

bool EXINTx_IRQHandler(uint8_t num) {
    bool res = false;
    uint32_t ex_int_line = num_exint_line(num);
    flag_status ret = FALSE;
    ret = exint_interrupt_flag_get(ex_int_line);
    if(SET == ret) {
        exint_flag_clear(ex_int_line);
        ExtIntHandle_t* Node = ExtIntGetNode(num);
        if(Node) {
            Node->it_cnt++;
            res = true;
        }
    }
    return res;
}
