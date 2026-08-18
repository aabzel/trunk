#include "max9860_dac_commands.h"

#include "convert.h"
#include "log.h"
#include "max9860_diag.h"
#include "max9860_drv.h"
#include "audio_types.h"
#ifdef HAS_TEST_MAX9860
#include "test_max9860.h"
#endif



bool max9860_test_command(int32_t argc, char* argv[]) {
    bool res = false;
    double freq=1000.0;
    SampleType_t amplitude=100.0;
    uint32_t duration_ms=100.0;
    if(1 <= argc) {
        res = try_str2double(argv[0], &freq);
    }

    if(2 <= argc) {
        res = try_str2int16(argv[1], &amplitude);
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &duration_ms);
    }

    if(res) {
#ifdef HAS_TEST_MAX9860
        res = test_max9860_play_freq(freq, amplitude, duration_ms);
#endif
    }

    return res;
}

bool max9860_attenuation_command(int32_t argc, char* argv[]) {
    bool res = false;
    Gain_t gain = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2int8(argv[0], &gain);
    }

    if(res) {
        switch(argc){
            case 0:{
                gain = max9860_attenuation_get( );
                LOG_INFO(MAX9860, "GetAttenGain %d Ok", gain);
            } break;
            case 1:{
                res = max9860_attenuation_set(gain);
                if(res) {
                    LOG_INFO(MAX9860, "SetAttenGain %d Ok", gain);
                } else {
                    LOG_ERROR(MAX9860, "SetAttenGain %d err", gain);
                }

            } break;
            default:{
            	res = false;
            }break;
        }
    }

    if (false==res) {
        LOG_ERROR(MAX9860, "Usage: ma gain [-90...+3]");
    }
    return res;
}

bool max9860_dac_gain_command(int32_t argc, char* argv[]){
    bool res = false;
    Gain_t gain = 0;
    if(1 <= argc) {
        res = try_str2int8(argv[0], &gain);
    }

    if(res) {
        switch(argc){
        case 0:
            gain= max9860_dac_gain_get( );
              LOG_INFO(MAX9860, "GetDACGain %d Ok", gain);
            break;
        case 1:
            LOG_INFO(MAX9860, "SetDACGain %d Ok", gain);
            res=max9860_dac_gain_set(  gain);
            if(res) {
                LOG_INFO(MAX9860, "SetDACGain %d Ok", gain);
            } else {
                LOG_ERROR(MAX9860, "SetDACGain %d err", gain);
            }
            break;
        }
    }
    return res;
}

bool max9860_play_infinite_command(int32_t argc, char* argv[]){
    bool res = false;
    double freq = 1000.0;
    SampleType_t amplitude = 100.0;

    if(1 <= argc) {
        res = try_str2double(argv[0], &freq);
    }

    if(2 <= argc) {
        res = try_str2int16(argv[1], &amplitude);
    }

    if(res) {
        res = max9860_play_infinite(freq, amplitude);
        if (res) {
            LOG_INFO(MAX9860, "Ok Freq:%f Amp:%d",freq, amplitude);
        } else {
            LOG_ERROR(MAX9860, "Play Err");
        }
    }

    if(false==res){
        LOG_ERROR(MAX9860, "Usage: mpi freq Amp");
    }

    return res;
}



bool max9860_stereo_command(int32_t argc, char* argv[]){
    bool res = false;
    bool on_off = false;

    if(0 <= argc){
        res = true;
    }

    if(1 <= argc) {
        res = try_str2bool(argv[0], &on_off);
    }

    if(res){
        switch(argc){
        case 0:
            on_off=max9860_stereo_get();
            break;
        case 1:
            res=max9860_stereo_set(on_off);
            break;
        }
    } else {
        LOG_ERROR(MAX9860, "Usage: ms OnOff");
    }
    return res;
}



bool max9860_play_1kHz_tone_command(int32_t argc, char* argv[]){
	bool res= false;

	double amplitude=3333.0;
	double phase_ms=0.0;

    if(1 <= argc) {
        res = try_str2double(argv[0], &amplitude);
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &phase_ms);
    }

    if (res) {
        res = max9860_play_1kHz_tone(  amplitude,   phase_ms);
    }else{
    	 LOG_ERROR(MAX9860, "Usage: mo Amp Phase");
    }

	return res;
}
