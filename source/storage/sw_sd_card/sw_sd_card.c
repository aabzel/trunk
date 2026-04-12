#include "sw_sd_card.h"

#include <string.h>

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(SwSdCard, sw_sd_card)
COMPONENT_GET_CONFIG(SwSdCard, sw_sd_card)

/*ISO-26262 require verify configuration*/
bool SwSdCardIsValidConfig(const SwSdCardConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) { LOG_ERROR(SW_SD_CARD, "%u,NameErr", Config->num); }

        ifn(Config->buff) {
            res = false;
            LOG_ERROR(SW_SD_CARD, "%u,buff,Err", Config->num);
        }

        ifn(Config->size) {
            res = false;
            LOG_ERROR(SW_SD_CARD, "%u,size,Err", Config->num);
        }

        ifn(Config->block_size) {
            res = false;
            LOG_ERROR(SW_SD_CARD, "%u,block_size,Err", Config->num);
        }
    }
    return res;
}

bool sw_sd_card_init_custom(void) {
    bool res = false;
    LOG_INFO(SW_SD_CARD, "Version:%s", SW_SD_CARD_VERSION);
    return res;
}

bool sw_sd_card_init_common(const SwSdCardConfig_t* const Config, SwSdCardHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->buff = Config->buff;
            Node->size = Config->size;
            Node->block_size = Config->block_size;
            res = true;
        }
    }
    return res;
}

/*
  The disk_ioctl function is called to control device specific features and
  miscellaneous functions other than generic read/write.

  pdrv  -  [IN] Drive number
  cmd   -  [IN] Control command code
  buff  -  [I/O] Pointer to the parameter depends on the command code.
                 Do not care if the command has no parameter to be passed.
  */
DRESULT sd_sw_diskctl(uint8_t pdrv, uint8_t cmd, void* buff) {
    DRESULT ret = RES_ERROR;
    switch(cmd) {
    case GET_BLOCK_SIZE: {
        uint32_t block_size = 1;
        memcpy(buff, &block_size, sizeof(block_size));
        ret = RES_OK;

    } break;
    case GET_SECTOR_SIZE: {
        uint32_t sector_size = DISK_SECTOR_SIZE;
        memcpy(buff, &sector_size, sizeof(sector_size));
        ret = RES_OK;
    } break;
    case GET_SECTOR_COUNT: {
        uint32_t sector_size = DISK_SECTOR_CNT;
        memcpy(buff, &sector_size, sizeof(sector_size));
        ret = RES_OK;
    } break;
    case CTRL_SYNC: {
        ret = RES_OK;
    } break;

    case CTRL_FORMAT: {
    } break;
    case CTRL_LOCK: {
    } break;
    case CTRL_EJECT: {
    } break;
    case MMC_GET_TYPE: {
    } break;
    case MMC_GET_CSD: {
    } break;
    case MMC_GET_CID: {
    } break;
    case MMC_GET_OCR: {
    } break;
    case MMC_GET_SDSTAT: {
    } break;
    case ATA_GET_REV: {
    } break;
    case ATA_GET_MODEL: {
    } break;
    case ATA_GET_SN: {
    } break;
    case CTRL_TRIM: {
    } break;

#if 0
        case ISDIO_MRITE:{} break;
        case CTRL_ERASE_SECTOR:{} break;
        case CTRL_POWER_IDLE:{} break;
        case CTRL_POWER_OFF:{} break;
        case CTRL_UNLOCK:{} break;
        case CTRL_GET_SMART:{} break;
        case ISDIO_READ:{} break;
        case ISDIO_WRITE:{} break;
#endif
    default: {
        ret = RES_ERROR;
    } break;
    }
    return ret;
}

bool disk_sw_read_sector(uint8_t num, uint32_t sector, uint8_t* const buff) {
    bool res = false;
    SwSdCardHandle_t* Node = SwSdCardGetNode(num);
    if(Node) {
        LOG_DEBUG(DISK, "DISK%u,Read,Sector:%u", num, sector);
        if(sector < DISK_SECTOR_CNT) {
            memcpy(buff, &Node->buff[sector * DISK_SECTOR_SIZE], DISK_SECTOR_SIZE);
            res = true;
        }
    }
    return res;
}

bool disk_sw_write_sector(uint8_t num, uint32_t sector, uint8_t* const buff) {
    bool res = false;
    SwSdCardHandle_t* Node = SwSdCardGetNode(num);
    if(Node) {
        LOG_DEBUG(DISK, "DISK%u,Write,Sector:%u", num, sector);
        if(sector < DISK_SECTOR_CNT) {
            memcpy(&Node->buff[sector * DISK_SECTOR_SIZE], buff, DISK_SECTOR_SIZE);
            res = true;
        }
    }
    return res;
}

bool sw_sd_card_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(SW_SD_CARD, "SW_SD_CARD%u", num);
    const SwSdCardConfig_t* Config = SwSdCardGetConfig(num);
    if(Config) {
        res = SwSdCardIsValidConfig(Config);
        if(res) {
#ifdef HAS_SW_SD_CARD_DIAG
            LOG_WARNING(SW_SD_CARD, "%s", SwSdCardConfigToStr(Config));
#endif
            SwSdCardHandle_t* Node = SwSdCardGetNode(num);
            if(Node) {
                res = sw_sd_card_init_common(Config, Node);

                Node->valid = true;
                Node->init = true;
            } else {
                LOG_ERROR(SW_SD_CARD, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(SW_SD_CARD, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(SW_SD_CARD, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(SW_SD_CARD, SW_SD_CARD, sw_sd_card)
