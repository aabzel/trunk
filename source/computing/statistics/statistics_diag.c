#include "statistics_diag.h"

#include <stdio.h>
#include <string.h>

#include "debug_info.h"
#include "log.h"
#include "statistics_types.h"
#include "table_utils.h"
#include "writer_config.h"

bool RandomVariableDiag(const RandomVariable_t* const Node) {
    bool res = false;
    if(Node) {
        static const table_col_t cols[] = {
            {5, "No"},
            {7, "value"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        char log_line[150];

        uint32_t i = 0;
        for(i = 0; i < Node->size; i++) {
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, i);
            snprintf(log_line, sizeof(log_line), "%s %f " TSEP, log_line, Node->value[i]);
            cli_printf("%s" CRLF, log_line);
            res = true;
        }

        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

bool statistics_bar_chart_diag(const RandomVariable_t* const Node) {
    bool res = false;
    if(Node) {
        static const table_col_t cols[] = {
            {5, "No"}, {9, "start"}, {9, "end"}, {7, "Cnt"}, {9, "%"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        char log_line[150];
        uint32_t i = 0;
        double total_probability = 0.0;
        for(i = 0; i < Node->interanl_cnt; i++) {
            double start = Node->min + Node->histogram_step * i;
            double end = start + Node->histogram_step;
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i + 1);
            snprintf(log_line, sizeof(log_line), "%s %7.3f " TSEP, log_line, start);
            snprintf(log_line, sizeof(log_line), "%s %7.3f " TSEP, log_line, end);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->bar_chart[i]);
            double local_probability = 100.0 * ((double)Node->bar_chart[i]) / ((double)Node->size);
            total_probability += local_probability;
            snprintf(log_line, sizeof(log_line), "%s %7.3f " TSEP, log_line, local_probability);
            cli_printf("%s" CRLF, log_line);
            res = true;
        }

        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        cli_printf("TotalProbability: %f %%" CRLF, total_probability);
    }

    return res;
}
