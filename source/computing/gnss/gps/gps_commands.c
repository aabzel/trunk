#include "gps_commands.h"

#include <stdbool.h>
#include <stdint.h>

#include "array.h"
#include "convert.h"
#include "gps.h"
#include "log.h"
#include "array_diag.h"

bool gps_prn_command(int32_t argc, char* argv[]){
    bool res = false;
    int prn = 0;
    if(1 <= argc) {
        res = try_str2int32(argv[0], &prn);
    }

    if(res) {
        uint8_t PrnCode[PRN_LENGTH*2]={0};
        memset(PrnCode,0,sizeof(PrnCode));
        LOG_PARN(GPS,"TryGeneratePRNcodeFor %d", prn);
        gps_generate_prn(PrnCode, prn);
        LOG_INFO(GPS,"PRN code %d,PRN_LENGTH:%u", prn,PRN_LENGTH);
        array_u8_print_dec(PrnCode, PRN_LENGTH);
        cli_printf(CRLF);
        uint32_t sum = arr_sum(PrnCode, PRN_LENGTH);
        LOG_INFO(GPS,"PRNcode %d,SumOnes:%u,,SumZeros:%u", prn,sum,PRN_LENGTH-sum);

        uint8_t PrnCodeHex[PRN_LENGTH/8+1]={0};
        res = array_bit_array_to_hex(PrnCode,PRN_LENGTH,PrnCodeHex,sizeof(PrnCodeHex));
        array_u8_print(PrnCodeHex, sizeof(PrnCodeHex));
        cli_printf(CRLF);
    }

    return res;
}

bool gps_prn_samples_command(int32_t argc, char* argv[]){
    bool res = false;
    int prn = 0;
    if(1 <= argc) {
        res = try_str2int32(argv[0], &prn);
    }

    if(res) {
        LOG_PARN(GPS,"TryGeneratePRNcodeSamplesFor %d", prn);
        int8_t GeneratedPrnSample[ONE_PRN_SAMPLE_CNT]={0};
        memset(GeneratedPrnSample,0,sizeof(GeneratedPrnSample));
        GpsHandle_t* Node=GpsGetNode(1);
        set_log_level(GPS,LOG_LEVEL_DEBUG);

        res = gps_generate_prn_samples(prn, GeneratedPrnSample, Node->sample_per_chip);
        array_i8_print_dec(GeneratedPrnSample, ONE_PRN_SAMPLE_CNT);
        cli_printf(CRLF);
        uint32_t sum1 = arr_i8_sum_vals(GeneratedPrnSample, ONE_PRN_SAMPLE_CNT,1);
        uint32_t sumM1 = arr_i8_sum_vals(GeneratedPrnSample, ONE_PRN_SAMPLE_CNT,-1);
        LOG_INFO(GPS,"PRNcode %d,SumOnes:%u,,SumMin1:%u", prn,sum1,sumM1);

        //uint8_t PrnCodeHex[ONE_PRN_SAMPLE_CNT/8+1]={0};
        //res = array_bit_array_to_hex(GeneratedPrnSample,ONE_PRN_SAMPLE_CNT,PrnCodeHex,sizeof(PrnCodeHex));
        //array_u8_print(PrnCodeHex, sizeof(PrnCodeHex));
        //cli_printf(CRLF);

        set_log_level(GPS,LOG_LEVEL_INFO);
    }

    return res;
}

bool gps_post_proc_command(int32_t argc, char* argv[]){
    bool res = false;
    char file_name[200]={0};

    uint8_t num= 0;
    if(1 <= argc) {
        res = try_str2int8(argv[0], &num);
    }

    if(2 <= argc) {
        LOG_INFO(GPS, "argv0 [%s]", argv[1]);
        strcpy(file_name, argv[1]);
        LOG_INFO(GPS, "FileName [%s]", file_name);
        res = true;
    }

    if(res){
        res= gps_post_proc(num, file_name);
        cli_printf(CRLF);
    }
    return res;
}

//gps 1 adc_sample2.bin
bool gps_proc_samples_command(int32_t argc, char* argv[]){
    bool res = false;

    uint8_t num= 0;
    if(1 <= argc) {
        res = try_str2int8(argv[0], &num);
    }

    if(res) {
        const GpsConfig_t* Config=GpsGetConfig( num);
        if(Config){
            res= gps_proc_sample(num, Config->file_name);
            cli_printf(CRLF);
        }
    }else{
        LOG_ERROR(GPS, "Usage: gps Num");
    }
    return res;
}
/*
 *gsp 1 5 1000
 *gsp 1 14 4200 3.0  6000 10000
 * */
bool gps_seek_prn_phase_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num= 1;
    int32_t prn = 14;
    double percent = 100.0;
    int32_t doppler_freq_hz = 2000;
    uint32_t phase_start_seek=5000;
    uint32_t phase_end_seek=10000;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2int8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], &prn);
    }

    if(3 <= argc) {
        res = try_str2int32(argv[2], &doppler_freq_hz);
    }

    if(4 <= argc) {
        res = try_str2number(argv[3], &percent);
    }

    if(5 <= argc) {
        res = try_str2uint32(argv[4], &phase_start_seek);
    }

    if(6 <= argc) {
        res = try_str2uint32(argv[5], &phase_end_seek);
    }

    if(res) {
        LOG_INFO(GPS, "PRN:%d,%d Hz,%f %%,PhaseRange:%u-%u Sample",prn,
        		doppler_freq_hz,
        		percent,phase_start_seek,phase_end_seek);
        const GpsConfig_t* Config = GpsGetConfig( num);
        if(Config) {
            res= gps_seek_prn_phase_all(num,
                    Config->file_name,
                    prn,
                    doppler_freq_hz,
                    percent,
                    phase_start_seek,
                    phase_end_seek);
            cli_printf(CRLF);
        }
    } else {
        LOG_ERROR(GPS, "Usage: gsp Num DopplerFreqHz");
    }
    return res;
}


/*
 * ges 1 14
 * */

// ll gps debug;ges 1 14
bool gps_escort_sat_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num= 1;
    int32_t prn = 14;
    if(1 <= argc) {
        res = try_str2int8(argv[0], &num);
    }
    if(2 <= argc) {
        res = try_str2int32(argv[1], &prn);
    }

    if(res) {
        LOG_INFO(GPS, "PRN:%d",prn);
        res= gps_escort_sat(num,  prn );
        if(res){
            LOG_INFO(GPS, "GpsEscortOk");
        }else{
            LOG_ERROR(GPS, "GpsEscortErr");
        }
        cli_printf(CRLF);
    } else {
        LOG_ERROR(GPS, "Usage: ges Num PRN");
    }
    return res;
}
// ll gps debug;epl 1 14
bool gps_escort_sat_epl_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num= 1;
    int32_t prn = 14;
    if(1 <= argc) {
        res = try_str2int8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], &prn);
    }

    if(res) {
        res = gps_escort_sat_epl(num, prn);
        if(res){
            LOG_INFO(GPS, "GpsEscortEplOk");
        }else{
            LOG_ERROR(GPS, "GpsEscortEplErr");
        }
        cli_printf(CRLF);
    } else {
        LOG_ERROR(GPS, "Usage: epl Num PRN");
    }
    return res;
}

/*
 * gcp 1 14 1 10
 * */
bool gps_capture_prn_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num= 1;
    int32_t prn = 14;
    int32_t doppler_hz = 0;
    uint32_t phase_start = 0;
    uint32_t phase_end = 1023*16-1;
    double time_s = 0.0;

    if(1 <= argc) {
        res = try_str2int8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], &prn);
    }

    if(3 <= argc) {
        res = try_str2number(argv[2], &time_s);
    }

    if(4 <= argc) {
        res = try_str2uint32(argv[3], &phase_start);
    }

    if(5 <= argc) {
        res = try_str2uint32(argv[4], &phase_end);
    }

    if(6 <= argc) {
        res = try_str2int32(argv[5], &doppler_hz);
    }

    if(res) {
        uint32_t phase_offset_sample = 0;
        LOG_INFO(GPS, "Num:%u,PRN%u,Time:%f s,SeekRange:%u...%u Sample",num, prn, time_s,phase_start,phase_end);
        res = gps_capture_prn(num, prn, time_s, phase_start, phase_end, &phase_offset_sample, doppler_hz);
        if(res) {
            LOG_INFO(GPS, "GpsCapture %u Sample", phase_offset_sample);
        } else {
            LOG_ERROR(GPS, "GpsEscortEplErr");
        }
        cli_printf(CRLF);
    } else {
        LOG_ERROR(GPS, "Usage: gcp Num PRN TimeS DopplerHz");
    }
    return res;
}

bool gps_prn_convolution_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num= 1;
    int32_t prn = 14;

    if(1 <= argc) {
        res = try_str2int8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], &prn);
    }

    if(res) {
        LOG_INFO(GPS, "Num:%u,PRN%u",num, prn);
        res = gps_prn_convolution(num, prn);
        if(res) {
            LOG_INFO(GPS, "PrnConvOk");
        } else {
            LOG_ERROR(GPS, "PrnConvErr");
        }
        cli_printf(CRLF);
    } else {
        LOG_ERROR(GPS, "Usage: gpc Num PRN");
    }
    return res;
}

//gpa 14
bool gps_prn_autocorrelation_command(int32_t argc, char* argv[]){
    bool res = false;
    int32_t prn = 14;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2int32(argv[0], &prn);
    }

    if(res) {
        LOG_INFO(GPS, "PRN%u", prn);
        res = gps_prn_autocorrelation(1, prn);
        if(res) {
            LOG_INFO(GPS, "PrnConvOk");
        } else {
            LOG_ERROR(GPS, "PrnConvErr");
        }
        cli_printf(CRLF);
    } else {
        LOG_ERROR(GPS, "Usage: gpa PRN");
    }
    return res;
}

