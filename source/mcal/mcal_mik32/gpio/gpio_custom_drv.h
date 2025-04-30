#ifndef GPIO_CUSTOM_DRV_H
#define GPIO_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "gpio_mcal.h"
#include "gpio_custom_const.h"
#include "gpio_custom_types.h"
#include "gpio_types.h"
#include "mik32_hal_gpio.h"

#ifdef HAS_EXT_INT
#include "ext_int_const.h"
#endif
//#include "mik32_hal.h"
#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

GpioSpeed_t GpioMik32SpeedToSpeed(GpioMik32Speed_t mik_speed);
GpioLogicLevel_t  GpioMik32LevelToLevel(GPIO_PinState pin_state);
HAL_GPIO_PullTypeDef GpioPullToMik32Pull(GpioPullMode_t pull_code);
HAL_GPIO_DSTypeDef GpioDriveSelToMik32DriveSel(GpioDriveSelect_t drive_select);
HAL_GPIO_ModeTypeDef GpioModeToMik32Mode(GpioApiMode_t mode);
HAL_GPIO_PullTypeDef GpioPull2Mik32Pull(GpioPullMode_t pull_code);
GpioDir_t GpioMik32DirToDir(HAL_GPIO_ModeTypeDef mode) ;
GpioApiMode_t GpioMik32ModeToMode(HAL_GPIO_ModeTypeDef mik_mode);
GpioPullMode_t GpioMik32Pull2GeneralPull(HAL_GPIO_PullTypeDef mik32_pull);
GPIO_PinState  GpioLevelToMik32Level(GpioLogicLevel_t level);

HAL_GPIO_ModeTypeDef gpio_get_mode(uint8_t pad_num);
GpioMik32Speed_t gpio_get_speed(uint8_t pad_num);
OutType_t gpio_get_out_type(uint8_t pad_num);
#ifdef HAS_EXT_INT
PinIntEdge_t pin_get_edge(uint8_t pin);
#endif
//PinInt_t* PinIntGetNode(uint16_t pad_num);
//Port_t PortLetter2PortNum(char port);
HAL_GPIO_ModeTypeDef gpio_mik_mode_get(uint8_t pad_num);
bool ext_int_reset_mask(uint32_t mask);
bool ext_int_set_mask(uint32_t mask);
//bool generate_sw_int(uint32_t mask);
//bool gpio_init_one(const GpioConfig_t* pinInstance);
bool gpio_set_state(uint8_t pad_num, GpioLogicLevel_t logic_level);
bool gpios_init(void);
bool is_edge_irq_en(uint8_t pad_num);
//bool pin_get_int(uint8_t pin);
//bool pin_get_int_pend(uint8_t pin);
uint32_t PinNum2PinMask(uint8_t pin_num);
uint32_t gpio_read(uint8_t pad_num);
uint8_t get_aux_num(uint8_t pad_num);
//uint8_t get_mcu_pin(uint8_t pad_num);
//uint8_t gpio_port_pin2pad(Port_t port, uint8_t pin);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_CUSTOM_DRV_H  */
