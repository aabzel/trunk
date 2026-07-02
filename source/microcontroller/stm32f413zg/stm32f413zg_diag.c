#include "stm32f413zg_diag.h"

#ifdef HAS_INTERRUPT
#include "interrupt_types.h"

/*
  for command
 int_diag
 */
const IntNumInfo_t IntNumInfo[] = {
        {    .name="SPI1", .int_n=SPI1_IRQn,},
        {    .name="SPI2", .int_n=SPI2_IRQn,},
        {    .name="SPI3", .int_n=SPI3_IRQn,},
        {    .name="SPI4", .int_n=SPI4_IRQn,},
        {    .name="SPI5", .int_n=SPI5_IRQn,},
        {    .name="ADC", .int_n=ADC_IRQn, },
        {    .name="USART1", .int_n=USART1_IRQn, },
        {    .name="USART2", .int_n=USART2_IRQn, },
        {    .name="USART3", .int_n=USART3_IRQn, },
        {    .name="UART4", .int_n=UART4_IRQn, },
        {    .name="UART5", .int_n=UART5_IRQn, },
        {    .name="USART6", .int_n=USART6_IRQn, },
        {    .name="DMA1_Stream0", .int_n=DMA1_Stream0_IRQn, },
        {    .name="DMA1_Stream1", .int_n=DMA1_Stream1_IRQn, },
        {    .name="DMA1_Stream2", .int_n=DMA1_Stream2_IRQn, },
        {    .name="DMA1_Stream3", .int_n=DMA1_Stream3_IRQn, },
        {    .name="DMA1_Stream4", .int_n=DMA1_Stream4_IRQn, },
        {    .name="DMA1_Stream5", .int_n=DMA1_Stream5_IRQn, },
        {    .name="DMA1_Stream6", .int_n=DMA1_Stream6_IRQn, },
        {    .name="DMA1_Stream7", .int_n=DMA1_Stream7_IRQn, },
        {    .name="DMA2_Stream0", .int_n=DMA2_Stream0_IRQn, },
        {    .name="DMA2_Stream1", .int_n=DMA2_Stream1_IRQn, },
        {    .name="DMA2_Stream2", .int_n=DMA2_Stream2_IRQn, },
        {    .name="DMA2_Stream3", .int_n=DMA2_Stream3_IRQn, },
        {    .name="DMA2_Stream4", .int_n=DMA2_Stream4_IRQn, },
        {    .name="DMA2_Stream5", .int_n=DMA2_Stream5_IRQn, },
        {    .name="DMA2_Stream6", .int_n=DMA2_Stream6_IRQn, },
        {    .name="DMA2_Stream7", .int_n=DMA2_Stream7_IRQn, },

        {    .name="TIM2", .int_n=TIM2_IRQn, },
        {    .name="TIM3", .int_n=TIM3_IRQn, },
        {    .name="TIM4", .int_n=TIM4_IRQn, },
        {    .name="CAN1_TX", .int_n=CAN1_TX_IRQn, },
        {    .name="CAN1_RX0", .int_n=CAN1_RX0_IRQn, },
        {    .name="CAN1_RX1", .int_n=CAN1_RX1_IRQn, },
        {    .name="CAN1_SCE", .int_n=CAN1_SCE_IRQn, },
        {    .name="CAN2_TX",  .int_n=CAN2_TX_IRQn, },
        {    .name="CAN2_RX0", .int_n=CAN2_RX0_IRQn, },
        {    .name="CAN2_RX1", .int_n=CAN2_RX1_IRQn, },
        {    .name="CAN2_SCE", .int_n=CAN2_SCE_IRQn, },
        {    .name="RCC", .int_n=RCC_IRQn, },
        {    .name="FLASH", .int_n=FLASH_IRQn, },
#if 0
#endif
};


uint32_t interrupt_info_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(IntNumInfo);
    return cnt;
}
#endif
