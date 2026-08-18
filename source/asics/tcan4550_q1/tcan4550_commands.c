
#include "tcan4550_commands.h"
#include <stdio.h>

#include "convert.h"
#include "debug_info.h"
#include "io_utils.h"
#include "log.h"
#include "str_utils.h"
#include "tcan4550_diag.h"
#include "tcan4550_drv.h"
#include "TCAN4550.h"
#include "table_utils.h"
#include "data_utils.h"
#include "writer_config.h"

bool tcan4550_diag_hl_command(int32_t argc, char* argv[]){
    bool res = true;
    LOG_INFO(CAN,"connected %u",  CanPhy.cur.connected);
    LOG_INFO(CAN,"WDT %sable",  (true==CanPhy.cur.wdt)?"En":"Dis");
    LOG_INFO(CAN,"int cnt %u",  CanPhy.cur.int_cnt);
    LOG_INFO(CAN,"cur mode %s",  can_mode2str(CanPhy.cur.mode));
    LOG_INFO(CAN,"bit rate %u bit/s",  CanPhy.cur.bit_rate);
    LOG_INFO(CAN,"lock %s",  (true==CanPhy.cur.lock)?"locked":"unlocked");
    LOG_INFO(CAN,"LEC %s",  lec2str(CanPhy.cur.lec));
    return res;
}

bool tcan4550_fifo_diag_command(int32_t argc, char* argv[]){
    bool res = false;
    if (0==argc) {
        res = true;
        tCanRegFiFo0Stat_t fifo0={0};
        tCanRegFiFo1Stat_t fifo1={0};
        res = tcan4550_read_reg(ADDR_MCAN_RXF0S, &fifo0.word)&&res;
        res = tcan4550_read_reg(ADDR_MCAN_RXF1S, &fifo1.word)&&res;
            static const table_col_t cols[] = {{5, "No"},
                                               {5, "Fill"},
                                               {5, "get"},
                                               {5, "put"},
                                               {5, "Full"},
                                               {5, "lost"}
                                               };
            table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
        if(res){
            io_printf(TSEP);
            io_printf("  0  " TSEP);
            io_printf(" %2u  " TSEP, fifo0.f0fl);
            io_printf(" %2u  " TSEP, fifo0.f0gi);
            io_printf(" %2u  " TSEP, fifo0.f0pi);
            io_printf(" %2u  " TSEP, fifo0.f0f);
            io_printf(" %2u  " TSEP, fifo0.rf0l);
            io_printf(CRLF);
            io_printf(TSEP);
            io_printf("  1  " TSEP);
            io_printf(" %2u  " TSEP, fifo1.f1fl);
            io_printf(" %2u  " TSEP, fifo1.f1gi);
            io_printf(" %2u  " TSEP, fifo1.f1pi);
            io_printf(" %2u  " TSEP, fifo1.f1f);
            io_printf(" %2u  " TSEP, fifo1.rf1l);
            io_printf(CRLF);
        }
            table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    }

    return res;
}

bool tcan4550_diag_ll_command(int32_t argc, char* argv[]){
    bool res = false;
    uint32_t out_reg = 0;

    out_reg = 0;
    res = tcan4550_read_reg(ADDR_DEVICE_ID0, &out_reg);
    res=tcan4550_parse_reg_dev_id0(out_reg);

    out_reg = 0;
    res = tcan4550_read_reg(ADDR_DEVICE_ID1, &out_reg);
    res = tcan4550_parse_reg_dev_id1(out_reg);

    out_reg = 0;
    res = tcan4550_read_reg(ADDR_SPI_2_REV, &out_reg);
    res = tcan4550_parse_reg_revision(out_reg);

    out_reg = 0;
    res = tcan4550_read_reg(ADDR_SPI_STATUS, &out_reg);
    res = tcan4550_parse_reg_status(out_reg);

    out_reg = 0;
    res = tcan4550_read_reg(ADDR_DEV_CONFIG, &out_reg);
    res = tcan4550_parse_reg_mode_op_cfg(out_reg);

    out_reg = 0;
    res = tcan4550_read_reg(ADDR_IF, &out_reg);
    res =  tcan4550_parse_reg_interrupt_flags(  out_reg);

    out_reg = 0;
    res = tcan4550_read_reg(ADDR_MCAN_NBTP, &out_reg);
    res =  tcan4550_parse_reg_bit_timing(out_reg);

    return res;
}

bool tcan4550_init_command(int32_t argc, char* argv[]){
    bool res = false;
    if(0==argc){
        res = tcan4550_init();
        if (res) {
            LOG_INFO(CAN, "init OK");
        }else{
            LOG_ERROR(CAN, "init err");
        }
    } else {
        LOG_ERROR(CAN, "Usage: ci");
    }
    return res;
}

bool tcan4550_deinit_command(int32_t argc, char* argv[]){
    bool res = false;
    if(0==argc){
        res = tcan4550_deinit();
        if (res) {
            LOG_INFO(CAN, "deinit OK");
        }else{
            LOG_ERROR(CAN, "deinit err");
        }
    } else {
        LOG_ERROR(CAN, "Usage: cdi");
    }
    return res;
}

bool tcan4550_int_diag_command(int32_t argc, char* argv[]){
    bool res = false;
    return res;
}

bool tcan4550_read_reg_command(int32_t argc, char* argv[]){
    bool res = false;
    uint16_t address=0;
    uint32_t reg_val=0;
    if(1==argc){
        res = try_str2uint16(argv[0], &address);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract address %s", argv[0]);
        }
    } else {
        LOG_ERROR(CAN, "Usage: crr addr");
    }
    if(true == res) {
        res = tcan4550_read_reg( address, &reg_val);
        if (res) {
            io_printf("0x%08x 0b%s"CRLF, reg_val, utoa_bin32(reg_val));
        } else {
            LOG_ERROR(CAN, "read error");
        }
    }
    return res;
}

bool tcan4550_set_lock_command(int32_t argc, char* argv[]){
    bool res = false;
    bool state=false;

    if(1<=argc){
        res = try_str2bool(argv[0], &state);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract state %s", argv[0]);
        }
    }

    if (res && (1==argc)) {
        res =  tcan4550_set_lock( state);
        if (res) {
            LOG_INFO(CAN, "OK");
        }else{
            LOG_ERROR(CAN, "err");
        }
    } else {
        LOG_ERROR(CAN, "Usage: csl state");
    }
    return res;
}

bool tcan4550_set_mode_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t dev_mode=0;

    if(1<=argc){
        res = try_str2uint8(argv[0], &dev_mode);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract mode %s", argv[0]);
        }
    }

    if (res && (1==argc)) {
        res =  tcan4550_set_mode((CanDevMode_t) dev_mode);
        if (res) {
            LOG_INFO(CAN, "OK %s",can_mode2str(dev_mode));
        }else{
            LOG_ERROR(CAN, "err");
        }
    } else {
        LOG_ERROR(CAN, "Usage: csm mode");
    }
    return res;
}

bool tcan4550_read_command(int32_t argc, char* argv[]){
    bool res = false;
    uint16_t address=0;
    uint8_t len = 0;
    uint8_t data[32]="";
    memset(data, 0xFF, sizeof(data));
    if(2==argc){
        res = try_str2uint16(argv[0], &address);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract address %s", argv[0]);
        }
        res = try_str2uint8(argv[1], &len);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract len %s", argv[1]);
        }
    }else{
        LOG_ERROR(CAN, "Usage: cr addr len");
    }
    if(true == res) {
        res = tcan4550_read( address, len, data, sizeof(data));
        if(res){
            print_mem(data,sizeof(data), true,true,true,true);
        }else{
            LOG_ERROR(CAN, "read error");
        }
    }
    return res;
}

static bool tcan4550_reg_map_diag(char* key_word1, char* key_word2){
    bool res = false;
    uint16_t reg_cnt = tcan4550_get_reg_cnt();
    uint32_t reg_val=0;
    static const table_col_t cols[] = {{5, "Num"},
                                       {8, "addr"},
                                       {12, "value,hex"},
                                       {41, "reg value,bin"},
                                       {15, "Name"}
    };
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    uint16_t num = 0,i=0;
    char temp_str[200];
    for(i=0;i<reg_cnt;i++){
        res = tcan4550_read_reg(  tCan4550RegLUT[i].addr, &reg_val);
        if(res){
          strcpy(temp_str, TSEP);
          snprintf(temp_str, sizeof(temp_str), "%s 0x%04x " TSEP, temp_str, tCan4550RegLUT[i].addr);
          snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str, reg_val);
          snprintf(temp_str, sizeof(temp_str), "%s %s " TSEP, temp_str, utoa_bin32(reg_val));
          snprintf(temp_str, sizeof(temp_str), "%s %13s " TSEP, temp_str, tCan4550RegLUT[i].name);
          snprintf(temp_str, sizeof(temp_str), "%s" CRLF, temp_str);
          if(is_contain(temp_str, key_word1, key_word2)) {
              io_printf(TSEP " %3u ", num);
              io_printf("%s", temp_str);
              num++;
          }
        }
    }

    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    return res;
}

bool tcan4550_reg_map_command(int32_t argc, char* argv[]){
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }
    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        LOG_ERROR(SYS, "Usage: cm keyWord1 keyWord2");
    }
    if(true == res) {
        res = tcan4550_reg_map_diag(keyWord1, keyWord2);
    }
    return res;
}

bool tcan4550_reset_command(int32_t argc, char* argv[]){
    bool res = false;
    res = tcan4550_reset();
    if(res){
        LOG_INFO(CAN, "reset OK");
    }else{
        LOG_ERROR(CAN, "reset error");
    }
    return res;
}

bool tcan4550_write_reg_command(int32_t argc, char* argv[]){
    bool res = false;
    uint16_t address=0;
    uint32_t reg_val = 0;
    if(1<=argc){
        res = try_str2uint16(argv[0], &address);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract address %s", argv[0]);
        }
    }
    if(2<=argc){
        res = try_str2uint32(argv[1], &reg_val);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract reg_val %s", argv[1]);
        }
    }

    if ((true==res) && (2==argc)) {
        res = tcan4550_write_reg(address, reg_val);
        if (true==res) {
            LOG_INFO(CAN, "write addr 0x%x val 0x%x ok",address,reg_val);
        }else{
            LOG_ERROR(CAN, "write err");
        }
    } else {
        LOG_ERROR(CAN, "Usage: cwr addr reg");
    }
    return res;
}

bool tcan4550_clear_mram_command(int32_t argc, char* argv[]){
    bool res = false;
    res = tcan4550_clear_mram();
    return res;
}
//cs 0x55 0x1122334455667788

bool tcan4550_send_std_frame_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t len = 8;
    uint16_t id= 0;
    uint64_t data64 = 0;
    if(1<=argc) {
        res = try_str2uint16(argv[0], &id);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract id %s", argv[0]);
        }
    }
    if(2<=argc){
        res = try_str2uint64(argv[1], &data64);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract data %s", argv[1]);
        }
    }

    if(3<=argc){
        res = try_str2uint8(argv[2], &len);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract len %s", argv[2]);
        }
    }

    if (res) {
        res = tcan4550_send_std(id, data64, len);
        if (res) {
            LOG_INFO(CAN, "send std id: 0x%06x data: 0x%llx %u byte  ok", id, data64, len);
        } else {
            LOG_ERROR(CAN, "Unable to send frame");
        }
    }
    return res;
}

bool tcan4550_send_ext_frame_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t len = 8;
    uint16_t id= 0;
    uint64_t data64 = 0;
    if(1<=argc) {
        res = try_str2uint16(argv[0], &id);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract id %s", argv[0]);
        }
    }
    if(2<=argc){
        res = try_str2uint64(argv[1], &data64);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract data %s", argv[1]);
        }
    }

    if(3<=argc){
        res = try_str2uint8(argv[2], &len);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract len %s", argv[2]);
        }
    }

    if (res) {
        res = tcan4550_send_ext(id, data64, len);
        if (res) {
            LOG_INFO(CAN, "send ext id: 0x%06x data: 0x%llx %u byte ok", id, data64, len);
        } else {
            LOG_ERROR(CAN, "Unable to send frame");
        }
    }
    return res;
}



bool tcan4550_get_fifos_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t fifo_num =0;
    if(0==argc){
        res = true;
    }
    if(1<=argc) {
        res = try_str2uint8(argv[0], &fifo_num);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract fifo_num %s", argv[0]);
        }
    }
    if(2<argc){
        LOG_ERROR(CAN, "Usage: cfg num");
    }

    if(res){
        TCAN4x5x_MCAN_RX_Header MsgHeader = {0};        // Initialize to 0 or you'll get garbage
        uint8_t num_bytes = 0;                           // Used since the ReadNextFIFO function will return how many bytes of data were read
        uint8_t dataPayload[64] = {0};                  // Used to store the received data

        num_bytes = TCAN4x5x_MCAN_ReadNextFIFO( (TCAN4x5x_MCAN_FIFO_Enum)fifo_num, &MsgHeader, dataPayload);   // This will read the next element in the RX FIFO 0
        if(num_bytes ){
            LOG_INFO(CAN, "Rx ID %u 0x%x",MsgHeader.ID, MsgHeader.ID);
            print_mem(dataPayload,num_bytes, true,true,true,true);
            res = true;
        }
    }
    return res;
}


bool tcan4550_set_rate_command(int32_t argc, char* argv[]){
    bool res = false;

    uint32_t bit_rate = 250000;
    if(1<=argc) {
        res = try_str2uint32(argv[0], &bit_rate);
        if(false == res) {
            LOG_ERROR(CAN, "Unable to extract bit rate %s", argv[0]);
        }
    }
    if (res) {
        res= tcan4550_set_bit_rate( bit_rate) ;
        if (res) {
            LOG_INFO(CAN, "Bit rate %f set OK",bit_rate);
        } else {
            LOG_ERROR(CAN, "Unable to set bit rate %f set",bit_rate);
        }
    }
    return res;
}


bool tcan4550_diag_mram_command(int32_t argc, char* argv[]){
    bool res = false;
    if(0==argc){
        res = true;
        uint16_t addr = 0;
        uint32_t read_reg = 0;
        for(addr = ADDR_MRAM; addr<=(ADDR_MRAM+MRAM_SZ-4); addr+=4){
            res = tcan4550_read_reg(addr, &read_reg)&&res ;
            if(res){
                if(0==read_reg){
                    io_printf(".");
                }else{
                    io_printf("x");
                }
            }
            if(0==(addr%(4*32))){
                io_printf(CRLF);
            }
        }
        if (res) {
            LOG_INFO(CAN, "OK");
        } else {
            LOG_ERROR(CAN, "error");
        }
        io_printf(CRLF);
    }
    return res;
}
