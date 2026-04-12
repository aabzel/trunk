#include "storage.h"

#include <string.h>
#include <time.h>

#ifdef HAS_LED
#include "led_drv.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_TBFP
#include "tbfp.h"
#endif

#ifdef HAS_W25Q32JV
#include "w25q32jv_drv.h"
#endif

static const StorageIdInfo_t StorageIdInfo[] = {
    {
        .id = PAR_ID_BOOT_CNT,
        .type = TYPE_UINT8,
    },
    {
        .id = PAR_ID_REBOOT_CNT,
        .type = TYPE_UINT16,
    },
    {
        .id = PAR_ID_BOOT_CMD,
        .type = TYPE_UINT8,
    },
//  {  .id = PAR_ID_BOOTLOADER_START, .type=TYPE_UINT32_HEX,},
#ifdef HAS_BOOTLOADER
    {
        .id = PAR_ID_APP_CRC32,
        .type = TYPE_UINT32_HEX,
    },
    {
        .id = PAR_ID_APP_LEN,
        .type = TYPE_UINT32,
    },
    {
        .id = PAR_ID_APP_START,
        .type = TYPE_UINT32_HEX,
    },
    {
        .id = PAR_ID_APP_STATUS,
        .type = TYPE_UINT8,
    },
#endif
};

StorageType_t storage_get_id_type(StorageId_t id) {
    StorageType_t type = 0;
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(StorageIdInfo); i++) {
        if(id == StorageIdInfo[i].id) {
            res = true;
            type = StorageIdInfo[i].type;
            break;
        }
    }
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(STORAGE, "UndefLenForTypeID:%u=%s", type, StorageTypeToStr(type));
#endif
    }
    return type;
}

static const StorageTypeInfo_t StorageSizeInfo[] = {
    {
        .type = TYPE_TIME_DATE,
        .len = sizeof(struct tm),
    },
    {
        .type = TYPE_UINT8,
        .len = 1,
    },
    {
        .type = TYPE_BOOL,
        .len = 1,
    },
    {
        .type = TYPE_INT8,
        .len = 1,
    },
    {
        .type = TYPE_UINT16,
        .len = 2,
    },
    {
        .type = TYPE_INT16,
        .len = 2,
    },
    {
        .type = TYPE_UINT32,
        .len = 4,
    },
    {
        .type = TYPE_UINT32_HEX,
        .len = 4,
    },
    {
        .type = TYPE_INT32,
        .len = 4,
    },
    {
        .type = TYPE_UINT64,
        .len = 8,
    },
    {
        .type = TYPE_UINT64,
        .len = 8,
    },
    {
        .type = TYPE_INT64,
        .len = 8,
    },
    {
        .type = TYPE_DOUBLE,
        .len = 8,
    },
    {
        .type = TYPE_FLOAT,
        .len = 4,
    },
    {
        .type = TYPE_STRUCT,
        .len = STORAGE_TYPE_UNDEF_LEN,
    }, /*Any*/
    {
        .type = TYPE_ARRAY,
        .len = STORAGE_TYPE_UNDEF_LEN,
    }, /*Any*/
    {
        .type = TYPE_STRING,
        .len = STORAGE_TYPE_UNDEF_LEN,
    }, /*Any*/
    {
        .type = TYPE_OPERATION,
        .len = STORAGE_TYPE_UNDEF_LEN,
    }, /*Any*/
};

uint32_t storage_get_type_len(StorageType_t type) {
    uint32_t len = 0;
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(StorageSizeInfo); i++) {
        if(type == StorageSizeInfo[i].type) {
            res = true;
            len = StorageSizeInfo[i].len;
            break;
        }
    }
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(STORAGE, "UndefLenForTypeID:%u=%s", type, StorageTypeToStr(type));
#endif
    }
    return len;
}

static uint8_t storage_data[STORAGE_DATA_SIZE] = {0};

#define STORAGE_DATA_OFFSET sizeof(StorageFrameHeader_t)
/*
 * tbfp_num - TBFP instance NUM
 * payload- tbfp frame payload
 * size - tbfp frame payload size
 */
bool storage_proc_cmd(uint8_t tbfp_num, const uint8_t* const payload, const uint32_t size) {
    bool res = false;
    if(payload) {
        if(size) {
            // runs
            StorageFrameHeader_t Header = {0};
            memcpy(&Header, payload, sizeof(StorageFrameHeader_t));

            memset(storage_data, 0x00, STORAGE_DATA_SIZE);
            memcpy(storage_data, payload, sizeof(StorageFrameHeader_t));

#ifdef HAS_LOG
            LOG_DEBUG(STORAGE, "%s", StorageFrameHeaderToStr(&Header));
#endif
            switch(Header.operation) {
            case ACCESS_WRITE_ONLY: {
                res = true;
#ifdef HAS_W25Q32JV
                res = w25q32jv_prog_page(Header.asic_num, Header.address, &payload[STORAGE_DATA_OFFSET], Header.size);
#endif
#ifdef HAS_TBFP
                res = tbfp_send_frame(tbfp_num, TBFP_FRAME_ID_STORAGE, storage_data, sizeof(StorageFrameHeader_t));
#endif
            } break;
            case ACCESS_ERASE: {
                res = true;
#ifdef HAS_W25Q32JV
                res = w25q32jv_chip_erase(Header.asic_num);
#endif

#ifdef HAS_TBFP
                res = tbfp_send_frame(tbfp_num, TBFP_FRAME_ID_STORAGE, storage_data, sizeof(StorageFrameHeader_t));
#endif
            } break;

            case ACCESS_READ_ONLY: {
                if(Header.size < STORAGE_DATA_SIZE) {
                    res = true;
#ifdef HAS_W25Q32JV
                    res = w25q32jv_read_data(Header.asic_num, Header.address,
                                             &storage_data[sizeof(StorageFrameHeader_t)], Header.size);

#endif

#ifdef HAS_TBFP
                    res = tbfp_send_frame(tbfp_num, TBFP_FRAME_ID_STORAGE, storage_data,
                                          sizeof(StorageFrameHeader_t) + Header.size);
#endif

                } else {
#ifdef HAS_LOG
                    LOG_ERROR(STORAGE, "TooBigSize:%u,Max:%u", Header.size, STORAGE_DATA_SIZE);
#endif
                }
            } break;
            default:
                break;
            }
        }
    }
    return res;
}

bool StorageIsValidParam(const StorageItem_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(Config->parser) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,Parser,ID:%u", Config->id);
#endif
            res = false;
        }

        uint32_t type_len = storage_get_type_len(Config->type);
        if(type_len < Config->len) {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,LenTooBit,ID:%u,TypeLen:%u", Config->id, type_len);
#endif
            res = false;
        }

        if(Config->len) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,Len,ID:%u", Config->id);
#endif
            res = false;
        }

        if(Config->default_value) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,DefVal,ID:%u", Config->id);
#endif
            res = false;
        }

        if(Config->name) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,Name,ID:%u", Config->id);
#endif
            res = false;
        }

        if(Config->type) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,type,ID:%u", Config->id);
#endif
            res = false;
        }

        if(Config->id) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,id");
#endif
            res = false;
        }

        if(Config->facility) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(STORAGE, "No,facility,ID:%u", Config->id);
#endif
            res = false;
        }
    }
    return res;
}

/*TODO: implement bin search */
StorageType_t storage_get_type(const StorageId_t id) {
    StorageType_t ret_type = TYPE_UNDEF;
    uint16_t i = 0;
    uint32_t cnt = storage_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(id == StorageArray[i].id) {
            ret_type = StorageArray[i].type;
            break;
        }
    }
    return ret_type;
}

uint32_t storage_get_len(const StorageId_t id) {
    uint32_t size = 0;
    StorageItem_t* Node = StorageGetNode(id);
    if(Node) {
        size = Node->len;
    } else {
        StorageType_t type = storage_get_id_type(id);
        size = storage_get_type_len(type);
    }
    return size;
}

StorageItem_t* StorageGetNode(const StorageId_t id) {
    StorageItem_t* Node = NULL;
    uint16_t i = 0;
    uint32_t cnt = storage_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(id == StorageArray[i].id) {
            Node = &StorageArray[i];
            break;
        }
    }
    return Node;
}
