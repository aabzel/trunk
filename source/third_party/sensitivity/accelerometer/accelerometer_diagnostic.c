#include "accelerometer_diagnostic.h"

#include <stdio.h>
#include <string.h>

#include "accelerometer.h"
#include "vector_diagnostic.h"
#include "vector.h"
#include "accelerometer_configuration.h"
#include "miscellaneous_float.h"
#include "writer_config.h"
#include "table_utils.h"

const char* ACCEL_CalibDataToStr(ACCEL_CALIB_DATA* const CalibData)
{
    static char text[80] = "";
    if(CalibData)
    {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sOffset:%s,"CRLF, text, VECTOR_fToStr(&CalibData->offset));
        snprintf(text, sizeof(text), "%s Scale:%s", text, VECTOR_fToStr(&CalibData->scale));
    }
    return text;
}

const char* ACCEL_ConfigToStr(const ACCEL_CONFIG* const Config)
{
    static char text[80] = "";
    if(Config)
    {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sPHY:%u,", text, Config->accelPhy);
        snprintf(text, sizeof(text), "%sAnum:%u,", text, Config->accelNum);
        snprintf(text, sizeof(text), "%sName:%s", text, Config->name);
    }
    return text;
}

const char* ACCEL_NodeToStr(const ACCEL_HANDLE* const Node)
{
    static char text[80] = "";
    if(Node)
    {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sPHY:%u,", text, Node->accelPhy);
        snprintf(text, sizeof(text), "%sAnum:%u,", text, Node->accelNum);
        snprintf(text, sizeof(text), "%sAccel:%s", text, VECTOR_fToStr(&Node->Acceleration));
    }
    return text;
}

static const char* AccelNeedCalibToStr(const STD_RESULT isInPresition)
{
    char* name = "";
    switch(isInPresition)
    {
        case RESULT_OK: name = "No"; break;
        case RESULT_NOT_OK:name = "Yes"; break;
        default: break;
    }
    return name;
}

STD_RESULT ACCEL_DiagNode(ACCEL_HANDLE* const Node)
{
	STD_RESULT ret = RESULT_NOT_OK;
    if(Node)
    {
        ret = RESULT_OK;
        cli_printf("%s"CRLF, ACCEL_NodeToStr(Node));
    }

    return ret;
}

STD_RESULT ACCEL_DiagConfig(const ACCEL_CONFIG* const Config)
{
    STD_RESULT ret = RESULT_NOT_OK;
    if(Config)
    {
        cli_printf("%s"CRLF, ACCEL_ConfigToStr(Config));
        ret = RESULT_OK;
    }

    return ret;
}

STD_RESULT ACCEL_Diag(void)
{
    STD_RESULT retStat = RESULT_NOT_OK;
    static const table_col_t cols[] = {
        { 4, "No" },
        { 8, "X,g" },   { 8, "Y,g" },   { 8, "Z,g" },
        { 8, "Abs,g" },
        { 8, "preci,g" },
        { 10, "NeedCalib" },
    };

    char text[120] = "";
    table_header(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));
    U32 cnt = ACCEL_GetCnt()+5;
    U32 i = 0;
    for (i = 0; i <= cnt; i++)
    {
        ACCEL_HANDLE* Node = ACCEL_GetNode(i);
        if (NULL_PTR != Node)
        {
            FLOAT32 accelAbs = VECTOR_CalcNormF(&Node->Acceleration);
            strcpy(text, TSEP);
            snprintf(text, sizeof(text), "%s %2u " TSEP, text, i);
            snprintf( text, sizeof(text), "%s %6.2f " TSEP, text, Node->Acceleration.dx);
            snprintf( text, sizeof(text), "%s %6.2f " TSEP, text, Node->Acceleration.dy);
            snprintf( text, sizeof(text), "%s %6.2f " TSEP, text, Node->Acceleration.dz);
            snprintf( text, sizeof(text), "%s %6.2f " TSEP, text, accelAbs);
            snprintf( text, sizeof(text), "%s %6.3f " TSEP, text, Node->precision);
            STD_RESULT ret = FLOAT_IsEqualAbsolute(1.0, accelAbs, Node->precision);
            snprintf( text, sizeof(text), "%s %8s " TSEP, text, AccelNeedCalibToStr(ret));
            cli_printf("%s" CRLF, text);
            retStat = RESULT_OK;

        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, SIZE_OF_ARRAY(cols));

    return retStat;
}
