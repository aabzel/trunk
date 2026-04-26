#include "stm32f407ve_diag.h"

#ifdef HAS_INTERRUPT
#include "interrupt_types.h"

/*
  for command
 int_diag
 */
const IntNumInfo_t IntNumInfo[] = {
        {    .name="ADC", .int_n=ADC_IRQn, /*IRQn_Type*/},
        {    .name="DMA1_Stream0", .int_n=DMA1_Stream0_IRQn, /*IRQn_Type*/},
        {    .name="DMA1_Stream1", .int_n=DMA1_Stream1_IRQn, /*IRQn_Type*/},
        {    .name="DMA1_Stream2", .int_n=DMA1_Stream2_IRQn, /*IRQn_Type*/},
        {    .name="DMA1_Stream3", .int_n=DMA1_Stream3_IRQn, /*IRQn_Type*/},
        {    .name="DMA1_Stream4", .int_n=DMA1_Stream4_IRQn, /*IRQn_Type*/},
        {    .name="DMA1_Stream5", .int_n=DMA1_Stream5_IRQn, /*IRQn_Type*/},
        {    .name="DMA1_Stream6", .int_n=DMA1_Stream6_IRQn, /*IRQn_Type*/},
        {    .name="DMA1_Stream7", .int_n=DMA1_Stream7_IRQn, /*IRQn_Type*/},

        {    .name="DMA2_Stream0", .int_n=DMA2_Stream0_IRQn, /*IRQn_Type*/},
        {    .name="DMA2_Stream1", .int_n=DMA2_Stream1_IRQn, /*IRQn_Type*/},
        {    .name="DMA2_Stream2", .int_n=DMA2_Stream2_IRQn, /*IRQn_Type*/},
        {    .name="DMA2_Stream3", .int_n=DMA2_Stream3_IRQn, /*IRQn_Type*/},
        {    .name="DMA2_Stream4", .int_n=DMA2_Stream4_IRQn, /*IRQn_Type*/},
        {    .name="DMA2_Stream5", .int_n=DMA2_Stream5_IRQn, /*IRQn_Type*/},
        {    .name="DMA2_Stream6", .int_n=DMA2_Stream6_IRQn, /*IRQn_Type*/},
        {    .name="DMA2_Stream7", .int_n=DMA2_Stream7_IRQn, /*IRQn_Type*/},
        {    .name="TIM2", .int_n=TIM2_IRQn, /*IRQn_Type*/},
        {    .name="TIM3", .int_n=TIM3_IRQn, /*IRQn_Type*/},
        {    .name="TIM4", .int_n=TIM4_IRQn, /*IRQn_Type*/},
        {    .name="CAN1_TX", .int_n=CAN1_TX_IRQn, /*IRQn_Type*/},
        {    .name="CAN1_RX0", .int_n=CAN1_RX0_IRQn, /*IRQn_Type*/},
        {    .name="CAN1_RX1", .int_n=CAN1_RX1_IRQn, /*IRQn_Type*/},
        {    .name="CAN1_SCE", .int_n=CAN1_SCE_IRQn, /*IRQn_Type*/},
        {    .name="CAN2_TX",  .int_n=CAN2_TX_IRQn, /*IRQn_Type*/},
        {    .name="CAN2_RX0", .int_n=CAN2_RX0_IRQn, /*IRQn_Type*/},
        {    .name="CAN2_RX1", .int_n=CAN2_RX1_IRQn, /*IRQn_Type*/},
        {    .name="CAN2_SCE", .int_n=CAN2_SCE_IRQn, /*IRQn_Type*/},
        {    .name="USART1", .int_n=USART1_IRQn, /*IRQn_Type*/},
        {    .name="USART2", .int_n=USART2_IRQn, /*IRQn_Type*/},
        {    .name="USART3", .int_n=USART3_IRQn, /*IRQn_Type*/},
        {    .name="UART4", .int_n=UART4_IRQn, /*IRQn_Type*/},
        {    .name="UART5", .int_n=UART5_IRQn, /*IRQn_Type*/},
        {    .name="USART6", .int_n=USART6_IRQn, /*IRQn_Type*/},
        {    .name="RCC", .int_n=RCC_IRQn, /*IRQn_Type*/},
        {    .name="FLASH", .int_n=FLASH_IRQn, /*IRQn_Type*/},
};


uint32_t interrupt_info_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(IntNumInfo);
    return cnt;
}
#endif
