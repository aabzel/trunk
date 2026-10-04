#include "w25m02gv_commands.h"

#include "convert.h"
#include "log.h"
#include "w25m02gv.h"

bool w25m02gv_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    char key_word[20] = "";
    if(0 <= argc) {
        res = true;
    }


    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        strcpy(key_word, argv[1]);
        res = true;
    }

    if(res) {
        LOG_INFO(W25M02GV, "LowLevelDiag KeyWord [%s]", key_word);
        res = w25m02gv_diag_low_level(num,key_word);
        if(res) {
            LOG_INFO(W25M02GV, "LowLevelDiagOk");
        } else {
            LOG_ERROR(W25M02GV, "LowLevelDiagErr");
        }
    }
    return res;
}

bool w25m02gv_diag_hl_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    res = w25m02gv_diag_high_level(num);
    return res;
}


bool w25m02gv_register_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint8_t addr = 0;
    W25m02gvRegUniversal_t Reg={0};

    if(1 <= num) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &addr);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &Reg.byte);
    }

    if(res) {
    	switch(argc){
    	case 2:{
            res = w25m02gv_register_read(num, addr, &Reg);
            if(res) {
                LOG_INFO(W25M02GV, "Get,Addr:0x%02x,Val:0x%02x", addr, Reg.byte);
            }

    	} break;
    	case 3:{
            LOG_INFO(W25M02GV, "Set,Addr:0x%02x,Val:0x%02x", addr, Reg.byte);
            res = w25m02gv_register_write(num, addr, Reg);
            if(res) {
            	 LOG_INFO(W25M02GV, "WriteOk");
            }
    	} break;
    	default:{res = false;} break;
    	}
    } else {
        LOG_ERROR(W25M02GV, "Usage: w25reg Num RegAddr RegVal");
    }

    return res;
}

bool w25m02gv_init_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    res = w25m02gv_init_one(num);
    return res;
}

#if 0
static bool w25m02gv_reg_hazy_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        res = true;
    }

    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = w25m02gv_reg_hazy(num);
        res = w25m02gv_reg_map_hidden_diag(num);
    }else{
        LOG_ERROR(W25M02GV, "Usage: nrh");
    }
    return res;
}
#endif


bool w25m02gv_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }

    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }


    if(2 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if(3 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        LOG_ERROR(W25M02GV, "Usage: maxregs keyWord keyWord");
    }
    if(res) {
        res = w25m02gv_reg_map_diag(num,keyWord1, keyWord2);
    }
    return res;
}

bool w25m02gv_reg_map_hidden_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = w25m02gv_reg_map_hidden_diag(num);
    }
    return res;
}



bool w25m02gv_spi_ping_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    res = w25m02gv_is_connected(num);
    if(res) {
        LOG_INFO(W25M02GV, "Connected!");
    } else {
        LOG_ERROR(W25M02GV, "Disconnected!");
    }
    return res;
}

bool w25m02gv_reset_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = w25m02gv_reset(num);
        if(res){
        LOG_INFO(W25M02GV, "ResetOk,Num:%u",num);
        }else{
        LOG_ERROR(W25M02GV, "ResetErr,Num:%u",num);
        }
    }else {
        LOG_ERROR(W25M02GV, "Usage: sar Num");
    }

    return res;
}
