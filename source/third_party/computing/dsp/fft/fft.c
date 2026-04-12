#include "fft.h"

#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define SQRT3 1.7320508075688771931766041

#define SQRT3_DIV_2 0.8660254037844385965883021
#define M_PI_MUL_2 6.2831853071795862319959269
#define ONE_OVER_THREE 0.333333333333333333333333

#define W51_REAL_ABS 0.3090169943749474512628694
#define W51_IMG_ABS 0.9510565162951535311819384
#define W52_REAL_ABS 0.8090169943749473402405670
#define W52_IMG_ABS 0.5877852522924732481257593

#define sincos(deg, _s, _c)                                                                                            \
    do {                                                                                                               \
        *(_s) = sin((deg));                                                                                            \
        *(_c) = cos((deg));                                                                                            \
    } while(0)

#define OMEGA_WITH_DEG(deg)                                                                                            \
    __extension__({                                                                                                    \
        double __cos, __sin;                                                                                           \
        sincos(deg, &__sin, &__cos);                                                                                   \
        __cos - I* __sin;                                                                                              \
    })

#define CONJ_OMEGA_WITH_DEG(deg)                                                                                       \
    __extension__({                                                                                                    \
        double __cos, __sin;                                                                                           \
        sincos(deg, &__sin, &__cos);                                                                                   \
        __cos + I* __sin;                                                                                              \
    })

#define OMEGA_WITH_2PI_DIV_N(ij, PI_2_DIV_N) OMEGA_WITH_DEG(ij* PI_2_DIV_N)
#define CONJ_OMEGA_WITH_2PI_DIV_N(ij, PI_2_DIV_N) CONJ_OMEGA_WITH_DEG(ij* PI_2_DIV_N)

static inline complex double omega_with_2pi_div_n(int ij, double cst) { return OMEGA_WITH_2PI_DIV_N(ij, cst); }

static inline complex double conj_omega_with_2pi_div_n(int ij, double cst) {
    return CONJ_OMEGA_WITH_2PI_DIV_N(ij, cst);
}

#define OMEGA(ij, N) OMEGA_WITH_2PI_DIV_N(ij, (M_PI_MUL_2 / (N)))
//#define CONJ_OMEGA(ij, N) CONJ_OMEGA_WITH_2PI_DIV_N(ij, (M_PI_MUL_2 / (N)))

// In this function I want to perform this operation
//
//         +--     --+
// [out] = |  1,  1  | * [in]
//         |  1, -1  |
//         +--     --+
#define _FFT2_CONTENT                                                                                                  \
    {                                                                                                                  \
        out[0] = in[0] + in[1];                                                                                        \
        out[1] = in[0] - in[1];                                                                                        \
    }

#define _INV_FFT2_CONTENT                                                                                              \
    {                                                                                                                  \
        out[0] = 0.5 * (in[0] + in[1]);                                                                                \
        out[1] = 0.5 * (in[0] - in[1]);                                                                                \
    }

// In this function I want to perform FFT3 operation
// and the FFT3 operation is defined as
//           0          1              2
//         +--                                     --+
//  out1   | 1,         1,             1             |  in1
//         |                                         |
//  out2 = | 1, (-1-sqrt(3))/2    (-1+sqrt(3))/2     |  in2
//         |                                         |
//  out3   | 1  (-1+sqrt(3))/2    (-1-sqrt(3))/2     |  in3
//         +--                                     --+
//
#define _FFT3_CONTENT                                                                                                  \
    {                                                                                                                  \
        static const complex double sq3_ps_1_d_2 = -0.5 + SQRT3_DIV_2 * I;                                             \
        static const complex double sq3_mi_1_d_2 = -0.5 - SQRT3_DIV_2 * I;                                             \
        out[0] = in[0] + in[1] + in[2];                                                                                \
        out[1] = in[0] + in[1] * sq3_mi_1_d_2 + in[2] * sq3_ps_1_d_2;                                                  \
        out[2] = in[0] + in[1] * sq3_ps_1_d_2 + in[2] * sq3_mi_1_d_2;                                                  \
    }

#define _INV_FFT3_CONTENT                                                                                              \
    {                                                                                                                  \
        static const complex double sq3_ps_1_d_2 = -0.5 + SQRT3_DIV_2 * I;                                             \
        static const complex double sq3_mi_1_d_2 = -0.5 - SQRT3_DIV_2 * I;                                             \
        out[0] = in[0] + in[1] + in[2];                                                                                \
        out[1] = in[0] + in[1] * sq3_ps_1_d_2 + in[2] * sq3_mi_1_d_2;                                                  \
        out[2] = in[0] + in[1] * sq3_mi_1_d_2 + in[2] * sq3_ps_1_d_2;                                                  \
        out[0] *= ONE_OVER_THREE;                                                                                      \
        out[1] *= ONE_OVER_THREE;                                                                                      \
        out[2] *= ONE_OVER_THREE;                                                                                      \
    }

#define _FFT5_CONTENT                                                                                                  \
    {                                                                                                                  \
        static const complex double w51 = W51_REAL_ABS - I * W51_IMG_ABS;                                              \
        static const complex double w52 = -W52_REAL_ABS - I * W52_IMG_ABS;                                             \
        static const complex double w53 = -W52_REAL_ABS + I * W52_IMG_ABS;                                             \
        static const complex double w54 = W51_REAL_ABS + I * W51_IMG_ABS;                                              \
        out[0] = in[0] + in[1] + in[2] + in[3] + in[4];                                                                \
        out[1] = in[0] + w51 * in[1] + w52 * in[2] + w53 * in[3] + w54 * in[4];                                        \
        out[2] = in[0] + w52 * in[1] + w54 * in[2] + w51 * in[3] + w53 * in[4];                                        \
        out[3] = in[0] + w53 * in[1] + w51 * in[2] + w54 * in[3] + w52 * in[4];                                        \
        out[4] = in[0] + w54 * in[1] + w53 * in[2] + w52 * in[3] + w51 * in[4];                                        \
    }

#define _INV_FFT5_CONTENT                                                                                              \
    {                                                                                                                  \
        static const complex double w51 = (W51_REAL_ABS - I * W51_IMG_ABS);                                            \
        static const complex double w52 = (-W52_REAL_ABS - I * W52_IMG_ABS);                                           \
        static const complex double w53 = (-W52_REAL_ABS + I * W52_IMG_ABS);                                           \
        static const complex double w54 = (W51_REAL_ABS + I * W51_IMG_ABS);                                            \
        out[0] = 0.2 * (in[0] + in[1] + in[2] + in[3] + in[4]);                                                        \
        out[1] = 0.2 * (in[0] + w54 * in[1] + w53 * in[2] + w52 * in[3] + w51 * in[4]);                                \
        out[2] = 0.2 * (in[0] + w53 * in[1] + w51 * in[2] + w54 * in[3] + w52 * in[4]);                                \
        out[3] = 0.2 * (in[0] + w52 * in[1] + w54 * in[2] + w51 * in[3] + w53 * in[4]);                                \
        out[4] = 0.2 * (in[0] + w51 * in[1] + w52 * in[2] + w53 * in[3] + w54 * in[4]);                                \
    }

// clang-format off
#define DECLARE_FFTX_FUNC(num)                                             \
    static inline void FFT##num(                                           \
            complex double in[],                                           \
            complex double out[])                                          \
                    _FFT##num##_CONTENT                                    \
                                                                           
#define DECLARE_IFFTX_FUNC(num)                                            \
    static inline void IFFT##num(                                          \
            complex double in[],                                           \
            complex double out[])                                          \
                    _INV_FFT##num##_CONTENT                                \
                                                                           \
// clang-format on

DECLARE_FFTX_FUNC(2)
DECLARE_FFTX_FUNC(3)
DECLARE_FFTX_FUNC(5)

DECLARE_IFFTX_FUNC(2)
DECLARE_IFFTX_FUNC(3)
DECLARE_IFFTX_FUNC(5)



typedef void (*fft_native_func_t)(complex double *, complex double *);

typedef void (*fft_mat_mul_func_t)(complex double *,
                                   complex double *,
                                   complex double const *const *,
                                   int);
typedef void (*mat_mult_func_t)(complex double *,
                                complex double *,
                                complex double **,
                                int);

typedef complex double (*omega_with_2pi_div_n_func_t)(int, double);


static void __FFT(complex double in[],
                  complex double out[],
                  complex double const *const *OMEGA_MAT,
                  fft_native_func_t functions[],
                  omega_with_2pi_div_n_func_t omega_func,
                  int size)
{
    if (size == 0) {
        return;
    } else if (size == 1) {
        out[0] = in[0];
    } else if (size == 2) {
        functions[0](in, out);
    } else if (size == 3) {
        functions[1](in, out);
    } else if (size == 5) {
        functions[2](in, out);
    } else {
        int p = 1;
        if (size % 2 == 0) {
            p = 2;
        } else if (size % 3 == 0) {
            p = 3;
        } else {
            for (int i = 5; i <= size; ++i) {
                if (size % i == 0) {
                    p = i;
                    break;
                }
            }
            if (p == size) {
                for (int i = 0; i < size; ++i) {
                    complex double sum = 0;
                    for (int j = 0; j < size; ++j) {
                        sum += in[j] * OMEGA_MAT[size][(i * j) % size];
                    }
                    out[i] = sum;
                }
                return;
            }
        }

        int new_size = size / p;
        complex double **entries_out, *__entries_out_content;
        complex double *entries_in = malloc(sizeof(complex double) * new_size);
        __entries_out_content =
            (complex double *) malloc(sizeof(complex double) * p * new_size);
        entries_out = (complex double **) malloc(sizeof(complex double *) * p);
        for (int i = 0; i < p; ++i) {
            entries_out[i] = __entries_out_content + (i * new_size);
        }

        // place the data;
        for (int i = 0; i < p; ++i) {
            for (int j = 0; j < new_size; ++j) {
                entries_in[j] = in[j * p + i];
            }
            __FFT(entries_in, entries_out[i], OMEGA_MAT, functions, omega_func,
                  new_size);
        }


        complex double *in_temp =
            (complex double *) malloc(sizeof(complex double) * (p << 1));
        complex double *out_temp = in_temp + p;

        for (int i = 0; i < new_size; ++i) {
            double m_pi_mul_2_sz = M_PI_MUL_2 / size;
            for (int j = 0; j < p; ++j) {
                in_temp[j] =
                    entries_out[j][i] * omega_func(i * j, m_pi_mul_2_sz);
            }
            __FFT(in_temp, out_temp, OMEGA_MAT, functions, omega_func, p);

            for (int j = 0; j < p; ++j) {
                out[i + new_size * j] = out_temp[j];
            }
        }
        free(in_temp);
        free(entries_in);
        free(entries_out);
        free(__entries_out_content);
    }
}

static void fft_iteration(complex double in[], complex double out[], int size, bool inverse)
{
    // from https://en.wikipedia.org/wiki/List_of_prime_numbers
    // There are 1000 prime numbers under 7919

    // omegas is a table to compute the FFT matrix first to reduct the redundant
    // computation. The initialization process would base on the prime divisor
    // number of @size.
    complex double **omegas = malloc(sizeof(complex double *) * 1000);
    memset(omegas, 0, sizeof(complex double *) * 1000);

    // defraction of size to init the omegas table
    int _tmp_size = size;
    int p = 2;
    while (p <= _tmp_size) {
        bool _in = false;
        while (_tmp_size % p == 0) {
            _tmp_size /= p;
            _in = true;
        }
        int _exp_conj = inverse * (-1) + !inverse;
        double __one_over_p = (inverse * (1.0 / p) + !inverse);
        if (_in) {
            omegas[p] = malloc(sizeof(complex double) * (p + 1));
            int half_p = p >> 1;
            for (int i = 0; i <= half_p; ++i) {
                omegas[p][i] = OMEGA(i * _exp_conj, p) * __one_over_p;
                omegas[p][p - i] = conj(omegas[p][i]);
            }
            omegas[p][0] = __one_over_p;
        }
        ++p;
    }

    fft_native_func_t functions[3];
    if (inverse) {
        functions[0] = IFFT2;
        functions[1] = IFFT3;
        functions[2] = IFFT5;
    } else {
        functions[0] = FFT2;
        functions[1] = FFT3;
        functions[2] = FFT5;
    }

    __FFT(in, out, (complex double const *const *) omegas, functions,
          (omega_with_2pi_div_n_func_t) ((unsigned long)
                                                 conj_omega_with_2pi_div_n *
                                             inverse +
                                         (unsigned long) omega_with_2pi_div_n *
                                             !inverse),
          size);

    for (int i = 0; i < 1000; ++i) {
        if (omegas[i] != 0) {
            free(omegas[i]);
        }
    }
    free(omegas);
}

void FFT_CALC(complex double in[], complex double out[], int size){
    fft_iteration(in, out, size, false);
}

void IFFT_CALC(complex double in[], complex double out[], int size){
    fft_iteration(in, out, size, true);
}

