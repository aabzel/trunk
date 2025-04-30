#include "bit_diag.h"

#include "log.h"
#include "bit_utils.h"
#include "num_to_str.h"

/*
  bd 0x00021805 0x44eb003f
  */
bool bit_diff(uint32_t val_a, uint32_t val_b) {
	bool res = false;
	log_level_time_stamp(false);
    LOG_INFO(SYS,"A:0x%x B:0x%x Different bits:",val_a,val_b);
    LOG_INFO(SYS,"A:%s", utoa_bin32(val_a));
    LOG_INFO(SYS,"B:%s", utoa_bin32(val_b));
    LOG_INFO(SYS,"-----------------------------------------");
    uint32_t diff = val_a^val_b;
    uint8_t diff_bits=count_set_bits(diff);
    LOG_INFO(SYS,"D:%s, DiffBits:%u", utoa_bin32(diff),diff_bits);
    uint32_t cnt=0;
    int32_t b  = 0;
    for(b=31;0 <= b; b--) {
    	uint32_t d1=GET_BIT_NUM(val_a, b);
		uint32_t d2=GET_BIT_NUM(val_b, b);
		if(d1!=d2) {
			cnt++;
			if(cnt<diff_bits){
			    cli_printf("%u , ",b);
			}else{
				cli_printf("%u",b);
			}
			res = true;
		}
    }
    cli_printf(CRLF);
    log_level_time_stamp(true);
    return res;
}
