#include "max98357_commands.h"

#include "log.h"
#include "convert.h"
#include "max98357_drv.h"

bool max98357_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = max98357_init();
        if(false == res) {
            LOG_ERROR(MAX98357, "InitErr");
        } else {
            LOG_INFO(MAX98357, "InitOk");
        }
    }
    return res;
}


bool max98357_play_1kHz_tone_command(int32_t argc, char* argv[]){
	bool res= false;

	double amplitude=3333.0;
	double phase_ms=0.0;
	uint8_t num = 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &amplitude);
    }

    if(3 <= argc) {
        res = try_str2double(argv[2], &phase_ms);
    }

    if (res) {
        res = max98357_play_1kHz_tone(num, amplitude, phase_ms);
        if(res){
        	LOG_INFO(MAX98357, "PlayOk");
        }
    }else{
    	 LOG_ERROR(MAX98357, "Usage: mto Num Amp Phase");
    }

	return res;
}

