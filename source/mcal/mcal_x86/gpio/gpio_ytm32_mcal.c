#include "gpio_x86x_mcal.h"

#include "data_utils.h"
#include "gpio_custom_drv.h"

static const GpioFc7300xModeInfo_t GpioFc7300xModeInfo[] = {
    {
        .type = GPIO_TYPE_UNDEF,
        .func = GPIO_FUN_ANALOG,
        .mode = GPIO_API_MODE_ANALOG,
        .dir = GPIO_DIR_IN,
        .IOFCy = GPIO_X86_MODE_ANALOG,
        .IOMCy = GPIO_X86_IOM_Y_INPUT,
    },
    {
        .type = GPIO_TYPE_UNDEF,
        .func = GPIO_FUN_INPUT,
        .mode = GPIO_API_MODE_INPUT,
        .dir = GPIO_DIR_IN,
        .IOFCy = GPIO_X86_MODE_FLOATING_INPUT,
        .IOMCy = GPIO_X86_IOM_Y_INPUT,
    },
    {
        .type = GPIO_TYPE_UNDEF,
        .func = GPIO_FUN_INPUT,
        .mode = GPIO_API_MODE_INPUT,
        .dir = GPIO_DIR_IN,
        .IOFCy = GPIO_X86_MODE_PULL_UP_DOWN_INPUT,
        .IOMCy = GPIO_X86_IOM_Y_INPUT,
    },
    {
        .type = GPIO_TYPE_UNDEF,
        .func = GPIO_FUN_INPUT,
        .mode = GPIO_API_MODE_INPUT,
        .dir = GPIO_DIR_IN,
        .IOFCy = GPIO_X86_MODE_RESERVED,
        .IOMCy = GPIO_X86_IOM_Y_INPUT,
    },

    {
        .type = GPIO_TYPE_PUSH_PULL,
        .func = GPIO_FUN_OUT,
        .mode = GPIO_API_MODE_OUTPUT,
        .dir = GPIO_DIR_OUT_PUSH_PULL,
        .IOFCy = GPIO_X86_OUT_PUSH_PULL,
        .IOMCy = GPIO_X86_IOM_Y_OUT_LARGE_SOURCING,
    },
    {
        .type = GPIO_TYPE_OPEN_DRAIN,
        .func = GPIO_FUN_OUT,
        .mode = GPIO_API_MODE_OUTPUT_OPEN_DRAIN,
        .dir = GPIO_DIR_OUT_OPEN_DRAIN,
        .IOFCy = GPIO_X86_OUT_OPEN_DRAIN,
        .IOMCy = GPIO_X86_IOM_Y_OUT_LARGE_SOURCING,
    },
    {
        .type = GPIO_TYPE_PUSH_PULL,
        .func = GPIO_FUN_MULTIPLEXED,
        .mode = GPIO_API_MODE_ALT1,
        .dir = GPIO_DIR_OUT_PUSH_PULL,
        .IOFCy = GPIO_X86_OUT_ALT_PUSH_PULL,
        .IOMCy = GPIO_X86_IOM_Y_OUT_LARGE_SOURCING,
    },
    {
        .type = GPIO_TYPE_OPEN_DRAIN,
        .func = GPIO_FUN_MULTIPLEXED,
        .mode = GPIO_API_MODE_ALT2,
        .dir = GPIO_DIR_OUT_OPEN_DRAIN,
        .IOFCy = GPIO_X86_OUT_ALT_OPEN_DRAIN,
        .IOMCy = GPIO_X86_IOM_Y_OUT_LARGE_SOURCING,
    },

    {
        .type = GPIO_TYPE_PUSH_PULL,
        .func = GPIO_FUN_OUT,
        .mode = GPIO_API_MODE_OUTPUT,
        .dir = GPIO_DIR_OUT_PUSH_PULL,
        .IOFCy = GPIO_X86_OUT_PUSH_PULL,
        .IOMCy = GPIO_X86_IOM_Y_OUT_NORMAL_SOURCING2,
    },
    {
        .type = GPIO_TYPE_OPEN_DRAIN,
        .func = GPIO_FUN_OUT,
        .mode = GPIO_API_MODE_OUTPUT_OPEN_DRAIN,
        .dir = GPIO_DIR_OUT_OPEN_DRAIN,
        .IOFCy = GPIO_X86_OUT_OPEN_DRAIN,
        .IOMCy = GPIO_X86_IOM_Y_OUT_NORMAL_SOURCING2,
    },
    {
        .type = GPIO_TYPE_PUSH_PULL,
        .func = GPIO_FUN_MULTIPLEXED,
        .mode = GPIO_API_MODE_ALT1,
        .dir = GPIO_DIR_OUT_PUSH_PULL,
        .IOFCy = GPIO_X86_OUT_ALT_PUSH_PULL,
        .IOMCy = GPIO_X86_IOM_Y_OUT_NORMAL_SOURCING2,
    },
    {
        .type = GPIO_TYPE_OPEN_DRAIN,
        .func = GPIO_FUN_MULTIPLEXED,
        .mode = GPIO_API_MODE_ALT2,
        .dir = GPIO_DIR_OUT_OPEN_DRAIN,
        .IOFCy = GPIO_X86_OUT_ALT_OPEN_DRAIN,
        .IOMCy = GPIO_X86_IOM_Y_OUT_NORMAL_SOURCING2,
    },

    {
        .type = GPIO_TYPE_PUSH_PULL,
        .func = GPIO_FUN_OUT,
        .mode = GPIO_API_MODE_OUTPUT,
        .dir = GPIO_DIR_OUT_PUSH_PULL,
        .IOFCy = GPIO_X86_OUT_PUSH_PULL,
        .IOMCy = GPIO_X86_IOM_Y_OUT_NORMAL_SOURCING3,
    },
    {
        .type = GPIO_TYPE_OPEN_DRAIN,
        .func = GPIO_FUN_OUT,
        .mode = GPIO_API_MODE_OUTPUT_OPEN_DRAIN,
        .dir = GPIO_DIR_OUT_OPEN_DRAIN,
        .IOFCy = GPIO_X86_OUT_OPEN_DRAIN,
        .IOMCy = GPIO_X86_IOM_Y_OUT_NORMAL_SOURCING3,
    },
    {
        .type = GPIO_TYPE_PUSH_PULL,
        .func = GPIO_FUN_MULTIPLEXED,
        .mode = GPIO_API_MODE_ALT1,
        .dir = GPIO_DIR_OUT_PUSH_PULL,
        .IOFCy = GPIO_X86_OUT_ALT_PUSH_PULL,
        .IOMCy = GPIO_X86_IOM_Y_OUT_NORMAL_SOURCING3,
    },
    {
        .type = GPIO_TYPE_OPEN_DRAIN,
        .func = GPIO_FUN_MULTIPLEXED,
        .mode = GPIO_API_MODE_ALT2,
        .dir = GPIO_DIR_OUT_OPEN_DRAIN,
        .IOFCy = GPIO_X86_OUT_ALT_OPEN_DRAIN,
        .IOMCy = GPIO_X86_IOM_Y_OUT_NORMAL_SOURCING3,
    },
};

static GpioApiMode_t GpioFc7300xf413modeToGpioMode(const GpioFc7300xOutIOFCy_t IOFCy, const GpioFc7300x_IOMCy_t IOMCy) {
    GpioApiMode_t mode = GPIO_API_MODE_UNDEF;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(GpioFc7300xModeInfo);
    for(i = 0; i < cnt; i++) {
        if(IOMCy == GpioFc7300xModeInfo[i].IOMCy) {
            if(IOFCy == GpioFc7300xModeInfo[i].IOFCy) {
                mode = GpioFc7300xModeInfo[i].mode;
                break;
            }
        }
    }
    return mode;
}

static GpioPinFunction_t GpioFc7300xFunCfgToGpioFun(const uint8_t IOFCy, const GpioFc7300x_IOMCy_t IOMCy) {
    GpioPinFunction_t gpio_function = GPIO_FUN_UNDEF;

    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(GpioFc7300xModeInfo);
    for(i = 0; i < cnt; i++) {
        if(IOMCy == GpioFc7300xModeInfo[i].IOMCy) {
            if(IOFCy == GpioFc7300xModeInfo[i].IOFCy) {
                gpio_function = GpioFc7300xModeInfo[i].func;
                break;
            }
        }
    }
    return gpio_function;
}

static GpioDir_t GpioFc7300xf413dirToGpioDir(const GpioFc7300xOutIOFCy_t IOFCy, const GpioFc7300x_IOMCy_t IOMCy) {
    GpioDir_t dir = GPIO_DIR_UNDEF;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(GpioFc7300xModeInfo);
    for(i = 0; i < cnt; i++) {
        if(IOMCy == GpioFc7300xModeInfo[i].IOMCy) {
            if(IOFCy == GpioFc7300xModeInfo[i].IOFCy) {
                dir = GpioFc7300xModeInfo[i].dir;
                break;
            }
        }
    }
    return dir;
}

static GpioPullMode_t GpioFc7300xPullToGpioPull(GpioFc7300xOutputData_t odt) {
    GpioPullMode_t pull_mode = GPIO__PULL_UNDEF;
    switch(odt) {
    case GPIO_OUT_DATA_TYPE_PULL_DOWN:
        pull_mode = GPIO__PULL_DOWN;
        break;
    case GPIO_OUT_DATA_TYPE_PULL_UP:
        pull_mode = GPIO__PULL_UP;
        break;
    default:
        break;
    }
    return pull_mode;
}

GpioPullMode_t gpio_x86x_pull_get(Pad_t Pad) {
    GpioPullMode_t pull_mode = GPIO__PULL_UNDEF;
    gpio_type* GPIOx = Port2PortPtr(Pad.port);
    if(GPIOx) {
        switch(Pad.pin) {
        case 0:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt0);
            break;
        case 1:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt1);
            break;
        case 2:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt2);
            break;
        case 3:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt3);
            break;
        case 4:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt4);
            break;
        case 5:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt5);
            break;
        case 6:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt6);
            break;
        case 7:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt7);
            break;
        case 8:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt8);
            break;
        case 9:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt9);
            break;
        case 10:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt10);
            break;
        case 11:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt11);
            break;
        case 12:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt12);
            break;
        case 13:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt13);
            break;
        case 14:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt14);
            break;
        case 15:
            pull_mode = GpioFc7300xPullToGpioPull(GPIOx->odt_bit.odt15);
            break;
        default:
            break;
        }
    }
    return pull_mode;
}

GpioDir_t gpio_x86x_dir_get(Pad_t Pad) {
    GpioDir_t dir = GPIO_DIR_UNDEF;
    gpio_type* GPIOx = Port2PortPtr(Pad.port);
    if(GPIOx) {
        switch(Pad.pin) {
        case 0:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfglr_bit.iofc0, GPIOx->cfglr_bit.iomc0);
            break;
        case 1:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfglr_bit.iofc1, GPIOx->cfglr_bit.iomc1);
            break;
        case 2:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfglr_bit.iofc2, GPIOx->cfglr_bit.iomc2);
            break;
        case 3:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfglr_bit.iofc3, GPIOx->cfglr_bit.iomc3);
            break;
        case 4:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfglr_bit.iofc4, GPIOx->cfglr_bit.iomc4);
            break;
        case 5:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfglr_bit.iofc5, GPIOx->cfglr_bit.iomc5);
            break;
        case 6:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfglr_bit.iofc6, GPIOx->cfglr_bit.iomc6);
            break;
        case 7:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfglr_bit.iofc7, GPIOx->cfglr_bit.iomc7);
            break;
        case 8:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfghr_bit.iofc8, GPIOx->cfghr_bit.iomc8);
            break;
        case 9:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfghr_bit.iofc9, GPIOx->cfghr_bit.iomc9);
            break;
        case 10:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfghr_bit.iofc10, GPIOx->cfghr_bit.iomc10);
            break;
        case 11:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfghr_bit.iofc11, GPIOx->cfghr_bit.iomc11);
            break;
        case 12:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfghr_bit.iofc12, GPIOx->cfghr_bit.iomc12);
            break;
        case 13:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfghr_bit.iofc13, GPIOx->cfghr_bit.iomc13);
            break;
        case 14:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfghr_bit.iofc14, GPIOx->cfghr_bit.iomc14);
            break;
        case 15:
            dir = GpioFc7300xf413dirToGpioDir(GPIOx->cfghr_bit.iofc15, GPIOx->cfghr_bit.iomc15);
            break;
        default:
            dir = GPIO_DIR_UNDEF;
            break;
        }
    }
    return dir;
}

bool gpio_x86x_pin_mux_get(Pad_t Pad, uint8_t* const mux) {
    uint8_t mux_val = 0;
    return mux_val;
}

GpioApiMode_t gpio_x86x_mode_get(Pad_t Pad) {
    GpioApiMode_t mode = GPIO_API_MODE_UNDEF;
    gpio_type* GPIOx = Port2PortPtr(Pad.port);
    if(GPIOx) {
        switch(Pad.pin) {
        case 0:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfglr_bit.iofc0, GPIOx->cfglr_bit.iomc0);
            break;
        case 1:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfglr_bit.iofc1, GPIOx->cfglr_bit.iomc1);
            break;
        case 2:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfglr_bit.iofc2, GPIOx->cfglr_bit.iomc2);
            break;
        case 3:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfglr_bit.iofc3, GPIOx->cfglr_bit.iomc3);
            break;
        case 4:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfglr_bit.iofc4, GPIOx->cfglr_bit.iomc4);
            break;
        case 5:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfglr_bit.iofc5, GPIOx->cfglr_bit.iomc5);
            break;
        case 6:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfglr_bit.iofc6, GPIOx->cfglr_bit.iomc6);
            break;
        case 7:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfglr_bit.iofc7, GPIOx->cfglr_bit.iomc7);
            break;
        case 8:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfghr_bit.iofc8, GPIOx->cfghr_bit.iomc8);
            break;
        case 9:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfghr_bit.iofc9, GPIOx->cfghr_bit.iomc9);
            break;
        case 10:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfghr_bit.iofc10, GPIOx->cfghr_bit.iomc10);
            break;
        case 11:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfghr_bit.iofc11, GPIOx->cfghr_bit.iomc11);
            break;
        case 12:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfghr_bit.iofc12, GPIOx->cfghr_bit.iomc12);
            break;
        case 13:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfghr_bit.iofc13, GPIOx->cfghr_bit.iomc13);
            break;
        case 14:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfghr_bit.iofc14, GPIOx->cfghr_bit.iomc14);
            break;
        case 15:
            mode = GpioFc7300xf413modeToGpioMode(GPIOx->cfghr_bit.iofc15, GPIOx->cfghr_bit.iomc15);
            break;
        default:
            mode = GPIO_API_MODE_UNDEF;
            break;
        }
    }
    return mode;
}

bool gpio_x86x_pin_fun_get(Pad_t Pad, GpioPinFunction_t* const function) {
    bool res = false;
    if(function) {
        *function = GPIO_FUN_UNDEF;
        gpio_type* GPIOx = Port2PortPtr(Pad.port);
        if(GPIOx) {
            switch(Pad.pin) {
            case 0:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfglr_bit.iofc0, GPIOx->cfglr_bit.iomc0);
                break;
            case 1:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfglr_bit.iofc1, GPIOx->cfglr_bit.iomc1);
                break;
            case 2:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfglr_bit.iofc2, GPIOx->cfglr_bit.iomc2);
                break;
            case 3:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfglr_bit.iofc3, GPIOx->cfglr_bit.iomc3);
                break;
            case 4:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfglr_bit.iofc4, GPIOx->cfglr_bit.iomc4);
                break;
            case 5:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfglr_bit.iofc5, GPIOx->cfglr_bit.iomc5);
                break;
            case 6:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfglr_bit.iofc6, GPIOx->cfglr_bit.iomc6);
                break;
            case 7:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfglr_bit.iofc7, GPIOx->cfglr_bit.iomc7);
                break;
            case 8:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfghr_bit.iofc8, GPIOx->cfghr_bit.iomc8);
                break;
            case 9:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfghr_bit.iofc9, GPIOx->cfghr_bit.iomc9);
                break;
            case 10:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfghr_bit.iofc10, GPIOx->cfghr_bit.iomc10);
                break;
            case 11:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfghr_bit.iofc11, GPIOx->cfghr_bit.iomc11);
                break;
            case 12:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfghr_bit.iofc12, GPIOx->cfghr_bit.iomc12);
                break;
            case 13:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfghr_bit.iofc13, GPIOx->cfghr_bit.iomc13);
                break;
            case 14:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfghr_bit.iofc14, GPIOx->cfghr_bit.iomc14);
                break;
            case 15:
                *function = GpioFc7300xFunCfgToGpioFun(GPIOx->cfghr_bit.iofc15, GPIOx->cfghr_bit.iomc15);
                break;
            }
        }
    }
    return res;
}
