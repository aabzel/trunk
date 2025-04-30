#include "pwm_drv.h"

#include "clock_utils.h"
#include "data_utils.h"
#include "hal_nrfx_diag.h"
#include "log.h"
#include "nrfx_pwm.h"
#include "pwm_custom_types.h"
#include "pwm_dep.h"
#include "pwm_diag.h"
#include "pwm_isr.h"
#include "pwm_types.h"

const static PwmStaticInfo_t PwmStaticInfo[] = {
#ifdef HAS_PWM0
    {
        .num = 0,
        .handler = pwm0_handler,
        .registers = NRF_PWM0_S,
        .drv_inst_idx = NRFX_PWM0_INST_IDX,
        .valid = true,
    },
#endif /*HAS_PWM0*/

#ifdef HAS_PWM1
    {
        .num = 1,
        .handler = pwm1_handler,
        .registers = NRF_PWM1_S,
        .drv_inst_idx = NRFX_PWM1_INST_IDX,
        .valid = true,
    },
#endif /*HAS_PWM1*/

#ifdef HAS_PWM2
    {
        .num = 2,
        .handler = pwm2_handler,
        .registers = NRF_PWM2_S,
        .drv_inst_idx = NRFX_PWM2_INST_IDX,
        .valid = true,
    },
#endif /*HAS_PWM2*/

#ifdef HAS_PWM3
    {
        .num = 3,
        .handler = pwm3_handler,
        .registers = NRF_PWM3_S,
        .drv_inst_idx = NRFX_PWM3_INST_IDX,
        .valid = true,
    },
#endif /*HAS_PWM3*/
};

static PwmStaticInfo_t* PwmGetStaticNode(uint8_t num) {
    PwmStaticInfo_t* Node = NULL;
    uint8_t i = 0;
    uint8_t cnt = ARRAY_SIZE(PwmStaticInfo);
    LOG_DEBUG(PWM, "Total: %u Need %u", cnt, num);
    for(i = 0; i < cnt; i++) {
        if(num == PwmStaticInfo[i].num) {
            LOG_DEBUG(PWM, "spotNum %u", num);
            if(PwmStaticInfo[i].valid) {
                LOG_DEBUG(PWM, "spotValid %u", num);
                Node = (PwmStaticInfo_t*)&PwmStaticInfo[i];
                break;
            }
        }
    }
    return Node;
}

bool pwm_phase_set(uint8_t num, uint32_t phase) {
    bool res = true;
#warning TODO
    return res;
}

bool pwm_start(uint8_t num) {
    bool res = false;
    LOG_DEBUG(PWM, "Start: %u", num);
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        Node->sequence.values.p_common =
            &Node->comparator15bit;   ///< Pointer to an array with duty cycle values. This array must be in Data RAM.
                                      /**< This field is defined as an union of pointers
                                       *   to provide a convenient way to define duty
                                       *   cycle values in various loading modes
                                       *   (see @ref nrf_pwm_dec_load_t).
                                       *   In each value, the most significant bit (15)
                                       *   determines the polarity of the output and the
                                       *   others (14-0) compose the 15-bit value to be
                                       *   compared with the pulse generator counter. */
        Node->sequence.length = 1;    ///< Number of 16-bit values in the array pointed by @p values.
        Node->sequence.repeats = 1;   ///< Number of times that each duty cycle is to be repeated (after being played
                                      ///< once). Ignored in @ref NRF_PWM_STEP_TRIGGERED mode.
        Node->sequence.end_delay = 1; ///< Additional time (in PWM periods) that the last duty cycle is to be kept after
                                      ///< the sequence is played. Ignored in @ref NRF_PWM_STEP_TRIGGERED mode.

        uint32_t ret = nrfx_pwm_simple_playback(&Node->h_pwm, &Node->sequence, 1, 0);
        if(ret) {
            LOG_INFO(PWM, "Ret %u", ret);
        }
        res = true;
    }

    return res;
}

bool pwm_duty_set(uint8_t num, PwmChannel_t channel, double duty) {
    bool res = false;
    LOG_DEBUG(PWM, "Set PWM%u, Ch:%u, Duty %6.2f", num, channel, duty);
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        Node->comparator15bit = ((double)Node->count_period) - ((double)Node->count_period) * (duty / 100.0);
        LOG_DEBUG(PWM, "PWM%u Set , Period: %u, Cnt:%u", num, Node->count_period, Node->comparator15bit);
        res = true;
        res = pwm_start(num);
    }

    return res;
}

/*(see page 354) 7.23 PWM — Pulse width modulation*/
bool pwm_init_one(uint8_t num) {
    bool res = false;
    LOG_INFO(PWM, "Init %u", num);

    const PwmConfig_t* Config = PwmGetConfig(num);
    if(Config) {
        PwmDiagConfig(Config);
        LOG_WARNING(PWM, "Config:PWM%u,Freq:%f Hz,Dudy:%f %%", num, Config->frequency_hz, Config->duty);
        PwmHandle_t* Node = PwmGetNode(num);
        if(Node) {
            LOG_INFO(PWM, "Spot PWM%u", num);
            res = pwm_init_cache(Config, Node);

            if(Node->init_done) {
                nrfx_pwm_uninit(&Node->h_pwm);
            }

            uint8_t cnt = ARRAY_SIZE(PwmStaticInfo);
            LOG_WARNING(PWM, "Stop %u Configs", cnt);
            const PwmStaticInfo_t* StaticNode = PwmGetStaticNode(num);
            if(StaticNode) {
                LOG_WARNING(PWM, "SpotStaticConfigFor %u", num);
                Node->h_pwm.p_registers = StaticNode->registers;
                Node->h_pwm.drv_inst_idx = StaticNode->drv_inst_idx;

                // nrfx_pwm_handler_t handler = StaticNode->handler;
                nrfx_pwm_config_t local_config = {0};
                uint32_t i = 0;
                for(i = 0; i < 4; i++) {
                    local_config.output_pins[i] = Node->pad[i].byte;
                }

                local_config.irq_priority = 0;               ///< Interrupt priority.
                local_config.base_clock = NRF_PWM_CLK_16MHz; ///< Base clock frequency.
                local_config.count_mode = NRF_PWM_MODE_UP;   ///< Operating mode of the pulse generator counter.
                double pediod_s = 1.0 / Config->frequency_hz;

                Node->count_period = SEC_TO_TIMER_PERIOD(pediod_s, 16000000);
                if(1 == Node->count_period) {
                    Node->count_period = 2;
                }
                LOG_WARNING(PWM, "DesPeriod %u tick", Node->count_period);
                local_config.top_value = Node->count_period;  ///< Value up to which the pulse generator counter counts.
                local_config.load_mode = NRF_PWM_LOAD_COMMON; ///< Mode of loading sequence data from RAM.
                local_config.step_mode = NRF_PWM_STEP_AUTO;   ///< Mode of advancing the active sequence.
                local_config.skip_gpio_cfg = true;
                nrfx_err_t ret = 0;
                ret = nrfx_pwm_init(&Node->h_pwm, &local_config, NULL, NULL);
                if(NRFX_SUCCESS == ret) {
                    LOG_INFO(PWM, "PWM%u InitOk", num);
                    Node->init_done = true;
                    res = true;
                    if(Config->on) {
                        LOG_INFO(PWM, "PWM%u Set Duty %f %%", num, Config->duty);
                        res = pwm_duty_set(num, PWM_CHANNEL0, Config->duty);
                        LOG_INFO(PWM, "PWM%u Start...", num);
                        res = pwm_start(num);
                        if(res) {
                            LOG_INFO(PWM, "PWM%u StartOk", num);
                        } else {
                            LOG_ERROR(PWM, "PWM%u StartErr", num);
                            res = false;
                        }
                    }
                } else {
                    res = false;
                    LOG_ERROR(PWM, "Init %u %u=%s Err", num, ret, HalStatus2Str(ret));
                }

            } else {
                LOG_ERROR(PWM, "NoInfoNode %u", num);
            }
        } else {
            LOG_ERROR(PWM, "NoNode %u", num);
        }

    } else {
        LOG_DEBUG(PWM, "NoConfig %u", num);
    }

    return res;
}

bool pwm_stop(uint8_t num) {
    bool res = false;
    LOG_INFO(PWM, "PWM%u Stop", num);
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        res = nrfx_pwm_stop(&Node->h_pwm, true);
        if(res) {
            LOG_INFO(PWM, "Stop %u Ok", num);
        } else {
            LOG_ERROR(PWM, "Stop %u Err", num);
        }
    }
    return res;
}

bool pwm_frequency_set(uint8_t num, PwmChannel_t channel, double frequency_hz) {
    bool res = false;
    LOG_WARNING(PWM, "PWM%u SetFreq:%f Hz", num, frequency_hz);
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        LOG_INFO(PWM, "Spot PWM%u", num);
        if(Node->init_done) {
            nrfx_pwm_uninit(&Node->h_pwm);
        }

        const PwmStaticInfo_t* StaticNode = PwmGetStaticNode(num);
        if(StaticNode) {
            LOG_WARNING(PWM, "SpotStaticConfigFor %u", num);
            Node->h_pwm.p_registers = StaticNode->registers;
            Node->h_pwm.drv_inst_idx = StaticNode->drv_inst_idx;
            // nrfx_pwm_handler_t handler = StaticNode->handler;
            nrfx_pwm_config_t local_config = {0};
            uint32_t i = 0;
            for(i = 0; i < 4; i++) {
                local_config.output_pins[i] = Node->pad[i].byte;
            }

            local_config.irq_priority = 0;               ///< Interrupt priority.
            local_config.base_clock = NRF_PWM_CLK_16MHz; ///< Base clock frequency.
            local_config.count_mode = NRF_PWM_MODE_UP;   ///< Operating mode of the pulse generator counter.
            double pediod_s = 1.0 / Node->frequency_hz;

            Node->count_period = SEC_TO_TIMER_PERIOD(pediod_s, 16000000);
            if(1 == Node->count_period) {
                Node->count_period = 2;
            }
            LOG_WARNING(PWM, "DesPeriod %u tick", Node->count_period);
            local_config.top_value = Node->count_period;  ///< Value up to which the pulse generator counter counts.
            local_config.load_mode = NRF_PWM_LOAD_COMMON; ///< Mode of loading sequence data from RAM.
            local_config.step_mode = NRF_PWM_STEP_AUTO;   ///< Mode of advancing the active sequence.
            local_config.skip_gpio_cfg = true;
            nrfx_err_t ret = 0;
            ret = nrfx_pwm_init(&Node->h_pwm, &local_config, NULL, NULL);
            if(NRFX_SUCCESS == ret) {
                Node->init_done = true;
                Node->frequency_hz = frequency_hz;
                LOG_INFO(PWM, "PWM%u InitOk", num);
                res = true;
                if(Node->on) {
                    LOG_INFO(PWM, "PWM%u Set Duty %f %%", num, Node->duty);
                    res = pwm_duty_set(num, PWM_CHANNEL0, Node->duty);
                    LOG_INFO(PWM, "PWM%u Start...", num);
                    res = pwm_start(num);
                    if(res) {
                        LOG_INFO(PWM, "PWM%u StartOk", num);
                    } else {
                        LOG_ERROR(PWM, "PWM%u StartErr", num);
                        res = false;
                    }
                }
            } else {
                res = false;
                LOG_ERROR(PWM, "Init %u %u=%s Err", num, ret, HalStatus2Str(ret));
            }
        } else {
            LOG_ERROR(PWM, "NoStaticNode %u", num);
        }
    } else {
        LOG_ERROR(PWM, "NoNode %u", num);
    }
    return res;
}
