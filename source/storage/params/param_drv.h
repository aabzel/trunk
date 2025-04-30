#ifndef PARAM_IDS_H
#define PARAM_IDS_H

#include <stdio.h>

#ifdef HAS_CLOCK
#include "clock.h"
#endif

#include "std_includes.h"
#include "param_config.h"
#include "param_diag.h"
#include "param_types.h"

#define PARAM_PERIOD_US SEC_2_USEC(3)

#ifdef HAS_PARAM_DIAG
/*MACRO Function for polymorphism*/
#define LOAD_PARAM(COMPONENT, PAR_ID, VARIABLE, DEF_VAL)                                                               \
    do {                                                                                                               \
        char format[50] = "";                                                                                          \
        bool res_loc = false;                                                                                          \
        const char* val2str = "?";                                                                                     \
        res_loc = param_get(PAR_ID, (uint8_t*)&VARIABLE);                                                              \
        uint32_t par_len = param_get_len(PAR_ID);                                                                      \
        val2str = param_val2str(PAR_ID, (uint8_t*)(&VARIABLE), par_len);                                               \
        if(res_loc) {                                                                                                  \
            snprintf(format, sizeof(format), "Load %s FromParams %%u [%s]", ParamId2Str(PAR_ID), val2str);             \
            LOG_INFO(COMPONENT, format, VARIABLE);                                                                     \
        } else {                                                                                                       \
            snprintf(format, sizeof(format), "SetDflt %s %%u [%s]", ParamId2Str(PAR_ID), val2str);                     \
            LOG_WARNING(COMPONENT, format, VARIABLE);                                                                  \
            VARIABLE = DEF_VAL;                                                                                        \
            res_loc = false;                                                                                           \
            out_res = false;                                                                                           \
        }                                                                                                              \
    } while(0);
#else
#define LOAD_PARAM(COMPONENT, PAR_ID, VARIABLE, DEF_VAL)                                                               \
    do {                                                                                                               \
        bool res_loc = false;                                                                                          \
        res_loc = param_get(PAR_ID, (uint8_t*)&VARIABLE);                                                              \
        if(false == res_loc) {                                                                                         \
            VARIABLE = DEF_VAL;                                                                                        \
            res_loc = false;                                                                                           \
            out_res = false;                                                                                           \
        }                                                                                                              \
    } while(0);
#endif /*HAS_LOG*/

#ifdef HAS_LOG
/*MACRO Function for polymorphism*/
#define LOAD_PARAM_V2(COMPONENT, PAR_ID, VARIABLE)                                                                     \
    do {                                                                                                               \
        char format[50] = "";                                                                                          \
        bool res_loc = false;                                                                                          \
        const char* val2str = "?";                                                                                     \
        uint32_t par_len = param_get_len(PAR_ID);                                                                      \
        val2str = param_val2str(PAR_ID, (uint8_t*)(&VARIABLE), par_len);                                               \
        res_loc = param_get(PAR_ID, (uint8_t*)&VARIABLE);                                                              \
        if(res_loc) {                                                                                                  \
            val2str = param_val2str(PAR_ID, (uint8_t*)(&VARIABLE), par_len);                                           \
            snprintf(format, sizeof(format), "Load %s FromParams %%u [%s]", ParamId2Str(PAR_ID), val2str);             \
            LOG_INFO(COMPONENT, format, VARIABLE);                                                                     \
        } else {                                                                                                       \
            snprintf(format, sizeof(format), "UseDflt %s %%u [%s]", ParamId2Str(PAR_ID), val2str);                     \
            LOG_WARNING(COMPONENT, format, VARIABLE);                                                                  \
            res_loc = false;                                                                                           \
            out_res = false;                                                                                           \
        }                                                                                                              \
    } while(0);
#else
#define LOAD_PARAM_V2(COMPONENT, PAR_ID, VARIABLE_PTR)                                                                    \
    do {                                                                                                                  \
        bool res_loc = false;                                                                                             \
        res_loc = param_get(PAR_ID, (uint8_t*)&VARIABLE);                                                                 \
        if(!(res) {                                                                                                    \
            res_loc = false;                                                                                           \
            out_res = false;                                                                                           \
        }                                                                                                                 \
    } while(0);
#endif /*HAS_LOG*/

uint16_t param_get_type_len(StorageType_t type_id);
bool param_init(void);
bool param_proc(void);

#ifdef HAS_PARAM_SET
bool param_set(Id_t param_id, const void* const data);
bool param_set_lazy(Id_t param_id, const void* const data);
#endif


bool param_invalidate(Id_t param_id);
bool param_get(Id_t param_id, void* const out_data);
StorageType_t param_get_type(Id_t id);
uint16_t param_get_real_len(Id_t id);
size_t param_get_len(Id_t param_id);
//uint16_t param_get_type_len(StorageType_t type_id);
//uint32_t param_get_cnt(void);

#endif /* PARAM_IDS_H  */
