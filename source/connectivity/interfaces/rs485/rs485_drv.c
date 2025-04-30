#include "rs485_drv.h"

#include <string.h>

#include "rs485_types.h"
#include "rs485_config.h"
#include "bit_utils.h"
//#include "protocol_types.h"
#include "protocol_diag.h"
#include "log.h"

bool addr_is_mask(ProtocolNode_t * const BusNet,Addr32Mask_t* Mask){
    bool res = false;
    if(BusNet) {
        if(Mask) {
            if(0==Mask->size) {
                res = true;
                LOG_DEBUG(RS485,"Match Mask: %s=Addr %s", Mask322Str(&Mask), utoa_bin32(BusNet->addr) );
            }else {
                if(Mask->size<=32) {
                    uint32_t range=generate_32bit_mask(Mask->size);
                    LOG_DEBUG(RS485,"Range %s:size: %u", utoa_bin32(range),Mask->size);
                    uint32_t mask_val =Mask->addr&range;
                    uint32_t addr_val =BusNet->addr&range;
                    if(addr_val == mask_val ){
                        LOG_DEBUG(RS485,"Match Mask: %s=Addr %s",
                                Mask322Str(&Mask),
                                utoa_bin32(BusNet->addr)
                                );
                        res = true;
                    }else{
                        res = false;
                    }
                }else{
                    res = false;
                }
            }
        }
    }
    return res;
}


ProtocolNode_t* Addr2Node(uint32_t addr){
    ProtocolNode_t* Node = NULL;
    uint32_t cnt = bus_get_cnt();
    uint32_t i = 0;
    for(i=0;i<cnt;i++) {
        if(BusNet[i].addr==addr){
            Node = &BusNet[i];
            break;
        }
    }
    return Node;
}


static bool rs485_is_mask_exist(Addr32Mask_t Mask,
        Rs485Bus_t* const Rs485Bus
        ){
    bool res = false;
    Rs485Bus->ask_cnt++;
    LOG_INFO(RS485,"%4u: IsAnyBodyWith %s",Rs485Bus->ask_cnt,Mask322Str(&Mask));
    bool out_res = false;

    if(BusNet) {
        uint32_t cnt = bus_get_cnt();
        uint32_t i=0;
        for (i=0; i<cnt; i++) {
            res = addr_is_mask(&Rs485Bus->BusNet[i],&Mask);
            if(res) {
                if(0==BusNet[i].status.mute) {
                    out_res = true;
                    LOG_WARNING(RS485,"ACK Addr 0x%x=%s Mask:%s",BusNet[i].addr,utoa_bin32(BusNet[i].addr),Mask322Str(&Mask));
                }
            }
        }
    }
    return out_res;
}

static bool add_addr(Rs485Bus_t* Rs485Bus, uint32_t addr) {
    bool res = false;
    if(Rs485Bus){
        LOG_WARNING(RS485,"SpotAddr 0x%x!",addr);
        Rs485Bus->cnt++;
        if(Rs485Bus->i<BUS_MAX){
            Rs485Bus->AddrList[Rs485Bus->i] = addr;
            Rs485Bus->i++;
        }

        ProtocolNode_t* Node=Addr2Node(addr);
        if(Node){
            Node->status.mute=1;
            LOG_WARNING(RS485,"MuteAddr 0x%x",addr);
            res = true;
        }
    }
    return res;
}

bool rs485_scan_ll(Rs485Bus_t* Rs485Bus,
        Addr32Mask_t Mask,
        uint32_t cur_index){
    bool res = false;

    if(Rs485Bus){

        if(Mask.size<=32) {
            if(cur_index<32) {
                Mask.size=cur_index+1;
                Mask.addr |=(1<<(cur_index));
                res = rs485_is_mask_exist(Mask,Rs485Bus);
                if(res) {
                    if(cur_index<31) {
                        res = rs485_scan_ll(Rs485Bus,  Mask,  cur_index+1);
                    }else{
                        //LOG_WARNING(RS485,"SpotAddr 0x%x:%u",Mask.addr,Mask.size);
                        add_addr(Rs485Bus,Mask.addr);
                    }
                }else{
                    LOG_NOTICE(RS485,"NoMask %s!", Mask322Str(&Mask));

                }

                Mask.size=cur_index+1;
                Mask.addr &=~(1<<(cur_index));
                res = rs485_is_mask_exist(Mask,Rs485Bus);
                if(res) {
                    if(cur_index<31) {
                         res= rs485_scan_ll(Rs485Bus,  Mask,     cur_index+1);
                    } else {
                        //LOG_WARNING(RS485,"SpotAddr 0x%x: %u",Mask.addr,Mask.size);
                        add_addr(Rs485Bus,Mask.addr);
                    }
                }else{
                    LOG_NOTICE(RS485,"NoMask %s!", Mask322Str(&Mask));

                }

            }
        }
    }
    return res;
}

bool rs485_scan(void){
    bool res = false;
    LOG_INFO(RS485,"Scan");
    Addr32Mask_t Mask;
    Mask.size=0;
    Mask.addr=0;
    Rs485Bus.ask_cnt=0;

    res = rs485_is_mask_exist(Mask,&Rs485Bus);
    Rs485Bus.ask_cnt++;
    if (res) {
        res = rs485_scan_ll(&Rs485Bus,Mask,0);
    }

    return res;
}

bool rs485_init(void){
    bool res = false;
    LOG_WARNING(RS485,"Init");
    set_log_level(RS485,LOG_LEVEL_NOTICE);
    Rs485Bus.i=0;
    Rs485Bus.cnt=0;
    memset(Rs485Bus.AddrList,0,sizeof(Rs485Bus.AddrList));

    uint32_t cnt=bus_get_cnt();
    uint32_t i=0;
    for(i=0;i<cnt;i++){
        BusNet[i].addr=BusNetConfig[i];
        BusNet[i].status.byte = 0;
        res = true;
    }

    Rs485Bus.BusNet=BusNet;
    return res;
}
