#include "common_functions.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#ifdef HAS_SYSTEM
#include "system.h"
#endif

#ifdef HAS_ARRAY
#include "array.h"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_INTERRUPT
#include "interrupt_mcal.h"
#endif

#ifdef HAS_INTERFACES
#include "interface_drv.h"
#endif /*HAS_INTERFACES*/

#ifdef HAS_MULTIMEDIA
#include "proc_multimedia.h"
#endif /*HAS_MULTIMEDIA*/

#ifdef HAS_SYSTICK
#include "systick_mcal.h"
#endif

#ifdef HAS_CONNECTIVITY
#include "proc_connectivity.h"
#endif

#ifdef HAS_CLOCK
#include "clock.h"
#endif

#ifdef HAS_SOFTWARE_TIMER
#include "software_timer.h"
#endif /*HAS_SOFTWARE_TIMER*/

#ifdef HAS_SUPER_CYCLE
#include "super_cycle.h"
#endif /*HAS_SUPER_CYCLE*/

#if defined(HAS_RTOS_TASKS) && defined(HAS_SUPER_CYCLE)
#error "BareMetal scheduler can not work simultaneously with RTOS scheduler"
#endif /*HAS_RTOS_TASKS HAS_SUPER_CYCLE*/

#ifdef HAS_LOG_UTILS
#include "writer_generic.h"
#endif

#ifdef HAS_FREE_RTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

#ifdef HAS_GARBAGE_COLLECTOR
#include "garbage_collector.h"
#endif /*HAS_GARBAGE_COLLECTOR*/

#ifdef HAS_SW_DAC
#include "sw_dac_drv.h"
#endif /*HAS_SW_DAC*/

#ifdef HAS_MBR
#include "mbr_drv.h"
#endif /*HAS_MBR*/

#ifdef HAS_DMA
#include "dma_mcal.h"
#endif /*HAS_DMA*/

#ifdef HAS_SOFTWARE_TIMER
#include "software_timer.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_ADC
#include "adc_mcal.h"
#endif /*HAS_ADC*/

#ifdef HAS_APPLICATIONS
//#include "applications_proc.h"
#endif /*HAS_APPLICATIONS*/

#ifdef HAS_LED
#include "led_drv.h"
#endif /*HAS_LED*/

#ifdef HAS_LED_RGB
#include "led_rgb_drv.h"
#endif /*HAS_LED_RGB*/

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifdef HAS_BOOT
#include "boot_driver.h"
#endif

#ifdef HAS_SENSITIVITY
#include "sensitivity_init.h"
#endif

#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif

#ifdef HAS_DAC
#include "dac_drv.h"
#endif /*HAS_DAC*/

#ifdef HAS_GPIO
#include "gpio_mcal.h"
#endif

#ifdef HAS_GPIO_PWM
#include "gpio_pwm_drv.h"
#endif /*HAS_GPIO_PWM*/

#ifdef HAS_HEALTH_MONITOR
#include "health_monitor.h"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif /*HAS_CORE*/

#ifdef HAS_MCU
#include "hw_init.h"
#endif /*HAS_MCU*/

#ifdef HAS_LOG
#include "log.h"
#endif /*HAS_LOG*/

#include "sw_init.h"

#ifdef HAS_MCU
#include "board_config.h"
//#include "sys_config.h"
#endif

#ifdef HAS_TASK
#include "task_info.h"
#endif

#ifdef HAS_FLASH_FS
#include "flash_fs.h"
#endif /*HAS_FLASH_FS*/

#ifdef HAS_USB

#ifdef HAS_USB_DEVICE
#include "usb_device.h"
#endif /*HAS_USB_DEVICE*/

#ifdef HAS_SYSTICK
#include "systick_mcal.h"
#endif

#ifdef HAS_USB_HOST
//#include "usb_host.h"
#endif /*HAS_USB_HOST*/

#endif /*HAS_USB*/

#ifdef HAS_IWDG
//#include "iwdg_drv.h"
#endif /*HAS_WDT*/

#ifdef HAS_WIN_UTILS
#include "win_utils.h"
#endif

#if defined(HAS_NORTOS) && defined(HAS_GENERIC) && !defined(HAS_STRING_READER_PROC)
#warning "NoRTOS Generic Firmware should contain STRING_READER"
#endif /**/

#if defined(HAS_NORTOS) && defined(HAS_BOOTLOADER) && !defined(HAS_STRING_READER_PROC)
#warning "NoRTOS Generic Firmware should contain STRING_READER"
#endif /**/

#ifdef HAS_SUPER_CYCLE
void super_cycle_proc(uint64_t loop_start_time_us) {

#ifdef HAS_TASK
    tasks_proc(loop_start_time_us);
#endif // HAS_TASK
}
#endif /*HAS_SUPER_CYCLE*/

bool try_init(bool status, char* message) {
    if(false == status) {
#ifdef HAS_LOG
        LOG_ERROR(HMON, "Init %s Error", message);
#endif

#ifdef HAS_HEALTH_MONITOR
        HealthMon.init_error = true;
        HealthMon.init_error_cnt++;

        uint32_t rem = ERR_MSG_SIZE - strlen(HealthMon.error_messege);
        if(strlen(message) < rem) {
            bool res = false;

            res = array_add_front((uint8_t*)HealthMon.error_messege, ERR_MSG_SIZE, (uint8_t*)">", 1);
            if(res) {
                res = array_add_front((uint8_t*)HealthMon.error_messege, ERR_MSG_SIZE, (uint8_t*)message,
                                      strlen(message));
                HealthMon.error_messege[ERR_MSG_SIZE - 1] = 0x00;
            }
            // sprintf(HealthMon.error_messege, "%s>%s", HealthMon.error_messege, message); /*Ok*/
            // res= array_add_front(HealthMon.error_messege,strlen(HealthMon.error_messege)+1,message, strlen(message));
            // sprintf(HealthMon.error_messege, "%s_%s", message, HealthMon.error_messege ); /*DoesNotWork*/
        }
#endif /*HAS_HEALTH_MONITOR*/
    } else {
#ifdef HAS_LOG
        LOG_INFO(HMON, "Init %s OK", message);
#endif
    }
    return status;
}
