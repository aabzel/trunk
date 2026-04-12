#include "interrupt_config.h"

#include "sys_config.h"
#include "data_utils.h"

#ifdef HAS_EHAL
#include "microcontroller_ehal_const.h"
#endif

#ifdef HAS_YTM32B1ME0_1_3_1
#include "YTM32B1ME0.h"
#endif

#define  INTERRUPT_CONFIG_ADC   \
    { .irq_n =ADC0_IRQn, .on_off = false,  .valid = true, .name ="ADC0", .priority = 7, },   \
    { .irq_n =ADC1_IRQn, .on_off = false,  .valid = true, .name ="ADC1", .priority = 7, },




#define  INTERRUPT_CONFIG_DMA   \
    { .irq_n =DMA1_IRQn, .on_off = false,  .valid = true, .name ="DMA1", .priority = 7, },   \
    { .irq_n =DMA2_IRQn, .on_off = false,  .valid = true, .name ="DMA2", .priority = 7, },   \
    { .irq_n =DMA3_IRQn, .on_off = false,  .valid = true, .name ="DMA3", .priority = 7, },   \
    { .irq_n =DMA4_IRQn, .on_off = false,  .valid = true, .name ="DMA4", .priority = 7, },   \
    { .irq_n =DMA5_IRQn, .on_off = false,  .valid = true, .name ="DMA5", .priority = 7, },   \
    { .irq_n =DMA6_IRQn, .on_off = false,  .valid = true, .name ="DMA6", .priority = 7, },   \
    { .irq_n =DMA7_IRQn, .on_off = false,  .valid = true, .name ="DMA7", .priority = 7, },   \
    { .irq_n =DMA8_IRQn, .on_off = false,  .valid = true, .name ="DMA8", .priority = 7, },   \
    { .irq_n =DMA9_IRQn, .on_off = false,  .valid = true, .name ="DMA9", .priority = 7, },   \
    { .irq_n =DMA10_IRQn, .on_off = false,  .valid = true, .name ="DMA10", .priority = 7, },   \
    { .irq_n =DMA11_IRQn, .on_off = false,  .valid = true, .name ="DMA11", .priority = 7, },   \
    { .irq_n =DMA12_IRQn, .on_off = false,  .valid = true, .name ="DMA12", .priority = 7, },   \
    { .irq_n =DMA13_IRQn, .on_off = false,  .valid = true, .name ="DMA13", .priority = 7, },   \
    { .irq_n =DMA14_IRQn, .on_off = false,  .valid = true, .name ="DMA14", .priority = 7, },   \
    { .irq_n =DMA15_IRQn, .on_off = false,  .valid = true, .name ="DMA15", .priority = 7, },   \
    { .irq_n =DMA_Error_IRQn, .on_off = false,  .valid = true, .name ="DMA_Error", .priority = 7, },


#define INTERRUPT_CONFIG_LIN  \
    { .irq_n =LINFlexD0_IRQn, .on_off = false,  .valid = true, .name ="LINFlexD0", .priority = 7, },  \
    { .irq_n =LINFlexD1_IRQn, .on_off = false,  .valid = true, .name ="LINFlexD1", .priority = 7, },  \
    { .irq_n =LINFlexD2_IRQn, .on_off = false,  .valid = true, .name ="LINFlexD2", .priority = 7, },  \
    { .irq_n =LINFlexD3_IRQn, .on_off = false,  .valid = true, .name ="LINFlexD3", .priority = 7, },  \
    { .irq_n =LINFlexD4_IRQn, .on_off = false,  .valid = true, .name ="LINFlexD4", .priority = 7, }, \
    { .irq_n =LINFlexD5_IRQn, .on_off = false,  .valid = true, .name ="LINFlexD5", .priority = 7, },


#define INTERRUPT_CONFIG_TMR_CH

#if 0
    { .irq_n =pTMR_Ch0_IRQn, .on_off = false,  .valid = true, .name ="pTMR_Ch0", .priority = 7, },  \
    { .irq_n =pTMR_Ch1_IRQn, .on_off = false,  .valid = true, .name ="pTMR_Ch1", .priority = 7, },  \
    { .irq_n =pTMR_Ch2_IRQn, .on_off = false,  .valid = true, .name ="pTMR_Ch2", .priority = 7, },
    { .irq_n =pTMR_Ch3_IRQn, .on_off = false,  .valid = true, .name ="pTMR_Ch3", .priority = 7, },
#endif

#define INTERRUPT_CONFIG_TIMER0    \
    { .irq_n =lpTMR0_IRQn, .on_off = false,  .valid = true, .name ="lpTMR0", .priority = 7, },  \
    { .irq_n =TMR0_Ch3_IRQn, .on_off = false,  .valid = true, .name ="TMR0_Ch3", .priority = 7, },  \
    { .irq_n =TMR0_Ch2_IRQn, .on_off = false,  .valid = true, .name ="TMR0_Ch2", .priority = 7, },  \
    { .irq_n =TMR0_Ch0_IRQn, .on_off = false,  .valid = true, .name ="TMR0_Ch0", .priority = 7, },  \
    { .irq_n =TMR0_Ch1_IRQn, .on_off = false,  .valid = true, .name ="TMR0_Ch1", .priority = 7, },  \
    { .irq_n =eTMR0_Ch0_Ch1_IRQn, .on_off = false,  .valid = true, .name ="eTMR0_Ch0_Ch1", .priority = 7, },  \
    { .irq_n =eTMR0_Ch2_Ch3_IRQn, .on_off = false,  .valid = true, .name ="eTMR0_Ch2_Ch3", .priority = 7, },  \
    { .irq_n =eTMR0_Ch4_Ch5_IRQn, .on_off = false,  .valid = true, .name ="eTMR0_Ch4_Ch5", .priority = 7, },  \
    { .irq_n =eTMR0_Ch6_Ch7_IRQn, .on_off = false,  .valid = true, .name ="eTMR0_Ch6_Ch7", .priority = 7, },  \
    { .irq_n =eTMR0_Fault_IRQn, .on_off = false,  .valid = true, .name ="eTMR0_Fault", .priority = 7, },  \
    { .irq_n =eTMR0_Ovf_IRQn, .on_off = false,  .valid = true, .name ="eTMR0_Ovf", .priority = 7, },


#define INTERRUPT_CONFIG_TIMER1    \
    { .irq_n =eTMR1_Ovf_IRQn, .on_off = false,  .valid = true, .name ="eTMR1_Ovf", .priority = 7, },  \
    { .irq_n =eTMR1_Fault_IRQn, .on_off = false,  .valid = true, .name ="eTMR1_Fault", .priority = 7, }  ,  \
    { .irq_n =eTMR1_Ch0_Ch1_IRQn, .on_off = false,  .valid = true, .name ="eTMR1_Ch0_Ch1", .priority = 7, },  \
    { .irq_n =eTMR1_Ch2_Ch3_IRQn, .on_off = false,  .valid = true, .name ="eTMR1_Ch2_Ch3", .priority = 7, },  \
    { .irq_n =eTMR1_Ch4_Ch5_IRQn, .on_off = false,  .valid = true, .name ="eTMR1_Ch4_Ch5", .priority = 7, },  \
    { .irq_n =eTMR1_Ch6_Ch7_IRQn, .on_off = false,  .valid = true, .name ="eTMR1_Ch6_Ch7", .priority = 7, },

#define INTERRUPT_CONFIG_TIMER2    \
    { .irq_n =eTMR2_Ovf_IRQn, .on_off = false,  .valid = true, .name ="eTMR2_Ovf", .priority = 7, },  \
    { .irq_n =eTMR2_Fault_IRQn, .on_off = false,  .valid = true, .name ="eTMR2_Fault", .priority = 7, },  \
    { .irq_n =eTMR2_Ch6_Ch7_IRQn, .on_off = false,  .valid = true, .name ="eTMR2_Ch6_Ch7", .priority = 7, },  \
    { .irq_n =eTMR2_Ch4_Ch5_IRQn, .on_off = false,  .valid = true, .name ="eTMR2_Ch4_Ch5", .priority = 7, },  \
    { .irq_n =eTMR2_Ch2_Ch3_IRQn, .on_off = false,  .valid = true, .name ="eTMR2_Ch2_Ch3", .priority = 7, },  \
    { .irq_n =eTMR2_Ch0_Ch1_IRQn, .on_off = false,  .valid = true, .name ="eTMR2_Ch0_Ch1", .priority = 7, },

#define INTERRUPT_CONFIG_TIMER5    \
    { .irq_n =eTMR5_Ovf_IRQn, .on_off = false,  .valid = true, .name ="eTMR5_Ovf", .priority = 7, },   \
    { .irq_n =eTMR5_Fault_IRQn, .on_off = false,  .valid = true, .name ="eTMR5_Fault", .priority = 7, },   \
    { .irq_n =eTMR5_Ch6_Ch7_IRQn, .on_off = false,  .valid = true, .name ="eTMR5_Ch6_Ch7", .priority = 7, },   \
    { .irq_n =eTMR5_Ch4_Ch5_IRQn, .on_off = false,  .valid = true, .name ="eTMR5_Ch4_Ch5", .priority = 7, },   \
    { .irq_n =eTMR5_Ch2_Ch3_IRQn, .on_off = false,  .valid = true, .name ="eTMR5_Ch2_Ch3", .priority = 7, },   \
    { .irq_n =eTMR5_Ch0_Ch1_IRQn, .on_off = false,  .valid = true, .name ="eTMR5_Ch0_Ch1", .priority = 7, },


#define INTERRUPT_CONFIG_TIMER4    \
    { .irq_n =eTMR4_Ovf_IRQn, .on_off = false,  .valid = true, .name ="eTMR4_Ovf", .priority = 7, },   \
    { .irq_n =eTMR4_Fault_IRQn, .on_off = false,  .valid = true, .name ="eTMR4_Fault", .priority = 7, },   \
    { .irq_n =eTMR4_Ch6_Ch7_IRQn, .on_off = false,  .valid = true, .name ="eTMR4_Ch6_Ch7", .priority = 7, },   \
    { .irq_n =eTMR4_Ch4_Ch5_IRQn, .on_off = false,  .valid = true, .name ="eTMR4_Ch4_Ch5", .priority = 7, },   \
    { .irq_n =eTMR4_Ch2_Ch3_IRQn, .on_off = false,  .valid = true, .name ="eTMR4_Ch2_Ch3", .priority = 7, },   \
    { .irq_n =eTMR4_Ch0_Ch1_IRQn, .on_off = false,  .valid = true, .name ="eTMR4_Ch0_Ch1", .priority = 7, },


#define INTERRUPT_CONFIG_TIMER3    \
    { .irq_n =eTMR3_Ovf_IRQn, .on_off = false,  .valid = true, .name ="eTMR3_Ovf", .priority = 7, },  \
    { .irq_n =eTMR3_Fault_IRQn, .on_off = false,  .valid = true, .name ="eTMR3_Fault", .priority = 7, },  \
    { .irq_n =eTMR3_Ch6_Ch7_IRQn, .on_off = false,  .valid = true, .name ="eTMR3_Ch6_Ch7", .priority = 7, },  \
    { .irq_n =eTMR3_Ch4_Ch5_IRQn, .on_off = false,  .valid = true, .name ="eTMR3_Ch4_Ch5", .priority = 7, },  \
    { .irq_n =eTMR3_Ch2_Ch3_IRQn, .on_off = false,  .valid = true, .name ="eTMR3_Ch2_Ch3", .priority = 7, },  \
    { .irq_n =eTMR3_Ch0_Ch1_IRQn, .on_off = false,  .valid = true, .name ="eTMR3_Ch0_Ch1", .priority = 7, },

#define INTERRUPT_CONFIG_TIMER    \
    INTERRUPT_CONFIG_TMR_CH  \
    INTERRUPT_CONFIG_TIMER0   \
    INTERRUPT_CONFIG_TIMER1   \
    INTERRUPT_CONFIG_TIMER2   \
    INTERRUPT_CONFIG_TIMER3   \
    INTERRUPT_CONFIG_TIMER4   \
    INTERRUPT_CONFIG_TIMER5




#define INTERRUPT_CONFIG_CAN0  \
    { .irq_n =CAN0_ORed_IRQn, .on_off = false,  .valid = true, .name ="CAN0_ORed", .priority = 7, },    \
    { .irq_n =CAN0_Error_IRQn, .on_off = false,  .valid = true, .name ="CAN0_Error", .priority = 7, },    \
    { .irq_n =CAN0_Wake_Up_IRQn, .on_off = false,  .valid = true, .name ="CAN0_Wake_Up", .priority = 7, },    \
    { .irq_n =CAN0_ORed_0_15_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN0_ORed_0_15_MB", .priority = 7, },    \
    { .irq_n =CAN0_ORed_16_31_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN0_ORed_16_31_MB", .priority = 7, },    \
    { .irq_n =CAN0_ORed_32_47_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN0_ORed_32_47_MB", .priority = 7, },    \
    { .irq_n =CAN0_ORed_48_63_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN0_ORed_48_63_MB", .priority = 7, },

#define INTERRUPT_CONFIG_CAN1    \
    { .irq_n =CAN1_ORed_IRQn, .on_off = false,  .valid = true, .name ="CAN1_ORed", .priority = 7, },    \
    { .irq_n =CAN1_Error_IRQn, .on_off = false,  .valid = true, .name ="CAN1_Error", .priority = 7, },    \
    { .irq_n =CAN1_Wake_Up_IRQn, .on_off = false,  .valid = true, .name ="CAN1_Wake_Up", .priority = 7, },    \
    { .irq_n =CAN1_ORed_0_15_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN1_ORed_0_15_MB", .priority = 7, },    \
    { .irq_n =CAN1_ORed_16_31_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN1_ORed_16_31_MB", .priority = 7, },    \
    { .irq_n =CAN1_ORed_32_47_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN1_ORed_32_47_MB", .priority = 7, },    \
    { .irq_n =CAN1_ORed_48_63_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN1_ORed_48_63_MB", .priority = 7, },

#define INTERRUPT_CONFIG_CAN2    \
    { .irq_n =CAN2_ORed_0_15_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN2_ORed_0_15_MB", .priority = 7, },    \
    { .irq_n =CAN2_ORed_16_31_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN2_ORed_16_31_MB", .priority = 7, },    \
    { .irq_n =CAN2_ORed_32_47_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN2_ORed_32_47_MB", .priority = 7, },    \
    { .irq_n =CAN2_ORed_48_63_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN2_ORed_48_63_MB", .priority = 7, },    \
    { .irq_n =CAN2_Wake_Up_IRQn, .on_off = false,  .valid = true, .name ="CAN2_Wake_Up", .priority = 7, },    \
    { .irq_n =CAN2_Error_IRQn, .on_off = false,  .valid = true, .name ="CAN2_Error", .priority = 7, },


#define INTERRUPT_CONFIG_CAN3    \
        { .irq_n =CAN3_ORed_IRQn, .on_off = false,  .valid = true, .name ="CAN3_ORed", .priority = 7, },    \
        { .irq_n =CAN3_Error_IRQn, .on_off = false,  .valid = true, .name ="CAN3_Error", .priority = 7, },    \
        { .irq_n =CAN3_Wake_Up_IRQn, .on_off = false,  .valid = true, .name ="CAN3_Wake_Up", .priority = 7, },    \
        { .irq_n =CAN3_ORed_0_15_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN3_ORed_0_15_MB", .priority = 7, },    \
        { .irq_n =CAN3_ORed_16_31_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN3_ORed_16_31_MB", .priority = 7, },



#define INTERRUPT_CONFIG_CAN4    \
        { .irq_n =CAN4_ORed_IRQn, .on_off = false,  .valid = true, .name ="CAN4_ORed", .priority = 7, },    \
        { .irq_n =CAN4_Error_IRQn, .on_off = false,  .valid = true, .name ="CAN4_Error", .priority = 7, },    \
        { .irq_n =CAN4_Wake_Up_IRQn, .on_off = false,  .valid = true, .name ="CAN4_Wake_Up", .priority = 7, },    \
        { .irq_n =CAN4_ORed_0_15_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN4_ORed_0_15_MB", .priority = 7, },    \
        { .irq_n =CAN4_ORed_16_31_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN4_ORed_16_31_MB", .priority = 7, },


#define INTERRUPT_CONFIG_CAN5    \
        { .irq_n =CAN5_ORed_IRQn, .on_off = false,  .valid = true, .name ="CAN5_ORed", .priority = 7, },    \
        { .irq_n =CAN5_Error_IRQn, .on_off = false,  .valid = true, .name ="CAN5_Error", .priority = 7, },    \
        { .irq_n =CAN5_Wake_Up_IRQn, .on_off = false,  .valid = true, .name ="CAN5_Wake_Up", .priority = 7, },    \
        { .irq_n =CAN5_ORed_0_15_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN5_ORed_0_15_MB", .priority = 7, },    \
        { .irq_n =CAN5_ORed_16_31_MB_IRQn, .on_off = false,  .valid = true, .name ="CAN5_ORed_16_31_MB", .priority = 7, },


#define INTERRUPT_CONFIG_CAN   \
    INTERRUPT_CONFIG_CAN0  \
    INTERRUPT_CONFIG_CAN1  \
    INTERRUPT_CONFIG_CAN2  \
    INTERRUPT_CONFIG_CAN3  \
    INTERRUPT_CONFIG_CAN4  \
    INTERRUPT_CONFIG_CAN5


#define INTERRUPT_CONFIG_I2C    \
    { .irq_n = I2C0_Master_IRQn, .on_off = false,  .valid = true, .name ="I2C0_Master", .priority = 7, },   \
    { .irq_n = I2C0_Slave_IRQn, .on_off = false,  .valid = true, .name ="I2C0_Slave", .priority = 7, },   \
    { .irq_n = I2C1_Master_IRQn, .on_off = false,  .valid = true, .name ="I2C1_Master", .priority = 7, },   \
    { .irq_n = I2C1_Slave_IRQn, .on_off = false,  .valid = true, .name ="I2C1_Slave", .priority = 7, },   \
    { .irq_n = I2C2_Master_IRQn, .on_off = false,  .valid = true, .name ="I2C2_Master", .priority = 7, },   \
    { .irq_n = I2C2_Slave_IRQn, .on_off = false,  .valid = true, .name ="I2C2_Slave", .priority = 7, },


#define INTERRUPT_CONFIG_GPIO   \
    { .irq_n = GPIOA_IRQn, .on_off = false,  .valid = true, .name ="GPIOA", .priority = 7, },   \
    { .irq_n = GPIOB_IRQn, .on_off = false,  .valid = true, .name ="GPIOB", .priority = 7, }, \
    { .irq_n = GPIOC_IRQn, .on_off = false,  .valid = true, .name ="GPIOC", .priority = 7, },   \
    { .irq_n = GPIOD_IRQn, .on_off = false,  .valid = true, .name ="GPIOD", .priority = 7, },   \
    { .irq_n = GPIOE_IRQn, .on_off = false,  .valid = true, .name ="GPIOE", .priority = 7, },   \


#define INTERRUPT_CONFIG_SPI   \
    { .irq_n = SPI0_IRQn, .on_off = false,  .valid = true, .name ="SPI0", .priority = 7, },   \
    { .irq_n = SPI1_IRQn, .on_off = false,  .valid = true, .name ="SPI1", .priority = 7, }, \
    { .irq_n = SPI2_IRQn, .on_off = false,  .valid = true, .name ="SPI2", .priority = 7, },   \
    { .irq_n = SPI3_IRQn, .on_off = false,  .valid = true, .name ="SPI3", .priority = 7, },   \
    { .irq_n = SPI4_IRQn, .on_off = false,  .valid = true, .name ="SPI4", .priority = 7, },   \
    { .irq_n = SPI5_IRQn, .on_off = false,  .valid = true, .name ="SPI5", .priority = 7, },


#define INTERRUPT_CONFIG_RESERVED  \
    { .irq_n = Reserved5_IRQn, .on_off = false,  .valid = true, .name ="Reserved5", .priority = 7, },   \
    { .irq_n = Reserved6_IRQn, .on_off = false,  .valid = true, .name ="Reserved6", .priority = 7, },   \
    { .irq_n = Reserved7_IRQn, .on_off = false,  .valid = true, .name ="Reserved7", .priority = 7, },   \
    { .irq_n = Reserved8_IRQn, .on_off = false,  .valid = true, .name ="Reserved8", .priority = 7, },   \
    { .irq_n = Reserved9_IRQn, .on_off = false,  .valid = true, .name ="Reserved9", .priority = 7, },   \
    { .irq_n = Reserved10_IRQn, .on_off = false,  .valid = true, .name ="Reserved10", .priority = 7, },   \
    { .irq_n = Reserved11_IRQn, .on_off = false,  .valid = true, .name ="Reserved11", .priority = 7, },   \
    { .irq_n = Reserved12_IRQn, .on_off = false,  .valid = true, .name ="Reserved12", .priority = 7, },   \
    { .irq_n = Reserved13_IRQn, .on_off = false,  .valid = true, .name ="Reserved13", .priority = 7, },   \
    { .irq_n = Reserved14_IRQn, .on_off = false,  .valid = true, .name ="Reserved14", .priority = 7, },   \
    { .irq_n = Reserved15_IRQn, .on_off = false,  .valid = true, .name ="Reserved15", .priority = 7, },   \
    { .irq_n = Reserved16_IRQn, .on_off = false,  .valid = true, .name ="Reserved16", .priority = 7, },   \
    { .irq_n = Reserved17_IRQn, .on_off = false,  .valid = true, .name ="Reserved17", .priority = 7, },   \
    { .irq_n = Reserved18_IRQn, .on_off = false,  .valid = true, .name ="Reserved18", .priority = 7, },   \
    { .irq_n = Reserved19_IRQn, .on_off = false,  .valid = true, .name ="Reserved19", .priority = 7, },   \
    { .irq_n = Reserved20_IRQn, .on_off = false,  .valid = true, .name ="Reserved20", .priority = 7, },   \
    { .irq_n = Reserved21_IRQn, .on_off = false,  .valid = true, .name ="Reserved21", .priority = 7, },   \
   { .irq_n = Reserved22_IRQn, .on_off = false,  .valid = true, .name ="Reserved22", .priority = 7, },   \
   { .irq_n = Reserved23_IRQn, .on_off = false,  .valid = true, .name ="Reserved23", .priority = 7, },   \
   { .irq_n = Reserved24_IRQn, .on_off = false,  .valid = true, .name ="Reserved23", .priority = 7, },   \
   { .irq_n = Reserved25_IRQn, .on_off = false,  .valid = true, .name ="Reserved24", .priority = 7, },   \
   { .irq_n = Reserved26_IRQn, .on_off = false,  .valid = true, .name ="Reserved25", .priority = 7, },   \
   { .irq_n = Reserved27_IRQn, .on_off = false,  .valid = true, .name ="Reserved26", .priority = 7, },   \
   { .irq_n = Reserved28_IRQn, .on_off = false,  .valid = true, .name ="Reserved27", .priority = 7, },   \
   { .irq_n = Reserved29_IRQn, .on_off = false,  .valid = true, .name ="Reserved28", .priority = 7, },   \
   { .irq_n = Reserved30_IRQn, .on_off = false,  .valid = true, .name ="Reserved30", .priority = 7, },   \
   { .irq_n = Reserved31_IRQn, .on_off = false,  .valid = true, .name ="Reserved31", .priority = 7, },   \
   { .irq_n = Reserved32_IRQn, .on_off = false,  .valid = true, .name ="Reserved32", .priority = 7, },   \
   { .irq_n = Reserved33_IRQn, .on_off = false,  .valid = true, .name ="Reserved33", .priority = 7, },   \
   { .irq_n = Reserved34_IRQn, .on_off = false,  .valid = true, .name ="Reserved34", .priority = 7, },   \
   { .irq_n = Reserved35_IRQn, .on_off = false,  .valid = true, .name ="Reserved35", .priority = 7, },   \
   { .irq_n = Reserved36_IRQn, .on_off = false,  .valid = true, .name ="Reserved36", .priority = 7, },   \
   { .irq_n = Reserved37_IRQn, .on_off = false,  .valid = true, .name ="Reserved37", .priority = 7, },   \
   { .irq_n = Reserved38_IRQn, .on_off = false,  .valid = true, .name ="Reserved38", .priority = 7, },   \
   { .irq_n = Reserved39_IRQn, .on_off = false,  .valid = true, .name ="Reserved39", .priority = 7, },   \
   { .irq_n = Reserved40_IRQn, .on_off = false,  .valid = true, .name ="Reserved40", .priority = 7, },   \
   { .irq_n = Reserved41_IRQn, .on_off = false,  .valid = true, .name ="Reserved41", .priority = 7, },   \
   { .irq_n = Reserved42_IRQn, .on_off = false,  .valid = true, .name ="Reserved42", .priority = 7, },   \
   { .irq_n = Reserved43_IRQn, .on_off = false,  .valid = true, .name ="Reserved43", .priority = 7, },   \
   { .irq_n = Reserved44_IRQn, .on_off = false,  .valid = true, .name ="Reserved44", .priority = 7, },   \
   { .irq_n = Reserved45_IRQn, .on_off = false,  .valid = true, .name ="Reserved45", .priority = 7, },   \
   { .irq_n = Reserved46_IRQn, .on_off = false,  .valid = true, .name ="Reserved46", .priority = 7, },   \
   { .irq_n = Reserved47_IRQn, .on_off = false,  .valid = true, .name ="Reserved47", .priority = 7, },   \
   { .irq_n = Reserved48_IRQn, .on_off = false,  .valid = true, .name ="Reserved48", .priority = 7, },   \
   { .irq_n = Reserved49_IRQn, .on_off = false,  .valid = true, .name ="Reserved49", .priority = 7, },   \
   { .irq_n = Reserved50_IRQn, .on_off = false,  .valid = true, .name ="Reserved50", .priority = 7, },   \
    { .irq_n = Reserved51_IRQn, .on_off = false,  .valid = true, .name ="Reserved51", .priority = 7, },   \
    { .irq_n = Reserved52_IRQn, .on_off = false,  .valid = true, .name ="Reserved52", .priority = 7, },   \
    { .irq_n = Reserved53_IRQn, .on_off = false,  .valid = true, .name ="Reserved53", .priority = 7, },   \
    { .irq_n = Reserved54_IRQn, .on_off = false,  .valid = true, .name ="Reserved54", .priority = 7, },

const InterruptConfig_t InterruptConfig[] ={
#if 0
    { .irq_n = NMI_IRQn, .on_off = false,  .valid = true, .name ="NMI", .priority = 7, },
    { .irq_n = HardFault_IRQn, .on_off = false,  .valid = true, .name ="HardFault", .priority = 7, },
    { .irq_n = NotAvail_IRQn, .on_off = false,  .valid = true, .name ="NotAvail", .priority = 7, },
    { .irq_n = MemManage_IRQn, .on_off = false,  .valid = true, .name ="MemManage", .priority = 7, },
    { .irq_n = UsageFault_IRQn, .on_off = false,  .valid = true, .name ="UsageFault", .priority = 7, },
    { .irq_n = SVC_IRQn, .on_off = false,  .valid = true, .name ="SVC", .priority = 7, },
    { .irq_n = BusFault_IRQn, .on_off = false,  .valid = true, .name ="BusFault", .priority = 7, },
    { .irq_n = DebugMon_IRQn, .on_off = false,  .valid = true, .name ="DebugMon", .priority = 7, },
    { .irq_n = PendSV_IRQn, .on_off = false,  .valid = true, .name ="PendSV", .priority = 7, },
#endif
   INTERRUPT_CONFIG_CAN     \
   INTERRUPT_CONFIG_DMA \
   INTERRUPT_CONFIG_LIN \
   INTERRUPT_CONFIG_I2C \
   INTERRUPT_CONFIG_ADC \
   INTERRUPT_CONFIG_GPIO \
   INTERRUPT_CONFIG_SPI \
   INTERRUPT_CONFIG_RESERVED \
   INTERRUPT_CONFIG_TIMER    \
    { .irq_n = SysTick_IRQn, .on_off = true,  .valid = true, .name ="SysTick", .priority = 7, },
    { .irq_n = RTC_IRQn, .on_off = false,  .valid = true, .name ="RTC", .priority = 7, },
    { .irq_n = FPU_IRQn, .on_off = false,  .valid = true, .name ="FPU", .priority = 7, },
    { .irq_n = EFM_IRQn, .on_off = false,  .valid = true, .name ="EFM", .priority = 7, },
    { .irq_n = EFM_Error_IRQn, .on_off = false,  .valid = true, .name ="EFM_Error", .priority = 7, },
    { .irq_n = PCU_IRQn, .on_off = false,  .valid = true, .name ="PCU", .priority = 7, },
    { .irq_n = EFM_Ecc_IRQn, .on_off = false,  .valid = true, .name ="EFM_Ecc", .priority = 7, },
    { .irq_n = RCU_IRQn, .on_off = false,  .valid = true, .name ="RCU", .priority = 7, },
    { .irq_n = RTC_IRQn, .on_off = false,  .valid = true, .name ="RTC", .priority = 7, },
    { .irq_n = RTC_Seconds_IRQn, .on_off = false,  .valid = true, .name ="RTC_Seconds", .priority = 7, },
    { .irq_n = SCU_IRQn, .on_off = false,  .valid = true, .name ="SCU", .priority = 7, },
    { .irq_n = ACMP0_IRQn, .on_off = false,  .valid = true, .name ="ACMP0", .priority = 7, },
    { .irq_n = PTU1_IRQn, .on_off = false,  .valid = true, .name ="PTU1", .priority = 7, },
    { .irq_n = TRNG_IRQn, .on_off = false,  .valid = true, .name ="TRNG", .priority = 7, },
    { .irq_n = HCU_IRQn, .on_off = false,  .valid = true, .name ="HCU", .priority = 7, },
    { .irq_n = INTM_IRQn, .on_off = false,  .valid = true, .name ="INTM", .priority = 7, },
    { .irq_n = WKU_IRQn, .on_off = false,  .valid = true, .name ="WKU", .priority = 7, },
    { .irq_n = ALIGN_0_IRQn, .on_off = false,  .valid = true, .name ="ALIGN_0", .priority = 7, },


#if 0
    { .irq_n = EMU_IRQn, .on_off = false,  .valid = true, .name ="EMU", .priority = 7, },
    { .irq_n = WDG_IRQn, .on_off = false,  .valid = true, .name ="WDG", .priority = 7, },
#endif
};


uint32_t interrupt_get_cnt(void) {
    uint32_t cnt =0;
    cnt = ARRAY_SIZE(InterruptConfig);
    return cnt;

}
