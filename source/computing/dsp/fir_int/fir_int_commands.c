#include "fir_int_commands.h"

#include "convert.h"
#include "fir_int.h"
#include "log.h"

bool fir_int_calc_frequency_response_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 1;
    double f_step = 0.0;
    if(0<=argc) {
        res = true;
    }

    if(1<=argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2<=argc) {
        res = try_str2double(argv[1], &f_step);
    }

    if(res) {
        res = fir_int_calc_frequency_response(num,f_step);
        if(res) {
            LOG_INFO(FIR_INT, "Ok");
        }else {
            LOG_ERROR(FIR_INT, "Err");
        }
    }else{
        LOG_ERROR(FIR_INT, "Usage: ffr Num");
    }

    return res;
}

bool fir_int_impulse_response_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 1;
    if(0<=argc) {
        res = true;
    }

    if(1<=argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = fir_int_impulse_response(num);
        if(res) {
            LOG_INFO(FIR_INT, "Ok");
        }else {
            LOG_ERROR(FIR_INT, "Err");
        }
    }else{
        LOG_ERROR(FIR_INT, "Usage: ffr Num");
    }

    return res;
}



bool fir_int_proc_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    double value = 0.0;

    if(2==argc){
        res = try_str2uint8(argv[0], &num);
        res = try_str2double(argv[1], &value);
    }

    if(res) {
        FirIntSample_t out=0.0;
        LOG_INFO(FIR_INT, "Proc,In:%f", value);
        res = fir_int_proc_in_out(  num, (FirIntSample_t)value, &out);
        if(res) {
            LOG_INFO(FIR_INT, "Out:%f", out);
        }else {
            LOG_ERROR(FIR_INT, "Out:%f", out);
        }
    }else{
        LOG_ERROR(FIR_INT, "Usage: fis Num M FcHz");
    }

    return res;
}

bool fir_int_init_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    res = try_str2uint8(argv[0], &num);

    if(res){
        res=fir_int_init_one(num);
    }else{
        LOG_ERROR(FIR_INT, "Usage: fis Num M FcHz");
    }

    return res;
}

bool fir_int_reset_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    if(1<=argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res){

        res=fir_int_reset_one(num);
    }

    return res;
}

bool fir_int_graphviz_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    res = try_str2uint8(argv[0], &num);
    if(res){
        res= fir_int_generate_graphviz(  num);
    }else{
        LOG_ERROR(FIR_INT, "Usage: fis Num M FcHz");
    }
    return res;
}

bool fir_int_diag_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;

    if(1==argc){
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = fir_int_diag(num);
        res = fir_int_diag_mem(num);
        res = fir_int_diag_raw_mem(num);
    }else{
        LOG_ERROR(FIR_INT, "Usage: fis Num M FcHz");
    }
    return res;
}


/*
 * ll FIR debug; fis 1 10 5000 48000
 * fis 1 10 5000 48000
*/
bool fir_int_synthesize_command(int32_t argc, char* argv[]){
    bool res = false;

    uint8_t num = 1;
    uint32_t order = 2;
    float cutoff_frequency_hz = 5000.0;
    float sample_frequency_hz = 48000.0;

    if(1<=argc){
        res = try_str2uint8(argv[0], &num);
    }

    if(2<=argc){
        res = try_str2uint32(argv[1], &order);
    }

    if(3<=argc){
        res = try_str2float(argv[2], &cutoff_frequency_hz);
    }

    if(4<=argc){
        res = try_str2float(argv[3], &sample_frequency_hz);
    }

    if(res){
        LOG_INFO(FIR_INT, "SynThesize,Num:%u,M:%u,Fcut:%f Hz,SampleFreq:%f Hz", num, order,cutoff_frequency_hz,sample_frequency_hz);
        res = fir_int_synthesize(num, order,(float) cutoff_frequency_hz, (float)sample_frequency_hz);
        if(res) {
            LOG_INFO(FIR_INT, "SynthesizeOk");
        }else {
            LOG_ERROR(FIR_INT, "SynthesizeErr");
        }
    }else{
        LOG_ERROR(FIR_INT, "Usage: fis Num M FcHz");
    }
    return res;
}
