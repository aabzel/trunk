#include "gps_1bit.h"

#include <stdio.h>
#include <string.h>

#include "file_pc.h"
#include "bit_utils.h"
#include "gps_misc.h"
#include "code_generator.h"
#include "log.h"

static uint64_t bytes_read = 0;
static FILE *src_data_file = NULL;

uint16_t tmp_prn_data[GPS_DATA_WORDS_CNT];
uint16_t tmp_data_i[GPS_DATA_WORDS_CNT];
uint16_t tmp_data_q[GPS_DATA_WORDS_CNT];


COMPONENT_GET_NODE(Gps1Bit, gps_1bit)

COMPONENT_GET_CONFIG(Gps1Bit, gps_1bit)


#define PACKED_BUF_SIZE		4096
static uint8_t packed_data_buf[PACKED_BUF_SIZE];


static uint8_t data_reader_open_file(char* path) {
	src_data_file = fopen(path, "rb");
	if (src_data_file == NULL)
		return 0;
	else
		return 1;
}

static void data_reader_close_file(void){
	if (src_data_file != NULL)
		fclose(src_data_file);
}



/// Read block, size - in bytes
static uint8_t data_reader_read_block(uint8_t* data, uint16_t size){
	if (src_data_file == NULL)
		return 0;
	size_t nread = fread(data, 1, size, src_data_file);
	if (nread != size)	{
		return 0;
	}
	bytes_read += nread;
	return 1;
}

static uint8_t data_reader_read_unpack(uint8_t* data, uint16_t samples_cnt){
	//1 byte packed - 4 samples
	uint16_t bytes_to_read = samples_cnt / 4; //packed bytes - 4Kbyte
	if (bytes_to_read > PACKED_BUF_SIZE)
		return 0;

	uint8_t res = data_reader_read_block(packed_data_buf, bytes_to_read);
	if (res == 0)
		return 0;

	memset(data, 0, samples_cnt / 8);

	uint16_t dst_cnt = 0;
	for (uint16_t i = 0; i < bytes_to_read; i++)	{
		//analyse packeed bytes
		dst_cnt = i / 2;
		uint8_t packed_byte = packed_data_buf[i];
		uint8_t tmp = reverse_bits(packed_byte);//4bits
		if ((i & 1) == 0)
			data[dst_cnt] |= tmp;
		else
			data[dst_cnt] |= tmp << 4;
	}

	return 1;
}

//Генерирует локальный PRN код
//Переносит принятые данные на частоту, близкую к 0
//Перебирает все фазы кода, и выводит фазу максимальной
static bool acquisition_freq_test(gps_ch_t* channel,
		uint8_t* data,
		uint16_t* const best_phase1 ,
		uint16_t* const max_correl_val_out
		){
	bool res = false;
	if(channel){
		if(data){
			if(best_phase1){
				if(max_correl_val_out){
					res = true;
				}

			}

		}
	}

	if(res) {
    	gps_generate_prn_data2(channel, tmp_prn_data, 0);
    	int16_t freq_offset_hz = channel->acq_data.given_freq_offset_hz;
    	gps_shift_to_zero_freq(data, (uint8_t*)tmp_data_i, (uint8_t*)tmp_data_q, IF_FREQ_HZ + freq_offset_hz);
    	uint16_t avr_val=0;

        int16_t max_correl_val = 0;
        max_correl_val = correlation_search(tmp_prn_data, tmp_data_i, tmp_data_q, 0, (PRN_LENGTH * 2), &avr_val, best_phase1);
        *max_correl_val_out = max_correl_val;
	}

    return res;
}

bool gps_1bit_seek_phase(char * data_path,  int prn, int16_t  doppler_freq_hz) {
	bool res = false;
	FILE *PhaseFilePtr = NULL;
    char prn_phase_file[80]={0};
    snprintf(prn_phase_file,sizeof(prn_phase_file),"PRN%d_phase_at_Doppler_%d_Hz.csv",prn,doppler_freq_hz);

    PhaseFilePtr = fopen(prn_phase_file, "w");
    if(PhaseFilePtr){

        //char data_path[300] = "D:\\PATH\\source2.bin";
        gps_fill_summ_table();

        gps_ch_t gps_channel1;
        memset(&gps_channel1, 0, sizeof(gps_channel1));
        gps_channel1.prn = prn;
        gps_channel1.acq_data.given_freq_offset_hz = doppler_freq_hz;
        gps_channell_prepare(&gps_channel1);

        uint8_t read_buffer[BITS_IN_PRN / 8];
        (void)read_buffer;
        LOG_INFO(GPS,"PRNsize %u byte", sizeof(read_buffer));
        LOG_INFO(GPS,"IF_FREQ_HZ %u Hz", IF_FREQ_HZ);
        uint8_t ret = data_reader_open_file(data_path);
        if (ret == 0)    {
            LOG_ERROR(GPS,"Open file fail");
            res = false;
        } else {
        	uint32_t prn_cnt = 8000;
            for (int i = 0; i < prn_cnt; i++)    {
                //Читаем 1мс данных
            	ret = data_reader_read_unpack(read_buffer, BITS_IN_PRN);
                if (ret == 0)        {
                	LOG_ERROR(GPS,"Can't read file\n");
                    break;
                } else {
                    uint16_t best_phase1 = 0; /*1 unit-8samples*/
                	uint16_t max_correl_val = 0;
                    acquisition_freq_test(&gps_channel1, read_buffer,&best_phase1,&max_correl_val);
                    //cli_printf("%d,%u,%u\n",i ,best_phase1,max_correl_val);
                    res = print_progress(  i,   prn_cnt);
                    fprintf(PhaseFilePtr,"%d,%u,%u\n" ,i,best_phase1*8,max_correl_val);
                    res = true;
                }
            }

            data_reader_close_file();
            LOG_INFO(GPS,"Execution end\n");
        }
        fclose(PhaseFilePtr);
    }
    return res;
}


bool gps_1bit_proc_one(uint8_t num){
    return true;
}


bool gps_1bit_init_one(uint8_t num){
    return true;
}

bool gps_1bit_init_custom(void){
    return true;
}

bool gps_unpack_u16( const  char* const file_name){
    bool res = false;
    if(file_name) {
        int32_t size_bytes = file_pc_get_size(file_name);
        LOG_INFO(GPS,"Size %d byte",size_bytes);
    	uint8_t read_buffer[BITS_IN_PRN / 8];
    	uint8_t ret = data_reader_open_file(file_name);
        if (ret == 0) {
        	LOG_ERROR(GPS,"Open file fail");
            res = false;
        } else {
            uint32_t prn_cnt = size_bytes/sizeof(read_buffer);;
            for (int i = 0; i < prn_cnt; i++) {
                //Читаем 1мс данных
                res = data_reader_read_unpack(read_buffer, BITS_IN_PRN);
                if (res == 0) {
                	LOG_ERROR(GPS,"Can't read file");
                    res = false;
                    break;
                } else {
                    res = file_pc_save_array("adc_sample_1bit_stream.bin", read_buffer, sizeof(read_buffer));
                    print_progress(i, prn_cnt);
                }
            }
        	data_reader_close_file();
        }
    }
    return res;
}

bool gps_1bit_stream_to_i8( const  char* const file_name){
    bool res = false;
    if(file_name){
        uint32_t size_bytes = file_pc_get_size(file_name);
        LOG_INFO(GPS,"Size %d byte",size_bytes);
        int32_t sample_cnt = size_bytes*8;
        LOG_INFO(GPS,"Samples:%d ",sample_cnt);
        FILE *BitStreamFile = NULL;
        FILE *ByteStreamFile = NULL;
        BitStreamFile = fopen(file_name, "rb");

        if(BitStreamFile) {
        	ByteStreamFile = fopen("byte_stream_i8.bin", "wb");
        	if(ByteStreamFile) {
        		uint32_t i =0;
        		for(i=0;i<size_bytes;i++) {

        	        uint8_t byte_8_samples =0;
        	        size_t nread = fread(&byte_8_samples, 1, 1, BitStreamFile);
        	        if(1==nread) {
        	        	int bit =0;
        	        	/*
        	        	 * Данные идут непрерывно.
                         Первый байт после декодирования - 0x9E = 0b1001_1110.
                         Соответственно, семплы, которые приходили c АЦП в
                         хронологическом порядке - 0,1,1,1,     1,0,0,1.
                          */
        	        	for(bit=0;bit<8;bit++){
        	        		int8_t sample = 0;
        	        		if(GET_BIT_NUM(byte_8_samples, bit)){
        	        			sample = -1;
        	        		} else {
        	        			sample = 1;
        	        		}
        	                size_t nwrite = fwrite((const void*)&sample, 1, 1, ByteStreamFile);
        	                if(1==nwrite){
        	                	res = true;
        	                }else{
                	        	LOG_ERROR(GPS,"WriteByteStreamErr");
                	        }

        	        	}

        	        }else{
        	        	LOG_ERROR(GPS,"readBitStrErr");
        	        }
        	        if(0==(i%1000)){
            	        print_progress(  i,   size_bytes);
        	        }
        		}
        	    fclose(ByteStreamFile);

        	}
        	fclose(BitStreamFile);
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(GPS, GPS, gps_1bit)

COMPONENT_PROC_PATTERT(GPS, GPS, gps_1bit)
