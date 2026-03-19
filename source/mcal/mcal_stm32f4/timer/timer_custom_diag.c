#include "timer_diag.h"

#include "clock_diag.h"
#include "sys_config.h"
#include "log.h"
#include "timer_const.h"

char* TimDirToStr(const TimerDir_t code) {
    char* name = "?";
    switch(code) {
        case TIMER_CNT_DIR_UP:       name = "Up";        break;
        case TIMER_CNT_DIR_DOWN:     name = "Down";      break;
        case TIMER_CNT_DIR_UP_DOWN:  name = "UpDown";    break;
        default: name = "??";        break;
    }
    return name;
}

const Reg32_t TimerRegs[] = {
    {
        .num = __COUNTER__,
        .offset = 0x00,
        .name = "TIMx_CR1",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x04,
        .name = "TIMx_CR2",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x08,
        .name = "TIMx_SMCR",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x0C,
        .name = "TIMx_DIER",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x10,
        .name = "TIMx_SR",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x14,
        .name = "TIMx_EGR",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x18,
        .name = "TIMx_CCMR1",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x1c,
        .name = "TIMx_CCMR2",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x20,
        .name = "TIMx_CCER",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x24,
        .name = "TIMx_CNT",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x28,
        .name = "TIMx_PSC",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x2c,
        .name = "TIMx_ARR",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x30,
        .name = "TIMx_RCR",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x34,
        .name = "TIMx_CCR1",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x38,
        .name = "TIMx_CCR2",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x3C,
        .name = "TIMx_CCR3",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x40,
        .name = "TIMx_CCR4",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x44,
        .name = "TIMx_BDTR",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x48,
        .name = "TIMx_DCR",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
    {
        .num = __COUNTER__,
        .offset = 0x4C,
        .name = "TIMx_DMAR",
        .access = ACCESS_READ_WRITE,
        .size = 4,
        .valid = true,
    },
};

uint32_t time_register_cnt(void) { return ARRAY_SIZE(TimerRegs); }

#if 0
const char *BusClockToStr(uint32_t bus_clock){
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
#endif

const char* TimerInfoToStr(const TimerInfo_t* const Info) {
    if(Info) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sClkBus:%s,", text, ClockBusToStr(Info->clock_bus));
        snprintf(text, sizeof(text), "%sN:%u,", text, Info->num);
        snprintf(text, sizeof(text), "%sBase:0x%p,", text, Info->TIMx);
        snprintf(text, sizeof(text), "%sIrq:%u,", text, Info->irq_n);
        snprintf(text, sizeof(text), "%sCLK:0x%u,", text, Info->clock_bus);
        snprintf(text, sizeof(text), "%sBit:%u,", text, Info->bitness);
    }
    return text;
}
