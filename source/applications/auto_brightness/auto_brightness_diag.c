#include "auto_brightness_diag.h"

#include <stdio.h>
#include <string.h>

#include "table_utils.h"
#include "log.h"
#include "auto_brightness.h"
#include "auto_brightness_config.h"
#include "writer_config.h"

bool AutoBrightnessDiagConfig(const AutoBrightnessConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(AUTO_BRIGHTNESS, "DecaWave:%u, PWM:%u, PwmFreq %u Hz",
                Config->dist_num,
                Config->pwm_num,
                Config->pwm_freq_hz);
        res = true;
    }

    return res;
}

char const* AutoBrightnessNode2Str(const AutoBrightnessHandle_t* const Node){
	static char text[80] = "";
	snprintf(text, sizeof(text), "PWM%u, Dist:%u, Duty:%6.2f %%, PwmFreq %u Hz, Dist %6.2f m, Err %u",
            Node->pwm_num,
            Node->dist_num,
            Node->duty_cycle,
            Node->pwm_freq_hz,
            Node->distance_m,
            Node->err_cnt);
	return text;
}

bool AutoBrightnessDiagNode(const AutoBrightnessHandle_t* const Node){
    bool res = false;
    if(Node){
        LOG_INFO(AUTO_BRIGHTNESS, "%s", AutoBrightnessNode2Str(Node));
        res = true;
    }

    return res;
}

bool auto_brightness_diag(void) {
    bool res = false;
    LOG_INFO(AUTO_BRIGHTNESS, "Diag");
    static const table_col_t cols[] = {
            {5, "No"},
            {9, "DistNum"},
            {5, "PWM"},
            {6, "Freq"},
            {8, "Dist"},
            {8, "Duty"},
            {5, "bin"},
            {5, "Err"},
    };
    uint32_t i=0;
    uint32_t cnt =auto_brightness_get_cnt();
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    char log_line[150];
    for(i=0; i<=cnt; i++) {
        AutoBrightnessHandle_t* Node = AutoBrightnessGetNode(i);
        if(Node) {
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->num);
            snprintf(log_line, sizeof(log_line), "%s %7u " TSEP, log_line, Node->dist_num);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->pwm_num);
            snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, Node->pwm_freq_hz);
            snprintf(log_line, sizeof(log_line), "%s %6.2f " TSEP, log_line, Node->distance_m);
            snprintf(log_line, sizeof(log_line), "%s %6.2f " TSEP, log_line, Node->duty_cycle);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->binary);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->err_cnt);
            cli_printf("%s" CRLF, log_line);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}


