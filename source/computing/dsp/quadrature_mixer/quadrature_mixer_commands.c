#include "quadrature_mixer_commands.h"

#include "convert.h"
#include "quadrature_mixer.h"
#include "log.h"


bool quadrature_mixer_proc_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    double value = 0.0;

    if(2==argc){
        res = try_str2uint8(argv[0], &num);
        res = try_str2double(argv[1], &value);
    }

    if(res) {
    }else{
        LOG_ERROR(QUADRATURE_MIXER, "Usage: fis Num M FcHz");
    }

    return res;
}

bool quadrature_mixer_lpf_iir_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    double k = 0.0;

    if(2==argc){
        res = try_str2uint8(argv[0], &num);
        res = try_str2double(argv[1], &k);
    }

    if(res) {
    	res = quadrature_mixer_lpf_iir(num, k);
    }else{
        LOG_ERROR(QUADRATURE_MIXER, "Usage: qmlps Num k");
    }

    return res;
}


bool quadrature_mixer_init_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    res = try_str2uint8(argv[0], &num);

    if(res){
        res=quadrature_mixer_init_one(num);
    }else{
        LOG_ERROR(QUADRATURE_MIXER, "Usage: fis Num M FcHz");
    }

    return res;
}


bool quadrature_mixer_diag_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;

    if(1==argc){
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = quadrature_mixer_diag(num);
    }else{
        LOG_ERROR(QUADRATURE_MIXER, "Usage: fis Num M FcHz");
    }
    return res;
}
