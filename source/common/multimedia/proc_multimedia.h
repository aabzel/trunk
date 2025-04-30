#ifndef PROC_MULTIMEDIA_H
#define PROC_MULTIMEDIA_H

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_MULTIMEDIA
#error "+HAS_MULTIMEDIA"
#endif

#ifndef HAS_TASK
#warning "+HAS_TASK"
#endif

#ifdef HAS_LC3
#define LC3_INIT                                                                                                       \
    {                                                                                                                  \
        .init_function = lc3_init,                                                                                     \
        .name = "LC3",                                                                                                 \
    },
#else
#define LC3_INIT
#endif

#ifdef HAS_USB_TO_I2S
#define USB_TO_I2S_INIT                                                                                                \
    {                                                                                                                  \
        .init_function = usb_to_i2s_init,                                                                              \
        .name = "Usb>I2s",                                                                                             \
    },
#else
#define USB_TO_I2S_INIT
#endif /*HAS_USB_TO_I2S*/

#define MULTIMEDIA_INIT                                                                                                \
    LC3_INIT                                                                                                           \
    USB_TO_I2S_INIT

bool play_1kHz_tone(uint8_t i2s_num, uint8_t dac_num, double amplitude, double phase);
void super_cycle_multimedia(uint64_t loop_start_time_us);
bool multimedia_init(void);

#endif /* PROC_MULTIMEDIA_H */
