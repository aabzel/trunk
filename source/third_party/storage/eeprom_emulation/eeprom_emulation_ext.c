#include "eeprom_emulation_ext.h"

#include "eeprom_emulation.h"

STD_RESULT EMEEP_Erase(const U32 sourceAddress,
                       const U32 size) {
    STD_RESULT ret = RESULT_NOT_OK;
    U32 curAddr = 0 ;
    U32 okCnt = 0 ;
    for(curAddr=sourceAddress; curAddr<(sourceAddress+size); curAddr++)
    {
        U8 DataWrite = 0xFF;
        ret = EMEEP_Store(curAddr, &DataWrite, 1);
        if(RESULT_OK==ret)
        {
            okCnt++;
        }
    }

    if(size==okCnt)
    {
        ret = RESULT_OK;
    } else
    {
        ret = RESULT_NOT_OK;
    }
    return ret;
}
