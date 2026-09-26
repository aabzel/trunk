#include "light_sensor_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "log_utils.h"
#include "light_sensor_drv.h"
#include "data_utils.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

bool light_sensor_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
        uint32_t i = 0;
        static const table_col_t cols[] = {
                {4, "No"},
                {7, "name"}
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint32_t cnt = light_sensor_get_cnt();
        for(i=0; i<=cnt; i++){
            LightSensorHandle_t* Node=LightSensorGetNode(i);
            if(Node){
                cli_printf(TSEP " %2u " TSEP, i);
                const LightSensorConfig_t* LightSensorConfNode = LightSensorGetConfigNode(i);
                if (LightSensorConfNode) {
                    cli_printf(" %5s " TSEP, LightSensorConfNode->name);
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



bool light_sensor_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1<=argc){
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
             LOG_ERROR(SYS, "ParseErr Num %s", argv[0]);
        }else{
        }
    }

    if(res){
    	res=light_sensor_init_one(num );
    }
    return res;
}
