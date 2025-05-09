#include "storage.h"

#include <string.h>

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

static uint8_t storage_tx_data[STORAGE_DATA_SIZE] = {0};
uint8_t storage_rx_data[STORAGE_DATA_SIZE] = {0};

#define STORAGE_DATA_OFFSET sizeof(StorageFrameHeader_t)

uint8_t read_addr_8bit(const uint32_t address) {
    uint8_t value = 0u;

    volatile uint8_t* p_addr = NULL;
    /*MISRA 2012 Rule 11.4: integer should not be converted to pointer */
    p_addr = (volatile uint8_t*)address;
    if(p_addr) {
        value = *p_addr;
    }

    return value;
}

bool write_addr_8bit(const uint32_t address, const uint8_t value) {
#ifdef HAS_LOG
    LOG_DEBUG(DBG, "WrireAddr[0x%08x]=0x%02x", address, value);
#endif
    bool res = true;
    volatile uint8_t* addr = NULL;
    addr = (volatile uint8_t*)address;
    (*addr) = value; /*May cause HardFault_Handler*/
    return res;
}

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
            StorageFrameHeader_t He_Storage_ader = {0};
            memcpy(&He_Storage_ader, payload, sizeof(StorageFrameHeader_t));

            memset(storage_tx_data, 0x00, STORAGE_DATA_SIZE);
            memcpy(storage_tx_data, payload, sizeof(StorageFrameHeader_t));

#ifdef HAS_LOG
            LOG_DEBUG(STORAGE, "%s", StorageFrameHeaderToStr(&He_Storage_ader));
#endif
            switch(He_Storage_ader.operation) {

            case ACCESS_READ_ONLY: {
                if(He_Storage_ader.size < STORAGE_DATA_SIZE) {
                    res = true;
#ifdef HAS_W25Q32JV
                    res = w25q32jv_read_data(He_Storage_ader.asic_num, He_Storage_ader.address,
                                             &storage_tx_data[sizeof(StorageFrameHeader_t)], He_Storage_ader.size);

#endif

#ifdef HAS_PC
                    memcpy(storage_rx_data,&storage_tx_data[sizeof(StorageFrameHeader_t)], He_Storage_ader.size);
#endif

#ifdef HAS_W25Q32JV
#ifdef HAS_TBFP
                    res = tbfp_send_frame(tbfp_num, FRAME_ID_STORAGE, storage_tx_data,
                                          sizeof(StorageFrameHeader_t) + He_Storage_ader.size);
#endif
#endif

                } else {
#ifdef HAS_LOG
                    LOG_ERROR(STORAGE, "TooBigSize:%u,Max:%u", He_Storage_ader.size, STORAGE_DATA_SIZE);
#endif
                }
            } break;

            case ACCESS_WRITE_ONLY: {
                res = true;
#ifdef HAS_W25Q32JV
                res = w25q32jv_prog_page(He_Storage_ader.asic_num, He_Storage_ader.address, &payload[STORAGE_DATA_OFFSET], He_Storage_ader.size);
#endif

#ifdef HAS_W25Q32JV
#ifdef HAS_TBFP
                res = tbfp_send_frame(tbfp_num, FRAME_ID_STORAGE, storage_tx_data, sizeof(StorageFrameHeader_t));
#endif
#endif

            } break;

            case ACCESS_ERASE: {
                res = true;
#ifdef HAS_W25Q32JV
                res = w25q32jv_chip_erase(He_Storage_ader.asic_num);
#endif

#ifdef HAS_TBFP
                res = tbfp_send_frame(tbfp_num, FRAME_ID_STORAGE, storage_tx_data, sizeof(StorageFrameHeader_t));
#endif
            } break;

            case ACCESS_ERASE_SECTOR: {
#ifdef HAS_W25Q32JV
                res = w25q32jv_erase_sector(He_Storage_ader.asic_num, He_Storage_ader.address);
#endif
#ifdef HAS_TBFP
                res = tbfp_send_frame(tbfp_num, FRAME_ID_STORAGE, storage_tx_data, sizeof(StorageFrameHeader_t));
#endif
            } break;

            default:
                break;
            }
        }
    }
    return res;
}

bool memory_write(const uint32_t phy_address, const uint8_t* const data, const uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < size; i++) {
        res = write_addr_8bit(phy_address + i, data[i]);
    }
    return res;
}

bool memory_read(const uint32_t phy_address, uint8_t* const data, const uint32_t size) {
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < size; i++) {
        data[i] = read_addr_8bit(phy_address + i);
    }
    return res;
}

/*
  read physical memory for external control

  tbfp_num - TBFP instance NUM
  payload- tbfp frame payload
  size - tbfp frame payload size
 */
bool storage_tbfp_memory(uint8_t tbfp_num, const uint8_t* const payload, const uint32_t size) {
    bool res = false;
    if(payload) {
        if(sizeof(StorageMemoryFrameHeader_t) < size) {
            StorageMemoryFrameHeader_t MemHeader = {0};
            memcpy(&MemHeader, payload, sizeof(StorageMemoryFrameHeader_t));
            memset(storage_tx_data, 0x00, STORAGE_DATA_SIZE);
            memcpy(storage_tx_data, payload, sizeof(StorageMemoryFrameHeader_t));

#ifdef HAS_LOG
            LOG_DEBUG(STORAGE, "%s", StorageMemoryFrameHeaderToStr(&MemHeader));
#endif
            switch(MemHeader.operation) {

            case ACCESS_WRITE_ONLY: {
                res = memory_write(MemHeader.address, &payload[sizeof(StorageMemoryFrameHeader_t)], MemHeader.size);
#ifdef HAS_TBFP
                res = tbfp_send_frame(tbfp_num, FRAME_ID_MEM, storage_tx_data, sizeof(StorageMemoryFrameHeader_t));
#endif
            } break;

            case ACCESS_READ_ONLY: {
                if(MemHeader.size < STORAGE_DATA_SIZE) {
                    res = memory_read(MemHeader.address, &storage_tx_data[sizeof(StorageMemoryFrameHeader_t)],
                                      MemHeader.size);
#ifdef HAS_TBFP
                    res = tbfp_send_frame(tbfp_num, FRAME_ID_MEM, storage_tx_data,
                                          sizeof(StorageMemoryFrameHeader_t) + MemHeader.size);
#endif

                } else {
#ifdef HAS_LOG
                    LOG_ERROR(STORAGE, "TooBigSize:%u,Max:%u", MemHeader.size, STORAGE_DATA_SIZE);
#endif
                }
            } break;
            default:
                break;
            } //    switch(MemHeader.operation) {
        }
    }
    return res;
}
