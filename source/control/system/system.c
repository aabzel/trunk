#include "system.h"

#include <stdio.h>
#include <string.h>

#include "common_functions.h"
#include "std_includes.h"
#include "system_init.h"

#ifdef HAS_GPIO
#include "gpio_mcal.h"
#endif

#ifdef HAS_WATCHDOG
#include "watchdog_mcal.h"
#endif

#ifdef HAS_BOARD_INFO
#include "board_info.h"
#endif

#ifdef HAS_GPIO_MAPPER
#include "gpio_mapper_mcal.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

/*Order matter!*/
const SystemInitInstance_t SystemInitInstance[] = {INIT_FUNCTIONS};

System_t System = {
    .init = false,
    .init_finish = false,
#ifdef HAS_GPIO
    .DebugPad =
        {
            .port = SYSTEM_DEBUG_PORT,
            .pin = SYSTEM_DEBUG_PIN,
        },
#endif
};

uint32_t system_init_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(SystemInitInstance);
    return cnt;
}

static bool sys_init_is_uniq_node(const SystemInitInstance_t* const Node) {
    bool res = false;
    uint32_t init_cnt = system_init_get_cnt();
    uint32_t spot_cnt = 0;
    uint32_t i = 0;

    for(i = 0; i < init_cnt; i++) {
        if(SystemInitInstance[i].init_function == Node->init_function) {
            spot_cnt++;
        }
    }

    if(1 == spot_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool system_init_array_uniq(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok = 0;
    uint32_t init_cnt = system_init_get_cnt();
    for(i = 0; i < init_cnt; i++) {
        res = sys_init_is_uniq_node(&SystemInitInstance[i]);
        if(res) {
            ok++;
        } else {
#ifdef HAS_LOG
            LOG_ERROR(SYS, "DoubleInit %u=[%s]", i, SystemInitInstance[i].name);
#endif
        }
    }

    if(init_cnt == ok) {
        res = true;
    } else {
        res = false;
    }

    return res;
}

uint32_t send_err_cnt = 0;

bool system_init_one(const SystemInitInstance_t* const Node, const uint32_t init_cnt) {
    bool res = true;
    // super_loop_run = false;
    System.init = false;
    System.init_finish = false;
#ifdef HAS_CORTEX_M4
    low_stack = (uint8_t*)RAM_END;
#endif

    if(init_cnt) {
        /*init from array */
#ifdef HAS_LOG
        memset(System.InitOrder, 0, sizeof(System.InitOrder));
        strcpy(System.InitOrder, "");
#endif

        uint32_t i = 0;
        uint32_t ok = 0;
        uint32_t error = 0;
        for(i = 0; i < init_cnt; i++) {
#ifdef HAS_WATCHDOG
            res = watchdog_proc();
#endif
            /*TODO Add GPIO positive front*/
            res = Node[i].init_function();
            if(res) {
                /*TODO Add GPIO  negative front*/
                ok++;
            } else {
                error++;
                snprintf(System.InitError, sizeof(System.InitError), "%s%s,", System.InitError, Node[i].name);
            }

#ifdef HAS_GPIO
            /*To debug by oscilloscope in case of hang on in init*/
            gpio_toggle(System.DebugPad);
#endif

            res = try_init(res, i + 1, init_cnt, Node[i].name);

#ifdef HAS_GPIO_MAPPER
            // TODO Add GPIO TOGGLE to trace init progress on DS-logic
            gpio_mapper_set(GPIO_MAP_INIT_LEN, i);
#endif

#ifdef HAS_LOG_COLOR
            snprintf(System.InitOrder, sizeof(System.InitOrder), "%s%s%s%s,", System.InitOrder, log_res_to_color(res),
                     Node[i].name, log_res_to_color(true));
#endif
        } // for(i = 0; i < init_cnt; i++)
#ifdef HAS_LOG
        LOG_INFO(SYS, "InitOrder:Err:%u,[%sEnd]", error, System.InitOrder);
#endif
        // led_mono_ctrl(2, true);
        if(ok == init_cnt) {
            res = true;
#ifdef HAS_LOG
            LOG_INFO(SYS, "InitComplete %u", init_cnt);
#endif
            System.init = true;
        } else {
            System.init = false;
#ifdef HAS_BOARD_INFO
            board_indicate_init_error();
#endif
            uint32_t error_cnt = init_cnt - ok;
            (void)error_cnt;
            res = false;
            float init_compleetness = 100.0f * ((float)ok) / ((float)init_cnt);
            (void)init_compleetness;
#ifdef HAS_LOG
            LOG_ERROR(SYS, "Init:Err:%u,[%s]", error_cnt, System.InitError);
#endif

#ifdef HAS_LOG
            LOG_ERROR(SYS, "InitInComplete:%u/%u,Only:%5.2f %%,Err:%u", ok, init_cnt, init_compleetness, error_cnt);
#endif
        }

#ifdef HAS_SYSTEM_EXT
        bool all_uniq = system_init_array_uniq();
#ifdef HAS_LOG
        log_info_res(SYS, all_uniq, "CheckUniqInit");
#endif
        res = res && all_uniq;
#endif
    }

    System.init_finish = true;

#ifdef HAS_LOG
    LOG_INFO(SYS, "InitCnt:%u", init_cnt);
#endif
    return res;
}

bool sysrem_pre_init(void) {
    bool res = true;
#ifdef HAS_LOG
    log_level_set(SYS, LOG_LEVEL_NOTICE);
#endif
    return res;
}

bool system_is_vaild_facility(const facility_t facility) {
    bool res = false;
    if(UNKNOWN_FACILITY < facility) {
        if(facility < ALL_FACILITY) {
            res = true;
        }
    }
    return res;
}

bool system_mcal_init(void) {
    bool res = true;
    uint32_t cnt = system_init_get_cnt();
    res = system_init_one(SystemInitInstance, cnt);
    return res;
}

BuildType_t system_get_prog_type(void) {
    BuildType_t FwType = BUILD_TYPE_DESKTOP_APP;
#ifdef HAS_MBR
    FwType = BUILD_TYPE_MBR;
#endif

#ifdef HAS_BOOTLOADER
    FwType = BUILD_TYPE_BOOTLOADER;
#endif

#ifdef HAS_GENERIC
    FwType = BUILD_TYPE_GENERIC;
#endif
    return FwType;
}
