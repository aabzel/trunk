#include "print_format.h"

#include <stdbool.h>
#include <string.h>

#include "convert.h"

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif

static void print_format_s64(ostream_t* s64__stream, const char s64__format[], uint8_t s64__values_count,
                             int64_t s64__value_1, int64_t s64__value_2, int64_t s64__value_3,
                             const char s64__ending[]);
static void print_format_u64(ostream_t* u64__stream, const char u64__format[], uint8_t u64__values_count,
                             uint64_t u64__value_1, uint64_t u64__value_2, uint64_t u64__value_3,
                             const char u64__ending[]);
static void print_format_s32(ostream_t* s32__stream, const char s32__format[], uint8_t s32__values_count,
                             int32_t s32__value_1, int32_t s32__value_2, int32_t s32__value_3,
                             const char s32__ending[]);
static void print_format_u32(ostream_t* u32__stream, const char u32__format[], uint8_t u32__values_count,
                             uint32_t u32__value_1, uint32_t u32__value_2, uint32_t u32__value_3,
                             const char u32__ending[]);
#ifdef HAS_STR2_FLOAT
static void print_format_flt(ostream_t* flt__stream, const char flt__format[], uint8_t flt__values_count,
                             float flt__value_1, float flt__value_2, float flt__value_3, const char flt__ending[]);
#endif

static void print_format_dbl(ostream_t* dbl__stream, const char dbl__format[], uint8_t dbl__values_count,
                             double dbl__value_1, double dbl__value_2, double dbl__value_3, const char dbl__ending[]);

void print_format_s64_1(ostream_t* s64_1__stream, const char s64_1__format[], int64_t s64_1__value_1,
                        const char s64_1__ending[]) {
    print_format_s64(s64_1__stream, s64_1__format, 1U, s64_1__value_1, s64_1__value_1, s64_1__value_1, s64_1__ending);
}

void print_format_s64_2(ostream_t* s64_2__stream, const char s64_2__format[], int64_t s64_2__value_1,
                        int64_t s64_2__value_2, const char s64_2__ending[]) {
    print_format_s64(s64_2__stream, s64_2__format, 2U, s64_2__value_1, s64_2__value_2, s64_2__value_2, s64_2__ending);
}

void print_format_s64_3(ostream_t* s64_3__stream, const char s64_3__format[], int64_t s64_3__value_1,
                        int64_t s64_3__value_2, int64_t s64_3__value_3, const char s64_3__ending[]) {
    print_format_s64(s64_3__stream, s64_3__format, 3U, s64_3__value_1, s64_3__value_2, s64_3__value_3, s64_3__ending);
}

void print_format_u64_1(ostream_t* u64_1__stream, const char u64_1__format[], uint64_t u64_1__value_1,
                        const char u64_1__ending[]) {
    print_format_u64(u64_1__stream, u64_1__format, 1U, u64_1__value_1, u64_1__value_1, u64_1__value_1, u64_1__ending);
}

void print_format_u64_2(ostream_t* u64_2__stream, const char u64_2__format[], uint64_t u64_2__value_1,
                        uint64_t u64_2__value_2, const char u64_2__ending[]) {
    print_format_u64(u64_2__stream, u64_2__format, 2U, u64_2__value_1, u64_2__value_2, u64_2__value_2, u64_2__ending);
}

void print_format_u64_3(ostream_t* u64_3__stream, const char u64_3__format[], uint64_t u64_3__value_1,
                        uint64_t u64_3__value_2, uint64_t u64_3__value_3, const char u64_3__ending[]) {
    print_format_u64(u64_3__stream, u64_3__format, 3U, u64_3__value_1, u64_3__value_2, u64_3__value_3, u64_3__ending);
}

void print_format_s32_1(ostream_t* s32_1__stream, const char s32_1__format[], int32_t s32_1__value_1,
                        const char s32_1__ending[]) {
    print_format_s32(s32_1__stream, s32_1__format, 1U, s32_1__value_1, s32_1__value_1, s32_1__value_1, s32_1__ending);
}

void print_format_s32_2(ostream_t* s32_2__stream, const char s32_2__format[], int32_t s32_2__value_1,
                        int32_t s32_2__value_2, const char s32_2__ending[]) {
    print_format_s32(s32_2__stream, s32_2__format, 2U, s32_2__value_1, s32_2__value_2, s32_2__value_2, s32_2__ending);
}

void print_format_s32_3(ostream_t* s32_3__stream, const char s32_3__format[], int32_t s32_3__value_1,
                        int32_t s32_3__value_2, int32_t s32_3__value_3, const char s32_3__ending[]) {
    print_format_s32(s32_3__stream, s32_3__format, 3U, s32_3__value_1, s32_3__value_2, s32_3__value_3, s32_3__ending);
}

void print_format_u32_1(ostream_t* u32_1__stream, const char u32_1__format[], uint32_t u32_1__value_1,
                        const char u32_1__ending[]) {
    print_format_u32(u32_1__stream, u32_1__format, 1U, u32_1__value_1, u32_1__value_1, u32_1__value_1, u32_1__ending);
}

void print_format_u32_2(ostream_t* u32_2__stream, const char u32_2__format[], uint32_t u32_2__value_1,
                        uint32_t u32_2__value_2, const char u32_2__ending[]) {
    print_format_u32(u32_2__stream, u32_2__format, 2U, u32_2__value_1, u32_2__value_2, u32_2__value_2, u32_2__ending);
}

void print_format_u32_3(ostream_t* u32_3__stream, const char u32_3__format[], uint32_t u32_3__value_1,
                        uint32_t u32_3__value_2, uint32_t u32_3__value_3, const char u32_3__ending[]) {
    print_format_u32(u32_3__stream, u32_3__format, 3U, u32_3__value_1, u32_3__value_2, u32_3__value_3, u32_3__ending);
}

#ifdef HAS_STR2_FLOAT
void print_format_flt_1(ostream_t* flt_1__stream, const char flt_1__format[], float flt_1__value_1,
                        const char flt_1__ending[]) {
    print_format_flt(flt_1__stream, flt_1__format, 1U, flt_1__value_1, flt_1__value_1, flt_1__value_1, flt_1__ending);
}
#endif

#ifdef HAS_STR2_FLOAT
void print_format_flt_2(ostream_t* flt_2__stream, const char flt_2__format[], float flt_2__value_1,
                        float flt_2__value_2, const char flt_2__ending[]) {
    print_format_flt(flt_2__stream, flt_2__format, 2U, flt_2__value_1, flt_2__value_2, flt_2__value_2, flt_2__ending);
}
#endif

#ifdef HAS_STR2_FLOAT
void print_format_flt_3(ostream_t* flt_3__stream, const char flt_3__format[], float flt_3__value_1,
                        float flt_3__value_2, float flt_3__value_3, const char flt_3__ending[]) {
    print_format_flt(flt_3__stream, flt_3__format, 3U, flt_3__value_1, flt_3__value_2, flt_3__value_3, flt_3__ending);
}
#endif

void print_format_dbl_1(ostream_t* dbl_1__stream, const char dbl_1__format[], double dbl_1__value_1,
                        const char dbl_1__ending[]) {
    print_format_dbl(dbl_1__stream, dbl_1__format, 1U, dbl_1__value_1, dbl_1__value_1, dbl_1__value_1, dbl_1__ending);
}

void print_format_dbl_2(ostream_t* dbl_2__stream, const char dbl_2__format[], double dbl_2__value_1,
                        double dbl_2__value_2, const char dbl_2__ending[]) {
    print_format_dbl(dbl_2__stream, dbl_2__format, 2U, dbl_2__value_1, dbl_2__value_2, dbl_2__value_2, dbl_2__ending);
}

void print_format_dbl_3(ostream_t* dbl_3__stream, const char dbl_3__format[], double dbl_3__value_1,
                        double dbl_3__value_2, double dbl_3__value_3, const char dbl_3__ending[]) {
    print_format_dbl(dbl_3__stream, dbl_3__format, 3U, dbl_3__value_1, dbl_3__value_2, dbl_3__value_3, dbl_3__ending);
}

#ifdef HAS_NUM_DIAG
static bool is_format_string(const char string[], uint8_t* arg_number) {
    static const uint8_t OPEN_BRACE = (uint8_t)'{';
    static const uint8_t CLOS_BRACE = (uint8_t)'}';
    static const uint8_t MIN_ARG = (uint8_t)'0';
    static const uint8_t MAX_ARG = (uint8_t)'2';

    bool is_format = false;

    uint8_t char0 = (uint8_t)string[0];
    uint8_t char1 = (uint8_t)string[1];
    uint8_t char2 = (uint8_t)string[2];

    bool is_open_brace = (char0 == OPEN_BRACE);
    bool is_arg_value = ((char1 >= MIN_ARG) && (char1 <= MAX_ARG));
    bool is_clos_brace = (char2 == CLOS_BRACE);

    if((is_open_brace == true) && (is_arg_value == true) && (is_clos_brace == true)) {
        *arg_number = (char1 - MIN_ARG);
        is_format = true;
    }

    return is_format;
}
#endif

static void print_format_s64(ostream_t* s64__stream, const char s64__format[], uint8_t s64__values_count,
                             int64_t s64__value_1, int64_t s64__value_2, int64_t s64__value_3,
                             const char s64__ending[]) {
#ifdef HAS_NUM_DIAG
    uint32_t s64__fmt_index = 0U;
    uint32_t s64__fmt_len = strlen(s64__format);

    int64_t s64__values[3] = {0};
    s64__values[0] = s64__value_1;
    s64__values[1] = s64__value_2;
    s64__values[2] = s64__value_3;

    while(s64__fmt_index < s64__fmt_len) {
        uint8_t s64__arg_index = 0U;
        if(is_format_string(&s64__format[s64__fmt_index], &s64__arg_index) == true) {
            if(s64__arg_index < s64__values_count) {
                oputs(s64__stream, rx_ltoa64(s64__values[s64__arg_index]));
            }
            s64__fmt_index += 3U;
        } else {
            oputc(s64__stream, s64__format[s64__fmt_index]);
            s64__fmt_index++;
        }
    }

    oputs(s64__stream, s64__ending);
#endif
}

static void print_format_u64(ostream_t* u64__stream, const char u64__format[], uint8_t u64__values_count,
                             uint64_t u64__value_1, uint64_t u64__value_2, uint64_t u64__value_3,
                             const char u64__ending[]) {
#ifdef HAS_NUM_DIAG
    uint32_t u64__fmt_index = 0U;
    uint32_t u64__fmt_len = strlen(u64__format);

    uint64_t u64__values[3];
    u64__values[0] = u64__value_1;
    u64__values[1] = u64__value_2;
    u64__values[2] = u64__value_3;

    while(u64__fmt_index < u64__fmt_len) {
        uint8_t u64__arg_index = 0U;
        if(is_format_string(&u64__format[u64__fmt_index], &u64__arg_index) == true) {
            if(u64__arg_index < u64__values_count) {
                oputs(u64__stream, rx_utoa64(u64__values[u64__arg_index]));
            }
            u64__fmt_index += 3U;
        } else {
            oputc(u64__stream, u64__format[u64__fmt_index]);
            u64__fmt_index++;
        }
    }

    oputs(u64__stream, u64__ending);
#endif
}

static void print_format_s32(ostream_t* s32__stream, const char s32__format[], uint8_t s32__values_count,
                             int32_t s32__value_1, int32_t s32__value_2, int32_t s32__value_3,
                             const char s32__ending[]) {
#ifdef HAS_NUM_DIAG
    uint32_t s32__fmt_index = 0U;
    uint32_t s32__fmt_len = strlen(s32__format);

    int32_t s32__values[3];
    s32__values[0] = s32__value_1;
    s32__values[1] = s32__value_2;
    s32__values[2] = s32__value_3;

    while(s32__fmt_index < s32__fmt_len) {
        uint8_t s32__arg_index = 0U;
        if(is_format_string(&s32__format[s32__fmt_index], &s32__arg_index) == true) {
            if(s32__arg_index < s32__values_count) {
                oputs(s32__stream, rx_ltoa32(s32__values[s32__arg_index]));
            }
            s32__fmt_index += 3U;
        } else {
            oputc(s32__stream, s32__format[s32__fmt_index]);
            s32__fmt_index++;
        }
    }

    oputs(s32__stream, s32__ending);
#endif
}

static void print_format_u32(ostream_t* u32__stream, const char u32__format[], uint8_t u32__values_count,
                             uint32_t u32__value_1, uint32_t u32__value_2, uint32_t u32__value_3,
                             const char u32__ending[]) {
#ifdef HAS_NUM_DIAG
    uint32_t u32__fmt_index = 0U;
    uint32_t u32__fmt_len = strlen(u32__format);

    uint32_t u32__values[3];
    u32__values[0] = u32__value_1;
    u32__values[1] = u32__value_2;
    u32__values[2] = u32__value_3;

    while(u32__fmt_index < u32__fmt_len) {
        uint8_t u32__arg_index = 0U;
        if(is_format_string(&u32__format[u32__fmt_index], &u32__arg_index) == true) {
            if(u32__arg_index < u32__values_count) {
                oputs(u32__stream, rx_utoa32(u32__values[u32__arg_index]));
            }
            u32__fmt_index += 3U;
        } else {
            oputc(u32__stream, u32__format[u32__fmt_index]);
            u32__fmt_index++;
        }
    }

    oputs(u32__stream, u32__ending);
#endif
}

#ifdef HAS_STR2_FLOAT
static void print_format_flt(ostream_t* flt__stream, const char flt__format[], uint8_t flt__values_count,
                             float flt__value_1, float flt__value_2, float flt__value_3, const char flt__ending[]) {
    uint32_t flt__fmt_index = 0U;
    uint32_t flt__fmt_len = strlen(flt__format);

    float flt__values[3];
    flt__values[0] = flt__value_1;
    flt__values[1] = flt__value_2;
    flt__values[2] = flt__value_3;

    while(flt__fmt_index < flt__fmt_len) {
        uint8_t flt__arg_index = 0U;
        if(is_format_string(&flt__format[flt__fmt_index], &flt__arg_index) == true) {
            if(flt__arg_index < flt__values_count) {
                const char* ptr = NULL;
                float val = flt__values[flt__arg_index];
                ptr = (const char*)rx_ftoa(val);
                oputs(flt__stream, (const char*)ptr);
            }
            flt__fmt_index += 3U;
        } else {
            oputc(flt__stream, flt__format[flt__fmt_index]);
            flt__fmt_index++;
        }
    }

    oputs(flt__stream, flt__ending);
}
#endif

static void print_format_dbl(ostream_t* dbl__stream, const char dbl__format[], uint8_t dbl__values_count,
                             double dbl__value_1, double dbl__value_2, double dbl__value_3, const char dbl__ending[]) {
#ifdef HAS_NUM_DIAG
    uint32_t dbl__fmt_index = 0U;
    uint32_t dbl__fmt_len = strlen(dbl__format);

    double dbl__values[3];
    dbl__values[0] = dbl__value_1;
    dbl__values[1] = dbl__value_2;
    dbl__values[2] = dbl__value_3;

    while(dbl__fmt_index < dbl__fmt_len) {
        uint8_t dbl__arg_index = 0U;
        if(is_format_string(&dbl__format[dbl__fmt_index], &dbl__arg_index) == true) {
            if(dbl__arg_index < dbl__values_count) {
                oputs(dbl__stream, rx_dtoa(dbl__values[dbl__arg_index]));
            }
            dbl__fmt_index += 3U;
        } else {
            oputc(dbl__stream, dbl__format[dbl__fmt_index]);
            dbl__fmt_index++;
        }
    }

    oputs(dbl__stream, dbl__ending);
#endif
}
