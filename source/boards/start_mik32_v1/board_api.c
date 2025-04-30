#include "board_api.h"

#include "rv32imc_driver.h"
#include "tbfp.h"
#include "time_mcal.h"

#ifdef HAS_SPIFI
#include "spifi_mcal.h"
#include "spifi_custom_drv.h"
#endif

#ifdef HAS_W25Q32JV
#include "w25q32jv_drv.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

bool board_init(void) {
    bool res = true;
#ifdef HAS_LOG
    set_log_level(SYS,LOG_LEVEL_INFO);
    LOG_INFO(SYS,"XTall:%u Hz",XTALL_FREQ_HZ);
#endif

    return res;
}

/*
  Init XIP -  execute-in-place
 */
bool board_init_xip(void) {
    bool res = false;
#ifdef HAS_SPIFI
    const SpiFiConfig_t *Config = SpiFiGetConfig(0);
    if (Config) {
        SpiFiInfo_t *Info = SpiFiGetInfo(0);
        if (Info) {
            SpiFiHandle_t *Node = SpiFiGetNode(0);
            if (Node) {
                // HAL_SPIFI_MspInit();
                HAL_SPIFI_Reset(&Node->Handle);

                W25q32jvRegUniversal_t UniReg2 = { 0 };
                res = w25q32jv_read_reg(1, W25Q32JV_STATUS_REG_2, &UniReg2);
                UniReg2.Status2.qe = W25_STAUS_2_QUAD_ENABLE;
                res = w25q32jv_write_reg2(1, UniReg2.byte);
                if (res) {
                    /* see Figure 24. Fast Read Quad I/O Instruction (M7-M0 should be set to Fxh)*/
                    SPIFI_MemoryCommandTypeDef CmdFastReadQuad = { 0 };
                    CmdFastReadQuad.OpCode = W25Q32JV_FAST_READ_QUAD_IO; /* Fast Read Quad I/O (EBh) */
                    CmdFastReadQuad.FieldForm = SPIFI_CONFIG_CMD_FIELDFORM_OPCODE_SERIAL;
                    CmdFastReadQuad.FrameForm = SPIFI_CONFIG_CMD_FRAMEFORM_OPCODE_3ADDR;
                    CmdFastReadQuad.InterimData = 0;
                    CmdFastReadQuad.InterimLength = 3;

                    SPIFI_MemoryModeConfig_HandleTypeDef SpiFiMem = { 0 };
                    SpiFiMem.Instance = Info->SPIFIx;
                    SpiFiMem.CacheEnable = SpiFiCacheCtrlToCacheEnable(Config->cache_on_off);
                    SpiFiMem.CacheLimit = Config->cache_limit;
                    SpiFiMem.Command = CmdFastReadQuad;
                    HAL_SPIFI_MemoryMode_Init(&SpiFiMem);
                }
            }
        }
    }
#endif

    return res;
}

bool application_launch(void) {
    bool res = true;
    res = board_init_xip();
    if(res) {
        res = rv32imc_boot_addr(EXT_ROM_START) ;
    }
    return res;
}

bool board_proc(void) {
    bool res = false;
    TbfpHandle_t *Tbfp = TbfpGetNode(1);
    if (Tbfp) {
#ifdef HAS_TIME
       uint32_t up_time_ms = time_get_ms32();
       uint32_t diff_ms = up_time_ms - Tbfp->rx_time_stamp_ms;
       if(BOARD_IDLE_TIME_OUT_MS < diff_ms) {
    	   Tbfp->rx_time_stamp_ms = time_get_ms32();
           res = application_launch( );
       }
#else
       uint32_t diff_iteration = Tbfp->iteration - Tbfp->rx_time_stamp_iteration;
       if(BOARD_IDLE_TIME_OUT_ITER < diff_iteration) {
           res = application_launch();
       }
#endif
        res = true;
    }
    return res;
}

bool application_mcal_init(void) {
    bool res = true;
#ifdef HAS_MBR
    res = application_launch();
#endif
    return res;
}
