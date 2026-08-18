#include "nau8814_dac_commands.h"

#include "convert.h"
#include "log.h"
#include "nau8814_drv.h"
#ifdef HAS_TEST_NAU8814
#include "test_nau8814.h"
#endif

// np 2000 15000 100000
bool nau8814_play_tone_command(int32_t argc, char* argv[]) {
    bool res = false;
    double freq = 1000.0;
    int32_t amplitude = 100;
    uint32_t duration_ms = 100.0;
    if(1 <= argc) {
        res = try_str2double(argv[0], &freq);
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], &amplitude);
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &duration_ms);
    }

    if(res) {
        res = nau8814_play_tone(1, freq, (SampleType_t)amplitude, duration_ms);
        if(res) {
            LOG_INFO(NAU8814, "PlayToneOk");
        } else {
            LOG_ERROR(NAU8814, "PlayToneErr");
        }
    } else {
        LOG_ERROR(NAU8814, "Usage: np FreqHz Amp DurationMs");
    }

    return res;
}

bool nau8814_dac_gain_command(int32_t argc, char* argv[]) {
    bool res = false;
    fGain_t gain = 0.0;
    if(1 <= argc) {
        res = try_str2float(argv[0], &gain);
    }

    if(res) {
        switch(argc) {
        case 0:
            gain = nau8814_dac_gain_get(1, &gain);
            LOG_INFO(NAU8814, "GetDACGain %f Ok", gain);
            break;
        case 1:
            LOG_INFO(NAU8814, "SetDACGain %f Ok", gain);
            res = nau8814_dac_gain_set(1, gain);
            if(res) {
                LOG_INFO(NAU8814, "SetDACGain %f Ok", gain);
            } else {
                LOG_ERROR(NAU8814, "SetDACGain %f err", gain);
            }
            break;
        }
    }
    return res;
}
//
bool nau8814_play_infinite_command(int32_t argc, char* argv[]) {
    bool res = false;
    double freq = 1000.0;
    int32_t amplitude = 100;
    uint32_t duration_ms = 3000;

    if(1 <= argc) {
        res = try_str2double(argv[0], &freq);
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], &amplitude);
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &duration_ms);
        if(false == res) {
            LOG_ERROR(NAU8814, "ParseErr DurationMs %s", argv[2]);
        }
    }

    if(res) {
        res = nau8814_play_tone(1, freq, (SampleType_t)amplitude, 0x0FFFFFFF);
        if(res) {
            LOG_INFO(NAU8814, "PlayOk");
        } else {
            LOG_ERROR(NAU8814, "PlayErr");
        }
    } else {
        LOG_ERROR(NAU8814, "Usage: npt FreqHz Amp DurationMs");
    }

    return res;
}

bool nau8814_play_1kHz_tone_command(int32_t argc, char* argv[]) {
    bool res = false;
    int32_t amplitude = 3333;
    uint32_t duratin_ms = 10000;

    if(1 <= argc) {
        res = try_str2int32(argv[0], &amplitude);
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &duratin_ms);
    }

    if(res) {
        LOG_INFO(NAU8814, "TryPlay1kHz");
        res = nau8814_play_1khz(1, (SampleType_t)amplitude, duratin_ms);
        if(res) {
            LOG_INFO(NAU8814, "CmdPlay1kOk");
        } else {
            LOG_ERROR(NAU8814, "CmdPlay1kErr");
        }
    } else {
        LOG_ERROR(NAU8814, "Usage: no Amp DurationMs");
    }

    return res;
}
