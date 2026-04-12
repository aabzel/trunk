#include "hash_table_s8.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(HashTableS8, hash_table_s8)
COMPONENT_GET_CONFIG(HashTableS8, hash_table_s8)

/*
  01234


/*
  -128 ->0
  127 - > 255
  */
static uint8_t hash_function(const int8_t value) {
    uint8_t index = (uint8_t)(value + 128);
    return index;
}

static bool hash_table_s8_init_custom(void) {
    bool res = false;
    // set_log_level(HASH_TABLE_S8, LOG_LEVEL_DEBUG);
    LOG_INFO(HASH_TABLE_S8, "Version:%u", HASH_TABLE_S8_VERSION);
    return res;
}

static bool hash_table_s8_init_common(const HashTableS8Config_t* const Config, HashTableS8Handle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

/*ISO-26262 require verify configuration*/
bool HashTableS8IsValidConfig(const HashTableS8Config_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            res = false;
            LOG_ERROR(HASH_TABLE_S8, "%u,NameErr", Config->num);
        }
    }
    return res;
}

bool hash_table_s8_push_ll(HashTableS8Handle_t* Node, const int8_t value) {
    bool res = true;
    LOG_DEBUG(HASH_TABLE_S8, "AddVal:%d", value);
    uint8_t index = hash_function(value);
    Node->HashTable[index]++;
    return res;
}

bool hash_table_s8_check_ll(HashTableS8Handle_t* Node, const int8_t value) {
    bool res = false;
    uint8_t index = hash_function(value);
    LOG_DEBUG(HASH_TABLE_S8, "Val:%d,Index:%u", value, index);
    if(Node->HashTable[index]) {
        res = true;
    }
    LOG_DEBUG(HASH_TABLE_S8, "CheckVal:%d,%u", value, res);
    return res;
}

bool hash_table_s8_pull_ll(HashTableS8Handle_t* Node, const int8_t value) {
    bool res = false;
    LOG_DEBUG(HASH_TABLE_S8, "Pull:%d", value);
    uint8_t index = hash_function(value);
    if(Node->HashTable[index]) {
        Node->HashTable[index]--;
        res = true;
    }
    return res;
}

#if 0
bool hash_table_s8_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(HASH_TABLE_S8, "Proc %u", i);
    HashTableS8Handle_t* Node = HashTableS8GetNode(i);
    if(Node) {
    }
    return res;
}
#endif

bool hash_table_s8_push(uint8_t num, const int8_t value) {
    bool res = false;
    HashTableS8Handle_t* Node = HashTableS8GetNode(num);
    if(Node) {
        res = hash_table_s8_push_ll(Node, value);
    }
    return res;
}

bool hash_table_s8_pull(uint8_t num, const int8_t value) {
    bool res = false;
    HashTableS8Handle_t* Node = HashTableS8GetNode(num);
    if(Node) {
        res = hash_table_s8_pull_ll(Node, value);
    }
    return res;
}

bool hash_table_s8_check(uint8_t num, const int8_t value) {
    bool res = false;
    HashTableS8Handle_t* Node = HashTableS8GetNode(num);
    if(Node) {
        res = hash_table_s8_check_ll(Node, value);
    }
    return res;
}

bool hash_table_s8_init_one_ll(const HashTableS8Config_t* const Config, HashTableS8Handle_t* const Node) {
    bool res = false;
    if(Config) {
        LOG_WARNING(HASH_TABLE_S8, "HASH_TABLE_S8%u", Config->num);
        res = HashTableS8IsValidConfig(Config);
        if(res) {
#ifdef HAS_HASH_TABLE_S8_DIAG
            LOG_WARNING(HASH_TABLE_S8, "%s", HashTableS8ConfigToStr(Config));
#endif
            if(Node) {
                res = hash_table_s8_init_common(Config, Node);
                uint32_t i = 0;
                for(i = 0; i < 256; i++) {
                    Node->HashTable[i] = 0;
                }
                Node->valid = true;
                Node->init = true;
                LOG_INFO(HASH_TABLE_S8, "InitOk:%u", Config->num);
                res = true;
            } else {
                LOG_ERROR(HASH_TABLE_S8, "NodeErr %u", Config->num);
            }
        } else {
            LOG_ERROR(HASH_TABLE_S8, "ConfigErr %u", Config->num);
        }
    } else {
        LOG_PARN(HASH_TABLE_S8, "ConfigErr %u", Config->num);
    }
    return res;
}

bool hash_table_s8_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(HASH_TABLE_S8, "N:%u", num);
    const HashTableS8Config_t* Config = HashTableS8GetConfig(num);
    if(Config) {
        HashTableS8Handle_t* Node = HashTableS8GetNode(num);
        if(Node) {
            res = hash_table_s8_init_one_ll(Config, Node);
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(HASH_TABLE_S8, HASH_TABLE_S8, hash_table_s8)
// COMPONENT_PROC_PATTERT(HASH_TABLE_S8, HASH_TABLE_S8, hash_table_s8)
