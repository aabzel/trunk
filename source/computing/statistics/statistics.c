#include "statistics.h"

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"
#include "file_api.h"
#include "float_utils.h"
#include "log.h"
#include "statistics_diag.h"
#ifdef HAS_MATH
#include "utils_math.h"
#endif

RandomVariable_t RandomVariable = {
    .value = NULL,
    .size = 0,
};

bool statistics_expected_value(RandomVariable_t* const Node) {
    bool res = false;
    if(Node) {
        uint32_t i = 0;
        Node->sum = 0.0;
        Node->min = DBL_MAX;
        Node->max = DBL_MIN;
        for(i = 0; i < Node->size; i++) {
            Node->min = MIN(Node->min, Node->value[i]);
            Node->max = MAX(Node->max, Node->value[i]);
            Node->sum += Node->value[i];
        }
        Node->spread = Node->max - Node->min;
        Node->expected_value = Node->sum / Node->size;
        LOG_INFO(STATISTICS, "ExpectedValue %f", Node->expected_value);
        LOG_INFO(STATISTICS, "MIN: %f, MAX: %f, Spread:%f", Node->min, Node->max, Node->spread);

        res = true;
    }
    return res;
}

#define POW_TWO(ARG) ((ARG) * (ARG))

bool statistics_standard_deviation(RandomVariable_t* const Node) {
    bool res = false;
    if(Node) {
        uint32_t i = 0;
        double sum_of_squares = 0.0;
        for(i = 0; i < (Node->size); i++) {
            sum_of_squares += POW_TWO(Node->value[i] - Node->expected_value);
        }
        Node->variance = sum_of_squares / (Node->size - 1);
        LOG_INFO(STATISTICS, "Variance: %f", Node->variance);
        Node->standard_deviation = sqrt(Node->variance);
        LOG_INFO(STATISTICS, "StandardDeviation %f", Node->standard_deviation);
        res = true;
    }
    return res;
}


/*
 * column-the number of the column we are analyzing
 * */
bool statistics_load(const char* const file_name, uint32_t column) {
    bool res = false;
    LOG_INFO(STATISTICS, "Load File[%s],Column %u", file_name, column);
    int32_t line_cnt = file_line_cnt(file_name);
    if(line_cnt) {
        LOG_INFO(STATISTICS, "File [%s] Contains %d lines", file_name, line_cnt);
        RandomVariable.size = 0;
        RandomVariable.value = (double*)malloc(sizeof(double) * line_cnt + 100);
        if(RandomVariable.value) {
            memset(&RandomVariable.value[0], 0, sizeof(double) * (line_cnt));
            LOG_INFO(STATISTICS, "MallocOK %u byte", sizeof(double) * line_cnt);
            res = true;
        } else {
            LOG_ERROR(STATISTICS, "MallocErr %u byte", sizeof(double) * line_cnt);
            res = false;
        }

        if(res) {
            FILE* file_prt = NULL;
            file_prt = fopen(file_name, "r");
            if(file_prt) {
                double single_value = 0.0;
                LOG_INFO(STATISTICS, "File [%s] OpenOk", file_name);
                int i = 1;
                char text_line[500]={0};
                strcpy(text_line, "");
                while(NULL != fgets(text_line, sizeof(text_line), file_prt)) {
                    LOG_PARN(STATISTICS, "%u:[%s]", i, text_line);

                    res = csv_parse_double(text_line, column, &single_value);
                    if(res) {
                        RandomVariable.value[i - 1] = single_value;
                        RandomVariable.size++;
                    } else {
                        LOG_ERROR(STATISTICS, "CSV,parse,Err[%s]", text_line);
                    }

                    i++;
                    cli_printf("\rLoad:%u/%u,Value:%f", i, line_cnt,single_value);
                }
                fclose(file_prt);
                cli_printf(CRLF);
                LOG_INFO(STATISTICS, "File [%s] %u Lines", file_name, line_cnt);
                LOG_INFO(STATISTICS, "File [%s] CloseOk", file_name);

            } else {
                LOG_ERROR(STATISTICS, "File [%s] OpenErr", file_name);
            }
        }
    } else {
        LOG_INFO(STATISTICS, "File [%s] empty", file_name);
    }
    return res;
}

static uint32_t statistics_value_to_interval(RandomVariable_t* const Node, double value) {
    uint32_t i = 0;

    bool res = is_double_equal_absolute(value, Node->min, 0.00001);
    if(res) {
        i = 0;
    }

    if(!res) {
        for(i = 0; i < Node->interanl_cnt; i++) {
            double middle = Node->min + Node->histogram_step / 2.0 + ((double)i) * (Node->histogram_step);
            res = is_double_equal_absolute(value, middle, Node->histogram_step / 2.0);
            if(res) {
                res = true;
                break;
            }
        }
    }

    if(!res) {
        res = is_double_equal_absolute(value, Node->max, 0.00001);
        if(res) {
            i = Node->interanl_cnt - 1;
        }
    }

    return i;
}

bool statistics_bar_chart_update(RandomVariable_t* const Node, double value) {
    bool res = false;
    uint32_t interval = 0;
    interval = statistics_value_to_interval(Node, value);
    if(interval <= Node->interanl_cnt) {
        Node->bar_chart[interval]++;
    }
    return res;
}

bool statistics_calc_bar_chart(RandomVariable_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(STATISTICS, "Intervals:%u", Node->interanl_cnt);
        Node->bar_chart = malloc(Node->interanl_cnt * (sizeof(uint32_t)));
        if(Node->bar_chart) {
            memset(Node->bar_chart, 0, Node->interanl_cnt * (sizeof(uint32_t)));
            Node->histogram_step = Node->spread / Node->interanl_cnt;
            LOG_INFO(STATISTICS, "Value,Step:%f", Node->histogram_step);
            uint32_t i = 0;
            for(i = 0; i < Node->size; i++) {
                res = statistics_bar_chart_update(Node, Node->value[i]);
            }
            res = statistics_bar_chart_diag(Node);
        }
    }
    return res;
}
