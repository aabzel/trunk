#ifndef GPIO_CUSTOM_TYPES_H
#define GPIO_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "x86x.h"
#include "gpio_custom_const.h"
#include "microcontroller_drv.h"
#include "module_gpio_regs.h"
#include "module_driver_port.h"
#include "module_driver_gpio.h"

#define GPIO_CUSTOM_INFO           \
    GPIO_Type * GPIOx;             \
    PORT_InstanceType instance_type;   \
    GPIO_InstanceType gpio_instance_type;

typedef struct {
	GPIO_CUSTOM_INFO
	uint32_t* PINx;
    bool valid;
    GpioPort_t port;
    uint32_t clock_type;
#ifdef HAS_X86
    //scfg_port_source_type port_source;/*System configuration controller*/
#else
    uint8_t port_source;/*System configuration controller*/
#endif
}GpioPortInfo_t;


typedef struct {
    GpioPort_t port;
    bool valid;
}GpioInfo_t;

typedef struct {
    GpioPinFunction_t func;
    GpioApiMode_t mode;
    GpioDir_t dir;
   // GpioType_t type;
    GpioFc7300xOutIOFCy_t IOFCy;
    GpioFc7300x_IOMCy_t IOMCy;
}GpioFc7300xModeInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* GPIO_CUSTOM_TYPES_H  */
