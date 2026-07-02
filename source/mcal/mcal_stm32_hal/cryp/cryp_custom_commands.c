#include "cryp_custom_commands.h"

#include "log.h"
#include "cryp_api.h"

bool cryp_interrupt_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    CrypHandle_t* CrypNode = CrypGetNode(1);
    if(CrypNode) {
        LOG_INFO(LG_CRYP,"%u", CrypNode->in_cnt);
        LOG_INFO(LG_CRYP,"%u", CrypNode->out_cnt);
        LOG_INFO(LG_CRYP,"%u", CrypNode->int_cnt);

        HAL_StatusTypeDef ret= HAL_CRYP_GetConfig( &CrypNode->cryp_h , &CrypNode->Conf);
        if(HAL_OK==ret){
			LOG_INFO(LG_CRYP,"DataType %u", CrypNode->Conf.DataType);
        	LOG_INFO(LG_CRYP,"KeySize %u", CrypNode->Conf.KeySize);
        	LOG_INFO(LG_CRYP,"pKey %p", CrypNode->Conf.pKey);
        	LOG_INFO(LG_CRYP,"pInitVect %p", CrypNode->Conf.pInitVect);
        	LOG_INFO(LG_CRYP,"Algorithm %u", CrypNode->Conf.Algorithm);
        	LOG_INFO(LG_CRYP,"Header %p", CrypNode->Conf.Header);
        	LOG_INFO(LG_CRYP,"HeaderSize %u", CrypNode->Conf.HeaderSize);
        	LOG_INFO(LG_CRYP,"B0 %p", CrypNode->Conf.B0);
        	LOG_INFO(LG_CRYP,"DataWidthUnit %u", CrypNode->Conf.DataWidthUnit);
        	LOG_INFO(LG_CRYP,"HeaderWidthUnit %u", CrypNode->Conf.HeaderWidthUnit);
        	LOG_INFO(LG_CRYP,"KeyIVConfigSkip %u", CrypNode->Conf.KeyIVConfigSkip);
            res = true;
        }
    }
    return res;
}


