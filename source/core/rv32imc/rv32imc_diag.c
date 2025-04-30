#include "rv32imc_diag.h"

#include "csr.h"
#include "float_diag.h"
#include "log.h"
#include "mik32_it.h"
#include "rv32imc_driver.h"
#include "rv32imc_types.h"

static bool Scr1RegMIE_diag(const Scr1RegMIE_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_WARNING(SYS, "MIE:0x%08x", Node->dword);
        LOG_INFO(SYS, "MSIE:%u", Node->MSIE);
        LOG_INFO(SYS, "MTIE:%u", Node->MTIE);
        LOG_INFO(SYS, "MEIE:%u" CRLF, Node->MEIE);
        res = true;
    }
    return res;
}

static bool Scr1RegMSTATUS_diag(const Scr1RegMSTATUS_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_WARNING(SYS, "MSTATUS:0x%08x", Node->dword);
        LOG_INFO(SYS, "MIE:%u", Node->MIE);
        LOG_INFO(SYS, "MPIE:%u", Node->MPIE);
        LOG_INFO(SYS, "MPP:%u" CRLF, Node->MPP);
        res = true;
    }
    return res;
}

static bool Scr1RegMTVEC_diag(const Scr1RegMTVEC_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_WARNING(SYS, "MTVEC:0x%08x", Node->dword);
        LOG_INFO(SYS, "MODE:%u", Node->MODE);
        LOG_INFO(SYS, "Base:0x%08x" CRLF, Node->BASE);
        res = true;
    }
    return res;
}

extern int main(void);
extern void trap_entry(void);
// extern void trap_handler(void);
extern void _start(void);
extern void raw_trap_handler(void);

extern uint8_t __RAM_TEXT_IMAGE_START__;
extern uint8_t __RAM_TEXT_IMAGE_END__;
extern uint8_t __RAM_TEXT_START__;
extern uint8_t __TEXT_START__;
extern uint8_t __TEXT_END__;
extern uint8_t __DATA_START__;
extern uint8_t __DATA_END__;
extern uint8_t __STACK_START__;
extern uint8_t __C_STACK_TOP__;
extern uint8_t end;
extern uint8_t __TRAP_TEXT_START__;
extern uint8_t __RAM_TEXT_END__;
// extern uint8_t __global_pointer;

bool rv32imc_diag(void) {
    bool res = true;
    float up_time_s = rv32imc_up_time_get();
    LOG_INFO(SYS, "UpTime:%s", FloatToStr(up_time_s, 3));
    LOG_INFO(SYS, "_start:0x%08p", _start);
    LOG_INFO(SYS, "__C_STACK_TOP__:0x%08x", __C_STACK_TOP__);
    LOG_INFO(SYS, "&__C_STACK_TOP__:0x%08p", &__C_STACK_TOP__);
    // LOG_INFO(SYS,"&__C_STACK_TOP__:0x%08p" , &(&__C_STACK_TOP__));

    //   LOG_INFO(SYS,"__global_pointer:0x%08p" , __global_pointer);
    LOG_INFO(SYS, "TrapCnt:%u", int_cnt);
    LOG_INFO(SYS, "trap_entry:0x%08p", trap_entry);
    LOG_INFO(SYS, "raw_trap_handler:0x%08p", raw_trap_handler);
    LOG_INFO(SYS, "trap_handler:0x%08p", trap_handler);
    LOG_INFO(SYS, "main:0x%08p", main);
    LOG_INFO(SYS, "__RAM_TEXT_IMAGE_START__:0x%08p", &__RAM_TEXT_IMAGE_START__);
    LOG_INFO(SYS, "__RAM_TEXT_IMAGE_END__:0x%08p", &__RAM_TEXT_IMAGE_END__);
    LOG_INFO(SYS, "__RAM_TEXT_START__:0x%08p", &__RAM_TEXT_START__);
    LOG_INFO(SYS, "__TEXT_START__:0x%08p", &__TEXT_START__);
    LOG_INFO(SYS, "__TEXT_END__:0x%08p", &__TEXT_END__);
    LOG_INFO(SYS, "__DATA_START__:0x%08p", &__DATA_START__);
    LOG_INFO(SYS, "__DATA_END__:0x%08p", &__DATA_END__);
    LOG_INFO(SYS, "__STACK_START__:0x%08p", &__STACK_START__);
    LOG_INFO(SYS, "end:0x%08p", &end);
    LOG_INFO(SYS, "__TRAP_TEXT_START__:0x%08p", &__TRAP_TEXT_START__);
    LOG_INFO(SYS, "__RAM_TEXT_END__:0x%08p", &__RAM_TEXT_END__);

    // control/status registers
    uint32_t val = 0;
    Scr1RegMTVEC_t Reg;
    Reg.dword = read_csr(mtvec);
    Scr1RegMTVEC_diag(&Reg);

    val = read_csr(cycle);
    LOG_INFO(SYS, "cycle:0x%08x", val);

    val = read_csr(time);
    LOG_INFO(SYS, "time:0x%08x", val);

    val = read_csr(instret);
    LOG_INFO(SYS, "instret:0x%08x", val);

    val = read_csr(cycleh);
    LOG_INFO(SYS, "cycleh:0x%08x", val);

    val = read_csr(timeh);
    LOG_INFO(SYS, "timeh:0x%08x", val);

    val = read_csr(instreth);
    LOG_INFO(SYS, "instreth:0x%08x", val);

    val = read_csr(mvendorid);
    LOG_INFO(SYS, "mvendorid:0x%08x", val);

    val = read_csr(marchid);
    LOG_INFO(SYS, "marchid:0x%08x", val);

    val = read_csr(mimpid);
    LOG_INFO(SYS, "mimpid:0x%08x", val);

    val = read_csr(mhartid);
    LOG_INFO(SYS, "mhartid:0x%08x", val);

    Scr1RegMSTATUS_t RegMSTATUS;
    RegMSTATUS.dword = read_csr(mstatus);
    Scr1RegMSTATUS_diag(&RegMSTATUS);

    val = read_csr(misa);
    LOG_INFO(SYS, "misa:0x%08x", val);

    Scr1RegMIE_t RegMIE;
    RegMIE.dword = read_csr(mie);
    Scr1RegMIE_diag(&RegMIE);

    return res;
}
