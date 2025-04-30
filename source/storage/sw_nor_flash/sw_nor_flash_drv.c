#include "sw_nor_flash_drv.h"

#include <string.h>

#include "crc16_ccitt.h"
#include "log.h"
#include "nor_flash_drv.h"
#include "sw_nor_flash_config.h"

bool sw_nor_flash_read(uint8_t num, uint32_t phy_address, uint8_t * const data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(SW_NOR_FLASH, "Read Addr %u=0x%08x Size %u byte", phy_address, phy_address, size);
    if(data) {
        if(size) {
            res =  nor_flash_is_valid_addr(num, phy_address);
            if(res) {
               	NorFlashItem_t* Node = NorFlashGetNode(  num);
               	if(Node){
               		if(Node->memory){
                        memcpy(data, &Node->memory[phy_address], size);
                        res = true;
               		}
               	}else{
               	 LOG_ERROR(SW_NOR_FLASH, "%u NodeErr", num);
               	}
            } else {
                LOG_ERROR(SW_NOR_FLASH, "InvalidPhyAddress %u=0x%08x", phy_address, phy_address);
            }
        }
    }

    return res;
}

bool sw_nor_flash_erase_sector(uint8_t num,uint32_t phy_address) {
    bool res = false;
    res= nor_flash_is_valid_addr(num,  phy_address);
	if(res){
		res = false;
       	NorFlashItem_t* Node = NorFlashGetNode(  num);
       	if(res){
            memset(&Node->memory[phy_address], 0xff,SW_NOR_FLASH_SECTOR_SIZE);
            res = true;
       	}
    }
    return res;
}

bool sw_nor_flash_erase_chip(uint8_t num) {
    bool res = true;
    LOG_WARNING(SW_NOR_FLASH, "%u EraseAll",num);
   	NorFlashItem_t* Node =NorFlashGetNode(  num);
    if(Node) {
       if(Node->memory) {
    	    LOG_WARNING(SW_NOR_FLASH, "Erase %u byte",Node->size);
            memset(Node->memory, 0xff, Node->size);
            res = nor_flash_erase_verify(num, 0, Node->size);
            if(res) {
            	LOG_DEBUG(SW_NOR_FLASH, "ErraseOk");
            }else {
            	LOG_WARNING(SW_NOR_FLASH, "ErraseError");
            }
   		}
   	}else{
   		LOG_ERROR(SW_NOR_FLASH, "NodeError");
   	}
    return res;
}

bool sw_nor_flash_erase_block(uint8_t num,uint32_t phy_address, uint32_t block_size) {
    bool res = true;
    LOG_DEBUG(SW_NOR_FLASH, "Addr %u Erase Block %u byte", phy_address, block_size);
    res= nor_flash_is_valid_addr(num,  phy_address);
	if(res){
		res = false;
       	NorFlashItem_t* Node =NorFlashGetNode(  num);
       	if(Node){
            memset(&Node->memory[phy_address], 0xff, block_size);
       	}else{
       		LOG_ERROR(SW_NOR_FLASH, "NodeError");
       	}
    }
    return res;
}

/*10-22. Page Program (PP)
 * (page 28 )Figure 12. Program/Erase flow with read array data
 * */
bool sw_nor_flash_page_program(uint8_t num,uint32_t phy_address, const uint8_t*const data, uint32_t size) {
    bool res = false;
    LOG_DEBUG(SW_NOR_FLASH, "PageProg %u byte", size);
    res= nor_flash_is_valid_addr(num,  phy_address);
	if(res) {
		res = false;
       	NorFlashItem_t* Node =NorFlashGetNode(  num);
       	if(Node){
            uint32_t i = 0 ;
            for(i=0;i<size;i++) {
                Node->memory[phy_address+i] = data[i] & Node->memory[phy_address+i];
                res = true;
            }
       	}else{
       		LOG_ERROR(SW_NOR_FLASH, "NodeError");
       	}
    }
    return res;
}

bool sw_nor_flash_write(uint8_t num,uint32_t phy_address, const uint8_t* const data, uint32_t size){
    bool res = false;
    LOG_DEBUG(SW_NOR_FLASH, "Write Addr 0x%08x=%u Size: %u Byte", phy_address, phy_address, size);
    res= nor_flash_is_valid_addr(num, phy_address);
	if(res) {
		res = false;
       	NorFlashItem_t* Node = NorFlashGetNode(  num);
       	if(Node){
            uint32_t i = 0 ;
            for(i=0; i<size; i++) {
                Node->memory[phy_address+i] = data[i] & Node->memory[phy_address+i];
                res = true;
            }
            res = nor_flash_verify(num,  phy_address,  data, size);
            if(false==res){
            	LOG_ERROR(SW_NOR_FLASH, "VeryfyError");
            }
       	}else{
       		LOG_ERROR(SW_NOR_FLASH, "NodeError");
       	}
    }
    return res;
}

bool sw_nor_flash_erase_mem(uint8_t num,uint32_t phy_address, uint32_t size){
    bool res = false;
    LOG_DEBUG(SW_NOR_FLASH, "Errase  0x%08x...0x%08x Size: %u Byte", phy_address, phy_address+size, size);
    res= nor_flash_is_valid_addr(num, phy_address);
    if(res){
    	res = false;
    	NorFlashItem_t* Node =NorFlashGetNode(  num);
    	if(Node){
    		if(Node->memory){

                memset( &Node->memory[phy_address], 0xFF, size);
                res = true;
    		}
    	}
    }
    return res;
}

bool sw_nor_flash_zero(uint8_t num,uint32_t phy_address, uint32_t size) {
    bool res = false;
    LOG_DEBUG(SW_NOR_FLASH, "Zero 0x%08x=%u Size: %u Byte", phy_address, phy_address, size);
    res= nor_flash_is_valid_addr(num, phy_address);
	if (res) {
		NorFlashItem_t* Node =NorFlashGetNode(  num);
		if(Node){

          memset( &Node->memory[phy_address], 0, size);
          res = nor_flash_verify_zero(num, phy_address, size);
		}
    }
    return res;
}

bool sw_nor_flash_init(uint8_t num) {
    bool res = true;
    LOG_WARNING(SW_NOR_FLASH, "Init");
    set_log_level(SW_NOR_FLASH, LOG_LEVEL_INFO);

    res = sw_nor_flash_erase_chip(num);
    //set_log_level(SW_NOR_FLASH, LOG_LEVEL_INFO);
    return res;
}
