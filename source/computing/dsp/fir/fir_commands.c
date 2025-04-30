#include "fir_commands.h"

#include "convert.h"
#include "fir.h"
#include "log.h"

//fir_proc_file

/*
 fir_proc_file 8 directionNorm.csv 3 9
 * */
bool fir_proc_file_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 1;
    uint16_t column_x = 1;
    uint16_t column_y = 1;
    if(4 == argc) {
        res = try_str2uint8(argv[0], &num);
        // file name
        res = try_str2uint16(argv[2], &column_x);
        res = try_str2uint16(argv[3], &column_y);
    }

    if(res) {
        res = fir_proc_file(num, argv[1], column_x, column_y);
        log_res(FIR, res, "FrocFile");
    } else {
        LOG_ERROR(FIR, "Usage: fipf Num FileName colomn");
    }

    return res;
}

bool fir_calc_frequency_response_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    double f_step = 0.0;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &f_step);
    }

    if(res) {
        res = fir_calc_frequency_response(num, f_step);
        log_res(FIR, res, "CalcFrequencyFesponse");
    } else {
        LOG_ERROR(FIR, "Usage: ffr Num");
    }

    return res;
}

bool fir_impulse_response_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = fir_impulse_response(num);
        log_res(FIR, res, "impulse_response");
    } else {
        LOG_ERROR(FIR, "Usage: ffr Num");
    }

    return res;
}

bool fir_proc_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    double value = 0.0;

    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        res = try_str2double(argv[1], &value);
    }

    if(res) {
        FirSample_t out = 0.0;
        LOG_INFO(FIR, "Proc,In:%f", value);
        res = fir_proc_in_out(num, (FirSample_t)value, &out);
        log_res(FIR, res, "proc_in_out");
        if(res) {
            LOG_INFO(FIR, "Out:%f", out);
        } else {
            LOG_ERROR(FIR, "Out:%f", out);
        }
    } else {
        LOG_ERROR(FIR, "Usage: fis Num M FcHz");
    }

    return res;
}

bool fir_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    res = try_str2uint8(argv[0], &num);

    if(res) {
        res = fir_init_one(num);
        log_res(FIR, res, "init_one");
    } else {
        LOG_ERROR(FIR, "Usage: fis Num M FcHz");
    }

    return res;
}

bool fir_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {

        res = fir_reset_one(num);
        log_res(FIR, res, "reset_one");
    }

    return res;
}

bool fir_graphviz_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    res = try_str2uint8(argv[0], &num);
    if(res) {
    	res = false;
#ifdef HAS_FIR_DIAG
        res = fir_generate_graphviz(num);
#endif
        log_res(FIR, res, "generate_graphviz");
    } else {
        LOG_ERROR(FIR, "Usage: fis Num M FcHz");
    }
    return res;
}

bool fir_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 == argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
#ifdef HAS_FIR_DIAG
        res = fir_diag(num);
        res = fir_diag_mem(num);
#endif
        log_res(FIR, res, "diag");
    } else {
        LOG_ERROR(FIR, "Usage: fis Num M FcHz");
    }
    return res;
}

/*
 * ll FIR debug; fis 1 10 5000 48000
 * fis 1 10 5000 48000
 */
bool fir_synthesize_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint8_t num = 1;
    uint32_t order = 2;
    double cutoff_frequency_hz = 5000.0;
    double sample_frequency_hz = 48000.0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &order);
    }

    if(3 <= argc) {
        res = try_str2double(argv[2], &cutoff_frequency_hz);
    }

    if(4 <= argc) {
        res = try_str2double(argv[3], &sample_frequency_hz);
    }

    if(res) {
        LOG_INFO(FIR, "SynThesize,Num:%u,M:%u,Fcut:%f Hz,SampleFreq:%f Hz", num, order, cutoff_frequency_hz,
                 sample_frequency_hz);
        res = fir_synthesize(num, order, (FirSample_t)cutoff_frequency_hz, (FirSample_t)sample_frequency_hz);
        log_res(FIR, res, "synthesize");
    } else {
        LOG_ERROR(FIR, "Usage: fis Num M FcHz");
    }
    return res;
}
