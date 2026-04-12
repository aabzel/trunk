#include "core_driver.h"

#include "clock_const.h"
#include "code_generator.h"
#include "common_functions.h"
#include "compiler_const.h"
#include "float_utils.h"
#include "microcontroller_const.h"
#include "microcontroller_drv.h"

#ifdef HAS_RATIONAL_NUM
#include "rational_num.h"
#endif

#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_TIME
#include "none_blocking_pause.h"
#endif

#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#ifdef HAS_CORE_EXT
#include <string.h>

#ifdef HAS_ARRAY
#include "array.h"
#endif /**/

#endif

#ifdef HAS_BOOT
//#include "boot_config.h"
#endif

#ifdef HAS_FLASH
#include "flash_config.h"
#endif

#ifdef HAS_CORTEX_M33
#include "cortex_m33_driver.h"
#endif

#ifdef HAS_CORTEX_M0
#include "cortex_m0_driver.h"
#endif

#ifdef HAS_CORTEX_M4
#include "cortex_m4_driver.h"
#endif

#ifdef HAS_CORTEX_M7
#include "cortex_m7_driver.h"
#endif

#ifdef HAS_RISC_V
#include "rv32imc_driver.h"
#endif

#ifndef RAM_START
#error "Define MCU RAM_START"
#endif

#ifndef RAM_SIZE
#error "Define MCU RAM_SIZE configs"
#endif

COMPONENT_GET_NODE(Core, core)
COMPONENT_GET_CONFIG(Core, core)

uint8_t* low_stack = (uint8_t*)RAM_END;

/*TODO: Test it*/
#ifdef HAS_CORE_EXT
bool core_is_interrupt(void) {
    bool res = false;
#ifdef HAS_CORTEX_M4
    res = cortex_m4_is_interrupt();
#endif
    return res;
}
#endif

#ifdef HAS_CORE_EXT
void sampling_timer_interrupt_handler(void) {
    uint8_t* current_stack;
    int some_variable_on_stack = 0;
    current_stack = (uint8_t*)&some_variable_on_stack;
    if(current_stack < low_stack) {
        low_stack = current_stack;
    }
}
#endif

#ifdef HAS_CORE_EXT

_WEAK_FUN_ bool is_ram_addr(register uint32_t address) {
    bool res = false;
    if(RAM_START <= address) {
        if(address <= (RAM_START + RAM_SIZE)) {
            res = true;
        }
    }

    return res;
}
#endif

#ifdef HAS_CORE_EXT
static bool call_recursion(uint32_t stack_top_addr, uint32_t cur_depth, uint32_t max_depth, uint32_t* stack_size) {
    bool res = false;
    if(cur_depth < max_depth) {
        res = call_recursion(stack_top_addr, cur_depth + 1, max_depth, stack_size);
    } else if(cur_depth == max_depth) {
        uint32_t cur_stack_use = stack_top_addr - ((uint32_t)&res);
        *stack_size = cur_stack_use;
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool try_recursion(const uint32_t stack_top_addr, const uint32_t max_depth, uint32_t* const stack_size) {
    bool res = false;
    res = call_recursion(stack_top_addr, 0, max_depth, stack_size);
#ifdef HAS_LOG
    LOG_INFO(CORE, "Depth:%u,StackSize:%u,byte", max_depth, *stack_size);
#endif
    return res;
}
#endif

bool core_reboot(void) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(CORE, "ReBootNow!");
#endif

#ifdef HAS_TIME
    wait_ms(1000);
#endif

#ifdef HAS_CORTEX_M33
    res = cortex_m33_reboot();
#endif

#ifdef HAS_CORTEX_M4
    res = cortex_m4_reboot();
#endif

#ifdef HAS_CORTEX_M7
    res = cortex_m7_reboot();
#endif

#ifdef HAS_RISC_V
    res = rv32imc_boot_addr(EXT_ROM_START);
#endif

    return res;
}

#ifdef HAS_CORE_EXT
static bool arm_is_reserved_vector_zero(const ArmCortexVectorTable_t* const Node) {
    bool res = true;
    uint32_t i = 0;
    uint64_t res_cnt = 0;
    for(i = 0; i < 4; i++) {
        res_cnt += Node->RES1[i];
    }

    res_cnt += Node->RES2;

    if(0 == res_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif

#ifdef HAS_CORE_EXT
bool arm_is_vector(const ArmCortexVectorTable_t* const Node) {
    bool res = true;

    res = arm_is_reserved_vector_zero(Node);
    if(!res) {
#ifdef HAS_LOG
        LOG_DEBUG(CORE, "RevVectorError:Offset:%p", Node);
#endif
    }

    if(res) {
#ifdef HAS_CORE_EXT

        res = is_ram_addr(Node->stack_top);
        if(!res) {
#ifdef HAS_LOG
            LOG_DEBUG(CORE, "StackUpPrtUpError:Offset:%p", Node);
#endif
        }
#endif
    }

#ifdef HAS_FLASH_EX
    if(res) {
        res = is_flash_addr(Node->reset_handler);
        if(!res) {
#ifdef HAS_LOG
            LOG_DEBUG(CORE, "ResetHandlerError:0x%x", Node->reset_handler);
#endif
        }
    }

    if(res) {
        res = is_flash_addr(Node->HardFault_Handler);
        if(!res) {
        }
    }

    if(res) {
        res = is_flash_addr(Node->MemManage_Handler);
        if(!res) {
        }
    }

    if(res) {
        res = is_flash_addr(Node->BusFault_Handler);
        if(!res) {
        }
    }

    if(res) {
        res = is_flash_addr(Node->UsageFault_Handler);
        if(!res) {
        }
    }

    if(res) {
        res = is_flash_addr(Node->DebugMon_Handler);
        if(!res) {
        }
    }

    if(res) {
        res = is_flash_addr(Node->SVC_Handler);
        if(!res) {
        }
    }

    if(res) {
        res = is_flash_addr(Node->PendSV_Handler);
        if(!res) {
        }
    }

    if(res) {
        res = is_flash_addr(Node->NMI_Handler);
        if(!res) {
        }
    }
#endif /*HAS_FLASH_EX*/
    return res;
}
#endif

#ifdef HAS_CORE_EXT
FloatFixPoint_t core_stack_used(const uint32_t top_stack_val, const uint32_t stack_size) {
    FloatFixPoint_t Precent = {0};
#ifdef HAS_LOG
    LOG_DEBUG(CORE, "StackTop:0x%08X,Size:%u Byte", top_stack_val, stack_size);
#endif
#ifdef HAS_ARRAY_EXT
    uint32_t stack_size_dword = stack_size / 4;
    if(stack_size_dword) {
        uint32_t max_cont_patt_dw = 0;
        uint32_t* start_p = (uint32_t*)(top_stack_val - stack_size);
        bool res = array_u32_max_cont(start_p, stack_size_dword, STACK_PATTERN, &max_cont_patt_dw);
        if(res) {
            uint32_t busy_dw = 0;
            busy_dw = stack_size_dword - max_cont_patt_dw;
            res = fraction_to_fixed_point_float(100 * busy_dw, stack_size_dword, 5, &Precent);
        }
    }
#endif
    return Precent;
}
#endif

bool arm_cortex_check_arm_vector_table(const uint32_t vector_table_addr) {
    bool res = false;
#ifdef HAS_CORE_EXT
    ArmCortexVectorTable_t* VectorTable = (ArmCortexVectorTable_t*)vector_table_addr;
    res = arm_is_vector(VectorTable);
#endif

#if 0

    uint32_t stack_pointer_addr = read_addr_32bit(vector_table_addr);
#ifdef HAS_LOG
    LOG_DEBUG(CORE, "StackUpPtr:Addr:*(0x%08X)=0x%08X", vector_table_addr, stack_pointer_addr);
#endif
    res = is_ram_addr(stack_pointer_addr);
    if(res) {
#ifdef HAS_LOG
        LOG_DEBUG(CORE, "VerifyAddress:0x%08X,StackUpPrt:0x%08X", vector_table_addr, stack_pointer_addr);
#endif
        uint32_t reset_handler_offset = vector_table_addr + 4;

#ifdef HAS_DEBUGGER
        uint32_t reset_handler_addr = read_addr_32bit(reset_handler_offset);
        (void)reset_handler_addr;
#ifdef HAS_LOG
        LOG_DEBUG(CORE, "ResetHandler:Addr:*(0x%08X)=0x%08X", reset_handler_offset, reset_handler_addr);
#endif

#ifdef HAS_FLASH_EX
        res = is_flash_addr(reset_handler_addr);
        if(res) {
            LOG_DEBUG(CORE, "ResetHandlerOk:0x%x", reset_handler_addr);
        } else {
        }
#endif

#endif
    } else {
    }
#endif

    return res;
}

#ifdef HAS_CORE_EXT
bool core_exeption(uint32_t in, uint32_t* out) {
    bool res = false;
    if(out) {
        uint32_t temp = 0;
#ifdef HAS_LOG
        LOG_INFO(CORE, "TryEception:%u/0=?", in);
#endif
        // temp = in/0;
#ifdef HAS_LOG
        LOG_INFO(CORE, "Eception:%u/0=%u", in, temp);
#endif
        *out = temp;
        res = true;
    }
    return res;
}
#endif

/*        offset          Function
  .word   0               Reset_Handler
  .word   1         0     NMI_Handler
  .word   2         4     HardFault_Handler
  .word   3         8     MemManage_Handler
  .word   4         12    BusFault_Handler
  .word   5         16    UsageFault_Handler
  .word   6         20    0
  .word   7         24    0
  .word   8         28    0
  .word   9         32    0
  .word   10        36    SVC_Handler
  .word   11        40    DebugMon_Handler
  .word   12        44    0
  .word   13        48    PendSV_Handler
  .word   14        52    SysTick_Handler
  .word   15        60
 */

#ifdef HAS_ARM
// core_isr_handler_addr_get->core_isr_handler_addr_get
uint32_t core_isr_handler_addr_get(int16_t irq_n) {
    uint32_t isr_handler_addr = 0;
    (void)isr_handler_addr;
#ifdef HAS_CMSIS
    int32_t offset = 0;
    uint32_t vector_table_addr = 0;
    offset = ((int32_t)60) + ((int32_t)irq_n * 4);
    vector_table_addr += ((uint32_t)SCB->VTOR + 4);
    vector_table_addr += ((uint32_t)offset);

#ifdef HAS_DEBUGGER
    isr_handler_addr = read_addr_32bit(vector_table_addr);
#endif

#ifdef HAS_LOG
    LOG_DEBUG(CORE, "IRQ:%d,Offset:%d,Addr:0x%08p=0x%08x", irq_n, offset, vector_table_addr, isr_handler_addr);
#endif
#endif /* HAS_CMSIS */

    return isr_handler_addr;
}
#endif

#ifdef HAS_CORE_EXT
bool core_is_valid_isr_handler(int16_t irq_n) {
    bool res = false;
    uint32_t isr_handler_addr = core_isr_handler_addr_get(irq_n);
    res = mcu_is_text_addr(isr_handler_addr);
    return res;
}
#endif

#ifdef HAS_FPU
bool fpu_init(void) {
    bool res = true;
    /* set CP10 and CP11 Full Access */
#ifdef HAS_CMSIS
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));
#endif
    return res;
}
#endif

bool core_check_address(volatile const char* address) {
    bool is_valid = false;
#ifdef HAS_VENDOR_SDK
    is_valid = true;
    /* Cortex-M3, Cortex-M4, Cortex-M4F, Cortex-M7 are supported */
    static const uint32_t BFARVALID_MASK = (0x80 << SCB_CFSR_BUSFAULTSR_Pos);

    /* Clear BFARVALID flag by writing 1 to it */
    SCB->CFSR |= BFARVALID_MASK;

    /* Ignore BusFault by enabling BFHFNMIGN and disabling interrupts */
    uint32_t mask = __get_FAULTMASK();
    __disable_fault_irq();
    SCB->CCR |= SCB_CCR_BFHFNMIGN_Msk;

    /* probe address in question */
    *address;

    /* Check BFARVALID flag */
    if((SCB->CFSR & BFARVALID_MASK) != 0) {
        /* Bus Fault occured reading the address */
        is_valid = false;
    }

    /* Reenable BusFault by clearing  BFHFNMIGN */
    SCB->CCR &= ~SCB_CCR_BFHFNMIGN_Msk;
    __set_FAULTMASK(mask);

#endif
    return is_valid;
}

uint32_t cortex_offset_size_get(uint32_t const start) {
    uint32_t offset_size = 0;
#ifdef HAS_LOG
    LOG_INFO(CORE, "Addr:0x%x", start);
#endif
    char* run_addr = (char*)start;
    bool res = true;
    while(res) {
        res = core_check_address(run_addr);
        if(res) {
            offset_size++;
        } else {
            break;
        }
        run_addr++;
    }

#ifdef HAS_LOG
    LOG_INFO(CORE, "Start:0x%x,Size:%u", start, offset_size);
#endif

    return offset_size;
}

#ifdef HAS_CORE_EXT
static FloatFixPoint_t core_stack_used_get(CoreHandle_t* const Node) {
    FloatFixPoint_t stack_used = {0};
    if(Node) {
        if(Node->stack_limit < Node->stack_top) {
            uint32_t stack_size = Node->stack_top - Node->stack_limit;
            Node->stack_used = core_stack_used(Node->stack_top, stack_size);
#ifdef HAS_LOG
            LOG_DEBUG(CORE, "StackUsed:%s %%", FloatFixToStr(&Node->stack_used));
#endif
            stack_used = Node->stack_used;
        }
    }
    return stack_used;
}
#endif

#ifdef HAS_CORE_EXT
static bool core_stack_monitor_proc_one(uint8_t num) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(CORE, "CORE%u,Proc", num);
#endif
    CoreHandle_t* Node = CoreGetNode(num);
    if(Node) {
        Node->stack_used = core_stack_used_get(Node);
#ifdef HAS_CORE_DIAG
        res = core_diag_stack_usage(num, &Node->stack_used);
#endif
        Node->spin++;
    }
    return res;
}
#endif

static bool core_init_custom(void) {
    bool res = true;
#ifdef HAS_LOG
    // LOG_PARN(CORE, "CustomInit");
#endif
    return res;
}

#ifdef HAS_CORE_EXT
bool core_stack_monitor_proc(void) {
    bool res = false;
    uint32_t ok = 0;
    uint32_t cnt = core_get_cnt();
    (void)cnt;
    uint8_t num = 0;
    for(num = 0; num <= cnt; num++) {
        res = core_stack_monitor_proc_one(num);
        ok = ok_cnt_update(ok, res);
    }
    if(ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif

static bool core_init_common(const CoreConfig_t* const Config, CoreHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->stack_top = Config->stack_top;
            Node->stack_limit = Config->stack_limit;
            res = true;
        }
    }
    return res;
}

static bool CoreIsValidConfig(const CoreConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;

        ifn(is_ram_addr(Config->stack_top)) {
#ifdef HAS_LOG
            LOG_PARN(CORE, "CORE%u,StackTopNotRam:0x%x", Config->num, Config->stack_top);
#endif
            res = false;
        }

        ifn(is_ram_addr(Config->stack_limit)) {
#ifdef HAS_LOG
            LOG_PARN(CORE, "CORE%u,StackLinNotRam:0x%x", Config->num, Config->stack_limit);
#endif
            res = false;
        }

        ifn(Config->name) {
#ifdef HAS_LOG
            LOG_PARN(CORE, "CORE%u,Name,Error", Config->num);
#endif
            res = false;
        }
    }

    return res;
}

static bool core_init_one(uint8_t num) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(CORE, "CORE%u", num);
#endif
    const CoreConfig_t* Config = CoreGetConfig(num);
    if(Config) {
        res = CoreIsValidConfig(Config);
        if(res) {
#ifdef HAS_CORE_DIAG
#ifdef HAS_LOG
            LOG_WARNING(CORE, "%s", CoreConfigToStr(Config));
#endif
#endif
            CoreHandle_t* Node = CoreGetNode(num);
            if(Node) {
                res = core_init_common(Config, Node);
#ifdef HAS_FPU
                res = fpu_init();
#endif
                Node->valid = true;
                Node->stack_used.fractional = 0;
                Node->stack_used.integer = 0;
                Node->spin = 0;
                Node->init = true;
                res = true;
            } else {
#ifdef HAS_LOG
                LOG_ERROR(CORE, "NodeErr %u", num);
#endif
            }
        } else {
#ifdef HAS_LOG
            LOG_ERROR(CORE, "ConfigErr %u", num);
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_PARN(CORE, "ConfigErr %u", num);
#endif
    }
    return res;
}

COMPONENT_INIT_PATTERT(CORE, CORE, core)
