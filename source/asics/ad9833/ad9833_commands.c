#include "ad9833_commands.h"

#include <stdbool.h>
#include <stdio.h>

#include "convert.h"
#include "ad9833_drv.h"
#include "log.h"

bool cmd_ad9833_set_signal(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    SignalForm_t form = SIGNAL_FORM_UNDEF;
    double freq = 0.0;
    double phase = 0.0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(AD9833, "Unable to parse Num", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &form);
        if(false == res) {
            LOG_ERROR(AD9833, "Unable to parse form", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2double(argv[2], &freq);
        if(false == res) {
            LOG_ERROR(AD9833, "Unable to parse Freq", argv[2]);
        }
    }

    if(4 <= argc) {
        res = try_str2double(argv[3], &phase);
        if(false == res) {
            LOG_ERROR(AD9833, "Unable to parse phase", argv[3]);
        }
    }

    if(res){
        res = ad9833_set_signal(  num,   form,   freq,   phase);
    }

    return res;
}


bool cmd_ad9833_init(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
    	res = true;
    }

    if(res) {
        res = ad9833_init();
        if(false == res) {
            LOG_ERROR(AD9833, "InitErr");
        } else {
            LOG_INFO(AD9833, "InitOk");
        }
    }
    return res;
}

bool cmd_ad9833_set_freq(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    RegNum_t reg_num = REG_NUM_UNDEF;
    double freq = 0.0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(AD9833, "Unable to parse Num", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &reg_num);
        if(false == res) {
            LOG_ERROR(AD9833, "Unable to parse reg_num", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2double(argv[2], &freq);
        if(false == res) {
            LOG_ERROR(AD9833, "Unable to parse Freq", argv[2]);
        }
    }

    if(res) {
        res= ad9833_set_freq(  num,   reg_num,   freq);
        if(res) {
            LOG_INFO(AD9833, "SetFreqOk");
        } else {
            LOG_ERROR(AD9833, "SetFreqErr");
        }
    }else{
        LOG_ERROR(AD9833, "Usage: adf Num regNum FreqHz");
    }
    return res;
}

bool cmd_ad9833_set_phase(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    RegNum_t reg_num=REG_NUM_UNDEF;
    double phase = 0.0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(AD9833, "Unable to parse Num", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &reg_num);
        if(false == res) {
            LOG_ERROR(AD9833, "Unable to parse reg_num", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2double(argv[2], &phase);
        if(false == res) {
            LOG_ERROR(AD9833, "Unable to parse phase", argv[2]);
        }
    }

    if(res){
      res=ad9833_set_phase(  num,   reg_num,   phase);
      if(res) {
          LOG_INFO(AD9833, "SetPhaseOk");
      } else {
          LOG_ERROR(AD9833, "SetPhaseErr");
      }
    }
    return res;
}


bool cmd_ad9833_set_form(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    SignalForm_t form = SIGNAL_FORM_UNDEF;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(AD9833, "Unable to parse Num", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &form);
        if(false == res) {
            LOG_ERROR(AD9833, "Unable to parse form", argv[1]);
        }
    }

    if(res) {
        res = ad9833_set_form(num, form);
    }
    return res;
}
