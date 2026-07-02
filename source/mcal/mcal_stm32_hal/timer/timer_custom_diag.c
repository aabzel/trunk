#include "timer_custom_diag.h"

#ifdef HAS_BIT_DIAG
#include "bit_diag.h"
#endif

#include "clock_diag.h"
#include "array_diag.h"
#include "sys_config.h"
#include "log.h"
#include "timer_const.h"
#include "num_to_str.h"
#include "timer_mcal.h"

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

static bool timer_diag_reg_ccmr(const TimerRegCCMR_t * const pCcmr, uint8_t num) {
    bool res = false ;
    LOG_WARNING(TIMER,"CCMR%u:0x%02x=%s",num,pCcmr->byte,utoa_bin8(pCcmr->byte));
    LOG_INFO(TIMER,"CC%uS:%u",num,pCcmr->CCxS);
    LOG_INFO(TIMER,"OC%uFE:%u",num,pCcmr->OCxFE);
    LOG_INFO(TIMER,"OC%uPE:%u",num,pCcmr->OCxPE);
    LOG_INFO(TIMER,"OC%uM:%u",num,pCcmr->OCxM);
    LOG_INFO(TIMER,"OC%uCE:%u",num,pCcmr->OCxCE);


    return res;
}


bool timer_diag_reg_ccmr1(const uint32_t ccmr1) {
    bool res = false ;
    TimerRegCCMR1_t CCMR1;
    CCMR1.dword=ccmr1;
    timer_diag_reg_ccmr(&CCMR1.CH1, 1);
    timer_diag_reg_ccmr(&CCMR1.CH2, 2);
    return res;
}

bool timer_diag_reg_ccmr2(const uint32_t ccmr2) {
    bool res = false ;
    TimerRegCCMR2_t CCMR2;
    CCMR2.dword=ccmr2;
    timer_diag_reg_ccmr(&CCMR2.CH3, 3);
    timer_diag_reg_ccmr(&CCMR2.CH4, 4);
    return res;
}

bool timer_diag_reg_fields(uint8_t num){
    bool res = false ;
    TimerInfo_t* Info = TimerGetInfo(num) ;
    if(Info) {
        res = timer_diag_reg_ccmr1(Info->TIMx->CCMR1);
        res = timer_diag_reg_ccmr2(Info->TIMx->CCMR2);
    }
    return res;
}

#ifdef HAS_BIT_DIAG
const char* TimerComparatorAvailabilityToStr (const TimerComparatorAvailability_t comp) {
    static char temp[200] = "";
    strcpy(temp, "");
    snprintf(temp, sizeof(temp), "%s%s" , temp, BitToStr(comp.compare1,"1","_"));
    snprintf(temp, sizeof(temp), "%s%s" , temp, BitToStr(comp.compare2,"2","_"));
    snprintf(temp, sizeof(temp), "%s%s" , temp, BitToStr(comp.compare3,"3","_"));
    snprintf(temp, sizeof(temp), "%s%s" , temp, BitToStr(comp.compare4,"4","_"));
    return temp;
}
#endif

const char* TimerNumToToken(const uint8_t num) {
    static char temp[8] = "";
    strcpy(temp, "");
    snprintf(temp, sizeof(temp), "TIM%u" , num);
    return temp;
}

static bool timer_info_diag_one(const TimerInfo_t* const Info) {
    bool res = false ;
    char temp[200] = "";
    strcpy(temp, TSEP);
    snprintf(temp, sizeof(temp), "%s %5s " TSEP, temp, TimerNumToToken(Info->num));
    snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, Info->bitness);
    snprintf(temp, sizeof(temp), "%s %p " TSEP, temp, Info->TIMx);
    snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, ClockBusToStr(Info->clock_bus));
    snprintf(temp, sizeof(temp), "%s %11s " TSEP, temp, ArrayI32ToStr(Info->irq_n,Info->irq_cnt));
#ifdef HAS_BIT_DIAG
    snprintf(temp, sizeof(temp), "%s %5s " TSEP, temp, TimerComparatorAvailabilityToStr(Info->Comparators));
#endif
    cli_printf("%s" CRLF, temp);
    res = true;
    return res;
}

bool timer_info_diag(void) {
    bool res = false;
    uint32_t cnt = timer_mcu_cnt_get();

    static const table_col_t cols[] = {
        {7, "Num"},
        {4, "bit"},
        {12, "PhyAddre"},//0x40010000
        {6, "clkBus"},
        {13, "irqN"},
        {7, "Com"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t i =0;
    for(i=0;i<cnt;i++){
        TimerInfo_t* Info=TimerGetInfo(i);
        if(Info){
            res = timer_info_diag_one(Info);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
