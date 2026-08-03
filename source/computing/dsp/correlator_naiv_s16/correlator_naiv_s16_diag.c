#include "correlator_naiv_s16_diag.h"

#include <stdio.h>
#include <string.h>

#include "circular_buffer_index.h"
#include "correlator_naiv_s16.h"
#include "float_diag.h"
#include "log.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_PC
#include "win_utils.h"
#endif

bool correlator_naiv_s16_expract_mem(uint8_t num, uint32_t need, int16_t* const value) {
    bool res = false;
    LOG_DEBUG(CORRELATOR_NAIV_S16, "Need %u", need);
    CorrelatorNaivS16Handle_t* Node = CorrelatorNaivS16GetNode(num);
    if(Node) {
        if(value) {
            LOG_DEBUG(CORRELATOR_NAIV_S16, "Need: %u Val:%d", need, Node->x[need]);
            *value = Node->x[need];
            res = true;
        }
    }
    return res;
}

bool CorrelatorNaivS16DiagConfig(const CorrelatorNaivS16Config_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(CORRELATOR_NAIV_S16, "N:%u,Order:%u [%s]", Config->num, Config->size, Config->name);
        res = true;
    }
    return res;
}

#ifdef HAS_PC
#define CORRELATOR_NAIV_S16_STRUCTURE_FILE "CorrelatorNaivS16Structure.gv"
#define RENDER "C:/Program Files/Google/Chrome/Application/chrome.exe"

#define NODE_X_STEP 3
#define NODE_Y_STEP 3
#define NODE_ROOT 2
#endif

#ifdef HAS_PC
bool correlator_naiv_s16_node_generate_graphviz(CorrelatorNaivS16Handle_t* Node, FILE* FilePtr, int x, int y,
                                                char* lText, double val) {
    bool res = false;
    fprintf(FilePtr, "%s [label=%f][pos=\"%d,%d!\"]\n", lText, val, x, y);
    return res;
}
#endif

bool correlator_naiv_s16_generate_graphviz(uint8_t num) {
    bool res = false;
#ifdef HAS_PC
    CorrelatorNaivS16Handle_t* Node = CorrelatorNaivS16GetNode(num);
    if(Node) {
        int16_t in = 0.0;
        int64_t out = 0;
        res = correlator_naiv_s16_pull_ll(Node, in, &out);
        int16_t mult = 0;
        FILE* GvFilePtr = NULL;

        char GvFileName[80] = "";
        sprintf(GvFileName, "CorrelatorNaivS16%u_Code.gv", num);

        GvFilePtr = fopen(GvFileName, "w");
        if(GvFilePtr) {
            // int ret = 0;
            fprintf(GvFilePtr, "digraph CorrelatorNaivS16Filter {\n");
            fprintf(GvFilePtr, "    rankdir=TB\n");
            fprintf(GvFilePtr, "    splines=ortho\n");
            uint32_t i = 0;
            uint32_t x = 0;
            // uint32_t y = 0;
            uint32_t axis = (NODE_X_STEP * Node->size - 2) / 2;

            fprintf(GvFilePtr, "in [shape=point][pos =\"%d,%d!\"]\n", in, x - NODE_X_STEP, NODE_ROOT);
            fprintf(GvFilePtr, "X [label=\"X:%f\"] [shape=point][pos =\"%d,%d!\"]\n", in, x, NODE_ROOT);
            for(i = 0; i < Node->size - 1; i++) {
                x = NODE_X_STEP + NODE_X_STEP * i;
                fprintf(GvFilePtr, "X%u [label=\"X%u:%f\"] [shape=box][pos = \"%d,%d!\"]\n", i, i, Node->x[i], x,
                        NODE_ROOT);
            }

            fprintf(GvFilePtr, "B0 [label=\"B0:%f\"][shape=circle][pos=\"%d,%d!\"]\n", Node->ReferenceSignal[0], x,
                    NODE_ROOT + NODE_Y_STEP);
            for(i = 0; i < Node->size; i++) {
                x = NODE_X_STEP * i;
                fprintf(GvFilePtr, "B%u [label=\"B%u:%f\"] [shape=circle][pos = \"%d,%d!\"][color=red]\n", i, i,
                        Node->ReferenceSignal[i], x, NODE_ROOT + NODE_Y_STEP);
            }

            fprintf(GvFilePtr, "Sum [label=\"+\"][shape=ellipse][pos = \"%d,%d!\"]\n", axis,
                    NODE_ROOT + 2 * NODE_Y_STEP);
            fprintf(GvFilePtr, "Y [label=Y][label=%f] [pos =\"%d,%d!\"]\n", out, axis, NODE_ROOT + 3 * NODE_Y_STEP);

            /*Connections*/
            mult = Node->ReferenceSignal[0] * in;
            fprintf(GvFilePtr, "X->B0 [label=%f][color=red]\n", mult);
            fprintf(GvFilePtr, "B0->Sum[color = red]\n");
            fprintf(GvFilePtr, "in->X[color =black]\n");

            for(i = 0; i < Node->size - 1; i++) {
                fprintf(GvFilePtr, "X%u->B%u [label=%f] [color = red]\n", i, i + 1, Node->ReferenceSignal[i + 1]);
                double mult_xb = Node->x[i] * Node->ReferenceSignal[i + 1];
                fprintf(GvFilePtr, "B%u->Sum[label=%f][color = red]\n", i + 1, mult_xb);
            }

            fprintf(GvFilePtr, "X->X0 [color =blue]\n");
            for(i = 0; i < Node->size - 2; i++) {
                fprintf(GvFilePtr, "X%u->X%u [color =blue]\n", i, i + 1);
            }

            fprintf(GvFilePtr, "Sum->Y[color = red]\n");
            fprintf(GvFilePtr, "}\n");
            fclose(GvFilePtr);

            char CmdCommand[200] = "";
            char SvgFileName[200] = "";

            sprintf(SvgFileName, "CorrelatorNaivS16_%u_Schematic.svg", num);

            sprintf(CmdCommand, "start dot.exe -Kneato -Tsvg %s -o %s", GvFileName, SvgFileName);
            res = win_cmd_run(CmdCommand);
            // res = win_cmd_run("start chrome.exe -open out.svg");
            sprintf(CmdCommand, "start \"%s\" -open %s", RENDER, SvgFileName);
            // res = win_cmd_run(CmdCommand);
        } else {
            LOG_ERROR(CORRELATOR_NAIV_S16, "FileGenerateErr");
        }
    } else {
        LOG_ERROR(CORRELATOR_NAIV_S16, "NodeErr");
    }
#endif

    return res;
}

bool correlator_naiv_s16_diag(uint8_t num) {
    bool res = false;
    CorrelatorNaivS16Handle_t* Node = CorrelatorNaivS16GetNode(num);
    if(Node) {

        static const table_col_t cols[] = {{5, "i"},    {5, "i+1"},    {8, "RawX"}, {8, "PhyIdx"},
                                           {8, "X[i]"}, {8, "B[i+1]"}, {8, "Mult"}};
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        char log_line[150];
        double mult = 0.0;
        double x_in = 0.0;
        double sum = 0.0;
        int16_t xi = 0.0;
        uint32_t phy_index = 0;

        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %3d " TSEP, log_line, -1);
        snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, 0);
        snprintf(log_line, sizeof(log_line), "%s %6s " TSEP, log_line, "---");
        snprintf(log_line, sizeof(log_line), "%s %6s " TSEP, log_line, "---");
        snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, x_in);
        snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, Node->ReferenceSignal[0]);
        mult = x_in * Node->ReferenceSignal[0];
        snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, mult);
        cli_printf("%s" CRLF, log_line);
        sum += mult;
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint32_t i = 0;
        for(i = 0; i < Node->size - 1; i++) {
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i + 1);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, Node->x[i]);
            snprintf(log_line, sizeof(log_line), "%s %6u " TSEP, log_line, phy_index);
            xi = 0;
            correlator_naiv_s16_expract_mem(num, i, &xi);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, xi);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, Node->ReferenceSignal[i + 1]);
            mult = xi * Node->ReferenceSignal[i + 1];
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

bool correlator_naiv_s16_diag_raw_mem(uint8_t num) {
    bool res = false;
    CorrelatorNaivS16Handle_t* Node = CorrelatorNaivS16GetNode(num);
    if(Node) {
        static const table_col_t cols[] = {
            {5, "i"}, {8, "RawX"}, {8, "Ref"}, {8, "Mux"}, {8, "Sum"},
        };

        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint32_t i = 0;
        uint32_t sum = 0;
        for(i = 0; i < Node->size; i++) {
            int16_t mux = Node->x[i] * Node->ReferenceSignal[i];
            sum += mux;
            char log_line[150] = "";
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
            snprintf(log_line, sizeof(log_line), "%s %6d " TSEP, log_line, Node->x[i]);
            snprintf(log_line, sizeof(log_line), "%s %6d " TSEP, log_line, Node->ReferenceSignal[i]);
            snprintf(log_line, sizeof(log_line), "%s %6d " TSEP, log_line, mux);
            snprintf(log_line, sizeof(log_line), "%s %6d " TSEP, log_line, sum);
            cli_printf("%s" CRLF, log_line);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

bool correlator_naiv_s16_diag_mem(uint8_t num) {
    bool res = false;
    CorrelatorNaivS16Handle_t* Node = CorrelatorNaivS16GetNode(num);
    if(Node) {
        LOG_INFO(CORRELATOR_NAIV_S16, "CORRELATOR_NAIV_S16%u,ProcCnt:%u", num, Node->proc_cnt);
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
            snprintf(log_line, sizeof(log_line), "%s %6d " TSEP, log_line, Node->x[i]);
            int16_t x = 0;
            correlator_naiv_s16_expract_mem(num, i, &x);
            snprintf(log_line, sizeof(log_line), "%s %6d " TSEP, log_line, x);
            cli_printf("%s" CRLF, log_line);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

const char* CorrelatorNaivS16NodeToStr(const CorrelatorNaivS16Handle_t* const Node) {
    static char lText[300] = "?";
    if(Node) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%sN:%u,", lText, Node->num);
        snprintf(lText, sizeof(lText), "%sInit:%u,", lText, Node->init);
        snprintf(lText, sizeof(lText), "%sM:%u", lText, Node->size);
        snprintf(lText, sizeof(lText), "%s/%u,", lText, Node->max_size);
        snprintf(lText, sizeof(lText), "%sFsam:%s Hz,", lText, FloatToStr(Node->sample_rate_hz, 1));
        snprintf(lText, sizeof(lText), "%sInCnt:%u", lText, Node->proc_cnt);
    }
    return lText;
}

const char* CorrelatorNaivS16ConfigToStr(const CorrelatorNaivS16Config_t* const Config) {
    static char lText[300] = "?";
    if(Config) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%sN:%u,", lText, Config->num);
        snprintf(lText, sizeof(lText), "%sM:%u", lText, Config->size);
        snprintf(lText, sizeof(lText), "%s/%u,", lText, Config->max_size);
        snprintf(lText, sizeof(lText), "%sFsam:%s Hz,", lText, FloatToStr(Config->sample_rate_hz, 2));
    }
    return lText;
}
