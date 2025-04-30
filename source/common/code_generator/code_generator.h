#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#include <stddef.h> /*For NULL*/

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

/**/
#ifdef HAS_CG_LOG

#define CG_FASIL   #XXX

#define LOG_INIT_ALL  LOG_WARNING(FASIL, "InitAll:%u,%u",cnt, CUSTOM_CNT);
#define LOG_PROC_ALL  LOG_PARN(FASIL, "ProcAll:%u", cnt);
#define LOG_PROC_OK  LOG_PARN(FASIL, "%s%u Proc Ok", CG_FASIL, num);
#define LOG_INIT_OK  LOG_INFO(FASIL, "%s_%u Init Ok", CG_FASIL, num);
#define LOG_PROC_ERROR  LOG_PARN(FASIL, "%s%u Proc Err", CG_FASIL, num);
#define LOG_INIT_ERROR   LOG_DEBUG(FASIL, "%s_%u Init Err", CG_FASIL, num);
#define LOG_PROC_STATISTIC  LOG_PARN(FASIL, "Proc %u %s", ok, CG_FASIL);
#define LOG_INIT_STATISTIC  LOG_INFO(FASIL, "Init %u %s", ok, CG_FASIL);
#define LOG_SET_FASIL_INFO  log_level_get_set(FASIL, LOG_LEVEL_INFO);
#define LOG_SET_FASIL_DEBUG  log_level_get_set(FASIL, LOG_LEVEL_DEBUG);
#else
#define LOG_INIT_ALL
#define LOG_SET_FASIL_DEBUG
#define LOG_PROC_ALL
#define LOG_INIT_ERROR
#define LOG_PROC_OK
#define LOG_INIT_OK
#define LOG_PROC_ERROR
#define LOG_INIT_STATISTIC
#define LOG_PROC_STATISTIC
#define LOG_SET_FASIL_INFO
#endif




/*
 * #include "code_generator.h"
 *
 * COMPONENT_GET_INFO(Xxx)
 * COMPONENT_GET_NODE(Xxx, xxx)
 * COMPONENT_GET_CONFIG(Xxx, xxx)
 * COMPONENT_INIT_PATTERT(FASIL, XXX, xxx)
 * COMPONENT_PROC_PATTERT(FASIL, XXX, xxx)
 *
 */
#define COMPONENT_IS_VALID(XXX, xxx)                                                                                   \
    bool xxx##_is_valid(uint8_t num) {                                                                                 \
        bool res = false;                                                                                              \
        uint32_t i = 0;                                                                                                \
        for(i = 0; i < xxx##_get_cnt(); i++) {                                                                         \
            if(num == XXX##Config[i].num) {                                                                            \
                if(XXX##Config[i].valid) {                                                                             \
                    res = true;                                                                                        \
                    break;                                                                                             \
                }                                                                                                      \
            }                                                                                                          \
        }                                                                                                              \
        return res;                                                                                                    \
    }

#define COMPONENT_GET_NODE(Xxx, xxx)                                                                                   \
    Xxx##Handle_t* Xxx##GetNode(uint8_t num) {                                                                         \
        Xxx##Handle_t* Node = NULL;                                                                                    \
        uint32_t i = 0;                                                                                                \
        uint32_t cnt = xxx##_get_cnt();                                                                                \
        for(i = 0; i < cnt; i++) {                                                                                     \
            if(num == Xxx##Instance[i].num) {                                                                          \
                if(Xxx##Instance[i].valid) {                                                                           \
                    Node = &Xxx##Instance[i];                                                                          \
                    break;                                                                                             \
                }                                                                                                      \
            }                                                                                                          \
        }                                                                                                              \
        return Node;                                                                                                   \
    }

#define COMPONENT_GET_INFO(Xxx)                                                                                        \
    const Xxx##Info_t* Xxx##GetInfo(uint8_t num) {                                                                     \
        Xxx##Info_t* Info = NULL;                                                                                      \
        uint32_t i = 0;                                                                                                \
        uint32_t cnt = ARRAY_SIZE(Xxx##Info);                                                                          \
        for(i = 0; i < cnt; i++) {                                                                                     \
            if(num == Xxx##Info[i].num) {                                                                              \
                if(Xxx##Info[i].valid) {                                                                               \
                    Info = &Xxx##Info[i];                                                                              \
                    break;                                                                                             \
                }                                                                                                      \
            }                                                                                                          \
        }                                                                                                              \
        return Info;                                                                                                   \
    }

#define COMPONENT_GET_CONFIG(Xxx, xxx)                                                                                 \
    const Xxx##Config_t* Xxx##GetConfig(uint8_t num) {                                                                 \
        const Xxx##Config_t* Config = NULL;                                                                            \
        uint32_t i = 0;                                                                                                \
        uint32_t cnt =  xxx##_get_cnt();                                                                               \
        for(i = 0; i < cnt; i++) {                                                                                     \
            if(num == Xxx##Config[i].num) {                                                                            \
                if(Xxx##Config[i].valid) {                                                                             \
                    Config = &Xxx##Config[i];                                                                          \
                    break;                                                                                             \
                }                                                                                                      \
                break;                                                                                                 \
            }                                                                                                          \
        }                                                                                                              \
        return Config;                                                                                                 \
    }

/*
  xxx_init() names are busy in AT32F435_437_Firmware_Library HAL/SPL (eg i2c_init)
 */

/*TODO Add driver version*/
#define COMPONENT_INIT_PATTERT_CNT(FASIL, XXX, xxx, CUSTOM_CNT)                                                        \
    bool xxx##_mcal_init(void) {                                                                                       \
        bool res = true;                                                                                               \
        res = xxx##_init_custom();                                                                                     \
        uint32_t ok = 0;                                                                                               \
        LOG_SET_FASIL_DEBUG                                                                                            \
        uint32_t cnt = xxx##_get_cnt();                                                                                \
        (void) cnt ;                                                                                                   \
        LOG_INIT_ALL                                                                                                   \
        uint32_t num = 0;                                                                                              \
        for(num = 0; num <= CUSTOM_CNT; num++) {                                                                       \
            res = xxx##_init_one(num);                                                                                 \
            if(res) {                                                                                                  \
            	LOG_INIT_OK                                                                                            \
                ok++;                                                                                                  \
            } else {                                                                                                   \
            	LOG_INIT_ERROR                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
        if(ok) {                                                                                                       \
            res = true;                                                                                                \
            LOG_INIT_STATISTIC                                                                                         \
        } else {                                                                                                       \
            res = false;                                                                                               \
        }                                                                                                              \
        LOG_SET_FASIL_INFO                                                                                             \
        return res;                                                                                                    \
    }

/*TODO Add driver version*/
#define COMPONENT_INIT_PATTERT(FASIL, XXX, xxx) COMPONENT_INIT_PATTERT_CNT(FASIL, XXX, xxx, cnt)

#define COMPONENT_PROC_PATTERT_CNT(FASIL, XXX, xxx, CUSTOM_CNT)                                                        \
    bool xxx##_proc(void) {                                                                                            \
        bool res = true;                                                                                               \
        uint32_t ok = 0;                                                                                               \
        uint32_t cnt = xxx##_get_cnt();                                                                                \
        (void) cnt ;                                                                                                   \
        LOG_PROC_ALL                                                                                                   \
        uint32_t num = 0;                                                                                              \
        for(num = 0; num <= cnt; num++) {                                                                              \
            res = xxx##_proc_one(num);                                                                                 \
            if(res) {                                                                                                  \
            	LOG_PROC_OK                                                                                            \
                ok++;                                                                                                  \
            } else {                                                                                                   \
            	LOG_PROC_ERROR                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
        if(ok) {                                                                                                       \
            res = true;                                                                                                \
            LOG_PROC_STATISTIC                                                                                         \
        } else {                                                                                                       \
            res = false;                                                                                               \
        }                                                                                                              \
        return res;                                                                                                    \
    }

#define COMPONENT_PROC_PATTERT(FASIL, XXX, xxx) COMPONENT_PROC_PATTERT_CNT(FASIL, XXX, xxx, cnt)

#ifdef __cplusplus
}
#endif

#endif /* CODE_GENERATOR_H */
