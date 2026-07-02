#ifndef GPIO_MCAL_API_H
#define GPIO_MCAL_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "gpio_config.h"
#include "gpio_types.h"

#ifdef HAS_GPIO_DIAG
#include "gpio_diag.h"
#endif

#ifdef HAS_GPIO_CUSTOM
#include "gpio_isr.h"
#endif

#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_drv.h"
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

/*API*/
const GpioConfig_t* gpio_get_config(const Pad_t pad);
#ifdef HAS_GPIO_CUSTOM
const GpioPortInfo_t* GpioGetPortInfo(const GpioPort_t port);
#endif
bool gpio_clock_init(void);
bool gpio_init_custom(void);
bool gpio_init_pad(const Pad_t Pad);
bool gpio_init_one(const GpioConfig_t* const Config);
bool gpio_init_out(const Pad_t Pad);
bool gpio_init_out_pad(const Pad_t Pad);
bool gpio_mcal_init(void); //gpio_init-busy name
bool gpio_deinit_pad(const Pad_t Pad);
bool gpio_init_adc_pad(const Pad_t Pad);
bool gpio_init_ext_int(const Pad_t Pad);

bool gpio_proc(void);
bool gpio_proc_one(const GpioConfig_t* const Config);
uint32_t num_exint_line(uint8_t num);

/*Set*/
bool gpio_pad_mux_set(const Pad_t Pad,const uint8_t mux);
bool gpio_pin_mux_set(GpioPort_t port, uint8_t pin, uint8_t mux);
bool gpio_dir_set(Pad_t Pad, GpioDir_t dir);
bool gpio_mode_set(const Pad_t Pad, const GpioApiMode_t mode);
bool gpio_pull_set(Pad_t Pad, GpioPullMode_t pull_code);
bool gpio_logic_level_set(Pad_t Pad, GpioLogicLevel_t logic_level);
bool gpio_set_state_verify(Pad_t Pad, GpioLogicLevel_t logic_level);
bool gpio_toggle(const Pad_t Pad);
#ifdef HAS_MULTICORE
//bool gpio_set_pin_mcu(Pad_t Pad, GpioPinMcuSel_t mcu_sel);
#endif /*HAS_MULTICORE*/

/*Get*/
uint8_t gpio_port_cnt_get(void);
GpioApiMode_t gpio_pin_mux_to_mode(const uint8_t mux);
bool GpioIsValidConfig(const GpioConfig_t* const Config);
uint32_t GpioPinNumToPinMask(uint8_t pin_num);
GpioLogicLevel_t gpio_get_state_short(const Pad_t pad);
#ifdef HAS_GPIO_EXT
bool gpio_get_state(Pad_t Pad, GpioLogicLevel_t* const logic_level);
bool gpio_pin_mux_get(const Pad_t Pad, uint8_t* const mux);
bool gpio_pin_fun_get(Pad_t Pad, GpioPinFunction_t* const function);
bool gpio_is_valid_pad(Pad_t Pad);
bool gpio_is_valid_mode(GpioApiMode_t mode);
bool gpio_is_valid_pull(GpioPullMode_t pull);
bool pin_get_int_pend(uint8_t pin);
bool pin_get_int(uint8_t pin);
//PinInt_t* PinIntGetNode(uint16_t gpio_pin);
GpioApiMode_t gpio_mode_get(Pad_t Pad);
GpioDir_t gpio_dir_get(const Pad_t Pad);
GpioLogicLevel_t gpio_opposite_level_get(GpioLogicLevel_t origin_ll);
GpioPullMode_t gpio_pull_get(const Pad_t Pad);
GpioSpeed_t gpio_speed_get(Pad_t Pad);
uint32_t port_reg_cnt(void);
uint32_t gpio_reg_cnt(void);
//GpioPort_t PortLetter2PortNum(char port);
//PinIntEdge_t pin_get_edge(uint8_t pin);
bool gpio_is_pin_single(const Pad_t Pad);
#endif

/*TODO rename to gpio_get_logic_level*/
bool parse_pad(char* argv[], Pad_t* pad);
const char* GpioGetCon1(Pad_t Pad);
const char* GpioGetCon2(Pad_t Pad);
uint8_t gpio_padval_2pin(Pad_t Pad);
uint8_t gpio_padval_2port(Pad_t Pad);
uint8_t gpio_port_pin2pad(GpioPort_t port, uint8_t pin);
uint8_t pad_assign(Pad_t Pad, char* wire_name);

bool GpioProcReadLow(GpioLogicLevel_t active);
bool GpioProcReadHi(GpioLogicLevel_t active);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_MCAL_API_H  */
