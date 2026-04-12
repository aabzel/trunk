#include "median_filter_fast.h"

#include <stdlib.h>

#include "circular_buffer_dword.h"
#include "code_generator.h"
#include "float_utils.h"
#include "hash_table_s8.h"
#include "log.h"
#include "max_heap.h"
#include "min_heap.h"
#include "utils_math.h"

COMPONENT_GET_NODE(MedianFilterFast, median_filter_fast)
COMPONENT_GET_CONFIG(MedianFilterFast, median_filter_fast)

static bool median_filter_fast_init_custom(void) {
    bool res = true;
    LOG_INFO(MEDIAN_FILTER_FAST, "CustomInit");
    // set_log_level(MEDIAN_FILTER_FAST,LOG_LEVEL_DEBUG);
    return res;
}

static bool median_filter_form_min_heap_config(const MedianFilterFastConfig_t* const Config,
                                               BinHeapConfig_t* const ConfigMin) {
    bool res = false;
    if(ConfigMin) {
        if(Config) {
            ConfigMin->array = Config->tempLarge;
            ConfigMin->capacity = Config->bin_heap_size;
            ConfigMin->name = "MinHeapSmall";
            ConfigMin->num = 10;
            ConfigMin->valid = true;
            res = true;
        }
    }
    return res;
}

#ifdef HAS_MEDIAN_FILTER_FAST_HASH_TABLE
static bool median_filter_form_hash_table_s8_config(const MedianFilterFastConfig_t* const Config,
                                                    HashTableS8Config_t* const ConfigHash) {
    bool res = false;
    if(ConfigHash) {
        if(Config) {
            //  ConfigHash->size = Config->hash_table_s8_size;
            //   ConfigHash->Memory = Config->HashTableS8Memory;
            ConfigHash->name = "HashTableS8";
            ConfigHash->num = 12;
            ConfigHash->valid = true;
            res = true;
        }
    }
    return res;
}
#endif

static bool median_filter_form_max_heap_config(const MedianFilterFastConfig_t* const Config,
                                               BinHeapConfig_t* const ConfigMax) {
    bool res = false;
    if(ConfigMax) {
        if(Config) {
            ConfigMax->array = Config->tempSmall;
            ConfigMax->capacity = Config->bin_heap_size;
            ConfigMax->name = "MaxHeapSmall";
            ConfigMax->num = 11;
            ConfigMax->valid = true;
            res = true;
        }
    }

    return res;
}

#ifdef HAS_MEDIAN_FILTER_FAST_HASH_TABLE
static bool prune_large(MedianFilterFastHandle_t* const Node) {
    bool res;
    bool loop = true;
    bool ok = false;
    while(loop) {
#ifdef HAS_MED_FILT_DEBUG
        LOG_DEBUG(MEDIAN_FILTER_FAST, "prune_large");
#endif
        uint32_t cnt = min_heap_size(&Node->Large);
        if(cnt) {
            int32_t root_large = 0;
            res = min_heap_peek(&Node->Large, &root_large);
            if(res) {
#ifdef HAS_MED_FILT_DEBUG
                LOG_DEBUG(MEDIAN_FILTER_FAST, "root_large:%d", root_large);
#endif
                loop = hash_table_s8_check_ll(&Node->ToDelete, (int8_t)root_large);
                if(loop) {
#ifdef HAS_MED_FILT_DEBUG
                    LOG_DEBUG(MEDIAN_FILTER_FAST, "Del,root_large:%d", root_large);
#endif
                    res = min_heap_delete_root(&Node->Large);
                    res = hash_table_s8_pull_ll(&Node->ToDelete, (int8_t)root_large);
                    ok = true;
                }
            }
        } else {
            loop = false;
        }
    }
    return ok;
}
#endif

static bool median_filter_fast_init_common(const MedianFilterFastConfig_t* Config, MedianFilterFastHandle_t* Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->sample_rate_hz = Config->sample_rate_hz;
            Node->num = Config->num;
            Node->size = Config->size;
            Node->tempLarge = Config->tempLarge;
            Node->tempSmall = Config->tempSmall;
            Node->max_size = Config->max_size;
            //     Node->hash_table_s8_size = Config->hash_table_s8_size;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}


#ifdef HAS_MEDIAN_FILTER_FAST_HASH_TABLE
static bool prune_small(MedianFilterFastHandle_t* const Node) {
    bool res;
    bool ok = false;
    bool loop = true;
    while(loop) {
#ifdef HAS_MED_FILT_DEBUG
        LOG_DEBUG(MEDIAN_FILTER_FAST, "prune_small");
#endif
        uint32_t cnt = max_heap_size(&Node->Small);
        if(cnt) {
            int32_t root_small = 0;
            res = max_heap_peek(&Node->Small, &root_small);
            if(res) {
#ifdef HAS_MED_FILT_DEBUG
                LOG_DEBUG(MEDIAN_FILTER_FAST, "root_small:%d", root_small);
#endif
                loop = hash_table_s8_check_ll(&Node->ToDelete, (int8_t)root_small);
                if(loop) {
#ifdef HAS_MED_FILT_DEBUG
                    LOG_DEBUG(MEDIAN_FILTER_FAST, "Del,root_small:%d", root_small);
#endif
                    res = max_heap_delete_root(&Node->Small);
                    res = hash_table_s8_pull_ll(&Node->ToDelete, (int8_t)root_small);
                    ok = true;
                }
            }
        } else {
            loop = false;
        }
    }
    return ok;
}
#endif

#ifdef HAS_MEDIAN_FILTER_FAST_HASH_TABLE
bool prune_both(MedianFilterFastHandle_t* const Node) {
    bool res = false;
#ifdef HAS_MED_FILT_DEBUG
    LOG_DEBUG(MEDIAN_FILTER_FAST, "PruneBoth");
#endif
    bool res1 = prune_small(Node);
    bool res2 = prune_large(Node);
    res = res1 || res2;
    LOG_NOTICE(MEDIAN_FILTER_FAST, "%s", MedianFilterFastNodeToStr(Node));
    return res;
}
#endif

static bool MedianFilterFastIsValidConfig(const MedianFilterFastConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(1 <= Config->size) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER_FAST, "Order,Err,Size:%u", Config->size);
        }

        ifn(1 <= Config->max_size) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER_FAST, "MaxSizeErr,Size:%u", Config->max_size);
        }

        ifn(1 <= Config->bin_heap_size) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER_FAST, "BinHeapSizeErr,Size:%u", Config->bin_heap_size);
        }

        ifn(Config->size <= Config->bin_heap_size) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER_FAST, "BinHeapSizeSmallErr,Order:%u,BinHeap:%u", Config->size,
                      Config->bin_heap_size);
        }

        ifn(Config->size <= Config->max_size) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER_FAST, "OrderErr,Order:%u,Max:%u", Config->size, Config->max_size);
        }

        ifn(0 < Config->sample_rate_hz) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER_FAST, "SampleRateErr");
        }

        ifn(Config->tempSmall) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER_FAST, "TempSmall,Err");
        }

        ifn(Config->tempLarge) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER_FAST, "tempLarge,Err");
        }
#if 0
        ifn(Config->HashTableS8Memory) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER_FAST, "HashTableS8Memory,Err");
        }
#endif

        ifn(Config->x) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER_FAST, "xErr");
        }

        ifn(Config->valid) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER_FAST, "ValidErr");
        }

        ifn(Config->name) {
            res = false;
            LOG_ERROR(MEDIAN_FILTER_FAST, "NameErr");
        }
    }

    return res;
}

static MedianFilterBalanceDir_t median_filter_fast_get_balance_dir_even(MedianFilterFastHandle_t* const Node) {
    MedianFilterBalanceDir_t balance_dir = MED_FILT_BALANCE_DIR_UNDEF;
    /* k is even  devided by 2  (4 6 8)*/
    if(Node->small_size < Node->large_size) {
        balance_dir = MED_FILT_BALANCE_DIR_DOWN;
    } else {
        if(Node->large_size < Node->small_size) {
            balance_dir = MED_FILT_BALANCE_DIR_UP;
        } else {
            // large_size == small_size
            balance_dir = MED_FILT_BALANCE_DIR_NONE;
        }
    }
    return balance_dir;
}

static MedianFilterBalanceDir_t median_filter_fast_get_balance_dir_odd(MedianFilterFastHandle_t* const Node) {
    MedianFilterBalanceDir_t balance_dir = MED_FILT_BALANCE_DIR_UNDEF;
    /*   k is odd (1; 3; 5; 7; 9)  */
    if(Node->small_size == (Node->large_size + 1)) {
        balance_dir = MED_FILT_BALANCE_DIR_NONE;
    } else {
        if(Node->small_size < Node->large_size) {
            balance_dir = MED_FILT_BALANCE_DIR_DOWN;
        } else {
            // large_size<(small_size+2)
            balance_dir = MED_FILT_BALANCE_DIR_UP;
        }
    }
    return balance_dir;
}

static MedianFilterBalanceDir_t median_filter_fast_get_balance_dir(MedianFilterFastHandle_t* const Node) {
    MedianFilterBalanceDir_t balance_dir = MED_FILT_BALANCE_DIR_UNDEF;
    LOG_DEBUG(MEDIAN_FILTER_FAST, "VirtSize:%s", MedianFilterVirtSizeToStr(Node));
    switch(Node->k_parity) {
    case MATH_PARITY_EVEN: {
        balance_dir = median_filter_fast_get_balance_dir_even(Node);
    } break;
    case MATH_PARITY_ODD: {
        balance_dir = median_filter_fast_get_balance_dir_odd(Node);
    } break;
    default: {
        balance_dir = MED_FILT_BALANCE_DIR_UNDEF;
    } break;
    }

    return balance_dir;
}

static bool median_filter_fast_shift_down(MedianFilterFastHandle_t* const Node) {
    bool res = false;
    int32_t top_val = 0;
    res = min_heap_pull(&Node->Large, &top_val);
    if(res) {
#ifdef HAS_MED_FILT_DEBUG
        LOG_DEBUG(MEDIAN_FILTER_FAST, "MoveDown:%d", top_val);
#endif
        Node->large_size--;
        res = max_heap_push(&Node->Small, top_val);
#ifdef HAS_MED_FILT_DEBUG
        log_res(MEDIAN_FILTER_FAST, res, "max_heap_push");
#endif

        Node->small_size++;
#ifdef HAS_MED_FILT_DEBUG
        LOG_DEBUG(MEDIAN_FILTER_FAST, "PushSmall:%d Ok", top_val);
#endif

#ifdef HAS_MEDIAN_FILTER_FAST_HASH_TABLE
        prune_large(Node);
#endif
    }

    return res;
}

static bool median_filter_fast_shift_up(MedianFilterFastHandle_t* const Node) {
    bool res = false;
    int32_t top_val = 0;
    res = max_heap_pull(&Node->Small, &top_val);
#ifdef HAS_MED_FILT_DEBUG
    LOG_DEBUG(MEDIAN_FILTER_FAST, "MoveUp:%d", top_val);
#endif
    if(res) {
        res = min_heap_push(&Node->Large, top_val);
        Node->small_size--;
        Node->large_size++;
#ifdef HAS_MEDIAN_FILTER_FAST_HASH_TABLE
        prune_small(Node);
#endif
    }
    return res;
}

#if 0
static bool median_filter_fast_force_delete(MedianFilterFastHandle_t* Node, int32_t x) {
    bool res = false;
    bool loop = true;
    while (loop) {
        int32_t large_root = 0;
        /*What's in the min heap root now?*/
        res = min_heap_peek(&Node->Large, &large_root);
        if (large_root == x) {
            res = min_heap_delete_root(&Node->Large);
            loop = false ;
        } else if (large_root < x) {
             loop = median_filter_fast_shift_down(Node);
        }
    }

    //int32_t small_root=0;
    //res = max_heap_peek(&Node->Small, &small_root);

    return res;
}
#endif

#if 0
static bool median_filter_fast_prune(MedianFilterFastHandle_t* const Node) {
    bool res = false;
    bool delete_done = false;
    LOG_DEBUG(MEDIAN_FILTER_FAST,"Prune");
    int32_t large_root = 0;
    /*What's in the min heap root now?*/
    res = min_heap_peek(&Node->Large, &large_root);
    if(res) {
        LOG_DEBUG(MEDIAN_FILTER_FAST,"large_root:%d",large_root);
        /*Should such an element be removed?*/
        res = hash_table_s8_pull_ll(&Node->ToDelete,(int8_t)large_root);
        if(res) {
            /*delete top element*/
            LOG_DEBUG(MEDIAN_FILTER_FAST,"DeletTopLarge");
            delete_done = min_heap_delete_root(&Node->Large);
        }
    }

    /*What's in the max heap root now?*/
    int32_t small_root=0;
    res = max_heap_peek(&Node->Small, &small_root);
    if(res) {
        LOG_DEBUG(MEDIAN_FILTER_FAST,"small_root:%d",small_root);
        /*Should such an element be removed?*/
        res = hash_table_s8_pull_ll(&Node->ToDelete,(int8_t)small_root);
        if(res) {
            LOG_DEBUG(MEDIAN_FILTER_FAST,"DeletTopSmall");
            delete_done = max_heap_delete_root(&Node->Small);
        }
    }

    return delete_done;
}
#endif

uint32_t median_filter_fast_get_tolal_size(const MedianFilterFastHandle_t* const Node) {
    uint32_t total_size = 0;
    uint32_t large_size = min_heap_size(&Node->Large);
    uint32_t small_size = max_heap_size(&Node->Small);
    total_size = small_size + large_size;
#ifdef HAS_MED_FILT_DEBUG
    LOG_DEBUG(MEDIAN_FILTER_FAST, "S:%d+L:%d=T:%d", small_size, large_size, total_size);
#endif
    return total_size;
}

static bool median_filter_fast_try_delete_old_top(MedianFilterFastHandle_t* const Node,
                                                  const int32_t sample_to_delete,
                                                  MedianFilterBalanceDir_t* dir) {
    bool res = false;
    bool delete_done = false;
    MedianFilterBalanceDir_t balance_dir = MED_FILT_BALANCE_DIR_UNDEF;

    int32_t large_root = 0;
    res = min_heap_peek(&Node->Large, &large_root);
    if(res) {
#ifdef HAS_MED_FILT_DEBUG
        LOG_DEBUG(MEDIAN_FILTER_FAST, "large_root:%d", large_root);
#endif
        if(large_root == sample_to_delete) {
#ifdef HAS_MED_FILT_DEBUG
            LOG_DEBUG(MEDIAN_FILTER_FAST, "DeletTopLarge:%d", sample_to_delete);
#endif
            delete_done = min_heap_delete_root(&Node->Large);
            Node->large_size--;
        } else {
            if(large_root < sample_to_delete) {
                balance_dir = MED_FILT_BALANCE_DIR_DOWN;
            }
        }
    }

    if(!delete_done) {
        int32_t small_root = 0;
        res = max_heap_peek(&Node->Small, &small_root);
        if(res) {
#ifdef HAS_MED_FILT_DEBUG
            LOG_DEBUG(MEDIAN_FILTER_FAST, "small_root:%d", small_root);
#endif
            if(sample_to_delete == small_root) {
#ifdef HAS_MED_FILT_DEBUG
                LOG_DEBUG(MEDIAN_FILTER_FAST, "DeletTopSmall:%d", sample_to_delete);
#endif
                delete_done = max_heap_delete_root(&Node->Small);
                Node->small_size--;
            } else {
                if(sample_to_delete < small_root) {
                    balance_dir = MED_FILT_BALANCE_DIR_UP;
                }
            }
        }
    }

    *dir = balance_dir;

    return delete_done;
}

/*
  if loop is true - BALANCE done
  */
static bool median_filter_fast_shift(MedianFilterFastHandle_t* const Node, const MedianFilterBalanceDir_t balance_dir) {
    bool loop = false;
    switch(balance_dir) {
    case MED_FILT_BALANCE_DIR_DOWN: {
        loop = median_filter_fast_shift_down(Node);
    } break;

    case MED_FILT_BALANCE_DIR_UP: {
        loop = median_filter_fast_shift_up(Node);
    } break;

    case MED_FILT_BALANCE_DIR_NONE: {
        loop = false;
    } break;

    default:
        loop = false;
        break;
    }
    return loop;
}

/*Delete del_value from on of heap*/
bool median_filter_fast_delete_old_force_dig_out_ll(MedianFilterFastHandle_t* const Node,
                                                    const int32_t del_value) {
    bool res = false;
    bool loop = true;
    while(loop) {
        MedianFilterBalanceDir_t seek_dir = MED_FILT_BALANCE_DIR_UNDEF;
        res = median_filter_fast_try_delete_old_top(Node, del_value, &seek_dir);
        if(res) {
            loop = false;
        } else {
            res = median_filter_fast_shift(Node, seek_dir);
        }
    }
    return res;
}

static bool median_filter_fast_spot_heap(MedianFilterFastHandle_t* const Node,
                                                  const int32_t sample_to_delete,
                                                  MedianFilterBalanceDir_t* dir) {
    bool res = false;
    bool spot_dir = false;
    MedianFilterBalanceDir_t balance_dir = MED_FILT_BALANCE_DIR_UNDEF;

    int32_t large_root = 0;
    res = min_heap_peek(&Node->Large, &large_root);
    if(res) {
#ifdef HAS_MED_FILT_DEBUG
        LOG_DEBUG(MEDIAN_FILTER_FAST, "large_root:%d", large_root);
#endif
        if(large_root <= sample_to_delete) {
#ifdef HAS_MED_FILT_DEBUG
            LOG_DEBUG(MEDIAN_FILTER_FAST, "DeletFromLarge:%d", sample_to_delete);
#endif
            balance_dir = MED_FILT_BALANCE_DIR_UP;
            spot_dir = true;
        }
    }


        int32_t small_root = 0;
        res = max_heap_peek(&Node->Small, &small_root);
        if(res) {
#ifdef HAS_MED_FILT_DEBUG
            LOG_DEBUG(MEDIAN_FILTER_FAST, "small_root:%d", small_root);
#endif
            if(sample_to_delete <= small_root) {
#ifdef HAS_MED_FILT_DEBUG
                LOG_DEBUG(MEDIAN_FILTER_FAST, "DeletFromSmall:%d", sample_to_delete);
#endif
                balance_dir = MED_FILT_BALANCE_DIR_DOWN;
                spot_dir = true;
            }
        }


    *dir = balance_dir;

    return spot_dir;
}

bool median_filter_fast_delete_old_force_ll(MedianFilterFastHandle_t* const Node,
                                            const int32_t del_value) {
    bool res = false;
    LOG_DEBUG(MEDIAN_FILTER_FAST, "DeleteForce:%d", del_value);
    MedianFilterBalanceDir_t location_dir = MED_FILT_BALANCE_DIR_UNDEF;
    res = median_filter_fast_spot_heap(Node, del_value, &location_dir);
    switch (location_dir) {
        case MED_FILT_BALANCE_DIR_UP: {
            res = min_heap_delete(&Node->Large, del_value);
            Node->large_size--;
        } break;
        case MED_FILT_BALANCE_DIR_DOWN: {
            res = max_heap_delete(&Node->Small, del_value);
            Node->small_size--;
        } break;
        default: break;
    }

    return res;
}


#ifdef HAS_MEDIAN_FILTER_FAST_HASH_TABLE
static bool median_filter_fast_remove_num_ll(MedianFilterFastHandle_t* const Node, const int32_t del_value) {
    bool res = false;
    bool delete_done = false;
#ifdef HAS_MED_FILT_DEBUG
    LOG_DEBUG(MEDIAN_FILTER_FAST, "ElementToDel:%d", del_value);
#endif
    res = hash_table_s8_push_ll(&Node->ToDelete, (int8_t)del_value);
#ifdef HAS_MED_FILT_DEBUG
    log_res(MEDIAN_FILTER_FAST, res, "pushToDel");
#endif

    int32_t small_root = 0;
    res = max_heap_peek(&Node->Small, &small_root);
    if(res) {
#ifdef HAS_MED_FILT_DEBUG
        LOG_DEBUG(MEDIAN_FILTER_FAST, "small_root:%d", small_root);
#endif
        if(del_value <= small_root) {
            Node->small_size--;
            delete_done = true;
            if(del_value == small_root) {
                prune_small(Node);
            }
        }
    }

    if(false == delete_done) {
        int32_t large_root = 0;
        res = min_heap_peek(&Node->Large, &large_root);
        if(res) {
#ifdef HAS_MED_FILT_DEBUG
            LOG_DEBUG(MEDIAN_FILTER_FAST, "large_root:%d", large_root);
#endif
            if(large_root <= del_value) {
                Node->large_size--;
                delete_done = true;
                if(del_value == large_root) {
                    prune_large(Node);
                }
            }
        }
    }
    return delete_done;
}
#endif

static bool median_filter_fast_rebalance_ll(MedianFilterFastHandle_t* const Node) {
    bool res = false;
    bool loop = true;
#ifdef HAS_MED_FILT_DEBUG
    LOG_DEBUG(MEDIAN_FILTER_FAST, "Rebalane,%s", MedianFilterFastNodeToStr(Node));
#endif
    while(loop) {
        MedianFilterBalanceDir_t balance_dir = MED_FILT_BALANCE_DIR_UNDEF;
        balance_dir = median_filter_fast_get_balance_dir(Node);
#ifdef HAS_MED_FILT_DEBUG
        LOG_DEBUG(MEDIAN_FILTER_FAST, "BalanceDir:%s", DirToStr(balance_dir));
#endif
        loop = median_filter_fast_shift(Node, balance_dir);
#ifdef HAS_MED_FILT_DEBUG
        LOG_NOTICE(MEDIAN_FILTER_FAST, "RebalaneDone,%s", MedianFilterFastNodeToStr(Node));
#endif
        // bool loop1 = median_filter_fast_shift(Node, balance_dir);
        // bool loop2 = prune_both(Node);
        // loop = loop1 || loop2;
    }
    res = true;

    return res;
}

static float median_filter_fast_calc_median(const MedianFilterFastHandle_t* const Node) {
    float median = 0.0;
#ifdef HAS_MED_FILT_DEBUG
    LOG_NOTICE(MEDIAN_FILTER_FAST, "%s", MedianFilterFastNodeToStr(Node));
#endif
    bool res = false;
    int32_t small_top = 0;
    int32_t large_top = 0;
    switch(Node->k_parity) {
    case MATH_PARITY_ODD: {
#ifdef HAS_MED_FILT_DEBUG
        LOG_DEBUG(MEDIAN_FILTER_FAST, "odd");
#endif
        /* not devided by 2*/
        res = max_heap_peek(&Node->Small, &small_top);
#ifdef HAS_MED_FILT_DEBUG
        log_res(MEDIAN_FILTER_FAST, res, "PeakMin");
#endif
        if(res) {
#ifdef HAS_MED_FILT_DEBUG
            LOG_DEBUG(MEDIAN_FILTER_FAST, "small_top:%d", small_top);
#endif
            median = (float)small_top;
        }
    } break;
    case MATH_PARITY_EVEN: {
#ifdef HAS_MED_FILT_DEBUG
        LOG_DEBUG(MEDIAN_FILTER_FAST, "Even");
#endif
        /*devided by 2*/
        res = min_heap_peek(&Node->Large, &large_top);
#ifdef HAS_MED_FILT_DEBUG
        log_res(MEDIAN_FILTER_FAST, res, "PeakMin");
#endif
        if(res) {
            res = max_heap_peek(&Node->Small, &small_top);
#ifdef HAS_MED_FILT_DEBUG
            log_res(MEDIAN_FILTER_FAST, res, "PeakMax");
#endif
            if(res) {
                median = ((float)(small_top + large_top)) / 2.0;
            }
        }
    } break;
    default:
        break;
    }
#ifdef HAS_MED_FILT_DEBUG
    LOG_DEBUG(MEDIAN_FILTER_FAST, "SmallRoot:%d,LargeRoot:%d,median:%f", small_top, large_top, median);
#endif
    return median;
}

static bool median_filter_fast_detete_num_ll(MedianFilterFastHandle_t* Node , int32_t del){
    bool res=false;
    LOG_DEBUG(MEDIAN_FILTER_FAST, "Delete:%d", del);
#ifdef HAS_MEDIAN_FILTER_FAST_HASH_TABLE
    res = median_filter_fast_remove_num_ll(Node, del);
#else
    res = median_filter_fast_delete_old_force_ll(Node, del);
#endif
    return res;
}

#ifdef HAS_MEDIAN_FILTER_FAST_FLUSH
static bool median_filter_flush_dir(MedianFilterFastHandle_t* Node, MedianFilterBalanceDir_t dir) {
    bool res = false;
    bool loop = true;
    while (loop) {
        loop = median_filter_fast_shift(Node, dir);
        if (loop) {
            res = prune_both(Node);
        }
    }
    return res;
}
#endif

#ifdef HAS_MEDIAN_FILTER_FAST_FLUSH
static bool median_filter_flush(MedianFilterFastHandle_t* Node){
    bool res = false;
    uint32_t tolal_size = median_filter_fast_get_tolal_size(Node);
    if ((Node->size*2) <= tolal_size) {
#ifdef HAS_MED_FILT_DEBUG
       LOG_DEBUG(MEDIAN_FILTER_FAST, "Flush,TotalSize:%u",  tolal_size);
#endif

       bool res1 = median_filter_flush_dir(Node, MED_FILT_BALANCE_DIR_DOWN);
       bool res2 = median_filter_flush_dir(Node, MED_FILT_BALANCE_DIR_UP);
       res = res1 || res2;
       Node->flush_cnt++;
    }
    return res;
}
#endif

static bool median_filter_fast_push_small(MedianFilterFastHandle_t* Node, const int32_t x) {
    bool res = false;
#ifdef HAS_MED_FILT_DEBUG
    LOG_DEBUG(MEDIAN_FILTER_FAST, "Push,Small:x:%d", x);
#endif
    res = max_heap_push(&Node->Small, x);
    Node->small_size++;
    return res;
}


static bool median_filter_fast_push_large(MedianFilterFastHandle_t* Node, const int32_t x) {
    bool res = false;

#ifdef HAS_MED_FILT_DEBUG
    LOG_DEBUG(MEDIAN_FILTER_FAST, "Push,Large:x:%d", x);
#endif
    res = min_heap_push(&Node->Large, x);
    Node->large_size++;

    return res;
}



static bool median_filter_fast_insert_saple(MedianFilterFastHandle_t* Node, const int32_t x) {
    bool res = false;
    bool is_insert = false;
    int32_t small_root = 0;
    res = max_heap_peek(&Node->Small, &small_root);
    if (res) {
#ifdef HAS_MED_FILT_DEBUG
        LOG_DEBUG(MEDIAN_FILTER_FAST, "x:%d,small.root:%d", x, small_root);
#endif
        if (x<=small_root ) {
            is_insert = median_filter_fast_push_small(Node, x);
        }
    }

    if (!is_insert) {
        int32_t large_root = 0;
        res = min_heap_peek(&Node->Large, &large_root);
        if (res) {
            if (large_root <= x) {
                is_insert = median_filter_fast_push_large(Node, x);
            }
        }
    }

    if (!is_insert) {
        is_insert = median_filter_fast_push_small(Node, x);
    }

    return res;
}

bool median_filter_fast_proc_in_out(uint8_t num, const int32_t x, float* const out_val) {
    bool res = false;
    MedianFilterFastHandle_t* Node = MedianFilterFastGetNode(num);
    if(Node) {
#ifdef HAS_MED_FILT_DEBUG
        LOG_NOTICE(MEDIAN_FILTER_FAST, CRLF CRLF "Proc,in:%d,%s", x, MedianFilterFastNodeToStr(Node));
#endif
        /*explore middle element */

        res=median_filter_fast_insert_saple(Node,x);

#ifdef HAS_MED_FILT_DEBUG
        LOG_NOTICE(MEDIAN_FILTER_FAST, "AfterPush,%s", MedianFilterFastNodeToStr(Node));
#endif

        int32_t del_value = 0;
        bool pull_res = circular_buffer_push_pull(&Node->SlidingWindow, x, &del_value);
        if(pull_res) {
            res = median_filter_fast_detete_num_ll(Node, del_value);
            median_filter_fast_rebalance_ll(Node);
#ifdef HAS_MED_FILT_DEBUG
            log_res(MEDIAN_FILTER_FAST, res, "ReBalance");
#endif
        }

        Node->proc_cnt++;

        *out_val = median_filter_fast_calc_median(Node);
#ifdef HAS_MED_FILT_DEBUG
        LOG_DEBUG(MEDIAN_FILTER_FAST, "Proc,in:%d->out:%f", x, *out_val);
#endif

#ifdef HAS_MEDIAN_FILTER_FAST_FLUSH
        median_filter_flush(Node);
#endif
    }
    return res;
}

static bool median_filter_fast_init_window(MedianFilterFastHandle_t* const Node) {
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < Node->size; i++) {
        float out_val = 0.0;
        res = median_filter_fast_proc_in_out(Node->num, 0, &out_val);
    }
    return res;
}

static bool median_filter_fast_depensencies(const MedianFilterFastConfig_t* const Config,
                                            MedianFilterFastHandle_t* const Node) {
    bool res = false;

    BinHeapConfig_t ConfigLarge = {0};
    res = median_filter_form_min_heap_config(Config, &ConfigLarge);
    res = min_heap_init_one_ll(&ConfigLarge, &Node->Large) && res;

    BinHeapConfig_t ConfigSmall = {0};
    res = median_filter_form_max_heap_config(Config, &ConfigSmall);
    res = max_heap_init_one_ll(&ConfigSmall, &Node->Small) && res;

#ifdef HAS_MEDIAN_FILTER_FAST_HASH_TABLE
    HashTableS8Config_t ConfigToDel = {0};
    res = median_filter_form_hash_table_s8_config(Config, &ConfigToDel);
    res = hash_table_s8_init_one_ll(&ConfigToDel, &Node->ToDelete) && res;
#endif

    res = circular_buffer_dword_init(&Node->SlidingWindow, Config->x, Config->size + 1) && res;
    if(res) {
        Node->init = true;
        LOG_INFO(MEDIAN_FILTER_FAST, "InitOk:%u", Config->num);
    }

    return res;
}

bool median_filter_fast_init_one(uint8_t num) {
    bool res = false;
    const MedianFilterFastConfig_t* Config = MedianFilterFastGetConfig(num);
    if(Config) {
        LOG_WARNING(MEDIAN_FILTER_FAST, "%s", MedianFilterFastConfigToStr(Config));
        res = MedianFilterFastIsValidConfig(Config);
        if(res) {
            MedianFilterFastHandle_t* Node = MedianFilterFastGetNode(num);
            if(Node) {
                res = median_filter_fast_init_common(Config, Node);
                Node->small_size = 0;
                Node->large_size = 0;
                Node->k_parity = math_calc_parity(Node->size);
                res = median_filter_fast_depensencies(Config, Node);
                res = median_filter_fast_init_window(Node);
            } else {
                LOG_ERROR(MEDIAN_FILTER_FAST, "NodeErr:%u", num);
                res = false;
            }
        } else {
            LOG_ERROR(MEDIAN_FILTER_FAST, "ConfigAbsurdErr:%u", num);
            res = false;
        }
    } else {
        LOG_ERROR(MEDIAN_FILTER_FAST, "ConfErr:%u", num);
        res = false;
    }

    return res;
}

COMPONENT_INIT_PATTERT(MEDIAN_FILTER_FAST, MEDIAN_FILTER_FAST, median_filter_fast)
