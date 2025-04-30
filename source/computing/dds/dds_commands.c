#include "dds_commands.h"

//#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "debug_info.h"
#include "log.h"
#include "dds_config.h"
#include "dds_diag.h"
#include "dds_drv.h"

#ifndef HAS_DDS
#error "+ HAS_DDS"
#endif

#ifndef HAS_DDS_COMMANDS
#error "+ HAS_DDS_COMMANDS"
#endif

bool cmd_dds_play(int32_t argc, char* argv[]){
    bool res = false;
    return res;
}

bool cmd_dds_set_sample(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        res = true;
        uint16_t dac_sample = 0U;
        uint8_t num = 0U;
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
        res = try_str2uint16(argv[1], &dac_sample);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr dac_sample [%s]", argv[1]);
        }
        LOG_INFO(DDS, "DAC:%u sample: 0x%04x or %u\n\r ", num, dac_sample, dac_sample);
        res = dds_set_sample(num, dac_sample);
        if(false == res) {
            LOG_ERROR(DDS, "Unable to set dac_sample [%d] on DAC [%d]", dac_sample, num);
        }
    } else {
        LOG_ERROR(DDS, "Usage: dss num code");
    }
    return res;
}

bool cmd_dds_set_pwm(int32_t argc, char* argv[]) {
    bool res = false;
    if(6 == argc) {
        uint8_t num = 0U;
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
        double dac_amplitude = 0.0f;

        double dacFrequency = 0.0f;
        if(res) {
            res = try_str2double(argv[1], &dacFrequency);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr frequency  [%s]", argv[1]);
            }
        }

        if(res) {
            res = try_str2double(argv[2], &dac_amplitude);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr voltage amplitude [%s]", argv[2]);
            }
        }

        double dacDutyCycle = 0.0f;
        if(res) {
            res = try_str2double(argv[3], &dacDutyCycle);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr duty cycle  [%s]", argv[3]);
            }
        }

        double dacPhase = 0.0f;
        if(res) {
            res = try_str2double(argv[4], &dacPhase);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr phase [%s]", argv[4]);
            }
        }

        double dacVoltageOffset = 0.0f;
        if(res) {
            res = try_str2double(argv[5], &dacVoltageOffset);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr voltage Y offset  [%s]", argv[5]);
            }
        }
        LOG_INFO(DDS, "Frequency: %f Amplitude: %f DutyCycle: %f Phase: %f offset %f", dacFrequency, dac_amplitude,
                 dacDutyCycle, dacPhase, dacVoltageOffset);
        if(res) {
            res = dds_set_pwm(num, dacFrequency, (SampleType_t)dac_amplitude, dacDutyCycle, dacPhase,
                                 (SampleType_t)dacVoltageOffset);
            if(false == res) {
                LOG_ERROR(DDS, "Unable to set PWM signal on DAC [%u]", num);
            }
        }
    } else {
        LOG_ERROR(DDS, "set pwm syntax: num freq amplitude DutyCycle phase offset");
    }
    return res;
}

bool cmd_dds_set_saw(int32_t argc, char* argv[]) {
    bool res = false;
    if(5 == argc) {
        res = true;
        uint8_t num = 0U;
        if(res) {
            res = try_str2uint8(argv[0], &num);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
            }
        }
        double dacFrequency = 0.0f;
        double dacVoltageOffset = 0.0f;
        if(res) {
            res = try_str2double(argv[1], &dacFrequency);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr frequency [%s]", argv[1]);
            }
        }
        double dac_amplitude = 0.0f;
        if(res) {
            res = try_str2double(argv[2], &dac_amplitude);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr amplitude [%s]", argv[2]);
            }
        }

        double dacPhase = 0.0f;
        if(res) {
            res = try_str2double(argv[3], &dacPhase);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr phase [%s]", argv[3]);
            }
        }
        if(res) {
            res = try_str2double(argv[4], &dacVoltageOffset);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr voltage Y offset [%s]", argv[4]);
            }
        }
        if(res) {
            LOG_INFO(DDS, "Frequency: %f Amplitude: %f Phase: %f offset %f", dacFrequency, dac_amplitude, dacPhase,
                     dacVoltageOffset);
            res = dds_set_saw(num, dacFrequency, (SampleType_t)dac_amplitude, dacPhase,
                                 (SampleType_t)dacVoltageOffset);
            if(false == res) {
                LOG_ERROR(DDS, "Unable to adjust saw signal");
            }
        }

    } else {
        LOG_ERROR(DDS, "set saw syntax: num frequency amplitude phase Yoffset");
    }
    return res;
}

bool cmd_dds_set_fence(int32_t argc, char* argv[]) {
    bool res = false;
    if(5 == argc) {
        res = true;
        uint8_t num = 0U;
        if(res) {
            res = try_str2uint8(argv[0], &num);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
            }
        }
        double dacFrequency = 0.0f;
        if(res) {
            res = try_str2double(argv[1], &dacFrequency);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr frequency [%s]", argv[1]);
            }
        }
        double dac_amplitude = 0.0f;
        if(res) {
            res = try_str2double(argv[2], &dac_amplitude);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr amplitude [%s]", argv[2]);
            }
        }

        double dacPhase = 0.0f;
        if(res) {
            res = try_str2double(argv[3], &dacPhase);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr phase [%s]", argv[3]);
            }
        }
        double dacVoltageOffset = 0.0f;
        if(res) {
            res = try_str2double(argv[4], &dacVoltageOffset);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr voltage Y offset [%s]", argv[4]);
            }
        }
        if(res) {
            LOG_INFO(DDS, "Frequency: %f Amplitude: %f Phase: %f offset %f", dacFrequency, dac_amplitude, dacPhase,
                     dacVoltageOffset);
            res = dds_set_fence(num, dacFrequency, (SampleType_t)dac_amplitude, dacPhase,
                                   (SampleType_t)dacVoltageOffset);
            if(false == res) {
                LOG_ERROR(DDS, "Unable to adjust saw signal");
            }
        }

    } else {
        LOG_ERROR(DDS, "set saw syntax: num frequency amplitude phase Yoffset");
    }
    return res;
}

bool cmd_dds_set_sin(int32_t argc, char* argv[]) {
    bool res = false;
    if(5 == argc) {
        res = true;
        uint8_t num = 0U;
        if(res) {
            res = try_str2uint8(argv[0], &num);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
            }
        }
        double dac_amplitude = 0.0f;
        double dacFrequency = 0.0f;
        double dacPhase = 0.0f;
        double dacVoltageOffset = 0.0f;
        if(res) {
            res = try_str2double(argv[1], &dacFrequency);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr frequency [%s]", argv[1]);
            }
        }
        if(res) {
            res = try_str2double(argv[2], &dac_amplitude);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr amplitude [%s]", argv[2]);
            }
        }

        if(res) {
            res = try_str2double(argv[3], &dacPhase);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr phase [%s]", argv[3]);
            }
        }
        if(res) {
            res = try_str2double(argv[4], &dacVoltageOffset);
            if(false == res) {
                LOG_ERROR(DDS, "ParseErr voltage Y offset [%s]", argv[4]);
            }
        }

        if(res) {
            LOG_INFO(DDS, "Frequency: %f Amplitude: %f Phase: %f offset %f", dacFrequency, dac_amplitude, dacPhase,
                     dacVoltageOffset);
            res = dds_set_sin(num, dacFrequency, (SampleType_t)dac_amplitude, dacPhase,
                                 (SampleType_t)dacVoltageOffset);
            if(false == res) {
                LOG_ERROR(DDS, "Unable to adjust sin signal");
            }
        }

    } else {
        LOG_ERROR(DDS, "set sin syntax: num frequency amplitude phase Yoffset");
    }
    return res;
}

bool cmd_dds_diag(int32_t argc, char* argv[]) {
    bool res = false;
    (void)argv;
    if(0 == argc) {
        res = dds_diag();
    } else {
        LOG_ERROR(DDS, "Usage: dad");
    }
    return res;
}

bool cmd_dds_set_array(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0U;
    uint32_t periods = 2;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &periods);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr periods [%s]", argv[1]);
        }
    }

    if(res) {
        res = dds_set_array(num, periods, 0);
        if(res) {
            LOG_INFO(DDS, LOG_OK);
        } else {
            LOG_ERROR(DDS, "Err");
        }
    } else {
        LOG_ERROR(DDS, "Usage: sdsa num periods");
    }

    return res;
}

bool cmd_dds_calc_static_tone(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0U;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }

    if(res) {
        res = dds_set_static_period_48k_1000hz_word(num);
        if(res) {
            LOG_INFO(DDS, "Calc1kHzToneOk");
        } else {
            LOG_ERROR(DDS, "Calc1kHzToneErr");
        }
    } else {
        LOG_ERROR(DDS, "Usage: sdsa DacNum");
    }

    return res;
}

bool cmd_dds_print_track(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1U;
    if(0 == argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }

    if(res) {
        res = dds_print_track(num);
        if(false == res) {
            LOG_ERROR(DDS, "PrintTrackErr %u", num);
        }
    } else {
        LOG_ERROR(DDS, "Usage: sdpt DacNum");
    }
    return res;
}

bool cmd_dds_rev_sample(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0U;
    uint8_t byte_cnt = 0U;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &byte_cnt);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr chank [%s]", argv[1]);
        }
    }
    if(res) {
        LOG_INFO(DDS, "%u TryRevTrack", num);
        switch(byte_cnt) {
        case 1:
            res = dds_rev_bytes(num);
            break;
        case 2:
            res = dds_rev_hwords(num);
            break;
        default:
            res = false;
            break;
        }
        if(false == res) {
            LOG_ERROR(DDS, "%u RevTrackErr", num);
        } else {
            LOG_INFO(DDS, "%u RevTrackOk", num);
        }
    } else {
        LOG_ERROR(DDS, "Usage: sdrd DacNum RevItem");
    }
    return res;
}

bool cmd_dds_pattern(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0U;
    uint8_t pattern = 0U;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &pattern);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr Pattern [%s]", argv[1]);
        }
    }

    if(res) {
        LOG_INFO(DDS, "Set Pattern %u", pattern);
        res = dds_pattern_set(num, pattern);
        if(res) {
            LOG_INFO(DDS, "Ok");
        }
    } else {
        LOG_ERROR(DDS, "Usage: sdrd DacNum Pattern");
    }
    return res;
}

bool cmd_dds_fps(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0U;
    uint32_t frame_per_sec = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &frame_per_sec);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr Pattern [%s]", argv[1]);
        } else {
            LOG_INFO(DDS, "ReadAmp %d", frame_per_sec);
        }
    }

    LOG_INFO(DDS, "argc %d", argc);
    if(res) {
        res = dds_set_fps(num, frame_per_sec);
    } else {
        LOG_ERROR(DDS, "Usage: sdf DacNum FPS");
    }

    return res;
}

bool cmd_dds_amp(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0U;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }

    int32_t amplitude = 0;
    if(2 <= argc) {
        res = try_str2int32(argv[1], (int32_t*)&amplitude);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr Pattern [%s]", argv[1]);
        } else {
            LOG_INFO(DDS, "ReadAmp %d", amplitude);
        }
    }
    LOG_INFO(DDS, "argc %d", argc);
    if(res) {
        DdsHandle_t* Node = DdsGetNode(num);
        if(Node) {
            LOG_INFO(DDS, "SeNode");
            if(2 == argc) {
                // LOG_INFO(DDS, "AmpTrySet %d",amplitude);
                Node->amplitude = (SampleType_t)amplitude;
                LOG_INFO(DDS, "AmpSet %d", Node->amplitude);
            } else {
                LOG_INFO(DDS, "AmpGet %d", Node->amplitude);
            }
        } else {
            LOG_ERROR(DDS, "NoNode %u", num);
        }
    } else {
        LOG_ERROR(DDS, "Usage: sda DacNum Amp");
    }

    return res;
}

bool cmd_dds_set_chirp(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0U;
    int32_t amplitude = 0;
    double frequency1 = 0;
    double frequency2 = 0;
    double chirp_duration_s = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2int32(argv[1], (int32_t*)&amplitude);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr Pattern [%s]", argv[1]);
        } else {
            LOG_INFO(DDS, "ReadAmp %d", amplitude);
        }
    }

    if(res) {
        res = try_str2double(argv[2], &frequency1);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr frequency [%s]", argv[2]);
        }
    }

    if(res) {
        res = try_str2double(argv[3], &frequency2);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr frequency [%s]", argv[3]);
        }
    }

    if(res) {
        res = try_str2double(argv[4], &chirp_duration_s);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr frequency [%s]", argv[4]);
        }
    }

    if(res) {
        res = dds_set_chirp(num,chirp_duration_s,frequency1,frequency2);
        log_res(DDS,res,"SetChirp");
    } else {
        LOG_ERROR(DDS, "Usage: ddschir Num Amp F1 F2 Dur");
    }
    return res;
}


bool cmd_dds_phase(int32_t argc, char* argv[]){
    double phase_s=0.0;
    uint8_t num = 0U;
    bool res = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr DacNum [%s]", argv[0]);
        }
    }

    if(res) {
        res = try_str2double(argv[2], &phase_s);
        if(false == res) {
            LOG_ERROR(DDS, "ParseErr frequency [%s]", argv[2]);
        }
    }

    if(res) {
        res = dds_phase_set(num, phase_s);
        log_res(DDS,res,"SetPhase");
    } else {
        LOG_ERROR(DDS, "Usage: ddp Num phase_s");
    }

    return res;
}
