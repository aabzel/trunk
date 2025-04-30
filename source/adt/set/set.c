#include "set.h"

#include <stdbool.h>

#include "crc32.h"
#include "log.h"
#include "set_types.h"
#include "sw_nvram.h"

SetItem_t* SetGetNode(uint8_t num) {
    SetItem_t* Node = NULL;
    /*TODO find with bin search*/
    uint32_t i = 0;
    for(i = 0; i < set_get_instance_cnt(); i++) {
        if(num == SetItem[i].num) {
            Node = &SetItem[i];
            break;
        }
    }
    return Node;
}

const SetConfig_t* SetGetConfig(uint8_t num) {
    const SetConfig_t* ConfNode = 0;
    uint32_t i = 0;
    /*TODO find with bin search*/
    for(i = 0; i < set_get_instance_cnt(); i++) {
        if(num == SetConfig[i].num) {
            ConfNode = &SetConfig[i];
            break;
        }
    }
    return ConfNode;
}

bool set_push_ll(SetItem_t* const Node, const void* const data, size_t size) {
    bool res = false;
    uint32_t address = crc32_calc(data, size);
    LOG_DEBUG(SET, "Push CRC32 0x%x, Size %u byte", address, size);
    res = sw_nvram_write(Node->nvram_num, address, data, size);
    if(res) {
        LOG_DEBUG(SET, "pushOk 0x%08x, %u byte", address, size);
    } else {
        LOG_ERROR(SET, "pushErr 0x%08x, %u byte", address, size);
    }
    return res;
}

bool set_push(uint8_t num, const void* const data, size_t size) {
    bool res = false;
    SetItem_t* Node = SetGetNode(num);
    if(Node) {
        res = set_push_ll(Node, data, size);
    } else {
        LOG_ERROR(SET, "NodeErr %u", num);
    }
    return res;
}

bool set_delete(SetItem_t* const Node, const void* const data, size_t size) {
    bool res = false;
    uint32_t address = crc32_calc(data, size);
    LOG_DEBUG(SET, "Delete CRC32 0x%x, Size %u byte", address, size);
    res = sw_nvram_delete(Node->nvram_num, address);
    return res;
}

bool set_check_ll(SetItem_t* const Node, const void* const data, size_t size) {
    bool res = false;
    uint32_t address = crc32_calc(data, size);
    LOG_DEBUG(SET, "IsCRC32 0x%x, Size %u byte", address, size);
    res = sw_nvram_is_address_exist(Node->nvram_num, address);
    if(res) {
        LOG_DEBUG(SET, "CRC32 0x%x exist", address);
    } else {
        LOG_DEBUG(SET, "NoCRC32 0x%x", address);
    }
    return res;
}

bool set_check(uint8_t num, const void* const data, size_t size) {
    bool res = false;
    LOG_DEBUG(SET, "Check %u Size %u", num, size);
    SetItem_t* Node = SetGetNode(num);
    if(Node) {
        res = set_check_ll(Node, data, size);
    } else {
        LOG_ERROR(SET, "NodeErr %u", num);
    }
    return res;
}

bool set_get_cnt(SetItem_t* const Node, size_t* const size) {
    bool res = true;
    if(size) {
        res = true;
        uint32_t cnt = nvram_entry_cnt(Node->nvram_num);
        LOG_INFO(SET, "Cnt %u", cnt);
        *size = cnt;
    }
    return res;
}

bool set_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SET, "Init", num);
    const SetConfig_t* Config = SetGetConfig(num);
    if(Config) {
        SetItem_t* Node = SetGetNode(num);
        if(Node) {
            Node->nvram_num = Config->nvram_num;
            res = true;
            // res = sw_nvram_init_one(Node->nvram_num);
        }
    }
    return res;
}

bool set_init(void) {
    bool res = true, out_res = true;
    LOG_WARNING(NVRAM, "Init");
    uint32_t nvram_cnt = set_get_instance_cnt();
    uint8_t i = 0;
    for(i = 1; i <= nvram_cnt; i++) {
        res = set_init_one(i);
        if(false == res) {
            out_res = false;
        }
    }
    return out_res;
}
