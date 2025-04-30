#ifndef TEST_CONVERT_H
#define TEST_CONVERT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif


bool test_try_str2type(void);
bool test_sscanf(void) ;
bool test_convert_try_str2number(void);
bool test_try_str2suffix_number(void);
bool test_convert_try_str2int8(void);
bool test_convert_try_str2uint8_invalid(void);
bool test_convert_is_dec_str(void);
bool test_convert_is_hex_str(void);
bool test_convert_try_str2uint8(void);
bool test_convert_try_strl2uint16_hex(void);
bool test_convert_try_strl2uint8_hex(void);
bool test_convert_try_str2int16(void);
bool test_convert_try_str2uint16(void);
bool test_convert_try_str2int32(void);
bool test_convert_try_str2uint32(void);
bool test_convert_try_str2luint32_hex(void);
bool test_convert_try_str2luint32(void);
bool test_convert_try_str2lint32(void);
bool test_convert_try_str2uint32_hex(void);
bool test_convert_try_str2lint64(void);
bool test_convert_try_str2luint64(void);
bool test_convert_try_str2int64(void);
bool test_convert_try_str2uint64(void);
bool test_convert_try_str2float(void);
bool test_convert_try_str2double(void);
bool test_convert_try_strl2double(void);
bool test_convert_try_str2bool(void);
bool test_convert_Ltoa32(void);
bool test_convert_Ltoa64(void);
bool test_convert_ULtoa32(void);
bool test_convert_ULtoa64(void);
bool test_double_to_str(void);
bool test_convert_Ltoa32_(void);
bool test_convert_Ltoa64_(void);
bool test_convert_ULtoa32_(void);
bool test_convert_ULtoa64_(void);
bool test_convert_ULtoa_hex64(void);
bool test_convert_ULtoa_hex32(void);
bool test_convert_str_sizeof(void);
bool test_convert_dtoa(void);
bool test_convert_dtoa_trim_zero(void);
bool test_convert_dtoa_nan(void);
bool test_convert_dtoa_inf(void);
bool test_convert_char_2_dec(void);
bool test_convert_ftoa_nan(void);
bool test_convert_ftoa_inf(void);
bool test_convert_rx_dtoa(void);
bool test_convert_ltoa_hex64(void);
bool test_parse_data_type(void);
bool test_convert_bool2name(void);
bool test_convert_utoa_bin32(void);
bool test_convert_utoa_bin24(void);
bool test_convert_try_str_ascii2nimble(void);
bool test_convert_try_str2array(void);
bool test_convert_utoa_bin16(void);
bool test_convert_utoa_bin16_plain(void);
bool test_convert_assemble_uint32(void);



#define TEST_SUIT_CONVERT                                                                                              \
    {"double_to_str", test_double_to_str},                            \
    {"str2number", test_convert_try_str2number},                            \
    {"convert_utoa_bin16_plain", test_convert_utoa_bin16_plain},                            \
    {"char_2_dec", test_convert_char_2_dec},            \
    {"test_try_str2type", test_try_str2type},            \
    {"try_str2suffix_number", test_try_str2suffix_number},            \
    {"parse_data_type", test_parse_data_type},             \
    {"strl2double", test_convert_try_strl2double},           \
    {"str2array", test_convert_try_str2array},                 \
    {"str2int8", test_convert_try_str2int8},                            \
    {"str2uint8_invalid", test_convert_try_str2uint8_invalid},       \
    {"Ascii2nimble", test_convert_try_str_ascii2nimble},            \
{"is_dec_str", test_convert_is_dec_str},            \
    {"is_hex_str", test_convert_is_hex_str}, {"str2uint8", test_convert_try_str2uint8},                            \
        {"strl2uint16_hex", test_convert_try_strl2uint16_hex}, {"strl2uint8_hex", test_convert_try_strl2uint8_hex},    \
        {"str2int16", test_convert_try_str2int16}, {"str2uint16", test_convert_try_str2uint16},                        \
        {"str2int32", test_convert_try_str2int32}, {"str2uint32", test_convert_try_str2uint32},                        \
        {"str2luint32_hex", test_convert_try_str2luint32_hex}, {"str2luint32", test_convert_try_str2luint32},          \
        {"str2lint32", test_convert_try_str2lint32}, {"str2uint32_hex", test_convert_try_str2uint32_hex},              \
        {"str2lint64", test_convert_try_str2lint64}, {"str2luint64", test_convert_try_str2luint64},                    \
        {"str2int64", test_convert_try_str2int64}, {"str2uint64", test_convert_try_str2uint64},                        \
        {"str2float", test_convert_try_str2float}, {"str2double", test_convert_try_str2double},                        \
        {"try_str2bool", test_convert_try_str2bool}, {"Ltoa32", test_convert_Ltoa32}, {"Ltoa64", test_convert_Ltoa64}, \
        {"ULtoa32", test_convert_ULtoa32}, {"ULtoa64", test_convert_ULtoa64}, {"Ltoa32_", test_convert_Ltoa32_},       \
        {"Ltoa64_", test_convert_Ltoa64_}, {"ULtoa32_", test_convert_ULtoa32_}, {"ULtoa64_", test_convert_ULtoa64_},   \
        {"ULtoa_hex64", test_convert_ULtoa_hex64}, {"ULtoa_hex32", test_convert_ULtoa_hex32},                          \
        {"str_sizeof", test_convert_str_sizeof}, {"dtoa_trim_zero", test_convert_dtoa_trim_zero},                      \
        {"ftoa_nan", test_convert_ftoa_nan}, {"ftoa_inf", test_convert_ftoa_inf}, {"rx_dtoa", test_convert_rx_dtoa},   \
        {"ltoa_hex64", test_convert_ltoa_hex64}, {"bool2name", test_convert_bool2name},                                \
        {"utoa_bin32", test_convert_utoa_bin32}, {"utoa_bin24", test_convert_utoa_bin24},                              \
        {"utoa_bin16", test_convert_utoa_bin16}, {"assemble_uint32", test_convert_assemble_uint32},

/*{"dtoa", test_convert_dtoa}, */
/*{"dtoa_nan", test_convert_dtoa_nan},*/
/*{"dtoa_inf", test_convert_dtoa_inf},*/
#ifdef __cplusplus
}
#endif

#endif /* TEST_CONVERT_H */
