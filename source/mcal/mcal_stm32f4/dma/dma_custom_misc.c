#include "dma_custom_misc.h"

uint32_t DmaGetMemDataAlignment(const DmaAligmant_t aligment_mem) {
    uint32_t code = 0xFFFFFFFF;
    switch(aligment_mem) {
    case DMA_ALIGNMENT_BYTE:
        code = DMA_MDATAALIGN_BYTE;
        break;
    case DMA_ALIGNMENT_WORD:
        code = DMA_MDATAALIGN_HALFWORD;
        break;
    case DMA_ALIGNMENT_DWORD:
        code = DMA_MDATAALIGN_WORD;
        break;
    default:
        break;
    }
    return code;
}

uint32_t DmaDirToStm32DmaDir(const DmaDir_t dir) {
    uint32_t code = 0xFFFFFFFF;
    switch(dir) {
    case DMA_MCAL_DIR_PERIPH_TO_MEMORY:
        code = DMA_PERIPH_TO_MEMORY;
        break;
    case DMA_MCAL_DIR_MEMORY_TO_PERIPH:
        code = DMA_MEMORY_TO_PERIPH;
        break;
    case DMA_MCAL_DIR_MEMORY_TO_MEMORY:
        code = DMA_MEMORY_TO_MEMORY;
        break;
    default:
        code = DMA_MEMORY_TO_MEMORY;
        break;
    }
    return code;
}

uint32_t DmaGetFiFoNode(const DmaFifo_t fifo) {
    uint32_t code = 0xFFFFFFFF;
    switch(fifo) {
    case DMA_FIFO_OFF:
        code = DMA_FIFOMODE_DISABLE;
        break;
    case DMA_FIFO_ON:
        code = DMA_FIFOMODE_ENABLE;
        break;
    default:
        break;
    }
    return code;
}

uint32_t DmaGetPriority(const DmaPriority_t priority) {
    uint32_t code = DMA_PRIORITY_LOW;
    switch(priority) {
    case DMA_PRIOR_LOW:
        code = DMA_PRIORITY_LOW;
        break;
    case DMA_PRIOR_MED:
        code = DMA_PRIORITY_MEDIUM;
        break;
    case DMA_PRIOR_HIGH:
        code = DMA_PRIORITY_HIGH;
        break;
    case DMA_PRIOR_VERY_HIGH:
        code = DMA_PRIORITY_VERY_HIGH;
        break;
    default:
        break;
    }
    return code;
}

uint32_t DmaGetMode(const DmaMode_t mode) {
    uint32_t code = 0xFFFFFFFF;
    switch(mode) {
    case DMA_MODE_NORMAL:
        code = DMA_NORMAL;
        break;
    case DMA_MODE_CIRCULAR:
        code = DMA_CIRCULAR;
        break;
    case DMA_MODE_PFCTRL:
        code = DMA_PFCTRL;
        break;
    default:
        break;
    }
    return code;
}

uint32_t PeriphBurst2StmPeriphBurst(const DmaBurst_t periph_burst) {
    uint32_t stm32_code = 0xFFFFFFFF;
    switch(periph_burst) {
    case DMA_BURST_SINGLE:
        stm32_code = DMA_PBURST_SINGLE;
        break;
    case DMA_BURST_INC4:
        stm32_code = DMA_PBURST_INC4;
        break;
    case DMA_BURST_INC8:
        stm32_code = DMA_PBURST_INC8;
        break;
    case DMA_BURST_INC16:
        stm32_code = DMA_PBURST_INC16;
        break;
    default:
        break;
    }
    return stm32_code;
}

uint32_t MemoryBurst2StmMemoryBurst(const uint8_t mem_burst) {
    uint32_t stm32_code = 0xFFFFFFFF;
    switch(mem_burst) {
    case DMA_BURST_SINGLE:
        stm32_code = DMA_MBURST_SINGLE;
        break;
    case DMA_BURST_INC4:
        stm32_code = DMA_MBURST_INC4;
        break;
    case DMA_BURST_INC8:
        stm32_code = DMA_MBURST_INC8;
        break;
    case DMA_BURST_INC16:
        stm32_code = DMA_MBURST_INC16;
        break;
    default:
        break;
    }
    return stm32_code;
}

uint32_t DmaGetPeriphInc(const uint8_t per_inc) {
    uint32_t code = 0xFFFFFFFF;
    switch(per_inc) {
    case DMA_INC_OFF:
        code = DMA_PINC_DISABLE;
        break;
    case DMA_INC_ON:
        code = DMA_PINC_ENABLE;
        break;
    default:
        break;
    }
    return code;
}

uint32_t DmaGetMemInc(const uint8_t mem_inc) {
    uint32_t code = 0xFFFFFFFF;
    switch(mem_inc) {
    case DMA_INC_OFF:
        code = DMA_MINC_DISABLE;
        break;
    case DMA_INC_ON:
        code = DMA_MINC_ENABLE;
        break;
    default:
        break;
    }
    return code;
}

uint32_t DmaGetPeriphDataAlignment(const DmaAligmant_t aligment_per) {
    uint32_t code = 0xFFFFFFFF;
    switch(aligment_per) {
    case DMA_ALIGNMENT_BYTE:
        code = DMA_PDATAALIGN_BYTE;
        break;
    case DMA_ALIGNMENT_WORD:
        code = DMA_PDATAALIGN_HALFWORD;
        break;
    case DMA_ALIGNMENT_DWORD:
        code = DMA_PDATAALIGN_WORD;
        break;
    default:
        code = 0xFFFFFFFF;
        break;
    }
    return code;
}
