#include "accelerometer_cli.h"

#include "accelerometer.h"
#include "vector_diagnostic.h"
#include "convert.h"
#include "accelerometer_diagnostic.h"
#include "mcal_to_ehal.h"
#include "log.h"
#include "vector_cli.h"


bool ACCEL_SaveCalibrateDataCommand(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t accelNum = 1;
    STD_RESULT ret = RESULT_NOT_OK;
    ACCEL_CALIB_DATA CalibrationData={0};

    if(7 <= argc){
        res = try_str2uint8(argv[0], &accelNum);
        log_res(SYS,res,"Num");
        ret = VECTOR_ReadVfromCli(argc, argv, 1, &CalibrationData.offset);
        log_res(SYS,res,"Offset");
        ret = VECTOR_ReadVfromCli(argc, argv, 4, &CalibrationData.scale);
        log_res(SYS,res,"Scale");
    }

    if(res) {
    	ret = ACCEL_SaveCalibData((U8) accelNum, &CalibrationData);
    	res = EHAL_RetToRes(ret);
        log_res(SYS,res,"CalibSave");
    }else{
 	   LOG_ERROR(SYS, "Usage: eacs AccleNum OffsetX OffsetY OffsetZ ScaleX ScaleY ScaleZ");
    }

    return res;
}


bool ACCEL_GetCommand(int32_t argc, char* argv[])
{
    bool res = false;
    U8 accelNum = 1;
    if(1 <= argc)
    {
        res = try_str2uint8(argv[0], &accelNum);
        if(false == res)
        {
            LOG_ERROR(SYS, "ParseErr [%s]", argv[0]);
        }
    }

    ACCEL_HANDLE* Node = ACCEL_GetNode(accelNum);
    if(Node)
    {
        LOG_INFO(SYS, "Accel%u:%s", accelNum, VECTOR_fToStr((VECTOR_F*) &Node->Acceleration));
        res = true;
    } else {
    	res = false;
    }

    return res;
}

bool ACCEL_InitCommand(int32_t argc, char* argv[])
{
    bool res = false;
    if(0 <= argc)
    {
        res = true;
    }

    if(res)
    {
        STD_RESULT ret = RESULT_NOT_OK;
        ret = ACCEL_Init();
        res = EHAL_RetToRes(ret);
    }
    return res;
}

bool ACCEL_DiagCommand(int32_t argc, char* argv[])
{
    bool res = false;
    if(0 <= argc)
    {
        res = true;
    }

    if(res)
    {
        STD_RESULT ret = RESULT_NOT_OK;
        ret = ACCEL_Diag();
        res = EHAL_RetToRes(ret);
    }
    return res;
}


bool ACCEL_CalibrateCommand(int32_t argc, char* argv[])
{
    bool res = false;
    uint8_t accelNum = 1;
    uint8_t calibNum = 1;
    if(1 <= argc)
    {
        accelNum = 1;
        calibNum = 1;
        res = true;
    }

    if(1 <= argc)
    {
        res = try_str2uint8(argv[0], &accelNum);
        if(false == res)
        {
            LOG_ERROR(SYS, "ParseErr [%s]", argv[0]);
        }
    }
    if(2 <= argc)
    {
        res = try_str2uint8(argv[1], &calibNum);
        if(false == res)
        {
            LOG_ERROR(SYS, "ParseErr [%s]", argv[1]);
        }
    }

    if(res)
    {
        STD_RESULT ret = RESULT_NOT_OK;
        ret = ACCEL_DeployPyramidCalib(accelNum, calibNum);
        res = EHAL_RetToRes(ret);
        log_res(SYS , res, "AccelCalib");
    }else{
        LOG_ERROR(SYS, "Usage AccleNum CalibNum");
    }

    return res;
}
