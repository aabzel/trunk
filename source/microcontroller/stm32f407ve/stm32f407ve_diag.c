#include "stm32f407ve_diag.h"

#ifdef HAS_INTERRUPT
#include "interrupt_types.h"

/*
  for command
 int_diag
 */
const IntNumInfo_t IntNumInfo[] = {
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
