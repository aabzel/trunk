#include "gps_1bit_commands.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "array.h"
#include "convert.h"
#include "gps_1bit.h"
#include "log.h"
#include "array_diag.h"



bool gps_unpack_u16_command(int32_t argc, char* argv[]){
    bool res = false;
    char file_name[200]="source2.bin";

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        LOG_INFO(GPS, "argv0 [%s]", argv[0]);
        strcpy(file_name, argv[0]);
        LOG_INFO(GPS, "FileName [%s]", file_name);
        res = true;
    }

    if(res){
        res= gps_unpack_u16( file_name);
        if(res){
        	LOG_INFO(GPS,"Ok");
        }else{
        	LOG_ERROR(GPS,"Err");
        }
    	cli_printf(CRLF);
    }
    return res;
}

/*
 g1sp source2.bin 5 1000
 g1sp source2.bin 5 500
 g1sp source2.bin 14 4000
 g1sp source2.bin 20 -1000
 g1sp source2.bin 30 2000

*/
bool gps_1bit_seek_prn_phase_command(int32_t argc, char* argv[]){
    bool res = false;

    int32_t prn = 14;
    int16_t doppler_freq_hz = 4000;
    char file_name[100]="source2.bin";

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = strcpy(file_name,argv[0]);
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], &prn);
    }

    if(3 <= argc) {
        res = try_str2int16(argv[2], &doppler_freq_hz);
    }

    if(res) {
    	LOG_INFO(GPS, "[%s],PRN:%d", file_name, prn);
       	res = gps_1bit_seek_phase(file_name,    prn,    doppler_freq_hz);
        cli_printf(CRLF);
    } else {
        LOG_ERROR(GPS, "Usage: g1sp FileName Prn DopplerFreqHz");
    }
    return res;
}

/*
 * g1t8 adc_sample_1bit_stream_4apr.bin
 * */
bool gps_1bit_stream_to_i8_command(int32_t argc, char* argv[]){
    bool res = false;
    char file_name[100]="adc_sample_1bit_stream_4apr.bin";

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = strcpy(file_name,argv[0]);
    }

    if(res) {
        LOG_INFO(GPS, "File:[%s]", file_name);
        res = gps_1bit_stream_to_i8(file_name);
        cli_printf(CRLF);
    } else {
        LOG_ERROR(GPS, "Usage: g1t8 FileName");
    }

    return res;
}

/*
 * g1lo 4092000 100
 * */
bool gps_1bit_lo_command(int32_t argc, char* argv[]){
    bool res = false;
	uint16_t tmp_data_i[GPS_DATA_WORDS_CNT];
	uint16_t tmp_data_q[GPS_DATA_WORDS_CNT];
	int32_t freq_hz = 4092000;
	uint32_t samples = 100;
    if(1 <= argc) {
        res = try_str2int32(argv[0], &freq_hz);
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &samples);
    }
    size_t word_cnt = samples/16;

    if(res) {
    	uint8_t read_buffer[BITS_IN_PRN / 8]={0};
	    gps_shift_to_zero_freq(read_buffer, tmp_data_i, tmp_data_q, (float) freq_hz);

	    LOG_WARNING(GPS, "I:%u words",word_cnt);
		res = array_u16_print_bin(tmp_data_i,   word_cnt);
        cli_printf(CRLF);
	    LOG_WARNING(GPS, "Q:%u words",word_cnt);

		res = array_u16_print_bin(tmp_data_q,   word_cnt);
		cli_printf(CRLF);
    }
    return res;
}
