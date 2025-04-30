#include "light_sensor_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "gpio_diag.h"
#include "log_utils.h"
#include "led_drv.h"
#include "data_utils.h"
#include "led_config.h"
#include "log.h"

#ifdef HAS_LIGHT_SENSOR_DIAG
#include "led_diag.h"
#endif

#include "table_utils.h"
#include "writer_config.h"

bool light_sensor_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
        uint32_t i = 0;
        static const table_col_t cols[] = {
                {4, "No"},
                {7, "mode"},
                {6, "period"},
                {5, "duty"},
                {6, "phase"},
                {6, "active"},
                {7, "name"}
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint32_t cnt = light_sensor_get_cnt();
        for(i=0; i<=cnt; i++){
            LedHandle_t* LedNode=LedGetNode(i);
            if(LedNode){
                cli_printf(TSEP " %2u " TSEP, i);
#ifdef HAS_LIGHT_SENSOR_DIAG
                cli_printf(  " %5s " TSEP, LedMode2Str(LedNode->mode));
#else /*HAS_LIGHT_SENSOR_DIAG*/
                cli_printf(  " %5u " TSEP, LedNode->mode);
#endif /*HAS_LIGHT_SENSOR_DIAG*/
                cli_printf(  " %4u " TSEP, LedNode->period_ms);
                cli_printf(" %3u " TSEP, LedNode->duty);
                cli_printf(" %4u " TSEP, LedNode->phase_ms);
                cli_printf(" %4s " TSEP, GpioLevel2Str(LedNode->active));
                const LedConfig_t* LedConfNode = LedGetConfigNode(i);
                if (LedConfNode) {
                    cli_printf(" %5s " TSEP, LedConfNode->name);
                }
                cli_printf( CRLF);
            }
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    } else {
        LOG_ERROR(LIGHT_SENSOR, "Usage: lmg");
    }
    return res;
}

bool light_sensor_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t led_num = 0;
    uint8_t in_duty = 0;
    LedHandle_t* LedNode = NULL;
    if(1<=argc){
        res = try_str2uint8(argv[0], &led_num);
        if(false == res) {
            LOG_ERROR(LIGHT_SENSOR, "Unable to extract Num %s", argv[0]);
        }else {
            LedNode = LedGetNode(led_num);
            if (LedNode) {
                LOG_INFO(LIGHT_SENSOR, "LedPtrOk!");
                res = true;
            }else{
                LOG_ERROR(LIGHT_SENSOR, "NoLedPtr%u");
                res = false;
            }
        }
    }

    if(2<=argc) {
        if(LedNode) {
            res = try_str2uint32(argv[1], &LedNode->period_ms);
            if(false == res) {
                LOG_ERROR(LIGHT_SENSOR, "Unable to extract period %s", argv[1]);
            }
        }
    }

    if(3<=argc) {
        if(LedNode) {
            res = try_str2uint8(argv[2], &in_duty);
            if(false == res) {
                LOG_ERROR(LIGHT_SENSOR, "Unable to extract duty %s", argv[2]);
            } else {
                if(in_duty<=100) {
                    LedNode->duty=in_duty;
                }
            }
        }
    }

    if(4 <= argc) {
        if(LedNode) {
            res = try_str2uint32(argv[3], &LedNode->phase_ms);
            if(false == res) {
                LOG_ERROR(LIGHT_SENSOR, "Unable to extract phase %s", argv[3]);
            }
        }
    }

    if(false==res) {
        LOG_ERROR(LIGHT_SENSOR, "Usage: lms num period_ms duty phase_ms");
        LOG_INFO(LIGHT_SENSOR, "period");
        LOG_INFO(LIGHT_SENSOR, "duty 0....100");
        LOG_INFO(LIGHT_SENSOR, "phase");
    }
    return res;
}

bool light_sensor_blink_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t led_num = 0;
    uint32_t duration_ms = 0;
    if(1<=argc){
        res = try_str2uint8(argv[0], &led_num);
        if(false == res) {
             LOG_ERROR(LIGHT_SENSOR, "Unable to extract Num %s", argv[0]);
        }
    }
    if(2<=argc){
            res = try_str2uint32(argv[1], &duration_ms);
            if(false == res) {
                LOG_ERROR(LIGHT_SENSOR, "Unable to extract duration_ms %s", argv[1]);
            }
    }

    if(res){
        res = light_sensor_blink(led_num, duration_ms);
        if(res){
            LOG_INFO(LIGHT_SENSOR, "Ok");
        }
    }

    if(false==res){
        LOG_ERROR(LIGHT_SENSOR, "Usage: lmb num duration_ms");
    }
    return res;
}

bool light_sensor_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t light_sensor_num = 0;
    if(1<=argc){
        res = try_str2uint8(argv[0], &light_sensor_num);
        if(false == res) {
             LOG_ERROR(SYS, "ParseErr Num %s", argv[0]);
        }else{
        }
    }

    if(res){
    	res=light_sensor_init_one(light_sensor_num );
    }
    return res;
}
