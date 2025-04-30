#include "test_calibration_data.h"


#include "log.h"
#include "unit_test_check.h"
#include "calibration_data.h"


bool test_calibration_data_types(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    set_log_level(CALIBRATION_DATA,LOG_LEVEL_DEBUG);

    ASSERT_EQ(256,sizeof(CalibrationData_t));

    set_log_level(CALIBRATION_DATA,LOG_LEVEL_INFO);
    return true;
}



bool test_calibration_data_read(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(CALIBRATION_DATA, LOG_LEVEL_DEBUG);

	CalibrationData_t Data = {0};
    ASSERT_TRUE( calibration_data_get(Data.buff));
 	LOG_INFO(CALIBRATION_DATA,"[%s]",CalibrationData2Str(&Data ));


    set_log_level(CALIBRATION_DATA,LOG_LEVEL_INFO);
    return true;
}

