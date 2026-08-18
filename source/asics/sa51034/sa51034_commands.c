#include "sa51034_commands.h"


#include "convert.h"
#include "log.h"
#include "sa51034_drv.h"

bool sa51034_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    char key_word[20] = "";
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        strcpy(key_word, argv[0]);
        res = true;
    }

    if(res) {
        LOG_INFO(SA51034, "LowLevelDiag KeyWord [%s]", key_word);
        res = sa51034_diag_low_level(1,key_word);
        if(res) {
            LOG_INFO(SA51034, "LowLevelDiagOk");
        } else {
            LOG_ERROR(SA51034, "LowLevelDiagOk");
        }
    }
    return res;
}

bool sa51034_diag_hl_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = sa51034_diag_high_level(1);
    return res;
}

bool sa51034_reg_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t addr = 0;
    uint8_t byte = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &addr);
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &byte);
    }

    if(res) {
        res = sa51034_reg_write(1,addr, byte);
        if(res) {
            LOG_INFO(SA51034, "Addr:0x%02x,Val:0x%02x", byte, byte);
        }
    }
    return res;
}

bool sa51034_reg_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint8_t addr = 0;

    if(1 == argc) {
        res = try_str2uint8(argv[0], &addr);
    }

    if(res) {
        uint8_t byte = 0;
        res = sa51034_reg_read(num, addr, &byte);
        if(res) {
            LOG_INFO(SA51034, "Addr:0x%02x,Val:0x%02x", addr, byte);
        }
    } else {
        LOG_INFO(SA51034, "Usage: maar RegAddr");
    }

    return res;
}

bool sa51034_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = sa51034_init_one(1);
    return res;
}


bool sa51034_reg_hazy_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = sa51034_reg_hazy(1);
        res = sa51034_reg_map_hidden_diag(1);
    }else{
        LOG_ERROR(SA51034, "Usage: nrh");
    }
    return res;
}


bool sa51034_reg_map_command(int32_t argc, char* argv[]) {
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
        LOG_ERROR(SA51034, "Usage: maxregs keyWord keyWord");
    }
    if(res) {
        res = sa51034_reg_map_diag(1,keyWord1, keyWord2);
    }
    return res;
}

bool sa51034_reg_map_hidden_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = sa51034_reg_map_hidden_diag(1);
    }
    return res;
}



bool sa51034_i2c_ping_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = sa51034_is_connected(1);
    if(res) {
        LOG_INFO(SA51034, "Connected!");
    } else {
        LOG_ERROR(SA51034, "Disconnected!");
    }
    return res;
}

bool sa51034_gain_command(int32_t argc, char* argv[]){
    bool res = false;

    uint8_t num = 1;
    Gain_t gain_db = 20;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &gain_db);
    }

    if(res) {
        switch(argc){
        case 1: {
        	res = sa51034_gain_get(num,&gain_db);
        	if(res) {
                LOG_INFO(SA51034, "Get,Num:%u,Gain:%d dB",num,gain_db);
        	}
        } break;
        case 2:{
            LOG_INFO(SA51034, "Set,Num:%u,Gain:%d dB",num,gain_db);
            res = sa51034_gain_set(num,gain_db);
        } break;
        }
    }else {
        LOG_ERROR(SA51034, "Usage: sf Num FreqHz");
    }
    return res;
}

bool sa51034_frequency_command(int32_t argc, char* argv[]){
    bool res = false;

    uint8_t num = 1;
    uint32_t frequency_hz = 400000;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &frequency_hz);
    }

    if(res) {
        switch(argc){
        case 1:{
        	res = sa51034_frequency_get(num,&frequency_hz);
        	if(res){
        		LOG_INFO(SA51034, "Get,Num:%u,Freq %uHz",num,frequency_hz);
        	}
        } break;
        case 2:{
            LOG_INFO(SA51034, "Set,Num:%u,Freq %uHz",num,frequency_hz);
            res = sa51034_frequency_set(num,frequency_hz);
        } break;
        }


    }else {
        LOG_ERROR(SA51034, "Usage: sf Num FreqHz");
    }

    return res;
}


bool sa51034_power_limit_command(int32_t argc, char* argv[]){
    bool res = false;

    uint8_t num = 1;
    double power_limit = 99;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &power_limit);
    }

    if(res) {
        switch(argc) {
        case 1: {
        	res = sa51034_power_limit_get(num,&power_limit);
        	if(res){
        		LOG_INFO(SA51034, "Get,Num:%u,PowerLimit:%f V",num,power_limit);
        	}
        } break;
        case 2: {
        	LOG_INFO(SA51034, "Set,Num:%u,PowerLimit:%f V",num,power_limit);
            res = sa51034_power_limit_set(num,power_limit);
        } break;
        }
    }else {
        LOG_ERROR(SA51034, "Usage: spl Num PowerLimitVol");
    }

    return res;
}
// sar
bool sa51034_reset_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        	res = sa51034_reset(num);
        	if(res){
        		LOG_INFO(SA51034, "ResetOk,Num:%u",num);
        	}else{
        		LOG_ERROR(SA51034, "ResetErr,Num:%u",num);
        	}
    }else {
        LOG_ERROR(SA51034, "Usage: sar Num");
    }

    return res;
}
