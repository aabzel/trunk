/// Copyright by Syntacore LLC © 2016, 2017. See LICENSE for details
/// @file       <csr.h>
/// Architecture specific CSR's defs and inlines
//  control/status registers

#ifndef SCR_CSR_H
#define SCR_CSR_H

#include <stdint.h>
#include <stdbool.h>

#define __xstringify(s) __stringify(s)
#define __stringify(s) #s

#ifdef read_csr
#undef read_csr
#endif

#ifdef write_csr
#undef write_csr
#endif

#ifdef swap_csr
#undef swap_csr
#endif

#ifdef set_csr
#undef set_csr
#endif

#ifdef clear_csr
#undef clear_csr
#endif

#ifdef rdtime
#undef rdtime
#endif

#ifdef rdcycle
#undef rdcycle
#endif

#ifdef rdinstret
#undef rdinstret
#endif

#define read_csr(reg)                                               \
    ({                                                              \
        unsigned long __tmp;                                        \
        __asm__ volatile ("csrr %0, " __xstringify(reg) : "=r"(__tmp)); \
        __tmp;                                                      \
    })

#define write_csr(reg, val)                                             \
    do {                                                                \
        if (__builtin_constant_p(val) && (unsigned long)(val) < 32) \
            __asm__ volatile ("csrw " __xstringify(reg) ", %0" :: "i"(val)); \
        else                                                            \
            __asm__ volatile ("csrw " __xstringify(reg) ", %0" :: "r"(val)); \
    } while (0)

#define swap_csr(reg, val)                                              \
    ({                                                                  \
        unsigned long __tmp;                                            \
        if (__builtin_constant_p(val) && (val) == 0)                    \
            __asm__ volatile ("csrrw %0, " __xstringify(reg) ", zero" :  "=r"(__tmp) :); \
        else if (__builtin_constant_p(val) && (unsigned long)(val) < 32) \
            __asm__ volatile ("csrrw %0, " __xstringify(reg) ", %1" : "=r"(__tmp) : "i"(val)); \
        else                                                            \
            __asm__ volatile ("csrrw %0, " __xstringify(reg) ", %1" : "=r"(__tmp) : "r"(val)); \
        __tmp;                                                          \
    })

#define set_csr(reg, bit)                                               \
    ({                                                                  \
        unsigned long __tmp;                                            \
        if (__builtin_constant_p(bit) && (bit) < 32)                    \
            __asm__ volatile ("csrrs %0, " __xstringify(reg) ", %1" : "=r"(__tmp) : "i"(bit)); \
        else                                                            \
            __asm__ volatile ("csrrs %0, " __xstringify(reg) ", %1" : "=r"(__tmp) : "r"(bit)); \
        __tmp;                                                          \
    })

#define clear_csr(reg, bit)                                             \
    ({                                                                  \
        unsigned long __tmp;                                            \
        if (__builtin_constant_p(bit) && (bit) < 32)                    \
            __asm__ volatile ("csrrc %0, " __xstringify(reg) ", %1" : "=r"(__tmp) : "i"(bit)); \
        else                                                            \
            __asm__ volatile ("csrrc %0, " __xstringify(reg) ", %1" : "=r"(__tmp) : "r"(bit)); \
        __tmp;                                                          \
    })

#define rdtime() read_csr(time)
#define rdcycle() read_csr(cycle)
#define rdinstret() read_csr(instret)

static inline unsigned long __attribute__((const)) cpuid(void)
{
  unsigned long res;
  __asm__ ("csrr %0, mcpuid" : "=r"(res));
  return res;
}

static inline unsigned long __attribute__((const)) impid(void)
{
  unsigned long res;
  __asm__ ("csrr %0, mimpid" : "=r"(res));
  return res;
}

#endif // SCR_CSR_H
