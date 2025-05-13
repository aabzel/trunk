#include "fw_loader.h"

#include <stdio.h>
#include <string.h>

#include "array.h"
#include "code_generator.h"
#include "debug_info.h"
#include "file_pc.h"
#include "log.h"
#include "win_utils.h"
#include "storage.h"
#include "hex_bin.h"
#include "time_mcal.h"
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
            Node->tbfp_num = Config->tbfp_num;
            //Node->bit_rate = Config->bit_rate;
            Node->file_name = Config->file_name;
            Node->valid = true;
            Node->write_sn = 0;
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



bool fw_loader_erase_chip(uint8_t num){
    bool res = false;
    LOG_INFO(FW_LOADER, "Erase:%u", num);
    FwLoaderHandle_t* Node = FwLoaderGetNode(  num);
    if(Node) {
        res = tbfp_storage_erase_generate(Node->tbfp_num);
        if(res) {
            TbfpHandle_t* Tbfp = TbfpGetNode(Node->tbfp_num);
            if(Tbfp) {
                Tbfp->rx_done = false;
                uint8_t serial_num = serial_port_com_to_num(Node->com_num);
                tbfp_terminal_print( Node->tbfp_num);
                res = serial_port_send( serial_num , Tbfp->TxFrame, Tbfp->tx_size) ;
                res = tbfp_wait_response_in_loop_ms(Tbfp, 6000);
                res = log_res(FW_LOADER,Tbfp->rx_done,"TbfpEraseResp");
            }
        }
    }
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
                Tbfp->rx_done = false;
                tbfp_terminal_print(Node->tbfp_num);
                uint8_t serial_num = serial_port_com_to_num(Node->com_num);
                res = serial_port_send(serial_num, Tbfp->TxFrame, Tbfp->tx_size) ;
                res = tbfp_wait_response_in_loop_ms(Tbfp, 5000); // <10000
                res = log_info_res(FW_LOADER, Tbfp->rx_done, "TbfpPingResp");
            }
        }
    }
    return res;
}

bool fw_loader_jump(uint8_t num, uint32_t base_address) {
    bool res = false;
    LOG_INFO(FW_LOADER, "Jump:%u,Addr:0x%08x", num,base_address);
    FwLoaderHandle_t* Node = FwLoaderGetNode(num);
    if(Node) {
        res = tbfp_generate_jump(Node->tbfp_num, base_address);
        if(res) {
           TbfpHandle_t* Tbfp = TbfpGetNode(Node->tbfp_num);
           if(Tbfp) {
               uint8_t serial_num = serial_port_com_to_num(Node->com_num);
               res = serial_port_send( serial_num , Tbfp->TxFrame, Tbfp->tx_size) ;
           }
        }
    }

    return res;
}

bool fw_loader_read(const uint8_t num,
                    const uint32_t relative_adress,
                    uint8_t *const data,
                    const uint32_t size){
    bool res = false;
    FwLoaderHandle_t* Node = FwLoaderGetNode(num);
    if(Node) {
        LOG_PARN(FW_LOADER, "N:%u,ReadSN:%u,Addr:0x%08x,Size:%02u,Data:%s", num, Node->read_sn, relative_adress,size);
        Node->read_sn++;
        res = tbfp_storage_read_generate( Node->tbfp_num, relative_adress, size);
        if(res) {
           res = false;
           TbfpHandle_t* Tbfp = TbfpGetNode(Node->tbfp_num);
           if(Tbfp) {
               Tbfp->rx_done = false;
               uint8_t serial_num = serial_port_com_to_num(Node->com_num);
               (void) serial_num;
               tbfp_terminal_print(Node->tbfp_num);
               res = serial_port_send( serial_num , Tbfp->TxFrame, Tbfp->tx_size) ;
               if(res) {
                   res = tbfp_wait_response_in_loop_ms(Tbfp, 10000);
                   res = log_parn_res(FW_LOADER, Tbfp->rx_done, "TbfpReadResp");
                   if(res) {
                	   res = false;
                       if(Tbfp->Storage.size<=size) {
                           if(0<Tbfp->Storage.size) {
                               memcpy(data,storage_rx_data,Tbfp->Storage.size);
                               res = true;
                           }else{
                               LOG_ERROR(FW_LOADER,"SizeZero" );
                           }
                       }else{
                           LOG_ERROR(FW_LOADER,"SizeErr:%u",Tbfp->Storage.size);
                       }
                   }
               }
           }
        }
    }
    return res;
}

bool fw_loader_write(const uint8_t num,
                     const uint32_t relative_adress,
                     const uint8_t *const data,
                     const uint32_t size) {
    bool res = false;
    //res = wait_in_loop_ms( 2);
    FwLoaderHandle_t* Node = FwLoaderGetNode(num);
    if(Node) {
        LOG_DEBUG(FW_LOADER, "N:%u,WrSN:%u,Addr:0x%08x,Size:%02u,Data:%s", num, Node->write_sn, relative_adress,size, ArrayToStr(data,size));
        Node->write_sn++;
        res = tbfp_storage_write_generate( Node->tbfp_num, relative_adress,   data, size   );
        if(res) {
           res = false;
           TbfpHandle_t* Tbfp = TbfpGetNode(Node->tbfp_num);
           if(Tbfp) {
               uint8_t serial_num = serial_port_com_to_num(Node->com_num);
               (void) serial_num;
               Tbfp->rx_done = false;
               tbfp_terminal_print( Node->tbfp_num);
               res = serial_port_send( serial_num , Tbfp->TxFrame, Tbfp->tx_size) ;
               if(res){
                   res = tbfp_wait_response_in_loop_ms(Tbfp, 10000);
                   res = log_res(FW_LOADER, Tbfp->rx_done, "TbfpWriteResp");
               }
           }
        }
    }
    return res;
}


bool fw_loader_write_verify(const uint8_t num,
                            const uint32_t relative_adress,
                            const uint8_t *const data,
                            const uint32_t size) {
    bool res = false ;
    LOG_DEBUG(FW_LOADER, "WrVerify,N:%u,Addr:0x%08x,Size:%02u,Data:%s", num, relative_adress,size, ArrayToStr(data,size));
    //res = wait_in_loop_ms( 2500);//  2000<?<3000
    res = fw_loader_write(num, relative_adress, data, size);
    log_res(FW_LOADER, res, "Write");
#if 1
    if(res) {
    	res = false ;
        if(size <= 256) {
            uint8_t rdData[256] = {0};
          //  res = wait_in_loop_ms( 250); // 0< <250
            res = fw_loader_read(num, relative_adress, rdData, size);
            res = log_res(FW_LOADER, res, "Read");
            if (res) {

                res = array_is_equal(data, rdData, size);
                res = log_res(FW_LOADER, res, "Verify");
            }
        }
    }
#endif
    return res;
}

bool fw_loader_download_firmware(const char * const fileName,
                                 const uint8_t com_port_num,
                                 const uint32_t bit_rate_hz,
                                 const uint32_t size ){
    bool res = false;
    FwLoaderHandle_t* Node = FwLoaderGetNode(1);
    if(Node){
        LOG_INFO(FW_LOADER, "ReadFw,File:%s,COM%u,Rate:%u Bit/s,ExpSize:%u byte", fileName, com_port_num,bit_rate_hz,size);
        Node->com_num = com_port_num;
        Node->file_name = fileName;
        Node->fw_size = size;
        res = serial_port_close(com_port_num);
        SerialPortHandle_t* SerialPort = SerialPortGetNode(1);
        if(SerialPort) {
            res = serial_port_re_init_one(1,   com_port_num,   bit_rate_hz, SerialPort->byte_tx_pause_ms);
            if(res) {
                res = fw_loader_download(1);
                log_res(FW_LOADER, res, "DownLoad");
            }
        }
    }
    return res;
}

#define FW_LOADER_READ_SIZE 64
//#define FW_LOADER_READ_SIZE 64
/*
 read firmware from CHIP to PC
 */
bool fw_loader_download(uint8_t num) {
    bool res = false;
    FwLoaderHandle_t* Node = FwLoaderGetNode(num);
    if(Node) {
        uint32_t start_ms = time_get_ms32();
        res = fw_loader_ping(num);
     //   HexBinHandle_t Item = {0};
        LOG_INFO(FW_LOADER, "N:%u,ReadFwToFile:[%s]", num, Node->file_name);

        uint32_t offset = 0;

        memset(Node->firmware_bin, 0xFF, FW_LOADER_BIN_SIZE);
        for(offset=0; offset <     Node->fw_size; offset+=FW_LOADER_READ_SIZE) {
            diag_progress_log(offset,     Node->fw_size, 10000);
            uint8_t rxData[FW_LOADER_READ_SIZE] = {0xFF};
            res = fw_loader_read(num, offset, rxData, FW_LOADER_READ_SIZE);
            if(res) {
                LOG_DEBUG(FW_LOADER,"%s", ArrayToStr( rxData,(uint32_t) FW_LOADER_READ_SIZE)       );
                memcpy(&Node->firmware_bin[offset],rxData,FW_LOADER_READ_SIZE);
            } else {
                break;
            }
        }

        res = file_pc_delete(Node->file_name);
        res = file_pc_save_array(Node->file_name, Node->firmware_bin, Node->fw_size);

        uint32_t end_ms = time_get_ms32();
        uint32_t duration_ms = end_ms - start_ms;
        LOG_INFO(FW_LOADER, "Duration:%u ms", duration_ms);
        LOG_INFO(FW_LOADER, "Duration:%s", TimeDurationMsToStr(duration_ms));
        float byte_rate = ((float)Node->fw_size)/MSEC_2_SEC(duration_ms);
        LOG_INFO(FW_LOADER, "Rate:%f Byte/s", byte_rate );
    }
    return res;
}

bool fw_loader_upload(uint8_t num, const char *const hex_file) {
    bool res = false;
    FwLoaderHandle_t* Node = FwLoaderGetNode(num);
    if (Node) {
        uint32_t start_ms = time_get_ms32();
        res = fw_loader_ping(num);
        log_res(FW_LOADER, res, "Ping");
        if (res) {
            res = fw_loader_erase_chip(num);
            log_res(FW_LOADER, res, "Erase");
            if (res) {
                res = wait_in_loop_ms( 5000);
                HexBinHandle_t Item = { 0 };
                LOG_INFO(FW_LOADER, "N:%u,UpLoadFile:[%s]", num, hex_file);
                res = hex_to_bin(&Item, hex_file);
                log_res(FW_LOADER, res, "Flash");
                if (res) {
                    res = fw_loader_jump(num, Item.base_address);
                    log_res(FW_LOADER, res, "Jump");
                    uint32_t end_ms = time_get_ms32();
                    uint32_t duration_ms = end_ms - start_ms;
                    LOG_INFO(FW_LOADER, "Duration:%u ms", duration_ms);
                    LOG_INFO(FW_LOADER, "BitSize:%u ", Item.bin_size_byte);

                    LOG_INFO(FW_LOADER, "Duration:%s", TimeDurationMsToStr(duration_ms));
                    float byte_rate = ((float)Item.bin_size_byte) / MSEC_2_SEC(duration_ms);
                    LOG_INFO(FW_LOADER, "Rate:%f Byte/s", byte_rate);
                }
            }
        }
    }
    return res;
}

bool fw_loader_erase_chip_cfg(const uint8_t com_port_num,
                              const uint32_t bit_rate_hz,
                              const uint32_t pause_ms){
    bool res = false;
    FwLoaderHandle_t* Node = FwLoaderGetNode(1);
    if(Node){
        LOG_INFO(FW_LOADER, "EraseFw, COM%u,Rate:%u Bit/s,Pause:%u ms",  com_port_num, bit_rate_hz, pause_ms);
        Node->com_num = com_port_num;
        res = serial_port_close(com_port_num);
        res = serial_port_re_init_one(1, com_port_num, bit_rate_hz, pause_ms);
        if(res) {
            res = wait_in_loop_ms( 1000);
            res = fw_loader_erase_chip(1);
            log_res(FW_LOADER, res, "EraseCfg");
        }
    }
    return res;
}

bool fw_loader_upload_file(const char * const fileName,
                           const uint8_t com_port_num,
                           const uint32_t bit_rate_hz,
                           const uint32_t pause_ms) {
    bool res = false;
    FwLoaderHandle_t* Node = FwLoaderGetNode(1);
    if(Node){
        LOG_INFO(FW_LOADER, "WriteFw,File:%s,COM%u,Rate:%u Bit/s,Pause:%u ms", fileName, com_port_num, bit_rate_hz, pause_ms);
        Node->com_num = com_port_num;
        Node->file_name = fileName;

        res = serial_port_close(com_port_num);
        res = serial_port_re_init_one(1, com_port_num, bit_rate_hz, pause_ms);
        if(res) {
            res = wait_in_loop_ms( 3000);
            res = fw_loader_upload(1, fileName);
            log_res(FW_LOADER, res, "UpLoad");
        }
    }
    return res;
}

COMPONENT_PROC_PATTERT(FW_LOADER, FW_LOADER, fw_loader)
COMPONENT_INIT_PATTERT(FW_LOADER, FW_LOADER, fw_loader)
