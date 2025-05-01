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
                res = tbfp_send_frame(tbfp_num, FRAME_ID_STORAGE, storage_data, sizeof(StorageFrameHeader_t));
#endif
            } break;

            case ACCESS_ERASE: {
                res = true;
#ifdef HAS_W25Q32JV
                res = w25q32jv_chip_erase(Header.asic_num);
#endif

#ifdef HAS_TBFP
                res = tbfp_send_frame(tbfp_num, FRAME_ID_STORAGE, storage_data, sizeof(StorageFrameHeader_t));
#endif
            } break;

            case ACCESS_ERASE_SECTOR: {
#ifdef HAS_W25Q32JV
                res = w25q32jv_erase_sector(Header.asic_num, Header.address);
#endif
#ifdef HAS_TBFP
                res = tbfp_send_frame(tbfp_num, FRAME_ID_STORAGE, storage_data, sizeof(StorageFrameHeader_t));
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
                    res = tbfp_send_frame(tbfp_num, FRAME_ID_STORAGE, storage_data,
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
