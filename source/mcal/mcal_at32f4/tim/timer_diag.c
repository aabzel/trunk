#include "timer_diag.h"

#include "sys_config.h"
#include "timer_const.h"

char *BusClock2Str(uint32_t bus_clock){
    char * name="?";	
    uint32_t pclk1=HAL_RCC_GetPCLK1Freq();
    uint32_t pclk2=HAL_RCC_GetPCLK2Freq();
    uint32_t hclk=HAL_RCC_GetHCLKFreq();
    if(bus_clock==pclk1){
    	name="APB1";
    }else if(bus_clock==pclk2){
    	name="APB2";
    }else if(bus_clock==hclk){
    	name="HCLK";
    }else{
    	name="?";
    }

	return name;
}

char *TimDir2Str(uint8_t code){
    char * name="?";
    switch(code){
        case CNT_DIR_UP: name="Up"; break;
        case CNT_DIR_DOWN: name="Down"; break;
        default: name="??";  break;
    }
    return name;
}
