#include "mik32_hal_irq.h"

// #define MIK32_IRQ_DEBUG

void HAL_IRQ_EnableInterrupts(void)
{   
    set_csr(mstatus, MSTATUS_MIE);
    set_csr(mie, MIE_MEIE);//Machine External Interrupt Enable.
}

void HAL_IRQ_DisableInterrupts(void)
{    
    clear_csr(mie, MIE_MSIE);//Machine Software Interrupt Disable.
    clear_csr(mie, MIE_MTIE);//Machine Timer Interrupt Disable.
    clear_csr(mie, MIE_MEIE);//Machine External Interrupt Disable.
}

void HAL_EPIC_MaskEdgeSet(uint32_t InterruptMask)
{
    EPIC->MASK_EDGE_SET |= InterruptMask;
}

void HAL_EPIC_MaskEdgeClear(uint32_t InterruptMask)
{
    EPIC->MASK_EDGE_CLEAR |= InterruptMask;
}

void HAL_EPIC_MaskLevelSet(uint32_t InterruptMask)
{
    EPIC->MASK_LEVEL_SET = InterruptMask;
}

void HAL_EPIC_MaskLevelClear(uint32_t InterruptMask)
{
    EPIC->MASK_LEVEL_CLEAR = InterruptMask;
}

uint32_t HAL_EPIC_GetStatus(void)
{
    return EPIC->STATUS;
}

uint32_t HAL_EPIC_GetRawStatus(void)
{
    return EPIC->RAW_STATUS;
}












