#include "fourier_series_commands.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "convert.h"
#include "log.h"
#include "fourier_series.h"

bool fourier_series_diag_command(int32_t argc, char* argv[]){
    bool res = false;

    return res;
}

bool fourier_series_init_command(int32_t argc, char* argv[]){
    bool res = false;
    res = fourier_series_init();
    return res;
}

bool fourier_series_calc_coefficient_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 1;
    uint8_t order = 1;
    char file_name[300] = "";

    if(0==argc){
           num = 1;
           order = 1;
           strcpy(file_name,"");
           res = true;
    }

    if(1<=argc){
           res = try_str2uint8(argv[0], &num);
    }

    if(2<=argc){
           res = try_str2uint8(argv[1], &order);
    }

    if(3<=argc) {
        strcpy(file_name,argv[2]);
        res = true;
    }

    if (res) {
        res = fourier_series_calc_coefficient(num,order,file_name);
    }else{
        LOG_ERROR(FOURIER_SERIES,"fscs num order file");
    }
    
    return res;
}

