#ifndef SCR1_TIMER_CONST_H
#define SCR1_TIMER_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#define SCR1_TIMER_MAX_VAL 0xFFFFFFFFFFFFUL
#define SCR1_TIMER_BASE 0x00490000
#define SCR1_TIMER_MAX_DIV 1023

typedef enum {
    CLK_SRC_AHB_CLK = 0, //AHB_CLK (до 32 ћ√ц);
    CLK_SRC_RTC_CLK = 1, //RTC_CLK (32768 √ц)
    CLK_SRC_UNDEF = 2
}SCR1_TIMER_CLKSRC_t;

typedef enum {
    SCR1_TIMER_CTRL_DISABLE = 0, // 0: выключен;
    SCR1_TIMER_CTRL_ENABLE = 1, //1: включен.
	SCR1_TIMER_CTRL_UNDEF = 2
}SCR1_TIMER_CTRL_t;


#ifdef __cplusplus
}
#endif

#endif /* SCR1_TIMER_CONST_H*/
