#ifndef GPIO_NRF53_CONST_H
#define GPIO_NRF53_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
    NRF_GPIO_PIN_MUX_APP=0,     /* Pin controlled by Application MCU. */
    NRF_GPIO_PIN_MUX_NET=1,     /* Pin controlled by Network MCU.*/
    NRF_GPIO_PIN_MUX_TRACE=7,  /* Pin controlled by Trace and Debug Subsystem.*/
    NRF_GPIO_PIN_MUX_UNDEF=2,
} GpioPinMcuSel_t;

#ifdef __cplusplus
}
#endif

#endif /* GPIO_NRF53_CONST_H  */
