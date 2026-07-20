#include "dma_channel_custom_commands.h"

#include "dma_mcal.h"
#include "dma_channel_custom_diag.h"
#include "log.h"
#include "sys_config.h"
#include "convert.h"


bool dma_channel_diag_custom_command(int32_t argc, char* argv[]){
    bool res = false;
    res = dma_channel_diag_custom();
    return res;
}

bool dma_channel_diag_ll_command(int32_t argc, char* argv[]){
    bool res = dma_channel_diag_low_level("","");
    return res;
}

/*
 dchmic 1 3 1
 */
bool dma_channel_half_move_it_ctrl_command(int32_t argc, char* argv[]){

    bool res = true;
    uint8_t dma_num = 0;
    uint8_t stream = 0;
    bool en = true;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &dma_num);
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &stream);
    }

    if(3 <= argc) {
        res = try_str2bool(argv[2], &en);
    }



    if(res) {
        DmaInfoChannel_t DmaPad = {
            .dma_num = dma_num,
            .stream = stream,
        };

        switch(argc) {
        case 2: {
            en = dma_channel_half_move_it_get(DmaPad);
            if(res) {
                LOG_INFO(DMA_CHANNEL, "Get,DMA%u_Stream_%u,HalfMoveInt:%u", dma_num, stream, en);
            }
        } break;

        case 3: {
            LOG_INFO(DMA_CHANNEL, "Set,DMA%u_Stream_%u,HalfMoveInt:%u", dma_num, stream, en);
            res = dma_channel_half_move_it_ctrl(DmaPad, en);
            log_info_res(DMA_CHANNEL, res, "HalfItSet");
        } break;

        default:
            break;
        }
    } else {
        LOG_ERROR(DMA_CHANNEL, "Usage: dchmic DmaNum Channel OnOff");
    }
    return res;

}


