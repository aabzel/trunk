#include "hash_table.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(HashTable, hash_table)
COMPONENT_GET_CONFIG(HashTable, hash_table)

static bool hash_table_init_cell(HashTableCell_t* const Cell) {
    bool res = false;
    if(Cell) {
        Cell->value = 0;
        Cell->cnt = 0;
        Cell->collision_flag = false;
        res = false;
    }
    return res;
}

/*
  01234

  0 5 -> 1
  1 5 -> 2
  2 5 -> 3
  3 5 -> 4
  3 5 -> 4
  4 5 -> 0
  5 5 -> 0
  */
static uint32_t cyclic_index_increase(const uint32_t in_index, const uint32_t size) {
    uint32_t out_index = 0;
    if(in_index < (size - 1)) {
        out_index = in_index + 1;
    } else {
        out_index = 0;
    }
    return out_index;
}
/*
  value -INT_MAX 0 INT_MAX
  size 1-N
  */
static uint32_t hash_function(const int32_t value, const uint32_t size) {
    uint32_t u_val = (uint32_t)value;
    uint32_t index = u_val % size;
    return index;
}

static bool hash_table_init_custom(void) {
    bool res = false;
    // log_level_set(HASH_TABLE, LOG_LEVEL_DEBUG);
    LOG_INFO(HASH_TABLE, "Version:%u", HASH_TABLE_VERSION);
    return res;
}

static bool hash_table_init_common(const HashTableConfig_t* const Config, HashTableHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->name = Config->name;
            Node->size = Config->size;
            Node->Memory = Config->Memory;
            res = true;
        }
    }
    return res;
}

/*ISO-26262 require verify configuration*/
bool HashTableIsValidConfig(const HashTableConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            res = false;
            LOG_ERROR(HASH_TABLE, "%u,NameErr", Config->num);
        }

        ifn(Config->Memory) {
            res = false;
            LOG_ERROR(HASH_TABLE, "%u,MemoryErr", Config->num);
        }

        ifn(Config->size) {
            res = false;
            LOG_ERROR(HASH_TABLE, "%u,SizeErr", Config->num);
        }
    }
    return res;
}

bool hash_table_push_ll(HashTableHandle_t* Node, const int32_t value) {
    bool res = false;
    LOG_DEBUG(HASH_TABLE, "AddVal:%d", value);
    uint32_t index = hash_function(value, Node->size);
    uint32_t k = 0;
    for(k = 0; k < Node->size; k++) {
        if(Node->Memory[index].cnt) {
            if(value == Node->Memory[index].value) {
                Node->Memory[index].cnt++;
                res = true;
                break;
            } else {
                if(0 == k) {
                    Node->Memory[index].collision_flag = true;
                    LOG_DEBUG(HASH_TABLE, "Collision!New:%d,Old:%d", value, Node->Memory[index].value);
                }
            }
        } else {
            Node->Memory[index].collision_flag = false;
            Node->Memory[index].cnt = 1;
            Node->Memory[index].value = value;
            res = true;
            break;
        }
        index = cyclic_index_increase(index, Node->size);
    }

    if(!res) {
        LOG_ERROR(HASH_TABLE, "AddErr:%d", value);
    }

    return res;
}

bool hash_table_peek_ll(HashTableHandle_t* Node, const int32_t value) {
    bool res = false;
    uint32_t index = hash_function(value, Node->size);
    LOG_DEBUG(HASH_TABLE, "Val:%d,Index:%u", value, index);
    uint32_t k = 0;
    for(k = 0; k < Node->size; k++) {
        LOG_DEBUG(HASH_TABLE, "k:%u,Index:%u,%s", k, index, HashTableCellToStr(&Node->Memory[index]));
        if(Node->Memory[index].cnt) {
            if(value == Node->Memory[index].value) {
                res = true;
                break;
            } else {
                if(Node->Memory[index].collision_flag) {
                    LOG_DEBUG(HASH_TABLE, "WasCollision,Index:%u", index);
                    // index = cyclic_index_increase(index, Node->size);
                    res = false;
                } else {
                    res = false;
                    // break;
                }
            }
        }
        index = cyclic_index_increase(index, Node->size);
    }
    LOG_DEBUG(HASH_TABLE, "CheckVal:%d,%u", value, res);
    return res;
}

bool hash_table_pull_ll(HashTableHandle_t* Node, const int32_t value) {
    bool res = false;
    LOG_DEBUG(HASH_TABLE, "Pull:%d", value);
    uint32_t index = hash_function(value, Node->size);
    uint32_t k = 0;
    for(k = 0; k < Node->size; k++) {
        if(Node->Memory[index].cnt) {
            if(value == Node->Memory[index].value) {
                Node->Memory[index].cnt--;
                res = true;
                break;
            } else {
                if(Node->Memory[index].collision_flag) {
                    res = false;
                } else {
                    res = false;
                    // break;
                }
            }
        } else {
            res = false;
            break;
        }
        index = cyclic_index_increase(index, Node->size);
    }
    return res;
}

#if 0
bool hash_table_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(HASH_TABLE, "Proc %u", i);
    HashTableHandle_t* Node = HashTableGetNode(i);
    if(Node) {
    }
    return res;
}
#endif

bool hash_table_push(uint8_t num, const int32_t value) {
    bool res = false;
    HashTableHandle_t* Node = HashTableGetNode(num);
    if(Node) {
        res = hash_table_push_ll(Node, value);
    }
    return res;
}

bool hash_table_pull(uint8_t num, const int32_t value) {
    bool res = false;
    HashTableHandle_t* Node = HashTableGetNode(num);
    if(Node) {
        res = hash_table_pull_ll(Node, value);
    }
    return res;
}

bool hash_table_peek(uint8_t num, const int32_t value) {
    bool res = false;
    HashTableHandle_t* Node = HashTableGetNode(num);
    if(Node) {
        res = hash_table_peek_ll(Node, value);
    }
    return res;
}

bool hash_table_init_one_ll(const HashTableConfig_t* const Config, HashTableHandle_t* const Node) {
    bool res = false;
    if(Config) {
        LOG_WARNING(HASH_TABLE, "HASH_TABLE%u", Config->num);
        res = HashTableIsValidConfig(Config);
        if(res) {
#ifdef HAS_HASH_TABLE_DIAG
            LOG_WARNING(HASH_TABLE, "%s", HashTableConfigToStr(Config));
#endif
            if(Node) {
                res = hash_table_init_common(Config, Node);
                uint32_t i = 0;
                for(i = 0; i < Node->size; i++) {
                    res = hash_table_init_cell(&Node->Memory[i]);
                }
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(HASH_TABLE, "NodeErr %u", Config->num);
            }
        } else {
            LOG_ERROR(HASH_TABLE, "ConfigErr %u", Config->num);
        }
    } else {
        LOG_PARN(HASH_TABLE, "ConfigErr %u", Config->num);
    }
    return res;
}

bool hash_table_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(HASH_TABLE, "HASH_TABLE%u", num);
    const HashTableConfig_t* Config = HashTableGetConfig(num);
    if(Config) {
        HashTableHandle_t* Node = HashTableGetNode(num);
        if(Node) {
            res = hash_table_init_one_ll(Config, Node);
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(HASH_TABLE, HASH_TABLE, hash_table)
// COMPONENT_PROC_PATTERT(HASH_TABLE, HASH_TABLE, hash_table)
