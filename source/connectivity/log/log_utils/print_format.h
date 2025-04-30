#ifndef PRINT_FORMAT_H_
#define PRINT_FORMAT_H_

#include "ostream.h"
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Quick HOWTO */
/* *********** */
/* You can find usage examples at utils_test/src/format_test.cpp */
/* Limitations: one format string may consist of no more than 3 parameters of
 * one type */

/* may the MISRA be with you */

void print_format_s64_1(ostream_t* s64_1__stream, const char s64_1__format[], int64_t s64_1__value_1,
                        const char s64_1__ending[]);
void print_format_s64_2(ostream_t* s64_2__stream, const char s64_2__format[], int64_t s64_2__value_1,
                        int64_t s64_2__value_2, const char s64_2__ending[]);
void print_format_s64_3(ostream_t* s64_3__stream, const char s64_3__format[], int64_t s64_3__value_1,
                        int64_t s64_3__value_2, int64_t s64_3__value_3, const char s64_3__ending[]);

void print_format_u64_1(ostream_t* u64_1__stream, const char u64_1__format[], uint64_t u64_1__value_1,
                        const char u64_1__ending[]);
void print_format_u64_2(ostream_t* u64_2__stream, const char u64_2__format[], uint64_t u64_2__value_1,
                        uint64_t u64_2__value_2, const char u64_2__ending[]);
void print_format_u64_3(ostream_t* u64_3__stream, const char u64_3__format[], uint64_t u64_3__value_1,
                        uint64_t u64_3__value_2, uint64_t u64_3__value_3, const char u64_3__ending[]);

void print_format_s32_1(ostream_t* s32_1__stream, const char s32_1__format[], int32_t s32_1__value_1,
                        const char s32_1__ending[]);
void print_format_s32_2(ostream_t* s32_2__stream, const char s32_2__format[], int32_t s32_2__value_1,
                        int32_t s32_2__value_2, const char s32_2__ending[]);
void print_format_s32_3(ostream_t* s32_3__stream, const char s32_3__format[], int32_t s32_3__value_1,
                        int32_t s32_3__value_2, int32_t s32_3__value_3, const char s32_3__ending[]);

void print_format_u32_1(ostream_t* u32_1__stream, const char u32_1__format[], uint32_t u32_1__value_1,
                        const char u32_1__ending[]);
void print_format_u32_2(ostream_t* u32_2__stream, const char u32_2__format[], uint32_t u32_2__value_1,
                        uint32_t u32_2__value_2, const char u32_2__ending[]);
void print_format_u32_3(ostream_t* u32_3__stream, const char u32_3__format[], uint32_t u32_3__value_1,
                        uint32_t u32_3__value_2, uint32_t u32_3__value_3, const char u32_3__ending[]);

void print_format_flt_1(ostream_t* flt_1__stream, const char flt_1__format[], float flt_1__value_1,
                        const char flt_1__ending[]);
void print_format_flt_2(ostream_t* flt_2__stream, const char flt_2__format[], float flt_2__value_1,
                        float flt_2__value_2, const char flt_2__ending[]);
void print_format_flt_3(ostream_t* flt_3__stream, const char flt_3__format[], float flt_3__value_1,
                        float flt_3__value_2, float flt_3__value_3, const char flt_3__ending[]);

void print_format_dbl_1(ostream_t* dbl_1__stream, const char dbl_1__format[], double dbl_1__value_1,
                        const char dbl_1__ending[]);
void print_format_dbl_2(ostream_t* dbl_2__stream, const char dbl_2__format[], double dbl_2__value_1,
                        double dbl_2__value_2, const char dbl_2__ending[]);
void print_format_dbl_3(ostream_t* dbl_3__stream, const char dbl_3__format[], double dbl_3__value_1,
                        double dbl_3__value_2, double dbl_3__value_3, const char dbl_3__ending[]);

#ifdef __cplusplus
}
#endif

#endif
