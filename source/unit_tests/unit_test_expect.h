#ifndef UNIT_TEST_EXPECT_H
#define UNIT_TEST_EXPECT_H

#include <inttypes.h>
#include <math.h>
#include <string.h>

#include "array.h"
#include "str_utils.h"
#include "unit_test_run.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#ifndef HAS_UNIT_TEST
#error "+HAS_UNIT_TEST"
#endif

#ifndef HAS_LOG
#error "Add LOG component"
#endif

/*Macros for Polymorphism*/

#define EXPECT_EQ_MEM(memL, memR, len)                                                                                 \
    do {                                                                                                               \
        bool test_res = array_is_equal((uint8_t*)memL, (uint8_t*)memR, len);                                                \
        if(false == test_res) {                                                                                             \
            LOG_ERROR(SYS, "%s:Line: %d different memory %d", __FUNCTION__, __LINE__);                                 \
                                                                                                      \
        }                                                                                                              \
    } while(0);

#define EXPECT_NEAR(base, val, error)                                                                                  \
    do {                                                                                                               \
        if((base + error) < val) {                                                                                     \
            LOG_ERROR(SYS, "%s:Line: %d in val %f big ", __FUNCTION__, __LINE__, val);                                 \
            res = false;                                                                                               \
        }                                                                                                              \
        if(val < (base - error)) {                                                                                     \
            LOG_ERROR(SYS, "%s:Line: %d in val %f small ", __FUNCTION__, __LINE__, val);                               \
            res = false;                                                                                               \
        }                                                                                                              \
    } while(0);

#define EXPECT_EQ_DOUBLE(EXP, REAL)                                                                                    \
    do {                                                                                                               \
        if(false==is_double_equal_absolute(EXP,REAL,EPSILONT)) {                                                       \
            LOG_ERROR(SYS, "%s():Line: %d in ExpDouble: %f  RealDouble: %f", __FUNCTION__, __LINE__, EXP, REAL);       \
            res = false;                                                                                               \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_TRUE(val_in)                                                                                            \
    do {                                                                                                               \
        bool val = val_in;                                                                                             \
        if(false == ((bool)val)) {                                                                                     \
            LOG_ERROR(SYS, "%s:Line: %d in val %d \n", __FUNCTION__, __LINE__, (int)val);                              \
            res = false;                                                                                               \
        }                                                                                                              \
    } while(0);

#define EXPECT_TRUE_NUM(val_in, ID)                                                                                    \
    do {                                                                                                               \
        bool val = val_in;                                                                                             \
        if(true != ((bool)val)) {                                                                                      \
            LOG_ERROR(SYS, "%s:Line: %d in val %d ID: %u", __FUNCTION__, __LINE__, (int)val, ID);                      \
            res = false;                                                                                               \
        }                                                                                                              \
    } while(0);

#define EXPECT_FALSE(val_in)                                                                                           \
    do {                                                                                                               \
        bool test_val = val_in;                                                                                             \
        if(false != test_val) {                                                                                     \
            LOG_ERROR(SYS, "%s:Line:%d", __FUNCTION__, __LINE__ );                                \
            res = false;                                                                                               \
        }                                                                                                              \
    } while(0);

#define EXPECT_EQ_FLOAT(val1, val2, DELTA)                                                                             \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if(val2 < (val1 - DELTA)) {                                                                                    \
            LOG_ERROR(SYS, "%s():Line: %d in val2: %f too low", __FUNCTION__, __LINE__, val2, val1);                   \
            res = false;                                                                                               \
        } else if((val1 + DELTA) < val2) {                                                                             \
            LOG_ERROR(SYS, "%s():Line: %d in val2: %f too big", __FUNCTION__, __LINE__, val2, val1);                   \
            res = false;                                                                                               \
        }                                                                                                              \
    } while(0);

#define EXPECT_EQ_U64(vala, valb)                                                                                      \
    do {                                                                                                               \
        uint64_t val1 = vala;                                                                                          \
        uint64_t val2 = valb;                                                                                          \
        if(val1 != val2) {                                                                                             \
            LOG_ERROR(SYS, "%s():Line: %d in val1: %llu val2: %llu", __FUNCTION__, __LINE__, val1,       \
                      val2);                                                                                           \
            LOG_ERROR(SYS, "%s():Line: %d in val1: 0x%llx val2: 0x%llx" , __FUNCTION__, __LINE__, val1,   \
                      val2);                                                                                           \
            res = false;                                                                                               \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_EQ(EXP_IN, REAL_IN)                                                                                     \
    do {                                                                                                               \
        int EXP = EXP_IN;                                                                                              \
        int REAL = REAL_IN;                                                                                            \
        if((EXP) != (REAL)) {                                                                                          \
            cli_printf(CRLF);                                                                                         \
            LOG_ERROR(SYS, "%s():Line: %d in Exp: %u  Real: %u=%d", __FUNCTION__, __LINE__, EXP, REAL, REAL);          \
            LOG_ERROR(SYS, "%s():Line: %d in ExpFloat: %f  RealFloat: %f", __FUNCTION__, __LINE__, EXP, REAL);         \
            LOG_ERROR(SYS, "%s():Line: %d in Exp: 0x%x Real: 0x%x", __FUNCTION__, __LINE__, EXP, REAL);                \
            res = false;                                                                                               \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_EQ_CONST(EXP, REAL)                                                                                     \
    do {                                                                                                               \
        if((EXP) != (REAL)) {                                                                                          \
            LOG_ERROR(SYS, "%s():Line: %d in Exp: %u  Real: %u=%d", __FUNCTION__, __LINE__, EXP, REAL, REAL);          \
            LOG_ERROR(SYS, "%s():Line: %d in ExpFloat: %f  RealFloat: %f", __FUNCTION__, __LINE__, EXP, REAL);         \
            LOG_ERROR(SYS, "%s():Line: %d in Exp: 0x%x Real: 0x%x", __FUNCTION__, __LINE__, EXP, REAL);                \
            res = false;                                                                                               \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_EQ_VARS(var1, var2, val)                                                                                \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if(!((var1 == val) || (var2 == val))) {                                                                        \
            LOG_ERROR(SYS, "%s():Line:%d in var1:%u var2:%u val:%u ", __FUNCTION__, __LINE__, var1, var2, val);        \
            res = false;                                                                                               \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_NE(val1, val2)                                                                                          \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if((val1) == (val2)) {                                                                                         \
            LOG_ERROR(SYS, "%s():Line: %d in val1: %u val2: %u ", __FUNCTION__, __LINE__, val1, val2);                 \
            res = false;                                                                                               \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_NE_U64(val1, val2)                                                                                          \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if((val1) == (val2)) {                                                                                         \
            LOG_ERROR(SYS, "%s():Line: %d in val1: %llu val2: %llu ", __FUNCTION__, __LINE__, val1, val2);             \
            res = false;                                                                                               \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_STREQ(in_strL, in_strR)                                                                                 \
    do {                                                                                                               \
        char* strL = (in_strL);                                                                                        \
        char* strR = (in_strR);                                                                                        \
        if(0 != strcmp_custon(strL, strR)) {                                                                           \
            LOG_ERROR(SYS, "%s():Line: %d in " CRLF "strL: [%s] " CRLF "strR: [%s] ", __FUNCTION__, __LINE__, strL,    \
                      strR);                                                                                           \
            res = false;                                                                                               \
        }                                                                                                              \
    } while(0);


/*strict inequality*/
#define EXPECT_BETWEEN(left, val, right)                                                                               \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if((val) < (left)) {                                                                                           \
            LOG_ERROR(SYS, "%s():Line: %d in left: %u val: %u ", __FUNCTION__, __LINE__, left, val);                   \
            res = false;                                                                                               \
        } else if((right) < (val)) {                                                                                   \
            LOG_ERROR(SYS, "%s():Line: %d in val: %u right: %u ", __FUNCTION__, __LINE__, val, right);                 \
            res = false;                                                                                               \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_BETWEEN_STRICT(left, val, right)                                                                               \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if((val) <= (left)) {                                                                                           \
            LOG_ERROR(SYS, "%s():Line: %d in left: %u val: %u ", __FUNCTION__, __LINE__, left, val);                   \
            res = false;                                                                                               \
        } else if((right) <= (val)) {                                                                                   \
            LOG_ERROR(SYS, "%s():Line: %d in val: %u right: %u ", __FUNCTION__, __LINE__, val, right);                 \
            res = false;                                                                                               \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_EQ_SOFT(exp_v, val, precision)                                                                          \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if((val) < (exp_v - precision)) {                                                                              \
            LOG_ERROR(SYS, "%s():Line: %d in val: %u exp_v: %u ", __FUNCTION__, __LINE__, val, exp_v);                 \
            res = false;                                                                                               \
        } else if((exp_v + precision) < val) {                                                                         \
            LOG_ERROR(SYS, "%s():Line: %d in val: %u exp_v: %u ", __FUNCTION__, __LINE__, val, exp_v);                 \
            res = false;                                                                                               \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_GR_64(val1, val2, id)                                                                                   \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if((val2) <= (val1)) {                                                                                         \
            LOG_ERROR(SYS, "%s():Line: %d in val1: %llu val2: %llu id: %u", __FUNCTION__, __LINE__, val1, val2, id);   \
            LOG_ERROR(SYS, "%s():Line: %d in val1: 0x%llx val2: 0x%llx id: %u", __FUNCTION__, __LINE__, val1, val2,    \
                      id);                                                                                             \
            res = false;                                                                                               \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_GR(val1, val2)                                                                                          \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if((val2) < (val1)) {                                                                                         \
            LOG_ERROR(SYS, "%s():Line: %d in val1: %u val2: %u", __FUNCTION__, __LINE__, val1, val2);                  \
            LOG_ERROR(SYS, "%s():Line: %d in val1: 0x%x val2: 0x%x", __FUNCTION__, __LINE__, val1, val2);              \
            res = false;                                                                                               \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#endif /* UNIT_TEST_EXPECT_H */
