#include "hist_filter_commands.h"

#include "convert.h"
#include "log.h"
#include "hist_filter_mcal.h"


bool hist_filter_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(HIST_FILTER, res, "Num");
    }

    if(res) {
        res = hist_filter_diag_one(num);
        log_info_res(HIST_FILTER, res, "Diag");

        res = hist_filter_diag();
        log_info_res(HIST_FILTER, res, "Diag");
    } else {
        LOG_ERROR(HIST_FILTER, "Usage: fdat");
    }

    return res;
}

bool hist_filter_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(HIST_FILTER, res, "Num");
    }

    if(0 == argc) {
        res = hist_filter_mcal_init();
        log_info_res(HIST_FILTER, res, "Init");
    }
    return res;
}


bool hist_filter_proc_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    float in_sample = 0 ;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(HIST_FILTER, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &in_sample);
        log_info_res(HIST_FILTER, res, "in_sample");
    }

    if(res) {
        int32_t out = hist_filter_proc_sample(  num, in_sample);
        LOG_INFO(HIST_FILTER, "HFILT%u,In:%f,Out:%d",num, in_sample, out);
    }else{
        LOG_ERROR(HIST_FILTER, "Usage: hfp Num sample");
    }

}
