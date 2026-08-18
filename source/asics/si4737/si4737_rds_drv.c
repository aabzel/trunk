#include <gpio_stm32_diag.h>
#include "si4737_rds_drv.h"

#include <stdbool.h>
#include <string.h>

#include "si4737_drv.h"
#include "byte_utils.h"
#include "bit_const.h"
#include "clocks.h"
#include "data_types.h"
#include "gpio_mcal.h"
#include "i2c_config.h"
#include "i2c_mcal.h"
#include "log.h"
#include "si4737_config.h"
#include "si4737_diag.h"
#include "timer_utils.h"
#include "rds_protocol.h"

bool si4737_set_fm_rds_int_source(void){
    bool res = true;
    FmRdsIntSource_t FmRdsIntSource;
    FmRdsIntSource.rds_new_block_a=1;
    FmRdsIntSource.rds_new_block_b=1;
    FmRdsIntSource.rds_sync_found=1;
    FmRdsIntSource.rds_recv=1;
    FmRdsIntSource.rds_sync_lost=1;
    res = si4737_set_property( SI4737_FM_RDS_INT_SOURCE, FmRdsIntSource.word);
    return res;
}

bool si4737_init_rds(void){
    bool res = true;
    LOG_INFO(RDS, "InitRDS");
    res = si4737_set_fm_rds_int_source();
    res = si4737_set_fm_rds_int_fifo_cnt(Si4737Config.rds_int_fifo_cnt );
    res = si4737_set_fm_rds_config(Si4737Config.rds_en);
    return res;
}


static bool si4737_parse_rds_status_resp1(uint8_t byte){
    bool res= false;
    FmRdsStatusResp1_t Resp1;
    Resp1.byte= byte;
    if(Resp1.rds_new_block_a){
        LOG_WARNING(RDS, "RxNewBlockA");
    }
    if(Resp1.rds_new_block_b){
        LOG_WARNING(RDS, "RxNewBlockB");
    }
    if(Resp1.rds_sync_found){
        LOG_WARNING(RDS, "RdsSyncSpot");
    }
    if(Resp1.rds_sync_lost){
        LOG_WARNING(RDS, "RdsSyncLost");
    }
    if(Resp1.rds_recv){
        LOG_WARNING(RDS, "RdsRx");
    }
    return res;
}


static bool si4737_parse_rds_status_resp2(uint8_t byte){
    bool res= false;
    FmRdsStatusResp2_t Resp2;
    Resp2.byte= byte;
    if(Resp2.rds_sync){
        LOG_WARNING(RDS, "RdsSync");
    }
    if(Resp2.grp_lost){
        LOG_WARNING(RDS, "FifoOverrun");
    }

    return res;
}


static bool si4737_parse_rds_status_resp12(uint8_t byte){
    bool res= false;
    FmRdsStatusResp12_t Resp12;
    Resp12.byte = byte;

    LOG_DEBUG(RDS, "%s", parse_rds_block_corr_err(Resp12.ble_a, RDS_BLOCK_A));
    LOG_DEBUG(RDS, "%s", parse_rds_block_corr_err(Resp12.ble_b, RDS_BLOCK_B));
    LOG_DEBUG(RDS, "%s", parse_rds_block_corr_err(Resp12.ble_c, RDS_BLOCK_C));
    LOG_DEBUG(RDS, "%s", parse_rds_block_corr_err(Resp12.ble_d, RDS_BLOCK_D));

    return res;
}

bool si4737_get_fm_rds_status(Si4737Handler_t* instance, uint8_t *rds_fifo_cnt){
    bool res = false;
    FmRdsStatusArg1_t Arg1;
    Arg1.int_ack = RDS_INT_ACK_CLEAR;
    Arg1.mt_fifo = RDS_RX_FIFO_READ;
    Arg1.status_only = RDS_STATUS_ONLY_OLDEST;
    res = si4737_set_command(SI4737_CMD_FM_RDS_STATUS, &Arg1.byte, 1);
    if(res) {
        FmRdsStatusResp_t Resp;
        memset(Resp.buff, 0, sizeof(FmRdsStatusResp_t));
        res = si4737_get_resp(Resp.buff, sizeof(FmRsqStatusResp_t));
        if(res) {
            si4737_proc_status(Resp.status.byte, instance);
            si4737_parse_rds_status_resp1(Resp.Resp1.byte);
            si4737_parse_rds_status_resp2(Resp.Resp2.byte);
            si4737_parse_rds_status_resp12(Resp.Resp12.byte);
            if(Resp.Resp1.rds_recv){
                instance->rds_recv_cnt++;
                res = rds_proc_message((uint16_t* ) &Resp.RdsData.words[0]);
            }

            if(Resp.rds_fifo_used){
            	 LOG_WARNING(RDS,"RdsFiFoCnt %u",Resp.rds_fifo_used);
            	 *rds_fifo_cnt=Resp.rds_fifo_used;
            }

#if 0
            LOG_INFO(RDS,"A 0x%04x [%c] [%c]",Resp.block_a.u16,(char)Resp.block_a.u8[0],(char)Resp.block_a.u8[1]);
            LOG_INFO(RDS,"B 0x%04x [%c] [%c]",Resp.block_b.u16,(char)Resp.block_b.u8[0],(char)Resp.block_b.u8[1]);
            LOG_INFO(RDS,"C 0x%04x [%c] [%c]",Resp.block_c.u16,(char)Resp.block_c.u8[0],(char)Resp.block_c.u8[1]);
            LOG_INFO(RDS,"D 0x%04x [%c] [%c]",Resp.block_d.u16,(char)Resp.block_d.u8[0],(char)Resp.block_d.u8[1]);
#endif
        }else{
            LOG_ERROR(RDS,"RespErr");
        }
    }else{
        LOG_ERROR(RDS,"CmdFmRdsStatusErr");
    }
    return res;
}

bool si4737_set_fm_rds_int_fifo_cnt(uint8_t rds_fifo_cnt){
    bool res = false;
    if(rds_fifo_cnt<=25){
        res= si4737_set_property(SI4737_FM_RDS_INT_FIFO_COUNT, (uint16_t )rds_fifo_cnt);
    }else{
        LOG_ERROR(RDS, "ParamErr %u", rds_fifo_cnt);
    }
    return res;
}

bool si4737_get_fm_rds_int_fifo_cnt(uint8_t* rds_fifo_cnt){
    bool res = false;
    uint16_t val=0;
    res= si4737_get_property(SI4737_FM_RDS_INT_FIFO_COUNT, &val);
    if(res){
        (*rds_fifo_cnt) = MASK_8BIT &val;
    }

    return res;
}

bool si4737_set_fm_rds_config(bool rds_en){
    bool res = false;
    FmRdsConfig_t FmRdsConfig;
    FmRdsConfig.word = 0;
    FmRdsConfig.bletha=RDS_BLOCK_CORR_3_5_BIT;
    FmRdsConfig.blethb=RDS_BLOCK_CORR_3_5_BIT;
    FmRdsConfig.blethc=RDS_BLOCK_CORR_3_5_BIT;
    FmRdsConfig.blethd=RDS_BLOCK_CORR_3_5_BIT;
    FmRdsConfig.rds_en = rds_en;
    res= si4737_set_property(SI4737_FM_RDS_CONFIG, FmRdsConfig.word);
    return res;
}
