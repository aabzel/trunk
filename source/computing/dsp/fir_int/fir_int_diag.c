#include "fir_int_diag.h"

#include <stdio.h>
#include <string.h>

#include "fir_int.h"
#include "log.h"
#ifdef HAS_PC
#include "win_utils.h"
#endif
#include "circular_buffer_index.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "writer_config.h"

bool fir_int_expract_mem(uint8_t num, CircularBufferIndex_t need, double* const value) {
    bool res = false;
    LOG_DEBUG(FIR_INT, "Need %u", need);
    FirIntHandle_t* Node = FirIntGetNode(num);
    if(Node) {
        CircularBufferIndex_t ind = circular_buffer_index_get_i(&Node->indexer, Node->indexer.size - 1 - need);
        if(value) {
            LOG_DEBUG(FIR_INT, "Need:%u,Phy:%u,Val:%d", need, ind, Node->x[ind]);
            *value =(double) Node->x[ind];
            res = true;
        }
    }
    return res;
}

bool FirIntDiagConfig(const FirIntConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(FIR_INT, "N:%u,Order:%u,[%s]", Config->num, Config->size, Config->name);
        res = true;
    }
    return res;
}

#ifdef HAS_PC
#define FIR_STRUCTURE_FILE "FirStructure.gv"
#define RENDER "C:/Program Files/Google/Chrome/Application/chrome.exe"
#define NODE_X_STEP 3
#define NODE_Y_STEP 3
#define NODE_ROOT 2

#endif


#ifdef HAS_PC
bool fir_int_node_generate_graphviz(FirIntHandle_t* Node, FILE* FilePtr, int x, int y, char* text, double val) {
    bool res = false;
    fprintf(FilePtr, "%s [label=%f][pos=\"%d,%d!\"]\n", text, val, x, y);
    return res;
}
#endif

bool fir_int_generate_graphviz(uint8_t num) {
    bool res = false;
#ifdef HAS_PC
    FirIntHandle_t* Node = FirIntGetNode(num);
    if(Node) {
    	FirIntSample_t in = 0.0;
        FirIntSample_t out = 0.0;
        res = fir_pop(1, in, &out);
        FirIntSample_t mult = 0;
        FILE* GvFilePtr = NULL;

        char GvFileName[80]="";
        sprintf(GvFileName, "Fir%u_Code.gv", num);

        GvFilePtr = fopen(GvFileName, "w");
        if(GvFilePtr) {
            // int ret = 0;
            fprintf(GvFilePtr, "digraph FirFilter {\n");
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
                fprintf(GvFilePtr, "X%u [label=\"X%u:%d\"] [shape=box][pos = \"%d,%d!\"]\n", i, i, Node->x[i], x,
                        NODE_ROOT);
            }

            fprintf(GvFilePtr, "B0 [label=\"B0:%f\"][shape=circle][pos=\"%d,%d!\"]\n", Node->a[0], x,
                    NODE_ROOT + NODE_Y_STEP);
            for(i = 0; i < Node->size; i++) {
                x = NODE_X_STEP * i;
                fprintf(GvFilePtr, "B%u [label=\"B%u:%f\"] [shape=circle][pos = \"%d,%d!\"][color=red]\n", i, i,
                        Node->a[i], x, NODE_ROOT + NODE_Y_STEP);
            }

            fprintf(GvFilePtr, "Sum [label=\"+\"][shape=ellipse][pos = \"%d,%d!\"]\n", axis,
                    NODE_ROOT + 2 * NODE_Y_STEP);
            fprintf(GvFilePtr, "Y [label=Y][label=%f] [pos =\"%d,%d!\"]\n", out, axis, NODE_ROOT + 3 * NODE_Y_STEP);

            /*Connections*/
            mult = Node->a[0] * in;
            fprintf(GvFilePtr, "X->B0 [label=%f][color=red]\n", mult);
            fprintf(GvFilePtr, "B0->Sum[color = red]\n");
            fprintf(GvFilePtr, "in->X[color =black]\n");

            for(i = 0; i < Node->size - 1; i++) {
                fprintf(GvFilePtr, "X%u->B%u [label=%d] [color = red]\n", i, i + 1, Node->a[i + 1]);
                double mult = Node->x[i] * Node->a[i + 1];
                fprintf(GvFilePtr, "B%u->Sum[label=%f][color = red]\n", i + 1, mult);
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

            sprintf(SvgFileName, "Fir_%u_Schematic.svg", num);

            sprintf(CmdCommand, "start dot.exe -Kneato -Tsvg %s -o %s", GvFileName,SvgFileName);
            res = win_cmd_run(CmdCommand);
            // res = win_cmd_run("start chrome.exe -open out.svg");
            sprintf(CmdCommand, "start \"%s\" -open %s", RENDER,SvgFileName);
            // res = win_cmd_run(CmdCommand);
        } else {
            LOG_ERROR(FIR_INT, "FileGenerateErr");
        }
    } else {
        LOG_ERROR(FIR_INT, "NodeErr");
    }
#endif

    return res;
}

bool fir_int_diag(uint8_t num) {
    bool res = false;
    FirIntHandle_t* Node = FirIntGetNode(num);
    if(Node) {
        circular_buffer_index_diag(&Node->indexer);

        static const table_col_t cols[] = {{5, "i"},    {5, "i+1"},    {8, "RawX"}, {8, "PhyIdx"},
                                           {8, "X[i]"}, {8, "B[i+1]"}, {8, "Mult"}};
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint8_t i = 0;
        char log_line[150];
        double mult = 0.0;
        double x_in = 0.0;
        double sum = 0.0;
        double xi = 0.0;
        CircularBufferIndex_t phy_index = 0;

        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %3d " TSEP, log_line, -1);
        snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, 0);
        snprintf(log_line, sizeof(log_line), "%s %6s " TSEP, log_line, "---");
        snprintf(log_line, sizeof(log_line), "%s %6s " TSEP, log_line, "---");
        snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, x_in);
        snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, Node->a_real[0]);
        mult = x_in * Node->a_numerator[0]/ Node->denominator;
        snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, mult);
        cli_printf("%s" CRLF, log_line);
        sum += mult;
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        for(i = 0; i < Node->size - 1; i++) {
            phy_index = circular_buffer_index_calc_phy_index(Node->indexer.size, Node->indexer.cur, i);
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i + 1);
            snprintf(log_line, sizeof(log_line), "%s %6d " TSEP, log_line, Node->x[i]);
            snprintf(log_line, sizeof(log_line), "%s %6u " TSEP, log_line, phy_index);
            xi = 0.0;
            fir_int_expract_mem(num, i, &xi);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, xi);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, Node->a_real[i + 1]);
            mult = xi * Node->a_numerator[i + 1]/Node->denominator;
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

bool fir_int_diag_raw_mem(uint8_t num) {
    bool res = false;
    FirIntHandle_t* Node = FirIntGetNode(num);
    if(Node) {
        circular_buffer_index_diag(&Node->indexer);
        static const table_col_t cols[] = {
        		{5, "i"},
        		{8, "RawX"},
        		{8, "Areal"},
        		{8, "Anum"},
        		{8, "Aeff"},
        };
        uint8_t i = 0;
        char log_line[150];

        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        for(i = 0; i < Node->size - 1; i++) {
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
            snprintf(log_line, sizeof(log_line), "%s %6d " TSEP, log_line, Node->x[i]);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, Node->a_real[i]);
            snprintf(log_line, sizeof(log_line), "%s %6d " TSEP, log_line, Node->a_numerator[i]);
            float a_calcd = ((float) Node->a_numerator[i])/((float)Node->denominator);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, a_calcd);
            cli_printf("%s" CRLF, log_line);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}

bool fir_int_diag_mem(uint8_t num) {
    bool res = false;
    FirIntHandle_t* Node = FirIntGetNode(num);
    if(Node) {
        LOG_INFO(FIR_INT, "FIR%u PopCnt %u", num, Node->pop_cnt);
        circular_buffer_index_diag(&Node->indexer);
        static const table_col_t cols[] = {
            {5, "i"},
            {8, "x[i]"},
            {5, "cur"},
            {8, "X[i]"},
        };
        uint8_t i = 0;
        char log_line[150];

        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        for(i = 0; i < Node->size - 1; i++) {
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
            snprintf(log_line, sizeof(log_line), "%s %6d " TSEP, log_line, Node->x[i]);
            snprintf(log_line, sizeof(log_line), "%s %3s " TSEP, log_line, (i == Node->indexer.cur) ? "*" : " ");
            double x = 0.0;
            fir_int_expract_mem(num, i, &x);
            snprintf(log_line, sizeof(log_line), "%s %6.3f " TSEP, log_line, x);
            cli_printf("%s" CRLF, log_line);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}


const char* FirIntNodeToStr(const  FirIntHandle_t* const Node){
    static char text[300] = "?";
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sInit:%u,", text, Node->init);
        snprintf(text, sizeof(text), "%sM:%u,", text, Node->size);
        snprintf(text, sizeof(text), "%sMmax:%u,", text, Node->max_size);
        snprintf(text, sizeof(text), "%sFsam:%s Hz,", text, DoubleToStr(Node->sample_rate_hz));
        snprintf(text, sizeof(text), "%sFcut:%s Hz,", text, DoubleToStr(Node->cut_off_freq_hz));
        snprintf(text, sizeof(text), "%sInCnt:%u", text, Node->pop_cnt);
    }
    return text;
}
