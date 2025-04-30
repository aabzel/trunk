#ifndef UNIT_TEST_ASSERTS_H
#define UNIT_TEST_ASSERTS_H

#include <inttypes.h>
#include <math.h>
#include <string.h>

#include "array.h"
#include "float_utils.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#include "str_utils.h"
#include "unit_test_run.h"

#ifndef HAS_UNIT_TEST
#error "+HAS_UNIT_TEST"
#endif

#ifndef HAS_LOG
#error "Add LOG component"
#endif

#define TEST_EPSILONT 0.0001

/*Macros for Polymorphism*/

#define ASSERT_EQ_MEM(memL, memR, len)                                                                                 \
    do {                                                                                                               \
        bool res = array_is_equal((uint8_t*)memL, (uint8_t*)memR, len);                                                \
        if(false == res) {                                                                                             \
            LOG_ERROR(SYS, "%s:Line: %d different memory %d", __FUNCTION__, __LINE__);                                 \
            return false;                                                                                              \
        }                                                                                                              \
    } while(0);

#define ASSERT_NEAR(base, val, error)                                                                                  \
    do {                                                                                                               \
        if((base + error) < val) {                                                                                     \
            LOG_ERROR(SYS, "%s:Line: %d in val %f big ", __FUNCTION__, __LINE__, val);                                 \
            return false;                                                                                              \
        }                                                                                                              \
        if(val < (base - error)) {                                                                                     \
            LOG_ERROR(SYS, "%s:Line: %d in val %f small ", __FUNCTION__, __LINE__, val);                               \
            return false;                                                                                              \
        }                                                                                                              \
    } while(0);

#define ASSERT_TRUE(val_in)                                                                                            \
    do {                                                                                                               \
        bool assert_val = val_in;                                                                                             \
        if(false == ((bool)assert_val)) {                                                                                     \
            LOG_ERROR(SYS, "%s:Line: %d in val %d \n", __FUNCTION__, __LINE__, (int)assert_val);                              \
            return false;                                                                                              \
        }                                                                                                              \
    } while(0);

#define ASSERT_FALSE(val_in)                                                                                           \
    do {                                                                                                               \
        bool val = val_in;                                                                                             \
        if(true == ((bool)val)) {                                                                                      \
            LOG_ERROR(SYS, "%s:Line: %d in val %d \n", __FUNCTION__, __LINE__, (int)val);                              \
            return false;                                                                                              \
        }                                                                                                              \
    } while(0);

#define ASSERT_EQ(EXP_IN, REAL_IN)                                                                                     \
    do {                                                                                                               \
        int EXP = (int) EXP_IN;                                                                                              \
        int REAL = (int) REAL_IN;                                                                                            \
        if((EXP) != (REAL)) {                                                                                          \
            LOG_ERROR(SYS, "%s():Line: %d in Exp: %u  Real: %u=%d", __FUNCTION__, __LINE__, EXP, REAL, REAL);          \
            LOG_ERROR(SYS, "%s():Line: %d in ExpFloat: %f  RealFloat: %f", __FUNCTION__, __LINE__, EXP, REAL);         \
            LOG_ERROR(SYS, "%s():Line: %d in Exp: 0x%x Real: 0x%x", __FUNCTION__, __LINE__, EXP, REAL);                \
            return false;                                                                                              \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define ASSERT_EQ_DOUBLE(EXP, REAL)                                                                                    \
    do {                                                                                                               \
        if(false == is_double_equal_absolute(EXP,REAL,TEST_EPSILONT)) {                                                \
            LOG_ERROR(SYS, "%s():Line: %d in ExpFloat: %f  RealFloat: %f", __FUNCTION__, __LINE__, EXP, REAL);         \
            return false;                                                                                              \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define ASSERT_EQ_CONST(EXP, REAL)                                                                                     \
    do {                                                                                                               \
        if((EXP) != (REAL)) {                                                                                          \
            LOG_ERROR(SYS, "%s():Line: %d in Exp: %u  Real: %u=%d", __FUNCTION__, __LINE__, EXP, REAL, REAL);          \
            LOG_ERROR(SYS, "%s():Line: %d in ExpFloat: %f  RealFloat: %f", __FUNCTION__, __LINE__, EXP, REAL);         \
            LOG_ERROR(SYS, "%s():Line: %d in Exp: 0x%x Real: 0x%x", __FUNCTION__, __LINE__, EXP, REAL);                \
            return false;                                                                                              \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define ASSERT_EQ_U64(vala, valb)                                                                                      \
    do {                                                                                                               \
        uint64_t val1 = vala;                                                                                          \
        uint64_t val2 = valb;                                                                                          \
        if(val1 != val2) {                                                                                             \
            LOG_ERROR(SYS, "%s():Line: %d in val1: %" PRIu64 " val2: %" PRIu64 "", __FUNCTION__, __LINE__, val1,       \
                      val2);                                                                                           \
            LOG_ERROR(SYS, "%s():Line: %d in val1: 0x%" PRIx64 " val2: 0x%" PRIx64 "", __FUNCTION__, __LINE__, val1,   \
                      val2);                                                                                           \
            return false;                                                                                               \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define ASSERT_NE(val1, val2)                                                                                          \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if((val1) == (val2)) {                                                                                         \
            LOG_ERROR(SYS, "%s():Line: %d in val1: %u val2: %u ", __FUNCTION__, __LINE__, val1, val2);                 \
            return false;                                                                                              \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define ASSERT_GR(val1, val2)                                                                                          \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if((val2) <= (val1)) {                                                                                         \
            LOG_ERROR(SYS, "%s():Line:%d,in,val1:%u,val2:%u", __FUNCTION__, __LINE__, val1, val2);                  \
            LOG_ERROR(SYS, "%s():Line:%d,in,val1:%f,val2:%f", __FUNCTION__, __LINE__, val1, val2);                  \
            LOG_ERROR(SYS, "%s():Line:%d,in,val1:0x%x,val2:0x%x", __FUNCTION__, __LINE__, val1, val2);              \
            return false;                                                                                              \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define ASSERT_GR_64(val1, val2, id)                                                                                   \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if((val2) <= (val1)) {                                                                                         \
            LOG_ERROR(SYS, "%s():Line: %d in val1: %llu val2: %llu id: %u", __FUNCTION__, __LINE__, val1, val2, id);   \
            LOG_ERROR(SYS, "%s():Line: %d in val1: 0x%llx val2: 0x%llx id: %u", __FUNCTION__, __LINE__, val1, val2,    \
                      id);                                                                                             \
            return false;                                                                                               \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define ASSERT_STREQ(in_exp, in_strR)                                                                                 \
    do {                                                                                                               \
        char* expected_str = (in_exp);                                                                                      \
        char* real_str = (in_strR);                                                                                          \
        if(0 != strcmp_custon(expected_str, real_str)) {                                                                                 \
            LOG_ERROR(SYS, "%s():Line: %d in " CRLF "Expe:[%s] " CRLF "Real:[%s] ", __FUNCTION__, __LINE__, expected_str,    \
                      real_str);                                                                                             \
            return false;                                                                                              \
        }                                                                                                              \
    } while(0);

#endif /* UNIT_TEST_ASSERTS_H */
