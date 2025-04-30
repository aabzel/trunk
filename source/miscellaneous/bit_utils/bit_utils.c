#include "bit_utils.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "data_types.h"
#ifdef HAS_LOG
#include "log.h"
#endif

/*3 -> 0b0111=7*/
bool bit_get_u8(uint8_t byte, uint8_t bit_num) {
    bool res = false;
    if(0x01 & (byte >> bit_num)) {
        res = true;
    }
    return res;
}

uint32_t generate_32bit_custom_mask(uint8_t max_bit, uint8_t min_bit) {
    uint32_t mask = 0x00000000U;
    if(min_bit <= max_bit) {
        uint32_t i = 0U;
        for(i = min_bit; i <= max_bit; i++) {
            mask |= (1 << i);
        }
    }
    return mask;
}

uint32_t generate_32bit_mask(uint8_t bit_len) {
    uint32_t mask = 0x00000000U;
    if(bit_len <= 32) {
        mask = generate_32bit_custom_mask(bit_len - 1, 0);
    }
    return mask;
}

uint32_t extract_subval_from_32bit(uint32_t in_val, uint8_t max_bit, uint8_t min_bit) {
    uint32_t outVal = 0;
    if((min_bit <= max_bit) && (max_bit <= 31) && (min_bit <= 31)) {
        uint32_t mask = generate_32bit_mask(max_bit - min_bit + 1);
        outVal = (in_val >> min_bit);
        outVal = outVal & mask;
    }
    return outVal;
}

uint8_t generate_8bit_mask(uint8_t bit_len) {
    uint8_t mask = 0x00000000U;
    if(bit_len <= 8) {
        uint8_t i = 0U;
        for(i = 0U; i < bit_len; i++) {
            mask |= (1 << i);
        }
    }
    return mask;
}
/**/
uint32_t insert_subval_in_32bit(uint32_t orig_val, uint32_t sub_val, uint8_t max_bit, uint8_t min_bit) {
    uint32_t out_val = 0;
#ifdef HAS_LOG
    LOG_DEBUG(SYS, "Insert In 0x%08x, Val 0x%x, %u-%u", orig_val, sub_val, max_bit, min_bit);
#endif
    uint32_t temp_val = 0;
    uint32_t mask = 0;
    mask = generate_32bit_custom_mask(max_bit, min_bit);
    // temp_val = temp_val >> min_bit;
    temp_val |= sub_val;
    temp_val = temp_val << min_bit;
#ifdef HAS_LOG
    LOG_DEBUG(SYS, "0x%08x SubValShifted ", temp_val);
    LOG_DEBUG(SYS, "0x%08x Mask ", mask);
    LOG_DEBUG(SYS, "0x%08x InvMask ", ~mask);
    LOG_DEBUG(SYS, "0x%08x OrigVal", orig_val);
#endif
    temp_val = (mask & temp_val) | ((~mask) & orig_val);
    out_val = temp_val;
#ifdef HAS_LOG
    LOG_DEBUG(SYS, "0x%08x ResVal", out_val);
#endif

    // uint32_t read_sub_val = extract_subval_from_32bit(out_val, max_bit, min_bit);
    // if(read_sub_val != sub_val) {
    //    out_val = 0xFFFFFFFF;
    // }
    return out_val;
}

uint64_t generate_64bit_mask(uint8_t bit_len) {
    uint64_t mask = 0x00000000U;
    if(bit_len <= 64) {
        uint32_t i = 0U;
        for(i = 0U; i < bit_len; i++) {
            mask |= (1 << i);
        }
    }
    return mask;
}

uint64_t extract_subval_from_64bit(uint64_t in_val, uint8_t max_bit, uint8_t min_bit) {
    uint64_t outVal = 0;
    if((min_bit <= max_bit) && (max_bit <= 63) && (min_bit <= 63)) {
        uint64_t mask = generate_64bit_mask(max_bit - min_bit + 1);
        outVal = (in_val >> min_bit);
        outVal = outVal & mask;
    }
    return outVal;
}

int32_t parse_n_bit_signed(uint32_t value, uint8_t bittness) {
    int32_t sval = value;
#ifdef HAS_LOG
    LOG_DEBUG(TEST, "%s(): %d %d", __FUNCTION__, value, bittness);
#endif
    if(GET_BIT_NUM(value, bittness - 1)) {
#ifdef HAS_LOG
        LOG_DEBUG(TEST, "Negative %d", value);
#endif
        uint32_t neg_abs = extract_subval_from_32bit(value, bittness - 2, 0);
        uint32_t mask = generate_32bit_mask(bittness - 1);
#ifdef HAS_LOG
        LOG_DEBUG(TEST, "mask: 0x%08x Bit:%d", mask, bittness - 1);
#endif
        neg_abs = (neg_abs ^ mask) + 1;
#ifdef HAS_LOG
        LOG_DEBUG(TEST, "neg_abs %d", neg_abs);
#endif
        sval = -1 * ((int32_t)neg_abs);
#ifdef HAS_LOG
        LOG_DEBUG(TEST, "out %d", sval);
#endif
    } else {
#ifdef HAS_LOG
        LOG_DEBUG(TEST, "Positive %d", value);
#endif
        sval = value;
    }
    return sval;
}

bool bit32_control_proc(uint32_t* p_reg, char cmd, uint8_t bit_num) {
    bool res = false;
    if(bit_num <= 31) {
        res = true;
        // uint32_t volatile * const p_reg = (uint32_t *) address_val;
        // cli_printf("%p %u " CRLF, p_reg, p_reg[0]);
        // uint32_t* val = (uint32_t*)address_val;
        switch(cmd) {
        case 's':
            p_reg[0] = p_reg[0] | (1U << (bit_num));
            break;
        case 'r':
            p_reg[0] = p_reg[0] & (~(1U << (bit_num)));
            break;
        case 't':
            p_reg[0] = p_reg[0] ^ (1U << (bit_num));
            break;
        default:
            res = false;
            break;
        }
        // cli_printf("%p %u " CRLF, p_reg, p_reg[0]);
    }
    return res;
}

uint8_t extract_subval_from_8bit(uint8_t in_val, uint8_t max_bit, uint8_t min_bit) {
    uint64_t outVal = 0;
    if((min_bit <= max_bit) && (max_bit <= 7) && (min_bit <= 7)) {
        uint64_t mask = generate_8bit_mask(max_bit - min_bit + 1);
        outVal = (in_val >> min_bit);
        outVal = outVal & mask;
    }
    return outVal;
}

/*
 * Function returns the number of set bits in binary  (Hamming weight)
 * representation of positive integer val
 * TODO: we can boost time of calculation by creating look up table for byte->am of bit
 *       It will reqire 512 byte of flash for 8bit value.
 *
 * */

uint8_t count_set_bits(uint32_t const inVal32bit) {
    uint8_t sum = 0;
    uint32_t val32bit = inVal32bit;
    while(0u != val32bit) {
        sum++;
        val32bit &= (val32bit - 1u);
    }
    return sum;
}

// Return sum of bits in "data"
uint8_t bit_summ16(uint16_t data) {
    uint8_t cnt = 0;
    for(uint8_t i = 0; i < 16; i++) {
        if(data & 1) {
            cnt++;
        }
        data = data >> 1;
    }
    return cnt;
}

/*
 *  Odd (Amount of 1 bits is 1 3 5 7 9 and so 31)
 *  even (Amount of 1 bits is 2 4 6 8 10 and so 32)
 *
 *  returns 1 if the parity in inValue is Odd
 *  (Amount of 1 bits is 1 3 5 7 9 and so 31)
 *
 *  inVal        bit        setBit  parity        return
 *  0          > 00       > 0  >    PARITY_EVEN   false
 *  1          > 01       > 1  >    PARITY_ODD    true
 *  2          > 10       > 1  >    PARITY_ODD    true
 *  3          > 11       > 2  >    PARITY_EVEN   false
 *  178        > 10110010 > 4  >    PARITY_EVEN   false
 *  0xFFFFFFFF > 1..111   > 32 >    PARITY_EVEN   false
 *  0xFFFFFFFE > 11..10   > 31 >    PARITY_ODD    true
 */
bool is_parity_odd(uint32_t const inVal) {
    bool otRet = false;
    uint8_t cntOnes = 0u;
    /*count set bits*/
    cntOnes = count_set_bits(inVal);
    if(0u < (cntOnes & 1u)) {
        otRet = true; /*(Amount of 1 bits is 1 3 5 7 9 and so 31)*/
    } else {
        otRet = false; /*(Amount of 1 bits is 2 4 6 8 10 and so 32)*/
    }

    return otRet;
}

uint8_t get_bit_from_32bit(uint32_t in_val, uint8_t bit_num) {
    uint8_t bit = 0xFF;
    if(bit_num < 32) {
        bit = MASK_1BIT & (in_val >> bit_num);
    }
    return bit;
}

uint16_t invert_bits16(uint16_t val) { return MASK_16BIT ^ val; }

#ifdef HAS_BIT_SWAP
uint8_t swap_bits_u8(uint8_t in_val) {
    uint8_t out_val = 0;
    uint8_t out = 0;
    uint8_t bit = 0U;
    for(bit = 0U; bit <= 7U; bit++) {
        out |= (in_val & 1);
        out_val = out;
        out = out << 1;
        in_val = in_val >> 1;
    }
    return out_val;
}

uint16_t swap_bits_u16(uint16_t in_val) {
    Type16Union_t un16in;
    Type16Union_t un16out;
    un16in.u16 = in_val;
    un16out.u8[0] = swap_bits_u8(un16in.u8[1]);
    un16out.u8[1] = swap_bits_u8(un16in.u8[0]);
    return un16out.u16;
}

// O(n) 4*(1+1+2(1+1)) = 4*(6) = 24
uint8_t swap_bits_u8_2(uint8_t in_val) {
    uint8_t out_val = 0;
    uint8_t mask_even = 0;
    uint8_t mask_odd = 0;
    uint8_t pair = 0;
    for(pair = 0; pair < 4; pair++) {
        mask_even = 1 << (pair * 2);
        mask_odd = 1 << (pair * 2 + 1);
        if(in_val & mask_even) { // 0 2 4
            out_val |= mask_odd;
        }
        if(in_val & mask_odd) { // 1 3 5
            out_val |= mask_even;
        }
    }
    return out_val;
}

uint8_t swap_bits_u8_slow(uint8_t in_val) {
    uint8_t out_val = 0;
    uint8_t bit = 0U;
    for(bit = 0U; bit < 8U; bit++) {
        if((((uint8_t)1U) << bit) == ((((uint8_t)1U) << bit) & in_val)) {
            out_val |= (((uint8_t)1) << (7U - bit));
        }
    }
    return out_val;
}

uint8_t swap_bits_u8_fast(uint8_t in_val) {
    uint8_t out_val = 0, power = 7;
    while(in_val != 0) {
        out_val += (in_val & 1) << (power--);
        in_val = in_val >> 1;
    }
    return out_val;
}

uint32_t swap_bits_u32(uint32_t in_val) {
    uint32_t out_val = 0U;
    uint32_t i = 0U;
    for(i = 0U; i < 32U; i++) {
        if((((uint32_t)1U) << i) == ((((uint32_t)1U) << i) & in_val)) {
            out_val |= (((uint32_t)1) << (31U - i));
        }
    }

    return out_val;
}

uint32_t swap_bits_u32_f(uint32_t num32b) {
    uint32_t reverseNum = 0u;
    uint32_t i;
    uint32_t is_i_bit_set;

    for(i = 0u; i <= 31; i++) {
        is_i_bit_set = (num32b & (1 << i));
        if(is_i_bit_set) {
            reverseNum |= (1 << (31 - i));
        }
    }
    return reverseNum;
}

uint64_t swap_bits_u64(uint64_t in_val) {
    uint64_t out_val = 0U;
    uint16_t i = 0U;
    for(i = 0U; i < 64U; i++) {
        if((((uint64_t)1U) << i) == ((((uint64_t)1U) << i) & in_val)) {
            out_val |= (((uint64_t)1) << (63U - i));
        }
    }

    return out_val;
}

uint64_t swap_bits_u64_v2(uint64_t in_val) {
    Type64Union_t un64in;
    Type64Union_t un64out;
    un64in.u64 = in_val;
    un64out.u8[0] = swap_bits_u8(un64in.u8[7]);
    un64out.u8[1] = swap_bits_u8(un64in.u8[6]);
    un64out.u8[2] = swap_bits_u8(un64in.u8[5]);
    un64out.u8[3] = swap_bits_u8(un64in.u8[4]);
    un64out.u8[4] = swap_bits_u8(un64in.u8[3]);
    un64out.u8[5] = swap_bits_u8(un64in.u8[2]);
    un64out.u8[6] = swap_bits_u8(un64in.u8[1]);
    un64out.u8[7] = swap_bits_u8(un64in.u8[0]);
    return un64out.u64;
}

#endif

bool is_valid_bit_mask_u8(char* in_mask) {
    bool out_res = true;
    //  LOG_DEBUG(SYS,"IsValidMask[%s]",in_mask);
    size_t len = strlen(in_mask);
    if(8 == len || 9 == len) {
        uint32_t i = 0;
        uint32_t sep_cnt = 0;
        for(i = 0; i < len; i++) {
            switch(in_mask[i]) {
            case '0':
            case '1':
            case 'x':
            case 'X':
                break;
            case '_':
                sep_cnt++;
                break;
            default:
#ifdef HAS_LOG
                LOG_ERROR(SYS, "[%u]='%c'", i, in_mask[i]);
#endif
                out_res = false;
                break;
            }
        }
        if(1 < sep_cnt) {
            out_res = false;
#ifdef HAS_LOG
            LOG_ERROR(SYS, "TooMuchSeps[%u]", sep_cnt);
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(SYS, "InvalMask[%s]", in_mask);
#endif
        out_res = false;
    }
    return out_res;
}
// 0b0101_0101,
//   x1xx_0xxx ->
// 0b0101_0101

// 0b0111_0011,
//   x0xx_1xxx ->
// 0b0011_1011
uint8_t adjust_bits_u8(uint8_t orig, char* in_mask) {
    uint8_t new_val = orig;
    // LOG_DEBUG(SYS,"AdjustBits: 0x%02x Mask[%s]",orig,in_mask);
    if(in_mask) {
        bool res = is_valid_bit_mask_u8(in_mask);
        if(res) {
            size_t len = strlen(in_mask);
            int32_t i = 0;
            int32_t bit = 0;
            for(i = (len - 1); 0 <= i; i--) {
                // LOG_DEBUG(SYS,"ProcChar Mask[%u]=[%c] ",i,in_mask[i]);
                switch(in_mask[i]) {
                case '0': {
                    // LOG_DEBUG(SYS,"SetBit %u in Val 0x%x",bit,new_val);
                    RESET_BIT_NUM(new_val, bit);
                    // LOG_DEBUG(SYS,"Res 0x%x",new_val);
                    bit++;
                } break;
                case '1': {
                    // LOG_DEBUG(SYS,"ReSetBit %u in Val 0x%x",bit,new_val);
                    SET_BIT_NUM(new_val, bit);
                    // LOG_DEBUG(SYS,"Res 0x%x",new_val);
                    bit++;
                } break;
                case 'X':
                case 'x': {
                    bit++;
                } break;
                case '_':
                    break;
                default: {
#ifdef HAS_LOG
                    LOG_DEBUG(SYS, "MaskErr [%s]", in_mask);
#endif
                }

                break;
                }
            }
        } else {
#ifdef HAS_LOG
            LOG_ERROR(SYS, "InvalMask[%s]", in_mask);
#endif
        }
    }
    return new_val;
}
