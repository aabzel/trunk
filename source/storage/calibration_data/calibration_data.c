#include "calibration_data.h"


#include <stdbool.h>
#include <string.h>

#include "param_drv.h"
#include "crc8_autosar.h"
#include "log.h"
#include "at24cxx_drv.h"


#ifdef HAS_CALIBRATION_DATA_WRITE

bool calibration_data_erase(void) {
    bool res = false;
    res = at24cxx_erase(  CalibrationDataInstance.eeprom_num, 0, 256);
    if (res) {
        LOG_DEBUG(CALIBRATION_DATA,"Eeprom_%u EraseOk", CalibrationDataInstance.eeprom_num);
    } else {
        LOG_ERROR(CALIBRATION_DATA,"Eeprom_%u EraseErr", CalibrationDataInstance.eeprom_num);
        res = false;
    }
    return res;
}

bool calibration_data_set(const void* const data){
    bool res = false;
    if(data) {
        res= at24cxx_write(CalibrationDataInstance.eeprom_num, 0, data, 256);
        if (res) {
            LOG_DEBUG(CALIBRATION_DATA,"Eeprom_%u WriteOk",CalibrationDataInstance.eeprom_num);
        } else {
            LOG_ERROR(CALIBRATION_DATA,"Eeprom_%u WriteErr",CalibrationDataInstance.eeprom_num);
            res = false;
        }
    }
    return res;
}
#endif


bool calibration_data_get(void* const data){
    bool res = false;
    if(data){
        CalibrationData_t* pData=(CalibrationData_t* )data;
        res = at24cxx_read( CalibrationDataInstance.eeprom_num , 0, pData->buff, 256);
        if (res) {
            uint8_t calc_crc8=crc8_autosar_calc(pData->buff, 255);
            if (calc_crc8==pData->crc8) {
                LOG_INFO(CALIBRATION_DATA,"CRC Ok");
                res = true;
            } else {
                res = false;
                LOG_ERROR(CALIBRATION_DATA,"CRC8 Discrepancy! Calc:%x, Read:%x",calc_crc8,pData->crc8);
            }
        } else {
            LOG_ERROR(CALIBRATION_DATA,"Eeprom_%u ReadErr",CalibrationDataInstance.eeprom_num);
            res = false;
        }
    }

    return res;
}

bool calibration_data_valid(const CalibrationData_t* const Data ){
    bool res = false;
    if(Data){
        if(CALIB_DATA_VER1==Data->version){
            res = true;
        }
    }
    return res;
}

bool calibration_data_init(void){
    bool res = false;
    LOG_WARNING(CALIBRATION_DATA,"Init");
    CalibrationDataInstance.eeprom_num = CalibrationDataConfig.eeprom_num;
    CalibrationDataInstance.valid = true;
    CalibrationDataInstance.init = true;

    CalibrationData_t Data = {0};
    memset(Data.buff, 0, sizeof(CalibrationData_t));
    res = calibration_data_get(Data.buff);
    if (res) {
          LOG_INFO(CALIBRATION_DATA,"SpotCalibData %s",CalibrationData2Str(&Data ));
          res = calibration_data_valid(&Data);
          if(res) {
              res = param_set_lazy(PAR_ID_DECAWAVE_ID,&Data.decawave_address);
          }else{
              LOG_ERROR(CALIBRATION_DATA,"Invalid");
          }
    } else {
        LOG_ERROR(CALIBRATION_DATA,"ReadErr");
        res = false;
    }

    return res;
}
