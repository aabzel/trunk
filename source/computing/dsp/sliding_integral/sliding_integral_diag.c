#include "sliding_integral_diag.h"

#include <stdio.h>
#include <string.h>

#include "circular_buffer_index.h"
#include "log.h"
#include "num_to_str.h"
#include "sliding_integral.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_PC
#include "win_utils.h"
#endif

bool sliding_integral_expract_mem(uint8_t num, uint32_t need, double* const value) {
    bool res = false;
    LOG_DEBUG(SLIDING_INTEGRAL, "Need %u", need);
    SlidingIntegralHandle_t* Node = SlidingIntegralGetNode(num);
    if(Node) {
        uint32_t ind = circular_buffer_index_get_i(&Node->indexer, Node->indexer.size - 1 - need);
        if(value) {
            LOG_DEBUG(SLIDING_INTEGRAL, "Need: %u Phy:%u Val:%f", need, ind, Node->x[ind]);
            *value = Node->x[ind];
            res = true;
        }
    }
    return res;
}

bool SlidingIntegralDiagConfig(const SlidingIntegralConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(SLIDING_INTEGRAL, "N:%u,Order:%u [%s]", Config->num, Config->size, Config->name);
        res = true;
    }
    return res;
}

#ifdef HAS_PC
#define SLIDING_INTEGRAL_STRUCTURE_FILE "SlidingIntegralStructure.gv"
#define RENDER "C:/Program Files/Google/Chrome/Application/chrome.exe"

#define NODE_X_STEP 3
#define NODE_Y_STEP 3
#define NODE_ROOT 2
#endif

#ifdef HAS_PC
bool sliding_integral_node_generate_graphviz(SlidingIntegralHandle_t* Node, FILE* FilePtr, int x, int y, char* lText,
                                             double val) {
    bool res = false;
    fprintf(FilePtr, "%s [label=%f][pos=\"%d,%d!\"]\n", lText, val, x, y);
    return res;
}
#endif

bool sliding_integral_diag(uint8_t num) {
    bool res = false;
    SlidingIntegralHandle_t* Node = SlidingIntegralGetNode(num);
    if(Node) {
        circular_buffer_index_diag(&Node->indexer);

        static const table_col_t cols[] = {{5, "i"}, {5, "i+1"}, {8, "RawX"}, {8, "PhyIdx"}, {8, "X[i]"}, {8, "Mult"}};
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        char log_line[150];
        double mult = 0.0;
        double x_in = 0.0;
        double sum = 0.0;
        double xi = 0.0;
        uint32_t phy_index = 0;

        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %3d " TSEP, log_line, -1);
        snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, 0);
        snprintf(log_line, sizeof(log_line), "%s %6s " TSEP, log_line, "---");
        snprintf(log_line, sizeof(log_line), "%s %6s " TSEP, log_line, "---");
        snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, x_in);
        cli_printf("%s" CRLF, log_line);
        sum += mult;
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint32_t i = 0;
        for(i = 0; i < Node->size - 1; i++) {
            phy_index = circular_buffer_index_calc_phy_index(Node->indexer.size, Node->indexer.cur, i);
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i + 1);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, Node->x[i]);
            snprintf(log_line, sizeof(log_line), "%s %6u " TSEP, log_line, phy_index);
            xi = 0.0;
            sliding_integral_expract_mem(num, i, &xi);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, xi);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, mult);
            cli_printf("%s" CRLF, log_line);
            res = true;
            sum += mult;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        cli_printf("Out: %f" CRLF, sum);
    }

    return res;
}

bool sliding_integral_diag_raw_mem(uint8_t num) {
    bool res = false;
    SlidingIntegralHandle_t* Node = SlidingIntegralGetNode(num);
    if(Node) {
        circular_buffer_index_diag(&Node->indexer);
        static const table_col_t cols[] = {{5, "i"}, {8, "RawX"}};
        char log_line[150] = "";

        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint32_t i = 0;
        for(i = 0; i < Node->size - 1; i++) {
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, Node->x[i]);
            cli_printf("%s" CRLF, log_line);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

bool sliding_integral_diag_mem(uint8_t num) {
    bool res = false;
    SlidingIntegralHandle_t* Node = SlidingIntegralGetNode(num);
    if(Node) {
        LOG_INFO(SLIDING_INTEGRAL, "SLIDING_INTEGRAL%u,ProcCnt:%u", num, Node->proc_cnt);
        circular_buffer_index_diag(&Node->indexer);
        static const table_col_t cols[] = {
            {5, "i"},
            {8, "x[i]"},
            {5, "cur"},
            {8, "X[i]"},
        };
        uint32_t i = 0;
        char log_line[150];

        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        for(i = 0; i < Node->size - 1; i++) {
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, Node->x[i]);
            snprintf(log_line, sizeof(log_line), "%s %3s " TSEP, log_line, (i == Node->indexer.cur) ? "*" : " ");
            double x = 0.0;
            sliding_integral_expract_mem(num, i, &x);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, x);
            cli_printf("%s" CRLF, log_line);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

const char* SlidingIntegralNodeToStr(const SlidingIntegralHandle_t* const Node) {
    static char lText[300] = "?";
    strcpy(lText, "");
    if(Node) {
        snprintf(lText, sizeof(lText), "%sN:%u,", lText, Node->num);
        snprintf(lText, sizeof(lText), "%sInit:%u,", lText, Node->init);
        snprintf(lText, sizeof(lText), "%sM:%u", lText, Node->size);
        snprintf(lText, sizeof(lText), "%s/%u,", lText, Node->max_size);
        snprintf(lText, sizeof(lText), "%sFsam:%s Hz,", lText, DoubleToStr(Node->sample_rate_hz));
        snprintf(lText, sizeof(lText), "%sInCnt:%u", lText, Node->proc_cnt);
    }
    return lText;
}

const char* SlidingIntegralConfigToStr(const SlidingIntegralConfig_t* const Config) {
    static char lText[300] = "?";
    strcpy(lText, "");
    if(Config) {
        snprintf(lText, sizeof(lText), "%sN:%u,", lText, Config->num);
        snprintf(lText, sizeof(lText), "%sM:%u", lText, Config->size);
        snprintf(lText, sizeof(lText), "%s/%u,", lText, Config->max_size);
        snprintf(lText, sizeof(lText), "%sFsam:%s Hz,", lText, DoubleToStr(Config->sample_rate_hz));
    }
    return lText;
}
