#ifndef UNIT_TEST_CHECK_CORTEX_M_H
#define UNIT_TEST_CHECK_CORTEX_M_H


#include <inttypes.h>
#include <math.h>
#include <string.h>

#include "cli_utils.h"
#include "log.h"
#include "unit_test_run.h"
/*Macros for Polymorphism*/
#define EXPECT_EQ_MEM(memL, memR, len)                                                                                 \
    do {                                                                                                               \
        int ret = memcmp(memL, memR, len);                                                                             \
        if(0 != ret) {                                                                                                 \
            LOG_ERROR(SYS, "%s:Line: %d different memory %d", __FUNCTION__, __LINE__, ret);                            \
            return false;                                                                                              \
        }                                                                                                              \
    } while(0);

#define EXPECT_NEAR(base, val, error)                                                                                  \
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

#define EXPECT_TRUE(val_in)                                                                                            \
    do {                                                                                                               \
        bool val = val_in;                                                                                             \
        if(true != ((bool)val)) {                                                                                      \
            LOG_ERROR(SYS, "%s:Line: %d in val %d ", __FUNCTION__, __LINE__, (int)val);                                \
            return false;                                                                                              \
        }                                                                                                              \
    } while(0);

#define EXPECT_TRUE_NUM(val_in, ID)                                                                                            \
    do {                                                                                                               \
        bool val = val_in;                                                                                             \
        if(true != ((bool)val)) {                                                                                      \
            LOG_ERROR(SYS, "%s:Line: %d in val %d id: %u", __FUNCTION__, __LINE__, (int)val, ID);                      \
            return false;                                                                                              \
        }                                                                                                              \
    } while(0);

#define EXPECT_FALSE(val_in)                                                                                           \
    do {                                                                                                               \
        bool val = val_in;                                                                                             \
        if(false != ((bool)val)) {                                                                                     \
            LOG_ERROR(SYS, "%s:Line: %d in val %d ", __FUNCTION__, __LINE__, (int)val);                                \
            return false;                                                                                              \
        }                                                                                                              \
    } while(0);


#define EXPECT_EQ_FLOAT(val1, val2, DELTA)                                                                                      \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if(val2<(val1-DELTA)) {                                                                                        \
            LOG_ERROR(SYS, "%s():Line: %d in val2: %f too low", __FUNCTION__, __LINE__, val2, val1);                   \
            return false;                                                                                              \
        } else if((val1+DELTA)<val2){                                                                                  \
            LOG_ERROR(SYS, "%s():Line: %d in val2: %f too big", __FUNCTION__, __LINE__, val2, val1);                   \
            return false;                                                                                              \
        }                                                                                                              \
    } while(0);

#define EXPECT_EQ_U64(val1, val2)                                                                                      \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if(val1 != val2) {                                                                                             \
            LOG_ERROR(SYS, "%s():Line: %d in val1: %" PRIu64 " val2: %" PRIu64 "", __FUNCTION__, __LINE__, val1,       \
                      val2);                                                                                           \
            LOG_ERROR(SYS, "%s():Line: %d in val1: 0x%" PRIx64 " val2: 0x%" PRIx64 "", __FUNCTION__, __LINE__, val1,   \
                      val2);                                                                                           \
            return false;                                                                                              \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_EQ(val1, val2)                                                                                          \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if(val1 != val2) {                                                                                             \
            LOG_ERROR(SYS, "%s():Line: %d in val1: %u  val2: %u\n", __FUNCTION__, __LINE__, val1, val2);                 \
            LOG_ERROR(SYS, "%s():Line: %d in val1: 0x%x val2: 0x%x\n", __FUNCTION__, __LINE__, val1, val2);              \
            return false;                                                                                              \
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
            return false;                                                                                              \
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
            return false;                                                                                              \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_STREQ(strL, strR)                                                                                       \
    do {                                                                                                               \
        if(0 != strcmp(strL, strR)) {                                                                                  \
            LOG_ERROR(SYS, "%s:Line: %d in " CRLF "strL: [%s] " CRLF "strR: [%s] ", __FUNCTION__, __LINE__, strL,      \
                      strR);                                                                                           \
            return false;                                                                                              \
        }                                                                                                              \
    } while(0);

#define EXPECT_BETWEEN(left, val, right)                                                                               \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if((val) < (left)) {                                                                                           \
            LOG_ERROR(SYS, "%s():Line: %d in left: %u val: %u ", __FUNCTION__, __LINE__, left, val);                   \
            return false;                                                                                              \
        } else if((right) < (val)) {                                                                                   \
            LOG_ERROR(SYS, "%s():Line: %d in val: %u right: %u ", __FUNCTION__, __LINE__, val, right);                 \
            return false;                                                                                              \
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
            return false;                                                                                              \
        } else if((exp_v + precision) < val) {                                                                         \
            LOG_ERROR(SYS, "%s():Line: %d in val: %u exp_v: %u ", __FUNCTION__, __LINE__, val, exp_v);                 \
            return false;                                                                                              \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_GR_64(val1, val2, id)                                                                                      \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if((val2) <= (val1)) {                                                                                          \
            LOG_ERROR(SYS, "%s():Line: %d in val1: %llu val2: %llu id: %u", __FUNCTION__, __LINE__, val1, val2, id);   \
            LOG_ERROR(SYS, "%s():Line: %d in val1: 0x%llx val2: 0x%llx id: %u", __FUNCTION__, __LINE__, val1, val2,    \
                      id);                                                                                             \
            return false;                                                                                              \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#define EXPECT_GR(val1, val2)                                                                                      \
    do {                                                                                                               \
        /*int val1 = vala; */                                                                                          \
        /*int val2 = val2; */                                                                                          \
        if((val2) <= (val1)) {                                                                                         \
            LOG_ERROR(SYS, "%s():Line: %d in val1: %u val2: %u", __FUNCTION__, __LINE__, val1, val2);                  \
            LOG_ERROR(SYS, "%s():Line: %d in val1: 0x%x val2: 0x%x", __FUNCTION__, __LINE__, val1, val2);              \
            return false;                                                                                              \
        } else {                                                                                                       \
            /*printf ("\n OK!\n");  */                                                                                 \
        }                                                                                                              \
    } while(0);

#endif /* UNIT_TEST_CHECK_CORTEX_M_H */
