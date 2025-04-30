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
#else
typedef uint8_t Port_t;
#endif

#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_drv.h"
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif


/*API*/
#ifdef HAS_GPIO_CUSTOM
const GpioInfo_t* GpioGetInfo(Port_t port);
#endif
bool gpio_clock_init(void);
bool gpio_init_custom(void);
bool gpio_mcal_init(void); //gpio_init-busy name
bool gpio_init_one(const GpioConfig_t* const Config);
bool gpio_proc(void);
bool gpio_proc_one(const GpioConfig_t* const Config);
bool gpio_deinit_one(Pad_t Pad);
uint32_t num_exint_line(uint8_t num);

/*Set*/
//bool generate_sw_int(uint32_t mask);
bool gpio_pin_mux_set(Port_t port, uint8_t pin , uint8_t mux   );
bool gpio_dir_set(uint8_t pad_num, GpioDir_t dir);
bool gpio_mode_set(Pad_t Pad, GpioApiMode_t mode);
bool gpio_pull_set(Pad_t Pad, GpioPullMode_t pull_code);
bool gpio_logic_level_set(Pad_t Pad, GpioLogicLevel_t logic_level);
bool gpio_set_state_verify(uint8_t pad_num, GpioLogicLevel_t logic_level);
bool gpio_toggle(const Pad_t Pad);
#ifdef HAS_MULTICORE
bool gpio_set_pin_mcu(Pad_t Pad, GpioPinMcuSel_t mcu_sel);
#endif /*HAS_MULTICORE*/

/*Get*/
#ifdef HAS_GPIO_EXT
bool gpio_is_valid_pad(uint8_t pad_num);
bool pin_get_int_pend(uint8_t pin);
bool pin_get_int(uint8_t pin);
bool gpio_pin_mux_get(uint8_t port, uint8_t pin , uint8_t* const mux);
bool gpio_pin_fun_get(Pad_t Pad, GpioPinFunction_t* const function);
bool gpio_get_state(uint8_t pad_num, GpioLogicLevel_t* const logic_level);
bool gpio_is_valid_mode(GpioApiMode_t mode);
bool gpio_is_valid_pull(GpioPullMode_t pull);
PinInt_t* PinIntGetNode(uint16_t gpio_pin);
GpioDir_t gpio_dir_get(uint8_t pad_num);
GpioSpeed_t gpio_speed_get(uint8_t pad_num);
GpioApiMode_t gpio_mode_get(uint8_t pad_num);
GpioPullMode_t gpio_pull_get(uint8_t pad_num);
//Port_t PortLetter2PortNum(char port);
GpioLogicLevel_t gpio_opposite_level_get(GpioLogicLevel_t origin_ll);
//PinIntEdge_t pin_get_edge(uint8_t pin);
bool gpio_is_pin_single(uint8_t byte);
#endif


/*TODO rename to gpio_get_logic_level*/
//bool gpio_is_valid_pad(uint8_t pad_num);
bool parse_pad(char* argv[], Pad_t* pad);
const char* GpioGetCon1(uint8_t pad);
const char* GpioGetCon2(uint8_t pad);
const GpioConfig_t* gpio_get_config(Pad_t pad);
uint8_t get_mcu_pin(uint8_t io_pin);
uint8_t gpio_padval_2pin(uint8_t pad_val);
uint8_t gpio_padval_2port(uint8_t pad_val);
uint8_t gpio_port_pin2pad(Port_t port, uint8_t pin);
uint8_t pad_assign(uint8_t pad_num, char* wire_name);

bool GpioProcReadLow(GpioLogicLevel_t active);
bool GpioProcReadHi(GpioLogicLevel_t active);



#ifdef __cplusplus
}
#endif

#endif /* GPIO_MCAL_API_H  */
