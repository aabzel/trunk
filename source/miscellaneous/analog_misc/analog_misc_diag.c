#include "analog_misc_diag.h"

#include "analog_misc.h"
#include "log.h"
#include "num_to_str.h"

/*
  bd 0x00021805 0x44eb003f
  */
bool analog_misc_diff(uint32_t val_a, uint32_t val_b) {
    bool res = false;
    log_level_time_stamp(false);
    LOG_INFO(SYS, "A:0x%x B:0x%x Different analog_miscs:", val_a, val_b);
    LOG_INFO(SYS, "A:%s", utoa_bin32(val_a));
    LOG_INFO(SYS, "B:%s", utoa_bin32(val_b));
    LOG_INFO(SYS, "-----------------------------------------");
    uint32_t diff = val_a ^ val_b;
    uint8_t diff_analog_miscs = count_set_analog_miscs(diff);
    LOG_INFO(SYS, "D:%s, DiffBits:%u", utoa_bin32(diff), diff_analog_miscs);
    uint32_t cnt = 0;
    int32_t b = 0;
    for(b = 31; 0 <= b; b--) {
        uint32_t d1 = GET_ANALOG_NUM(val_a, b);
        uint32_t d2 = GET_ANALOG_NUM(val_b, b);
        if(d1 != d2) {
            cnt++;
            if(cnt < diff_analog_miscs) {
                cli_printf("%u , ", b);
            } else {
                cli_printf("%u", b);
            }
            res = true;
        }
    }
    cli_printf(CRLF);
    log_level_time_stamp(true);
    return res;
}

#if 0
const char* BitToStr(const uint8_t val, const char* const name_one, const char* const name_zero) {
    char* name = "?";
    if(val) {
        name = name_one;
    } else {
        name = name_zero;
    }
    return name;
}

#endif
