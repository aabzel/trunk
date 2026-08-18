#include "bq24079_commands.h"


#include "bq24079_drv.h"
#include "bq24079_diag.h"
#include "convert.h"
#include "log.h"


bool bq24079_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res){
        res=bq24079_diag();
    }else{
        LOG_ERROR(BQ24079, "Usage: bqd");

    }
    return res;
}

bool bq24079_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    Bq24079Settings_t settings = BQ24079_UNDEF;

    if(1 == argc) {
        res = try_str2uint8(argv[0], &settings);
        if(false == res) {
            LOG_ERROR(BQ24079, "Unable to extract state %s", argv[0]);
        }
    }
        if(res) {
        	res = bq24079_settings_set(  settings);
        	if(res){
        		 LOG_INFO(BQ24079, "Set %u=%s Ok",settings,Bq24079SettingsToStr(settings));
        	}else{
        		 LOG_ERROR(BQ24079, "Set %u=%s Err",settings,Bq24079SettingsToStr(settings));
        	}

        }else{
            LOG_ERROR(BQ24079, "Usage: bqc settings");

        }
    return res;
}



bool bq24079_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if (res) {
        res = bq24079_init();
    } else {
        LOG_ERROR(BQ24079, "Usage: bqi");
    }
    return res;
}
