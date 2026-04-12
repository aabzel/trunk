#include "memory_manager_cli.h"

#include "memory_manager.h"
#include "memory_manager_diagnostic.h"
#include "array_diag.h"
#include "mcal_to_ehal.h"
#include "convert.h"
#include "mcal_diag.h"
#include "log.h"

bool memory_manager_init_cli(int32_t argc, char* argv[]){
    bool res = false;
    MEMMAN_Init();
    LOG_INFO(MEMORY_MANAGER, "Init");
    res = true;
    return res;
}

/*mmbd*/
bool memory_manager_bank_diag_cli(int32_t argc, char* argv[]){
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        STD_RESULT ret = MEMORY_MANAGER_BankDiag();
        res = EHAL_RetToRes(ret);
        log_res(MEMORY_MANAGER, res, "BankDiag");
    } else {
        LOG_ERROR(MEMORY_MANAGER, "ParseErr mmbd");
    }
    return res;
}
/*
  mmdi
 * */
bool memory_manager_diag_cli(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t memoryBankCnt = 7;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &memoryBankCnt);
        if(false == res) {
            LOG_ERROR(MEMORY_MANAGER, "ParseErr memoryBankCnt");
        }
    }

    if(res) {
        STD_RESULT ret = MEMORY_MANAGER_Diag((U8) memoryBankCnt);
        res = EHAL_RetToRes(ret);
        log_res(MEMORY_MANAGER, res, "Diag");
    }
    return res;
}

bool memory_manager_dump_cli(int32_t argc, char* argv[]){ return false;}
bool memory_manager_erase_cli(int32_t argc, char* argv[]){ return false;}


/*
  mmr 1  0 20
  mmr 1  0 10
  mmr 1  0 5
  mmr 1  0 3
  mmr 1  0 4
    mmr 3  0 4
    mmr 8  0 4
  mmr 1  1 3
  mmr 1  1 6
 */
bool memory_manager_read_cli(int32_t argc, char* argv[]){
    // Loads data from the specified logical memory bank
    bool res = false;
    uint8_t memoryBank = 0;
    uint32_t addressOffset = 0;
    uint32_t dataQty = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &memoryBank);
        if(false == res) {
            LOG_ERROR(MEMORY_MANAGER, "ParseErr memoryBank");
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &addressOffset);
        if(false == res) {
            LOG_ERROR(MEMORY_MANAGER, "ParseErr addressOffset");
        }
    }


    if(3 <= argc) {
        res = try_str2uint32(argv[2], &dataQty);
        if(false == res) {
            LOG_ERROR(MEMORY_MANAGER, "ParseErr dataQty");
        }
    }


    if(res) {
        STD_RESULT ret = RESULT_NOT_OK;
        LOG_INFO(MEMORY_MANAGER, "Read Addr %u Size %u", addressOffset, dataQty);
        cli_printf(CRLF);
        uint32_t i = 0;
        uint32_t okCnt = 0;
        for(i = 0; i < dataQty; i++) {
            U32 nSourceAddress = addressOffset + i;
            U8 readVal = 0;
            ret = MEMMAN_Load((U8) memoryBank,  nSourceAddress, &readVal, 1);
            res = EHAL_RetToRes(ret);
            if(RESULT_OK==ret) {
                cli_printf("%02X", readVal);
                okCnt++;
            } else {
                log_res(MEMORY_MANAGER, res, "Read");
                LOG_ERROR(MEMORY_MANAGER, "SourceAddress,0x%x ReadErr", nSourceAddress);
            }
        }

        cli_printf(CRLF);
        res = McalOkCntToRes(okCnt, dataQty);

    }else{
        LOG_ERROR(MEMORY_MANAGER, "ParseErr mmr memoryBank addressOffset dataQty");
    }

    return res;
}

bool memory_manager_write_cli(int32_t argc, char* argv[]){
    bool res = false;

    uint8_t memoryBank = 0;
    uint32_t addressOffset = 0;
    size_t dataQty = 0;
    uint8_t array[256] = {0};
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &memoryBank);
        if(false == res) {
            LOG_ERROR(MEMORY_MANAGER, "ParseErr memoryBank [%s]",argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &addressOffset);
        if(false == res) {
            LOG_ERROR(MEMORY_MANAGER, "ParseErr addressOffset [%s]", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2array(argv[2], array, sizeof(array), &dataQty);
        if(false == res) {
            LOG_ERROR(MEMORY_MANAGER, "ParseErr array [%s]", argv[2]);
        }
    }


    if(res) {
        STD_RESULT ret = RESULT_NOT_OK;
        res = print_hex(array, (uint32_t) dataQty);
        // Stores data to the specified logical memory bank
        ret = MEMMAN_Store((U8)  memoryBank, (U32) addressOffset,
                                       (U8*) array,
                                       (U32) dataQty);
        res = EHAL_RetToRes(ret);
        log_res(MEMORY_MANAGER, res, "Write");
    }else {
        LOG_ERROR(MEMORY_MANAGER, "ParseErr mmw memoryBank addressOffset DataHexArray");
    }

    return res;
}
