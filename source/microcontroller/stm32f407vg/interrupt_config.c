#include "interrupt_config.h"

#include "sys_config.h"

#ifdef HAS_MISCELLANEOUS
#include "data_utils.h"
#endif

#ifdef HAS_DMA_CHANNEL_INTERRUPT

#define INTERRUPT_CONFIG_DMA1_CHANNEL                                                               \
        {     .irq_n = DMA1_Stream0_IRQn, .priority = 2, .on_off = true, .valid = true,},           \
        {     .irq_n = DMA1_Stream1_IRQn, .priority = 2, .on_off = true, .valid = true,},           \
        {     .irq_n = DMA1_Stream2_IRQn, .priority = 2, .on_off = true, .valid = true,},           \
        {     .irq_n = DMA1_Stream3_IRQn, .priority = 2, .on_off = true, .valid = true,},           \
        {     .irq_n = DMA1_Stream4_IRQn, .priority = 2, .on_off = true, .valid = true,},           \
        {     .irq_n = DMA1_Stream5_IRQn, .priority = 2, .on_off = true, .valid = true,},           \
        {     .irq_n = DMA1_Stream6_IRQn, .priority = 2, .on_off = true, .valid = true,},           \
        {     .irq_n = DMA1_Stream7_IRQn, .priority = 2, .on_off = true, .valid = true,},

#define INTERRUPT_CONFIG_DMA2_CHANNEL                                                               \
        {     .irq_n = DMA2_Stream0_IRQn, .priority = 2, .on_off = true, .valid = true,},           \
        {     .irq_n = DMA2_Stream1_IRQn, .priority = 2, .on_off = true, .valid = true,},           \
        {     .irq_n = DMA2_Stream2_IRQn, .priority = 2, .on_off = true, .valid = true,},           \
        {     .irq_n = DMA2_Stream3_IRQn, .priority = 0, .on_off = true, .valid = true,},           \
        {     .irq_n = DMA2_Stream4_IRQn, .priority = 2, .on_off = true, .valid = true,},           \
        {     .irq_n = DMA2_Stream5_IRQn, .priority = 2, .on_off = true, .valid = true,},           \
        {     .irq_n = DMA2_Stream6_IRQn, .priority = 0, .on_off = true, .valid = true,},           \
        {     .irq_n = DMA2_Stream7_IRQn, .priority = 2, .on_off = true, .valid = true,},


#define INTERRUPT_CONFIG_DMA_CHANNEL           \
        INTERRUPT_CONFIG_DMA1_CHANNEL          \
        INTERRUPT_CONFIG_DMA2_CHANNEL

#else
#define INTERRUPT_CONFIG_DMA_CHANNEL
#endif


#ifdef HAS_USB_INTERRUPT
#define INTERRUPT_CONFIG_USB                                                           \
        {     .irq_n = OTG_HS_IRQn, .priority = 0, .on_off = true, .valid = true,},

#else
#define INTERRUPT_CONFIG_USB
#endif

#ifdef HAS_EXT_INT
#define INTERRUPT_CONFIG_EXT_INT \
        {     .irq_n = EXTI0_IRQn,  .priority = 4, .on_off = true, .valid = true,}, \
        {     .irq_n = EXTI1_IRQn,  .priority = 4, .on_off = true, .valid = true,}, \
        {     .irq_n = EXTI2_IRQn,  .priority = 4, .on_off = true, .valid = true,}, \
        {     .irq_n = EXTI3_IRQn,  .priority = 4, .on_off = true, .valid = true,}, \
        {     .irq_n = EXTI4_IRQn,  .priority = 4, .on_off = true, .valid = true,}, \
        {     .irq_n = EXTI9_5_IRQn,  .priority = 4, .on_off = true, .valid = true,}, \
        {     .irq_n = EXTI15_10_IRQn,  .priority = 4, .on_off = true, .valid = true,},
#else
#define INTERRUPT_CONFIG_EXT_INT
#endif


#ifdef HAS_CAN_INTERRUPT
#define INTERRUPT_CONFIG_CAN                                                          \
        {     .irq_n = CAN1_TX_IRQn,  .priority = 4, .on_off = true, .valid = true,},           \
        {     .irq_n = CAN1_RX0_IRQn, .priority = 4, .on_off = true, .valid = true,},          \
        {     .irq_n = CAN1_RX1_IRQn, .priority = 4, .on_off = true, .valid = true,},          \
        {     .irq_n = CAN2_RX1_IRQn, .priority = 4, .on_off = true, .valid = true,},          \
        {     .irq_n = CAN2_RX0_IRQn, .priority = 4, .on_off = true, .valid = true,},          \
        {     .irq_n = CAN2_TX_IRQn,  .priority = 4, .on_off = true, .valid = true,},
#else
#define INTERRUPT_CONFIG_CAN
#endif

#ifdef HAS_TIMER_INTERRUPT
#define INTERRUPT_CONFIG_TIMER                                                          \
        {     .irq_n = TIM4_IRQn,                .priority =0, .on_off=true, .valid=true,},                \
        {     .irq_n = TIM1_BRK_TIM9_IRQn,       .priority=8, .on_off=true, .valid=true,},       \
        {     .irq_n = TIM1_UP_TIM10_IRQn,       .priority=4, .on_off=true, .valid=true,},       \
        {     .irq_n = TIM1_TRG_COM_TIM11_IRQn,  .priority=4, .on_off=true, .valid=true,},  \
        {     .irq_n = TIM1_CC_IRQn,             .priority=4, .on_off=true, .valid=true,},

#else
#define INTERRUPT_CONFIG_TIMER
#endif


const InterruptConfig_t SECTION_CFG_DATA InterruptConfig[] ={
        {     .irq_n = USART3_IRQn, .priority = 1, .on_off = true, .valid = true,},
        {     .irq_n = ADC_IRQn, .priority = 1, .on_off = true, .valid = true,},
        INTERRUPT_CONFIG_CAN
        INTERRUPT_CONFIG_USB
        INTERRUPT_CONFIG_DMA_CHANNEL
        INTERRUPT_CONFIG_EXT_INT
        INTERRUPT_CONFIG_TIMER
};

uint32_t interrupt_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(InterruptConfig);
    return cnt;
}
