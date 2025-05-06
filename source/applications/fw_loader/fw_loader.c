#include "fw_loader.h"

#include <stdio.h>
#include <string.h>

#include "array.h"
#include "code_generator.h"
#include "debug_info.h"
#include "file_pc.h"
#include "log.h"
#include "win_utils.h"
#include "serial_port.h"
#include "tbfp_diag.h"

COMPONENT_GET_NODE(FwLoader, fw_loader)

COMPONENT_GET_CONFIG(FwLoader, fw_loader)

static bool fw_loader_init_common(const FwLoaderConfig_t* const Config, FwLoaderHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->com_num = Config->com_num;
            Node->serial_num = Config->serial_num;
            Node->tbfp_num = Config->tbfp_num;
            Node->bit_rate = Config->bit_rate;
            Node->hex_file_name = Config->hex_file_name;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

bool FwLoaderIsValidConfig(const FwLoaderConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
    }
    return res;
}

bool fw_loader_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(FW_LOADER, "Init:%u", num);
    set_log_level(FW_LOADER, LOG_LEVEL_DEBUG);

    const FwLoaderConfig_t* Config = FwLoaderGetConfig(num);
    if(Config) {
        res = FwLoaderIsValidConfig(Config);
        if(res) {
            FwLoaderHandle_t* Node = FwLoaderGetNode(num);
            if(Node) {
                res = fw_loader_init_common(Config, Node);
                set_log_level(FW_LOADER, LOG_LEVEL_INFO);
                Node->init = true;
                LOG_INFO(FW_LOADER, "Init:%u,Ok", num);
                res = true;
            }
        }
    }

    return res;
}

bool fw_loader_proc_one(uint8_t num) {
    bool res = false;
    FwLoaderHandle_t* Node = FwLoaderGetNode(num);
    if(Node) {
    }

    return res;
}

bool fw_loader_init_custom(void) {
    bool res = true;
    return res;
}


bool fw_loader_download(uint8_t num){
    bool res = false;
    return res;
}

bool fw_loader_ping(uint8_t num) {
    bool res = false;
    LOG_INFO(FW_LOADER, "Ping:%u", num);
    FwLoaderHandle_t* Node = FwLoaderGetNode(  num);
    if(Node) {
        res = tbfp_storage_read_generate(Node->tbfp_num, 0, 8);
        if(res) {
            TbfpHandle_t* Tbfp = TbfpGetNode(Node->tbfp_num);
            if(Tbfp) {
                res = serial_port_send( Node->serial_num , Tbfp->TxFrame, Tbfp->tx_size) ;
            }
        }
    }
    return res;
}

bool fw_loader_upload(uint8_t num, char* hex_file){
    bool res = false;
    return res;
}

COMPONENT_PROC_PATTERT(FW_LOADER, FW_LOADER, fw_loader)
COMPONENT_INIT_PATTERT(FW_LOADER, FW_LOADER, fw_loader)
