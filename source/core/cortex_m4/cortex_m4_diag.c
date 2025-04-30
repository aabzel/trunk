#include "cortex_m4_diag.h"

#include "cortex_m4_types.h"
#include "log.h"

const char* CortecM4CoProcAccessToStr(CoProcAccess_t access) {
    char* name = "?";
    switch(access) {
    case COPROC_ACCESS_DENIED:
        name = "denied";
        break;
    case COPROC_ACCESS_PRIVILEGED:
        name = "Privileged";
        break;
    case COPROC_ACCESS_RESERVED:
        name = "Reserved";
        break;
    case COPROC_ACCESS_FULL:
        name = "Full";
        break;
    default:
        break;
    }
    return name;
}

static char* FloatingPoint2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case FPU_MODE_OFF:
        name = "off";
        break;
    case FPU_MODE_ON:
        name = "on";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

static char* Faulmask2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case PREVENT_EXEPTRION_OFF:
        name = "AllowExept";
        break;
    case PREVENT_EXEPTRION_ON:
        name = "PrenentExpt";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

static char* TreadMode2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case TM_PRIV:
        name = "Privileged";
        break;
    case TM_UNPRIV:
        name = "Unprivileged";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

static char* StackPointerSel2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case CUR_MSP:
        name = "MSP";
        break;
    case CUR_PSP:
        name = "PSP";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

#ifdef HAS_CMSIS
bool CortexM4ScbDiag(const SCB_Type* const Node) {
    bool res = false;
    // SCB configuration struct
    if(Node) {
        cli_printf("SCB:%p:" CRLF, Node);
        cli_printf("VTOR:0x%08x" CRLF, Node->VTOR);
        cli_printf("CPUID:0x%08x" CRLF, Node->CPUID);
        cli_printf("ICSR:0x%08x" CRLF, Node->ICSR);
        cli_printf("AIRCR:0x%08x" CRLF, Node->AIRCR);
        cli_printf("SCR:0x%08x" CRLF, Node->SCR);
        cli_printf("CCR:0x%08x" CRLF, Node->CCR);
        cli_printf("SHCSR:0x%08x" CRLF, Node->SHCSR);
        cli_printf("CFSR:0x%08x" CRLF, Node->CFSR);
        cli_printf("HFSR:0x%08x" CRLF, Node->HFSR);
        cli_printf("DFSR:0x%08x" CRLF, Node->DFSR);
        cli_printf("MMFAR:0x%08x" CRLF, Node->MMFAR);
        cli_printf("BFAR:0x%08x" CRLF, Node->BFAR);
        cli_printf("AFSR:0x%08x" CRLF, Node->AFSR);
        cli_printf("DFR:0x%08x" CRLF, Node->DFR);
        cli_printf("ADR:0x%08x" CRLF, Node->ADR);
        cli_printf("CPACR:0x%08x" CRLF, Node->CPACR);
        res = true;
    }
    return res;
}
#endif

bool parse_control_reg(uint32_t reg_val) {
    bool res = true;
    RegCtrl_t RegCtrl;
    RegCtrl.val = reg_val;
    cli_printf("0 TrMode %u %s" CRLF, RegCtrl.npriv, TreadMode2Str(RegCtrl.npriv));
    cli_printf("1 SP %u %s" CRLF, RegCtrl.spsel, StackPointerSel2Str(RegCtrl.spsel));
    cli_printf("2 FPU %u %s" CRLF, RegCtrl.fpca, FloatingPoint2Str(RegCtrl.fpca));

    return res;
}

bool parse_faultmask_reg(uint32_t reg_val) {
    bool res = true;
    RegFaultmask_t RegCtrl;
    RegCtrl.val = reg_val;
    cli_printf("0  %u %s" CRLF, RegCtrl.faultmask, Faulmask2Str(RegCtrl.faultmask));

    return res;
}

bool parse_basepri_reg(uint32_t reg_val) {
    bool res = true;
    RegBasePri_t Reg;
    Reg.val = reg_val;
    cli_printf("Priority: %u " CRLF, Reg.basepri);
    return res;
}

bool cortex_m4_breakpoints(void) {
    bool res = true;
    uint32_t i = 0;
    cli_printf(CRLF);
    for(i = 0; i < BREAKPOINTS_MAX_CNT; i++) {
        cli_printf(" %u ", i);
        cli_printf(" 0x%08x ", FLASH_PATCH->FLASH_PATCH_COMPARATOR[i]);
        cli_printf(CRLF);
    }
    return res;
}
