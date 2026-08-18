#include "rs2058_diag.h"

#include <stdio.h>

#include "rs2058_config.h"
#include "rs2058_drv.h"
#include "log.h"
#include "gpio_mcal.h"
#include "table_utils.h"
#include "writer_config.h"
#include "gpio_diag.h"


const char* Rs2058SwStateToStr(Rs2058State_t state){
    const char* name="?";
    switch((uint8_t)state){
        case RS2058_SW_COM_NO: name="COM-NO";break;
        case RS2058_SW_COM_NC:name="COM-NC"; break;
    default:
        name="Err";
    break;
    }
    return name;
}

const char*  Rs2058SwConnToStr(Rs2058Sw_t* Node ){
    static char name[80]="Err";
    switch((uint8_t)Node->state){
        case RS2058_SW_COM_NO: {
            sprintf(name,"[%s]-[%s]",Node->com_wire_name,Node->no_wire_name);
        }break;
        case RS2058_SW_COM_NC:{
            sprintf(name,"[%s]-[%s]",Node->com_wire_name,Node->nc_wire_name);
        } break;
    default:

    break;
    }
    return name;

}

static bool rs2058_pins_diag( void) {
    bool res = false;

        res = true;
        static const table_col_t cols[] = {
                {4, "No"},
                {7, "Pad"},
                {6, "GPIO"},
                {8, "State"},
                {7, "WireName"}
        };

        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        uint32_t j = 0;
        uint32_t cnt=rs2058_get_cnt();
        for(j=0; j<cnt; j++) {
            uint32_t i = 0;
            const Rs2058Config_t* Config= Rs2058GetConfig(i);
            if(Config) {
                Rs2058Item_t* Node = Rs2058GetNode(  j);
                for(i=0; i<2; i++) {
                        cli_printf(TSEP " %2u " TSEP, i+1);
                        cli_printf(" %5s " TSEP, GpioPadToStr( Config->sw[i].in.byte));
                        cli_printf(" %4s " TSEP, GpioLevelToStr(Node->sw[i].in_ll));
                        cli_printf(" %6s " TSEP, Rs2058SwStateToStr(Node->sw[i].state));
                        cli_printf(" %6s " TSEP, Rs2058SwConnToStr(&Node->sw[i]));
                        cli_printf( CRLF);
                }
            }
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool rs2058_diag(void) {
    bool res = false;

    uint8_t i = 0;
    uint32_t cnt = rs2058_get_cnt();
    for(i=0; i<cnt; i++) {
        const Rs2058Config_t* Config= Rs2058GetConfig(i);
        if(Config){
            Rs2058Item_t* Node = Rs2058GetNode(  i);
            if(Node) {
                uint8_t j = 0;
                for (j=0; j<cnt; j++) {
                    res= gpio_get_state(  Config->sw[j].in.byte, &Node->sw[j].in_ll);
                    Node->sw[j].state=      Rs20582LogLev2State(   Node->sw[j].in_ll);
                }
            }
        }
    }

     rs2058_pins_diag(  );

    return res;
}
