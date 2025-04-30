#include "sw_nvram.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "array.h"
#include "crc16_ccitt.h"
#include "bit_const.h"
#include "byte_utils.h"
#ifdef HAS_TIME
#include "time_mcal.h"
#endif
#include "log.h"

#ifdef HAS_NOR_FLASH
#include "nor_flash_drv.h"
#include "nor_flash_diag.h"
#endif /*HAS_NOR_FLASH*/

#include "sw_nvram_diag.h"
#include "sw_nvram_config.h"

NvRamPage_t nvram_calc_opposite_page(NvRamPage_t active_page) {
    NvRamPage_t opposite_page = NVRAM_PAGE_UNDEF;
    switch(active_page) {
        case NVRAM_PAGE_1: opposite_page=NVRAM_PAGE_2;break;
        case NVRAM_PAGE_2: opposite_page=NVRAM_PAGE_1;break;
        default: break;
    }
    return opposite_page;
}

NvRamItem_t* NvRamGetNode(uint8_t num) {
    NvRamItem_t* Node = NULL;
    /*TODO find with bin search*/
    uint32_t i = 0;
    for(i = 0; i < sw_nvram_get_cnt(); i++) {
        if(num == NvRamItem[i].num) {
            Node = &NvRamItem[i];
            break;
        }
    }
    return Node;
}

const NvRamConfig_t* NvRamGetConfig(uint8_t num) {
    const NvRamConfig_t* ConfNode = 0;
    uint32_t i = 0;
    /*TODO find with bin search*/
    for(i = 0; i < sw_nvram_get_cnt(); i++) {
        if(num == NvRamConfig[i].num) {
            ConfNode = &NvRamConfig[i];
            break;
        }
    }
    return ConfNode;
}

bool sw_nvram_format(NvRamItem_t* Node, NvRamPage_t active_page ) {
    bool res = false;
    LOG_WARNING(NVRAM,"Assign page %u as Active", active_page);
    uint32_t page_code = 0;

    page_code = NVRAM_PAGE_CODE_ACTIVE;
    res = nor_flash_write(Node->nor_flash_num, Node->page[active_page].page_start,(uint8_t* ) &page_code, 4);
    if(res) {
        page_code = NVRAM_PAGE_CODE_PASSIVE;
        NvRamPage_t opposite_page =  nvram_calc_opposite_page(active_page);
        res = nor_flash_write(Node->nor_flash_num,Node->page[opposite_page].page_start, (uint8_t* )&page_code, 4);
        if(false==res) {
        	 LOG_ERROR(NVRAM,"Assign Pase %u 0x%x Err", opposite_page, page_code);
        }
    }else{
    	 LOG_ERROR(NVRAM,"Assign Pase %u 0x%x Err",active_page, page_code);
    }

    return res;
}

NvRamPage_t sw_nvram_select_page1_active_page2(NvRamItem_t* Node){
    NvRamPage_t active_page = NVRAM_PAGE_UNDEF;

    switch(Node->page[1].prefix){
        case NVRAM_PAGE_CODE_ACTIVE: {
            LOG_ERROR(NVRAM,"DoubleActiveErr!");
        }break;

        case NVRAM_PAGE_CODE_PASSIVE: {
            active_page = NVRAM_PAGE_1;
        }break;

        case NVRAM_PAGE_CODE_EMPTY: {
            active_page = NVRAM_PAGE_1;
        }break;

        default:{
            LOG_ERROR(NVRAM,"UndefPage1Prefix 0x%x", Node->page[1].prefix);
        } break;
    }

    return active_page;
}

NvRamPage_t sw_nvram_select_page1_passive_page2(NvRamItem_t* Node){
    NvRamPage_t active_page = NVRAM_PAGE_UNDEF;

    switch(Node->page[1].prefix) {

        case NVRAM_PAGE_CODE_ACTIVE: {
            active_page = NVRAM_PAGE_2;
        }break;

        case NVRAM_PAGE_CODE_PASSIVE: {
            LOG_ERROR(NVRAM,"DoublePassiveErr!");
        }break;

        case NVRAM_PAGE_CODE_EMPTY: {
            LOG_ERROR(NVRAM,"EmplyAndPassiveErr!");
        }break;

        default:{
            LOG_ERROR(NVRAM,"UndefPage1Prefix 0x%x",Node->page[1].prefix);
        } break;
    }

    return active_page;
}

NvRamPage_t sw_nvram_select_page1_empty_page2(NvRamItem_t* Node){
    NvRamPage_t active_page = NVRAM_PAGE_UNDEF;
    bool res = false;
    switch(Node->page[1].prefix){
    case NVRAM_PAGE_CODE_ACTIVE: {
        active_page = NVRAM_PAGE_2;
    }break;
    case NVRAM_PAGE_CODE_PASSIVE: {
        LOG_ERROR(NVRAM,"Page1EmplyPage2PassiveErr!");
    }break;
    case NVRAM_PAGE_CODE_EMPTY: {
        LOG_ERROR(NVRAM,"DoubleEmplyErr!");
        res= sw_nvram_format( Node,NVRAM_PAGE_1);
        if(res){
            active_page = NVRAM_PAGE_1;
        }else{
        	active_page = NVRAM_PAGE_UNDEF;
        	LOG_ERROR(NVRAM,"SetActivePageRtt");
        }

    }break;
    default:{
        LOG_ERROR(NVRAM,"UndefPage1Prefix 0x%x",Node->page[1].prefix);
    } break;
    }

    return active_page;
}

NvRamPage_t sw_nvram_select_active_page(NvRamItem_t* Node) {
    NvRamPage_t active_page = NVRAM_PAGE_UNDEF;
    switch(Node->page[0].prefix) {
        case NVRAM_PAGE_CODE_ACTIVE:  active_page = sw_nvram_select_page1_active_page2(Node); break;
        case NVRAM_PAGE_CODE_PASSIVE: active_page = sw_nvram_select_page1_passive_page2(Node);break;
        case NVRAM_PAGE_CODE_EMPTY:   active_page = sw_nvram_select_page1_empty_page2(Node);  break;
    default :
        LOG_ERROR(NVRAM,"UndefPage0Prefix 0x%x",Node->page[0].prefix);
        break;
    }
    return active_page;
}

NvRamPage_t sw_nvram_calc_active_page(NvRamItem_t* Node, const NvRamConfig_t* Config){
    NvRamPage_t active_page = NVRAM_PAGE_UNDEF;
    if(Config) {
        bool res = false;
        res = nor_flash_read(Node->nor_flash_num,Config->page[0].page_start, (uint8_t* const) &Node->page[0].prefix, NVRAM_PAGE_PREFIX_SIZE);
        if(res){
            res = nor_flash_read(Node->nor_flash_num,Config->page[1].page_start, (uint8_t* const) &Node->page[1].prefix, NVRAM_PAGE_PREFIX_SIZE);
            if(res){
                active_page=sw_nvram_select_active_page(Node);
            }
        }
    }
    return active_page;
}

bool sw_nvram_init_one(uint8_t num) {
    bool res = false;
    NvRamItem_t* Node = NvRamGetNode(num);
    const NvRamConfig_t* Config= NvRamGetConfig(num) ;
    if(Config){
        SwNvramDiag(Config);

    if(Node ) {
        LOG_WARNING(NVRAM,"Init %u", num);
        Node->nor_flash_num = Config->nor_flash_num;
        Node->nor_flash_num = Config->nor_flash_num;
        // Node->start_mem =Config->start_mem;
        memcpy(&Node->page[0],&Config->page[0], sizeof(NvRamPageConfig_t));
        memcpy(&Node->page[1],&Config->page[1], sizeof(NvRamPageConfig_t));
        LOG_INFO(NVRAM,"Page0Start 0x%x Size: %u", Node->page[0].page_start, Node->page[0].size);
        LOG_INFO(NVRAM,"Page1Start 0x%x Size: %u", Node->page[1].page_start, Node->page[1].size);

        NorFlashItem_t* FlashNode = NorFlashGetNode(Node->nor_flash_num);
        if(FlashNode) {
            LOG_INFO(NVRAM,"WorkWith NorFlash %u=%s", FlashNode->option, NorFlashOption2Str(FlashNode->option));
        }
        Node->active_page = sw_nvram_calc_active_page(Node, Config);
        if(NVRAM_PAGE_UNDEF!=Node->active_page ){
            LOG_INFO(NVRAM,"ActivePage %u", Node->active_page);
            if(Node->active_page<2){
                Node->start_mem = Node->page[Node->active_page].page_start+NVRAM_PAGE_PREFIX_SIZE;
                res = true;
            }else{
                Node->start_mem=0xFFFFFFFF;
            }
            Node->init = true;
        } else {
        	res = false;
        	Node->init = false;
        	LOG_ERROR(NVRAM, "CalcActivePage %u Err",Node->active_page);
        	nor_flash_mem_diag(  Node->nor_flash_num,Node->page[0].page_start,NVRAM_PAGE_PREFIX_SIZE,"Page1");
        	nor_flash_mem_diag(  Node->nor_flash_num,Node->page[1].page_start,NVRAM_PAGE_PREFIX_SIZE,"Page2");
        }
    }
}
    return res;
}

bool sw_nvram_init(void){
    bool res = true, out_res= true;
    LOG_WARNING(NVRAM,"Init");
    uint32_t nvram_cnt = sw_nvram_get_cnt() ;
    uint8_t i = 0;
    for(i=1; i <= nvram_cnt;i++) {
        res = sw_nvram_init_one(i);
        if(false==res) {
            out_res= false;
        }
    }
    return out_res;
}

bool nvram_is_valid_entry(NvRamHeader_t* Header){
    bool res = false;
    if(Header){
        if(NVRAM_SIGNATUGE==Header->signature){
            if(Header->address.plane == MASK_32BIT^Header->address.inverted){
                if(0<Header->data_size){
                    res = true;
                }else{
                	LOG_ERROR(NVRAM,"ZeroEntrySize");
                }
            }else{
            	LOG_ERROR(NVRAM,"AddrPlaneNotEqualInv 0x%x",Header->address.plane);
            }
        }else{
        	LOG_DEBUG(NVRAM,"SignatyreErr %x",Header->signature);
        }
    }
    return res;
}

uint32_t sw_nvram_get_end( NvRamItem_t* Node, uint32_t offset){
    uint32_t phy_end_addr = 0;
    bool res = false;
    if(Node) {
        Node->entry_cnt = 0;
        while(1) {
            NvRamHeader_t CurHeader={0};
            res = nor_flash_read(Node->nor_flash_num,offset, (uint8_t* const) &CurHeader, sizeof(NvRamHeader_t));
            if(res) {
                res = nvram_is_valid_entry(&CurHeader);
                if (res) {
                    LOG_DEBUG(NVRAM, "SpotNode AddrVirt: %u DataSize:%u",CurHeader.address.plane ,CurHeader.data_size);
                    Node->entry_cnt++;
                    offset += sizeof(NvRamHeader_t)+CurHeader.data_size;
                } else {
                    LOG_DEBUG(NVRAM,"NotAnEntry offset %u=0x%x",offset,offset);
                    res = is_arr_pat((uint8_t*) &CurHeader, sizeof(NvRamHeader_t), 0xFF);
                    if(res) {
                        phy_end_addr=offset;
                        break;
                    } else {
                        LOG_DEBUG(NVRAM,"NotSpareFlashForHeaderAtPhyAddr %u=0x%x",offset,offset);
                        //offset++;
                    }
                }
            }
        }
    }else{
  	  LOG_ERROR(NVRAM,"NodeErr");
    }
    return phy_end_addr ;
}

bool sw_nvram_glue_entry(NvRamItem_t* Node, int32_t base, uint32_t address, uint32_t physical_address){
    bool res = false;
    NvRamHeader_t Header;
    res = nor_flash_read(Node->nor_flash_num,  base, (uint8_t* const) &Header, sizeof(NvRamHeader_t));
    if(res) {
          res = nvram_is_valid_entry(&Header);
          if (res) {
              if(address < Header.address.plane) {
                  res= nor_flash_is_valid_addr(Node->nor_flash_num, Header.left_node_addr);
                  if(res) {
                      res = sw_nvram_glue_entry(Node, Header.left_node_addr, address, physical_address);
                  } else {
                      LOG_DEBUG(NVRAM, "Attach PhyAddr 0x%08x Left" ,physical_address );
                      size_t l_offset=offsetof(NvRamHeader_t, left_node_addr);
                      res = nor_flash_write(Node->nor_flash_num,base + l_offset, (uint8_t*) &physical_address, 4);
                  }
              } else {
                  res= nor_flash_is_valid_addr(Node->nor_flash_num,Header.right_node_addr);
                  if(res) {
                      res = sw_nvram_glue_entry(Node, Header.right_node_addr, address, physical_address);
                  } else {
                	  LOG_DEBUG(NVRAM, "Attach PhyAddr 0x%08x Right", physical_address );
                      size_t r_offset=offsetof(NvRamHeader_t, right_node_addr);
                      res = nor_flash_write(Node->nor_flash_num, base +r_offset, (uint8_t*) &physical_address, 4);
                  }
              }
          }
    }
    return res;
}

uint32_t nvram_entry_cnt(uint8_t num){
	uint32_t cnt = 0 ;
    NvRamItem_t* Node = NvRamGetNode(num);
    if(Node) {
        Node->phy_end_addr= sw_nvram_get_end( Node,Node->start_mem);
        cnt = Node->entry_cnt;
    }else{
    	LOG_ERROR(NVRAM,"NodeErr %u",num);
    }
    return cnt;
}

static bool sw_nvram_is_node_exist_ll(NvRamHeader_t* Header, NvRamItem_t* Node, uint32_t base, NvRamHeader_t* const SpotHeader ){
    bool res= false;
    NvRamHeader_t CurHeader;
    res = nor_flash_read(Node->nor_flash_num,base, (uint8_t* const) &CurHeader, sizeof(NvRamHeader_t));
    if(res){
           res= false;
           res = nvram_is_valid_entry(&CurHeader);
           if (res) {
               res= false;
               if(Header->address.plane<CurHeader.address.plane){
                   res=sw_nvram_is_node_exist_ll(Header,Node , CurHeader.left_node_addr, SpotHeader);
               }else if(CurHeader.address.plane<Header->address.plane) {
                   res=sw_nvram_is_node_exist_ll(Header,Node , CurHeader.right_node_addr, SpotHeader);
               } else {
                   res= false;
                   if(ENTRY_SAVE==CurHeader.state.not_deleted) {
                       if(ENTRY_FRESHNESS_LATEST==CurHeader.state.freshness) {
                           LOG_INFO(NVRAM, "AddrVirt %d Exist!", Header->address.plane);
                           if (Header->data_crc16==CurHeader.data_crc16) {
                               if(Header->data_size==CurHeader.data_size) {
                                   LOG_INFO(NVRAM, "CRC16match!");
                                   memcpy(SpotHeader,&CurHeader,sizeof(NvRamHeader_t));
                                   res = true;
                               }else{
                                   LOG_WARNING(NVRAM, "LenDiff!");
                               }
                           } else {
                               LOG_WARNING(NVRAM, "CRC16diff!");
                           }
                       }
                   }

                   if(false==res){
                           res=sw_nvram_is_node_exist_ll(Header,Node, CurHeader.right_node_addr, SpotHeader);

                   }
               }
           }else{
               res= false;
           }
    }
    return res;
}

bool sw_nvram_is_node_exist(NvRamItem_t* Node, NvRamPage_t active_page, NvRamHeader_t* Header ){
    bool res= false;
    NvRamHeader_t SpotHeader;
    uint32_t start_mem = Node->page[active_page].page_start + NVRAM_PAGE_PREFIX_SIZE;
    res = sw_nvram_is_node_exist_ll(Header, Node, start_mem, &SpotHeader);
    return res;
}


static bool sw_nvram_is_addr_exist(NvRamItem_t* Node, uint32_t base, uint32_t address, NvRamHeader_t* Header, uint32_t* const offset){
    bool res = false;
    res= nor_flash_is_valid_addr(Node->nor_flash_num,base);
    if(res) {
        NvRamHeader_t CurHeader={0};
        res = nor_flash_read(Node->nor_flash_num,base, (uint8_t* const) &CurHeader, sizeof(NvRamHeader_t));
        if(res) {
            res = nvram_is_valid_entry(&CurHeader);
            if (res) {
                res = false;
                LOG_DEBUG(NVRAM,"ValidNode Offset %u", base);
                if (address<CurHeader.address.plane){
                        res = sw_nvram_is_addr_exist(Node, CurHeader.left_node_addr,   address, Header, offset);
                } else if (CurHeader.address.plane<address){
                         res = sw_nvram_is_addr_exist(Node, CurHeader.right_node_addr,   address, Header, offset);
                } else {
                    LOG_DEBUG(NVRAM,"Spot Addr %u=0x%08x", address, address);
                    if(ENTRY_FRESHNESS_LATEST==CurHeader.state.freshness) {
                        if(1==CurHeader.state.not_deleted) {
                            LOG_DEBUG(NVRAM,"Addr %u Size %u CRC16 0x%x",CurHeader.address.plane, CurHeader.data_size,CurHeader.data_crc16);
                            *offset = base;
                            memcpy(Header,&CurHeader, sizeof(NvRamHeader_t));
                            res = true;
                        }
                    }

                    if(false==res){
                        res = sw_nvram_is_addr_exist(Node, CurHeader.right_node_addr, address, Header, offset);
                    }
                }
            }else{
                 res = false;
                 LOG_ERROR(NVRAM,"NotAnEntry Addr 0x%x Signature 0x%x", address, CurHeader.signature);
            }
        }
    }
    return res;
}

bool sw_nvram_is_address_exist(uint8_t num, uint32_t address){
	  bool res= false;
      NvRamItem_t* Node=NvRamGetNode(num);
      if (Node) {
          NvRamHeader_t OldHeader;
          memset(&OldHeader, 0, sizeof(NvRamHeader_t));
          uint32_t offset = 0;
          res = sw_nvram_is_addr_exist(Node, Node->start_mem, address, &OldHeader, &offset);
      }else{
    	  LOG_ERROR(NVRAM,"NodeErr %u",num);
      }
	  return res;
}

bool sw_nvram_write_opposite_page(NvRamItem_t* const Node, NvRamHeader_t const * const HeaderToMove, uint32_t from_addr) {
    bool res= false;
    LOG_WARNING(NVRAM, "MoveFrom 0x%08x", from_addr);
    if(Node) {
        if(HeaderToMove){
            if(0<HeaderToMove->data_size){
                res = true;
            }else {
                LOG_ERROR(NVRAM, "ZeroDataToMove");
            }
        }

        if(res) {

            cli_printf(CRLF);
            LOG_DEBUG(NVRAM, "Write Addr %d Size: %u bytes", HeaderToMove->address.plane, HeaderToMove->data_size);
            NvRamHeader_t NewHeader;
            NewHeader.signature = NVRAM_SIGNATUGE;
            NewHeader.address.plane = HeaderToMove->address.plane;
            NewHeader.address.inverted = MASK_32BIT ^ HeaderToMove->address.plane;
            NewHeader.write_counter = 0xFFFFFFFF;
            NewHeader.write_time_stamp = HeaderToMove->write_time_stamp;
            NewHeader.data_crc16 =  HeaderToMove->data_crc16;
            NewHeader.left_node_addr = 0xFFFFFFFF;
            NewHeader.right_node_addr = 0xFFFFFFFF;
            NewHeader.data_size = HeaderToMove->data_size;
            NewHeader.name_size = 0;
            NewHeader.state.freshness = ENTRY_FRESHNESS_LATEST;
            NewHeader.state.not_deleted = ENTRY_SAVE;
            NewHeader.state.byte = 0xFF;
            NewHeader.data_type = DATA_TYPE_ARRAY;

            NvRamPage_t opposite_page = nvram_calc_opposite_page(Node->active_page);
            res = sw_nvram_is_node_exist(Node, opposite_page, &NewHeader);
            if (res) {
                LOG_WARNING(NVRAM, "SpotDoubleWrite! Addr %u", HeaderToMove->address.plane);
                res = true;
            } else {
                NvRamHeader_t OldHeader;
                memset(&OldHeader, 0, sizeof(NvRamHeader_t));
                uint32_t offset = 0;
                uint32_t start_mem = Node->page[opposite_page].page_start + NVRAM_PAGE_PREFIX_SIZE;
                res = sw_nvram_is_addr_exist(Node, start_mem, HeaderToMove->address.plane, &OldHeader, &offset);
                if(res) {
                    /*Set entry as outdated*/
                    LOG_WARNING(NVRAM, "Outdated Addr:%u Size:%u", OldHeader.address.plane, OldHeader.data_size);
                    OldHeader.state.freshness = ENTRY_FRESHNESS_OBSOLATE;
                    size_t offset_status = offsetof(NvRamHeader_t, state);
                    uint32_t phy_address_status = offset + offset_status;
                    res =  nor_flash_write(Node->nor_flash_num,phy_address_status, &OldHeader.state.byte, 1);
                }

                uint32_t end_physical_address = sw_nvram_get_end(Node, start_mem);
                uint32_t spare_size = Node->page[opposite_page].size - end_physical_address;
                LOG_DEBUG(NVRAM, "EndOf NVRAM Addr %d Cnt %u Spare %u byte", end_physical_address, Node->entry_cnt, spare_size);

                uint32_t needed_size = sizeof(NvRamHeader_t)+HeaderToMove->data_size;
                if(needed_size < spare_size) {
                    LOG_DEBUG(NVRAM, "WriteHeader.. Spare %u byte Need Size: %u byte",spare_size-sizeof(NvRamHeader_t), HeaderToMove->data_size);
                    res = nor_flash_write(Node->nor_flash_num, end_physical_address, (uint8_t*) &NewHeader, sizeof(NvRamHeader_t));
                    if(res) {
                    	LOG_DEBUG(NVRAM, "MoveData.. %u byte",HeaderToMove->data_size);
                        res = nor_flash_memmove(Node->nor_flash_num, from_addr, end_physical_address+ sizeof(NvRamHeader_t), HeaderToMove->data_size);
                        /*register the physical_address of the desired node*/
                        if(Node->entry_cnt) {
                            LOG_DEBUG(NVRAM, "GlueEntry");
                            res = sw_nvram_glue_entry(Node, start_mem, HeaderToMove->address.plane, end_physical_address);
                        }else{
                        	LOG_DEBUG(NVRAM, "FirstEntry");
                        }
                    }
                } else {
                    LOG_ERROR(NVRAM, "NoMoreSpaceForEntry. Need %u byte Spare %u byte", needed_size, Node->spare_size);
                }
            }
        }
    }else{
  	  LOG_ERROR(NVRAM,"NodeErr");
    }

    return res;
}

bool sw_nvram_write(uint8_t num, uint32_t address , const  uint8_t* const data, uint32_t size){
    bool res= false;
    cli_printf(CRLF);
    LOG_DEBUG(NVRAM, "Write Addr 0x%08x Size: %u bytes", address, size);
    NvRamHeader_t NewHeader;
    NewHeader.signature = NVRAM_SIGNATUGE;
    NewHeader.address.plane = address;
    NewHeader.address.inverted = MASK_32BIT ^ address;
    NewHeader.write_counter = 0xFFFFFFFF;
    NewHeader.write_time_stamp = time_get_ms32();
    NewHeader.data_crc16 = calc_crc16_ccitt_false(data, size);
    NewHeader.left_node_addr = 0xFFFFFFFF;
    NewHeader.right_node_addr = 0xFFFFFFFF;
    NewHeader.data_size = size;
    NewHeader.name_size = 0;
    NewHeader.state.freshness = ENTRY_FRESHNESS_LATEST;
    NewHeader.state.not_deleted = ENTRY_SAVE;
    NewHeader.state.byte = 0xFF;
    NewHeader.data_type = DATA_TYPE_ARRAY;

    /*Is this data already in memory?*/

    NvRamItem_t* Node = NvRamGetNode(num);
    if(Node) {
        //Node->entry_cnt=nvram_entry_cnt(Node->start_mem);
        res= sw_nvram_is_node_exist(Node, Node->active_page, &NewHeader);
        if(false==res) {
            NvRamHeader_t OldHeader;
            uint32_t offset = 0;
            res = sw_nvram_is_addr_exist(Node, Node->start_mem, address, &OldHeader, &offset );
            if(res) {
                /*Set entry as outdated*/
                LOG_WARNING(NVRAM, "Outdated Addr:%u Size:%u",OldHeader.address.plane,OldHeader.data_size);
                OldHeader.state.freshness = ENTRY_FRESHNESS_OBSOLATE;
                size_t offset_status = offsetof(NvRamHeader_t, state);
                uint32_t phy_address_status = offset + offset_status;
                res =  nor_flash_write(Node->nor_flash_num,phy_address_status, &OldHeader.state.byte, 1);
            }

            Node->end_physical_address = sw_nvram_get_end(Node, Node->start_mem);
            NvRamPage_t cur_page = Node->active_page;
            Node->spare_size = Node->page[cur_page].size -Node->end_physical_address;

            LOG_DEBUG(NVRAM, "EndOf NVRAM Addr %d Cnt %u Spare %u byte", Node->end_physical_address, Node->entry_cnt, Node->spare_size);

            uint32_t needed_size = sizeof(NvRamHeader_t)+size;
            if(needed_size<Node->spare_size) {
                LOG_DEBUG(NVRAM, "WriteHeader..");
                res = nor_flash_write(Node->nor_flash_num,Node->end_physical_address, (uint8_t*) &NewHeader, sizeof(NvRamHeader_t));
                if(res) {
                    LOG_DEBUG(NVRAM, "WriteData..");
                    res = nor_flash_write(Node->nor_flash_num,Node->end_physical_address+ sizeof(NvRamHeader_t), data, size);
                    /*register the physical_address of the desired node*/
                    if(Node->entry_cnt){
                        LOG_DEBUG(NVRAM, "GlueEntry");
                        res = sw_nvram_glue_entry(Node, Node->start_mem, address, Node->end_physical_address);
                    }
                }
            } else {
                LOG_ERROR(NVRAM, "NoMoreSpaceForEntry. Need %u byte Spare %u byte", needed_size, Node->spare_size);
            }
         } else {
             LOG_WARNING(NVRAM, "SpotDoubleWrite!");
             res = true;
         }
    }else{
  	  LOG_ERROR(NVRAM,"NodeErr %u",num);
    }

    return res;
}


bool sw_nvram_check_entry(NvRamItem_t* const Node, uint32_t offset,
        uint32_t address, NvRamHeader_t* const SpotEntry,
        uint32_t* const phy_data_addr){
    bool res = false;
    NvRamHeader_t CurHeader;
    res = nor_flash_read(Node->nor_flash_num,  offset, (uint8_t* const) &CurHeader, sizeof(NvRamHeader_t));
    if(res){
        res = nvram_is_valid_entry(&CurHeader);
        if (res) {
            res = false;
            LOG_DEBUG(NVRAM,"ValidNode Offset %u", offset);
            if (address<CurHeader.address.plane) {
                    res = sw_nvram_check_entry(Node, CurHeader.left_node_addr,   address, SpotEntry, phy_data_addr);
            } else if (CurHeader.address.plane<address) {
                     res = sw_nvram_check_entry(Node, CurHeader.right_node_addr,   address, SpotEntry, phy_data_addr);
            } else {
                if(ENTRY_FRESHNESS_LATEST==CurHeader.state.freshness){
                    if(CurHeader.state.not_deleted){

                        uint32_t payload_phy_addr = offset+sizeof(NvRamHeader_t);
                        LOG_DEBUG(NVRAM,"Spot Addr %u Size %u CRC16 0x%x",CurHeader.address.plane, CurHeader.data_size,CurHeader.data_crc16);
                        uint16_t calc_crc16 = nor_flash_calc_crc16(Node->nor_flash_num, payload_phy_addr, CurHeader.data_size);
                        if(calc_crc16==CurHeader.data_crc16) {
                            LOG_DEBUG(NVRAM,"CRC16Ok At Offset %u=0x%x", payload_phy_addr, payload_phy_addr);
                            (*phy_data_addr) = payload_phy_addr;
                            memcpy(SpotEntry,&CurHeader, sizeof(NvRamHeader_t));
                            res = true;
                        }else {
                            LOG_ERROR(NVRAM,"CRC16err!");
                            res = false;
                        }
                    }
                }

                if(false==res){
                        res = sw_nvram_check_entry(Node, CurHeader.right_node_addr,   address, SpotEntry, phy_data_addr);

                }
            }
        }else{
             res = false;
             LOG_ERROR(NVRAM,"NotAnEntry Addr %u Signature 0x%x", address,CurHeader.signature);
        }
    }
    return res;
}

bool sw_nvram_read(uint8_t num, uint32_t address, uint8_t* const  data, uint32_t *const  size){
    bool res = false;
    LOG_WARNING(NVRAM, "Read Addr %d",address);

    NvRamItem_t* Node = NvRamGetNode(num);
    if(Node) {
        NvRamHeader_t CurHeader;
        memset(&CurHeader, 0, sizeof(NvRamHeader_t));
        uint32_t phy_data_addr = 0;
        res = sw_nvram_check_entry(Node, Node->start_mem, address, &CurHeader, &phy_data_addr);
        if(res) {
            LOG_DEBUG(NVRAM,"SpotEntry Addr %u PayLoadAddr %u Size %u byte", address, phy_data_addr, CurHeader.data_size);
            res = nor_flash_read(Node->nor_flash_num,phy_data_addr, data, CurHeader.data_size);
            (*size) = CurHeader.data_size;
        }else {
            LOG_DEBUG(NVRAM,"NoEntry Addr %u", address);
            (*size) = 0 ;
            res = true;
        }
    }else{
  	  LOG_ERROR(NVRAM,"NodeErr %u",num);
    }

    return res;
}


bool sw_nvram_traversal_level_order( NvRamItem_t* Node, uint32_t base, EntryActionFoo_t* EntryActionFoo ){
    bool res = false;
    NvRamHeader_t CurHeader;
    memset(&CurHeader, 0, sizeof(NvRamHeader_t));
    res = nor_flash_read(Node->nor_flash_num,base, (uint8_t* const) &CurHeader, sizeof(NvRamHeader_t));
    if(res) {
           res = nvram_is_valid_entry(&CurHeader);
           if (res) {
               if(EntryActionFoo) {
                   EntryActionFoo(Node, &CurHeader ,base);
               }

               res= nor_flash_is_valid_addr(Node->nor_flash_num,CurHeader.left_node_addr);
               if(res){
                   res = sw_nvram_traversal_level_order(Node, CurHeader.left_node_addr,EntryActionFoo);
               }

               res= nor_flash_is_valid_addr(Node->nor_flash_num,CurHeader.right_node_addr);
               if(res){
                   res = sw_nvram_traversal_level_order(Node, CurHeader.right_node_addr,EntryActionFoo);
               }
           }else{
               res= false;
           }
    }
    return res;
}

bool sw_nvram_traversal_in_order( NvRamItem_t* Node, uint32_t base, EntryActionFoo_t* EntryActionFoo ){
    bool res = false;
    NvRamHeader_t CurHeader;
    memset(&CurHeader, 0, sizeof(NvRamHeader_t));
    res = nor_flash_read(Node->nor_flash_num,base,(uint8_t* const) &CurHeader, sizeof(NvRamHeader_t));
    if(res) {
           res = nvram_is_valid_entry(&CurHeader);
           if (res) {
               res= nor_flash_is_valid_addr(Node->nor_flash_num,CurHeader.left_node_addr);
               if(res){
                   res = sw_nvram_traversal_in_order(Node, CurHeader.left_node_addr,EntryActionFoo);
               }

               if(EntryActionFoo) {
                   EntryActionFoo(Node, &CurHeader ,base);
               }

               res= nor_flash_is_valid_addr(Node->nor_flash_num,CurHeader.right_node_addr);
               if(res){
                   res = sw_nvram_traversal_in_order(Node, CurHeader.right_node_addr,EntryActionFoo);
               }
           }else{
               res= false;
           }
    }
    return res;
}


static bool sw_nvram_delete_entry_ll( NvRamItem_t* Node, uint32_t address, uint32_t base ){
    bool res= false;
    res= nor_flash_is_valid_addr(Node->nor_flash_num,base);
    if(res){
        NvRamHeader_t CurHeader;
        res = nor_flash_read(Node->nor_flash_num,base,( uint8_t* ) &CurHeader, sizeof(NvRamHeader_t));
        if(res) {
               res = nvram_is_valid_entry(&CurHeader);
               if (res) {
                   if(address < CurHeader.address.plane){
                       res = sw_nvram_delete_entry_ll(Node, address, CurHeader.left_node_addr);
                   }else if(CurHeader.address.plane < address) {
                       res = sw_nvram_delete_entry_ll(Node, address, CurHeader.right_node_addr);
                   } else {
                       if(1==CurHeader.state.not_deleted) {
                           LOG_DEBUG(NVRAM, "AddrVirt %d=0x%x Exist!", address, address);
                           CurHeader.state.not_deleted = ENTRY_DELETE;
                           size_t offset_status = offsetof(NvRamHeader_t, state);
                           uint32_t phy_address_status = base + offset_status;
                           res =  nor_flash_write(Node->nor_flash_num,  phy_address_status, &CurHeader.state.byte, 1);

                           phy_address_status = base + sizeof(NvRamHeader_t);
                           res = nor_flash_zero(Node->nor_flash_num, phy_address_status, CurHeader.data_size);
                           Node->del_cnt++;
                       }
                       res = sw_nvram_delete_entry_ll(Node, address, CurHeader.right_node_addr);
                   }
               }else{
                   res= false;
               }
        }
    }
    return res;
}

bool sw_nvram_delete(uint8_t num, uint32_t address){
    bool res = false;
    LOG_WARNING(NVRAM, "Delete Addr %u=0x%08x", address, address);
    NvRamItem_t* Node = NvRamGetNode(num);
    if(Node) {
        Node->del_cnt=0;
        res= sw_nvram_delete_entry_ll(Node, address, Node->start_mem);
        if(Node->del_cnt){
            res = true;
        }
    }else{
  	  LOG_ERROR(NVRAM,"NodeErr %u",num);
    }
    return res;
}

bool nvram_move_entry(NvRamItem_t* Node, NvRamHeader_t* const Header, uint32_t base){
    bool res = false;
    if(Node) {
        if(Header) {
            if(ENTRY_SAVE==Header->state.not_deleted) {
                if(ENTRY_FRESHNESS_LATEST==Header->state.freshness) {
                    LOG_WARNING(NVRAM, "PhyAddr 0x%08x MoveEntry Addr %u Size %u",
                            base, Header->address.plane, Header->data_size);
                    res = sw_nvram_write_opposite_page(Node, Header, base + sizeof(NvRamHeader_t));
                    if(res) {
                        LOG_WARNING(NVRAM, "DeleteNodeFromInitialPage");
                        Header->state.not_deleted = ENTRY_DELETE;
                        Header->state.freshness = ENTRY_FRESHNESS_OBSOLATE;
                        size_t offset_status = offsetof(NvRamHeader_t, state);
                        uint32_t phy_address_status = base + offset_status;
                        res =  nor_flash_write(Node->nor_flash_num,  phy_address_status, &Header->state.byte, 1);
                        phy_address_status = base + sizeof(NvRamHeader_t);
                        res = nor_flash_zero(Node->nor_flash_num, phy_address_status, Header->data_size);
                    }
                }
            }
        }
    }else{
  	  LOG_ERROR(NVRAM,"NodeErr");
    }
    return res;
}

bool nvram_errase_page(NvRamItem_t* Node, NvRamPage_t page){
	bool res = false;
    LOG_WARNING(NVRAM, "Errase Page %u", page);
	res = nor_flash_erase_mem(Node->nor_flash_num, Node->page[page].page_start, Node->page[page].size);
	if(res){
		 LOG_DEBUG(NVRAM, "Errase Page %u Ok", page);
	}else{
		LOG_ERROR(NVRAM, "Errase Page %u Err", page);
	}
    return res;
}

bool sw_nvram_toggle_page(NvRamItem_t* Node) {
    bool res = false;
    LOG_WARNING(NVRAM, "TogglePage. ActivePage %u", Node->active_page);
    if(Node ) {
    	NvRamPage_t opposite_page = nvram_calc_opposite_page(Node->active_page);
        res = nvram_errase_page(Node, opposite_page);
        if (res) {
            res = sw_nvram_traversal_level_order( Node, Node->start_mem, nvram_move_entry );
            Node->active_page = opposite_page;
            res = sw_nvram_format(Node, opposite_page);
        }
        Node->start_mem = Node->page[opposite_page].page_start + NVRAM_PAGE_PREFIX_SIZE;
    }else{
  	  LOG_ERROR(NVRAM,"NodeErr");
    }

    return res;
}
