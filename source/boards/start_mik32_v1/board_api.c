#include "board_api.h"

#include "rv32imc_driver.h"
#include "k1948bk018_const.h"
#include "core_driver.h"

#ifdef HAS_LED
#include "led_drv.h"
#endif

#ifdef HAS_TBFP
#include "tbfp.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

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
                HAL_SPIFI_MspInit();
                // HAL_SPIFI_Reset(&Node->Handle);

                W25q32jvRegUniversal_t UniReg1 = { 0 };
                res = w25q32jv_read_reg(1, W25Q32JV_STATUS_REG_1, &UniReg1);

                W25q32jvRegUniversal_t UniReg2 = { 0 };
                res = w25q32jv_read_reg(1, W25Q32JV_STATUS_REG_2, &UniReg2);// r
                if(res){
                    UniReg2.Status2.qe = W25_STAUS_2_QUAD_ENABLE;
                    res = w25q32jv_write_regs(1,UniReg1.byte, UniReg2.byte); // rr
                    if (res) {
                    	// r
                        /* see Figure 24. Fast Read Quad I/O Instruction (M7-M0 should be set to Fxh)*/
                        SPIFI_MemoryCommandTypeDef CmdFastReadQuad = { 0 };
                        CmdFastReadQuad.OpCode = W25Q32JV_FAST_READ_QUAD_IO; /* Fast Read Quad I/O (EBh) */
                        CmdFastReadQuad.FieldForm = SPIFI_CONFIG_CMD_FIELDFORM_OPCODE_SERIAL;
                        CmdFastReadQuad.FrameForm = SPIFI_CONFIG_CMD_FRAMEFORM_OPCODE_3ADDR;
                        CmdFastReadQuad.InterimData = 0;
                        CmdFastReadQuad.InterimLength = 3;

                        SPIFI_MemoryModeConfig_HandleTypeDef SpiFiMem = { 0 };
                        (void) SpiFiMem;
                        SpiFiMem.Instance = Info->SPIFIx;
                        SpiFiMem.CacheEnable = SpiFiCacheCtrlToCacheEnable(Config->cache_on_off);
                        SpiFiMem.CacheLimit = Config->cache_limit;
                        SpiFiMem.Command = CmdFastReadQuad;
        	            // r
                        HAL_SPIFI_MemoryMode_Init(&SpiFiMem); // hang on here
        	            led_mono_ctrl(2, 1);
                       // led_mono_ctrl(2, true);
                        res = true;
                    }
                }
            }
        }
    }
#endif

    return res;
}

bool application_launch(const uint32_t base_address) {
    bool res = true;
    res = board_init_xip();
    if(res) {
        //res = rv32imc_boot_spifi() ;
    	// no led_mono_ctrl(2, 1);
        //res = rv32imc_boot_addr(EXT_ROM_START) ;
        res = rv32imc_boot_addr(base_address) ;
    }
    return res;
}

uint32_t board_get_up_time_ms(void){
	   uint32_t up_time_ms = 0;
#ifdef HAS_TIME
       up_time_ms =  time_get_ms32();
#else
       up_time_ms = core_get_up_time_ms();
#endif
       return up_time_ms;
}

bool board_proc(void) {
    bool res = false;
#ifdef HAS_TBFP
    TbfpHandle_t *Tbfp = TbfpGetNode(1);
    if (Tbfp) {
#ifdef HAS_TIME
       uint32_t up_time_ms = 0;
       uint32_t diff_ms  = 0;
       up_time_ms = board_get_up_time_ms();
       diff_ms = up_time_ms - Tbfp->rx_time_stamp_ms;
       if(BOARD_IDLE_TIME_OUT_MS < diff_ms) {
           Tbfp->rx_time_stamp_ms = board_get_up_time_ms();
           res = application_launch(EXT_ROM_START );
       }
#else
       uint32_t diff_iteration = Tbfp->iteration - Tbfp->rx_time_stamp_iteration;
       if(BOARD_IDLE_TIME_OUT_ITER < diff_iteration) {
           res = application_launch(EXT_ROM_START);
       }
#endif
        res = true;
    }
#else
    res = application_launch();
#endif
    return res;
}

bool application_mcal_init(void) {
    bool res = true;
#ifdef HAS_MBR
    res = application_launch();
#endif
    return res;
}
