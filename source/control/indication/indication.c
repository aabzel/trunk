#include "indication.h"

#include <stddef.h>

#include "data_utils.h"
#include "led_config.h"
#include "led_drv.h"
#include "system.h"

static const Intication_t InticationLut[] = {
    {
        .fw_type = BUILD_TYPE_UNDEF,
        .freq = 8.0,
        .duty = 25,
        .color = COLOR_RED,
    },
    {
        .fw_type = BUILD_TYPE_MBR,
        .freq = 8.0,
        .duty = 25,
        .color = COLOR_RED,
    },
    {
        .fw_type = BUILD_TYPE_BOOTLOADER,
        .freq = 4.0,
        .duty = 75,
        .color = COLOR_YELLOW,
    },
    {
        .fw_type = BUILD_TYPE_GENERIC,
        .freq = 0.1,
        .duty = 10,
        .color = COLOR_GREEN,
    },
    {
        .fw_type = BUILD_TYPE_GENERIC_APP,
        .freq = 1.0,
        .duty = 25,
        .color = COLOR_GREEN,
    },
    {
        .fw_type = BUILD_TYPE_GENERIC_NET,
        .freq = 1.0,
        .duty = 50,
        .color = COLOR_GREEN,
    },
};

static const Intication_t* GetIndication(BuildType_t fw_type) {
    const Intication_t* Node = NULL;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(InticationLut); i++) {
        if(InticationLut[i].fw_type == fw_type) {
            Node = &InticationLut[i];
            break;
        }
    }
    return Node;
}

bool indication_init(void) {
    bool res = false;
    BuildType_t prog_type = system_get_prog_type();
    const Intication_t* Intication = GetIndication(prog_type);
    if(Intication) {
        res = led_pwm(LED_HEARTBEAT_ID, Intication->freq, Intication->duty);
#ifdef HAS_LED_RGB
        res = led_rgb_set_color(LED_HEARTBEAT_ID, Intication->color);
#endif
    }
    return res;
}

bool indication_alarm(uint8_t led_num) {
    bool res = false;
    res = led_pwm(led_num, 4.0, 40);
#ifdef HAS_LED_RGB
    res = led_rgb_set_color(led_num, COLOR_RED);
#endif
    return res;
}
