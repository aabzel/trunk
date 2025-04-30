#ifndef CONTROL_COMMANDS_H
#define CONTROL_COMMANDS_H

#ifdef HAS_LOG
#include "log.h"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_CONTROL
#error "+HAS_CONTROL"
#endif

#ifndef HAS_CONTROL_COMMANDS
#error "+HAS_CONTROL_COMMANDS"
#endif

#ifdef HAS_LED_MONO_COMMANDS
#include "led_mono_commands.h"
#else
#define LED_MONO_COMMANDS
#endif

#ifdef HAS_GENERIC_COMMANDS
#include "generic_commands.h"
#else
#define GENERIC_COMMANDS
#endif

#ifdef HAS_SCRIPT_COMMANDS
#include "script_commands.h"
#else
#define SCRIPT_COMMANDS
#endif

#ifdef HAS_LED_RGB_COMMANDS
#include "led_rgb_commands.h"
#else
#define LED_RGB_COMMANDS
#endif

#ifdef HAS_INTERRUPT_COMMANDS
#include "interrupt_commands.h"
#else
#define INTERRUPT_COMMANDS
#endif

#ifdef HAS_PID_COMMANDS
#include "pid_commands.h"
#else
#define PID_COMMANDS
#endif

#ifdef HAS_FREE_RTOS_COMMANDS
#include "free_rtos_commands.h"
#else
#define FREE_RTOS_COMMANDS
#endif

#ifdef HAS_IWDG_COMMANDS
#include "iwdg_commands.h"
#else
#define IWDG_COMMANDS
#endif

#ifdef HAS_WDT_COMMANDS
#include "watchdog_commands.h"
#else
#define WDT_COMMANDS
#endif

#ifdef HAS_CORE_COMMANDS
#include "core_commands.h"
#else
#define CORE_COMMANDS
#endif

#ifdef HAS_AUDIO_USB_COMMANDS
#include "audio_usb_commands.h"
#else
#define AUDIO_USB_COMMANDS
#endif

#ifdef HAS_DISPLAY_COMMANDS
#include "display_commands.h"
#else
#define DISPLAY_COMMANDS
#endif

#ifdef HAS_DAC_COMMANDS
#include "dac_commands.h"
#else
#define DAC_COMMANDS
#endif

#ifdef HAS_DAC_COMMANDS
#include "dac_commands.h"
#else
#define DAC_COMMANDS
#endif

#ifdef HAS_I2S_COMMANDS
#include "i2s_commands.h"
#else
#define I2S_COMMANDS
#endif

#ifdef HAS_RDS_COMMANDS
#include "rds_commands.h"
#else
#define RDS_COMMANDS
#endif

#ifdef HAS_ANT_MUX_COMMANDS
#include "aerial_mux_commands.h"
#else
#define ANT_MUX_COMMANDS
#endif

#ifdef HAS_CORE_COMMANDS
#include "core_commands.h"
#else
#define CORE_COMMANDS
#endif

#ifdef HAS_PWR_MUX_COMMANDS
#include "pwr_mux_commands.h"
#else
#define PWR_MUX_COMMANDS
#endif

#ifdef HAS_PWM_COMMANDS
#include "pwm_commands.h"
#else
#define PWM_COMMANDS
#endif

#ifdef HAS_RELAY_COMMANDS
#include "relay_commands.h"
#else
#define RELAY_COMMANDS
#endif

#ifdef HAS_SYSTEM_COMMANDS
#include "system_commands.h"
#else
#define SYSTEM_COMMANDS
#endif

#if defined(HAS_WM8731) && defined(HAS_BT1024)
bool cmd_action_bt1024_wm8731_fwd(int32_t argc, char* argv[]);

#define CONTROL_FWD_COMMANDS                                                              \
    SHELL_CMD("bt1026_wm8731_fwd", "bwf", cmd_action_bt1024_wm8731_fwd, "Bt1026Wm8731"),
#else
#define CONTROL_FWD_COMMANDS
#endif


#ifdef HAS_UNIT_TEST_COMMANDS
#include "unit_test_commands.h"
#else
#define UNIT_TEST_COMMANDS
#endif

#ifdef HAS_NVIC_COMMANDS
#include "nvic_commands.h"
#else
#define NVIC_COMMANDS
#endif

#ifdef HAS_SUPER_CYCLE_COMMANDS
#include "super_cycle_commands.h"
#else
#define SUPER_CYCLE_COMMANDS
#endif /*HAS_SUPER_CYCLE_COMMANDS*/

#ifdef HAS_MPU_COMMANDS
#include "mpu_commands.h"
#else
#define MPU_COMMANDS
#endif

#ifdef HAS_GPIO_PWM_COMMANDS
#include "gpio_pwm_commands.h"
#else
#define GPIO_PWM_COMMANDS
#endif

#ifdef HAS_DEBUGGER_COMMANDS
#include "debugger_commands.h"
#else
#define DEBUGGER_COMMANDS
#endif

#ifdef HAS_BOOT_COMMANDS
#include "boot_commands.h"
#else
#define BOOT_COMMANDS
#endif

#ifdef HAS_BOARD_COMMANDS
#include "board_commands.h"
#else
#define BOARD_COMMANDS
#endif

#ifdef HAS_BOOTLOADER_COMMANDS
#include "bootloader_commands.h"
#else
#define BOOTLOADER_COMMANDS
#endif

#ifdef HAS_BOARD_CUSTOM_COMMANDS
#include "board_custom_commands.h"
#else
#define BOARD_CUSTOM_COMMANDS
#endif

#ifdef HAS_PC_COMMANDS
#include "pc_commands.h"
#else
#define PC_COMMANDS
#endif /*HAS_PC_COMMANDS*/

#ifdef HAS_PWM_DAC_COMMANDS
#include "pwm_dac_commands.h"
#else
#define PWM_DAC_COMMANDS
#endif /*HAS_PWM_DAC_COMMANDS*/

#ifdef HAS_TASK_COMMANDS
#include "task_commands.h"
#else
#define TASK_COMMANDS
#endif /*HAS_TASK_COMMANDS*/

#define CONTROL_DIGITAL_COMMANDS

#define CONTROL_SOWTWARE_COMMANDS           \
    FREE_RTOS_COMMANDS                      \
    PID_COMMANDS                            \
    SUPER_CYCLE_COMMANDS                    \
    SCRIPT_COMMANDS                         \
    TASK_COMMANDS                           \
    PC_COMMANDS                             \
    CONTROL_FWD_COMMANDS                    \
    BOOT_COMMANDS                           \
    UNIT_TEST_COMMANDS                      \
    BOOTLOADER_COMMANDS                     \
    SYSTEM_COMMANDS                         \
    DEBUGGER_COMMANDS

#define CONTROL_HARDWARE_COMMANDS           \
    DAC_COMMANDS                            \
    PWR_MUX_COMMANDS                        \
    PWM_DAC_COMMANDS                        \
    DISPLAY_COMMANDS                        \
    LED_MONO_COMMANDS                       \
    LED_RGB_COMMANDS                        \
    GPIO_PWM_COMMANDS                       \
    RELAY_COMMANDS                          \
    INTERRUPT_COMMANDS                      \
    BOARD_COMMANDS                          \
    BOARD_CUSTOM_COMMANDS                   \
    CORE_COMMANDS                           \
    AUDIO_USB_COMMANDS                      \
    ANT_MUX_COMMANDS                        \
    NVIC_COMMANDS                           \
    MPU_COMMANDS                            \
    WDT_COMMANDS

#define CONTROL_COMMANDS                    \
    GENERIC_COMMANDS                        \
    CONTROL_HARDWARE_COMMANDS               \
    CONTROL_SOWTWARE_COMMANDS               \
    CONTROL_DIGITAL_COMMANDS


#endif /* CONTROL_COMMANDS_H */
