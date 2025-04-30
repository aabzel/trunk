#include "sw_nvram_diag.h"

#include <string.h>
#include <stdio.h>

#include "common_diag.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#ifdef HAS_DOT
#include "dot.h"
#endif
#include "sw_nvram.h"
#include "table_utils.h"
#include "writer_config.h"
#include "nor_flash_diag.h"
#include "log.h"
#include "nor_flash_drv.h"

#ifdef HAS_DOT
static char* Del2Color( NvRamNodeState_t state) {
    char * name ="indianred1";
    if(ENTRY_SAVE==state.not_deleted) {
        if(ENTRY_FRESHNESS_LATEST==state.freshness){
            name = "chartreuse";
        }else {
            name = "khaki";
        }
    }else {
        name = "gray94";
    }
    return name;
}

bool entry_graphiz(NvRamItem_t* Node, NvRamHeader_t* Header, uint32_t base){
    bool res = false;
   // int ret = 0;
    if(Header) {
        res = nor_flash_is_valid_addr(Node->nor_flash_num, base);
        if(res){
            fprintf( Node->dot_file, "Node0x%08x [label=\"Addr=%u\ \\n Size=%u\ \\n PhyAddr=0x%x\"] [style=filled] [fillcolor=%s]"CRLF,
                    base, Header->address.plane, Header->data_size,base, Del2Color(Header->state));
        }

        res = nor_flash_is_valid_addr(Node->nor_flash_num,Header->left_node_addr);
        if(res){
            fprintf( Node->dot_file, "Node0x%08x->Node0x%08x [color=blue]"CRLF,base,Header->left_node_addr);
        }else{
            fprintf( Node->dot_file, "NodeLeft0x%08x [label=\"\"][style = invis]"CRLF, base);
            fprintf( Node->dot_file, "Node0x%08x->NodeLeft0x%08x [color=blue]"CRLF,base,base);
        }

        res = nor_flash_is_valid_addr(Node->nor_flash_num,Header->right_node_addr);
        if(res) {
            fprintf( Node->dot_file, "Node0x%08x->Node0x%08x [color=red]"CRLF,base,Header->right_node_addr);
        }else {
            fprintf( Node->dot_file, "NodeRight0x%08x [label=\"\"] [style = invis]"CRLF, base);
            fprintf( Node->dot_file, "Node0x%08x->NodeRight0x%08x [color=red]"CRLF, base,base);
        }
    }
    return res;
}
#endif

bool sw_nvram_draw_tree_compose(char* name){
    bool res = false;

#ifdef HAS_DOT
    if(name) {
    	uint8_t nvram_num = 1;
        uint32_t nvram_cnt = sw_nvram_get_cnt();
        for(nvram_num = 1; nvram_num <= nvram_cnt; nvram_num++) {
            NvRamItem_t* Node = NvRamGetNode(nvram_num);
            const NvRamConfig_t* Config = NvRamGetConfig(nvram_num);
            if(Node && Config) {
                Node->dot_file = fopen(name, "w");
                if (Node->dot_file) {
                    LOG_INFO(NVRAM,"Open %s",name);
                    res = dot_header(Node->dot_file, "TB");
                    res = sw_nvram_traversal_in_order(Node, Node->start_mem, entry_graphiz );
                    res = dot_tail(Node->dot_file);
                    fclose(Node->dot_file);
                }
            }
        }
    }
#endif
    return res;
}

static const char* Fresh2Str(uint8_t freshness){
    char* name = "?";
    switch(freshness) {
        case ENTRY_FRESHNESS_OBSOLATE: name = "Old"; break;
        case ENTRY_FRESHNESS_LATEST: name = "New"; break;
        default: break;
    }
    return name;
}

static const char* Delete2Str(uint8_t deleted){
    char* name = "?";
    switch(deleted) {
        case ENTRY_DELETE: name = "Delete"; break;
        case ENTRY_SAVE: name = "Exist"; break;
        default: break;
    }
    return name;
}

bool entry_diag(NvRamItem_t* Node, NvRamHeader_t* Header, uint32_t base){
    bool res = false;
    if(Header) {
        uint16_t calc_crc16 = nor_flash_calc_crc16(Node->nor_flash_num, base+sizeof(NvRamHeader_t), Header->data_size);
        strcpy(Node->temp_str, TSEP);
        snprintf(Node->temp_str, sizeof(Node->temp_str), "%s 0x%08x " TSEP, Node->temp_str, base);
        snprintf(Node->temp_str, sizeof(Node->temp_str), "%s %10u " TSEP, Node->temp_str, Header->address.plane);
        snprintf(Node->temp_str, sizeof(Node->temp_str), "%s %4u " TSEP, Node->temp_str, Header->data_size);
        snprintf(Node->temp_str, sizeof(Node->temp_str), "%s 0x%04x " TSEP, Node->temp_str, Header->data_crc16);
        snprintf(Node->temp_str, sizeof(Node->temp_str), "%s 0x%04x " TSEP, Node->temp_str, calc_crc16);
        snprintf(Node->temp_str, sizeof(Node->temp_str), "%s 0x%08x " TSEP, Node->temp_str, Header->left_node_addr);
        snprintf(Node->temp_str, sizeof(Node->temp_str), "%s 0x%08x " TSEP, Node->temp_str, Header->right_node_addr);
        snprintf(Node->temp_str, sizeof(Node->temp_str), "%s %10u " TSEP, Node->temp_str, Header->write_time_stamp);
        snprintf(Node->temp_str, sizeof(Node->temp_str), "%s 0x%02x " TSEP, Node->temp_str, Header->state.byte);
        snprintf(Node->temp_str, sizeof(Node->temp_str), "%s %5s " TSEP, Node->temp_str, Fresh2Str(Header->state.freshness));
        snprintf(Node->temp_str, sizeof(Node->temp_str), "%s %6s " TSEP, Node->temp_str, Delete2Str(Header->state.not_deleted));
        cli_printf("%s" CRLF, Node->temp_str);
    }
    return res;
}

bool final_entry_diag(NvRamItem_t* Node, NvRamHeader_t* Header, uint32_t base){
    bool res = false;
    if(Header) {
    	if(ENTRY_SAVE==Header->state.not_deleted) {
    		if(ENTRY_FRESHNESS_LATEST == Header->state.freshness) {
                uint16_t calc_crc16 = nor_flash_calc_crc16(Node->nor_flash_num, base+sizeof(NvRamHeader_t), Header->data_size);
                strcpy(Node->temp_str, TSEP);
                snprintf(Node->temp_str, sizeof(Node->temp_str), "%s 0x%08x " TSEP, Node->temp_str, base);
                snprintf(Node->temp_str, sizeof(Node->temp_str), "%s %10u " TSEP, Node->temp_str, Header->address.plane);
                snprintf(Node->temp_str, sizeof(Node->temp_str), "%s %4u " TSEP, Node->temp_str, Header->data_size);
                snprintf(Node->temp_str, sizeof(Node->temp_str), "%s 0x%04x " TSEP, Node->temp_str, Header->data_crc16);
                snprintf(Node->temp_str, sizeof(Node->temp_str), "%s 0x%04x " TSEP, Node->temp_str, calc_crc16);
                snprintf(Node->temp_str, sizeof(Node->temp_str), "%s 0x%08x " TSEP, Node->temp_str, Header->left_node_addr);
                snprintf(Node->temp_str, sizeof(Node->temp_str), "%s 0x%08x " TSEP, Node->temp_str, Header->right_node_addr);
                snprintf(Node->temp_str, sizeof(Node->temp_str), "%s %10u " TSEP, Node->temp_str, Header->write_time_stamp);
                snprintf(Node->temp_str, sizeof(Node->temp_str), "%s 0x%02x " TSEP, Node->temp_str, Header->state.byte);
                cli_printf("%s" CRLF, Node->temp_str);
    		}
    	}
    }
    return res;
}

bool sw_nvram_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {12, "AddrPhy"},
        {12, "AddrVirt"},
        {6, "Size"},
        {8, "crc16R"},
        {8, "crc16C"},
        {12, "left"},
        {12, "right"},
        {12, "Time"},
        {6, "state"},
        {7, "fresh"},
        {8, "del"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t nvram_cnt = sw_nvram_get_cnt();
    uint8_t nvram_num = 1;
    for(nvram_num = 1; nvram_num <= nvram_cnt; nvram_num++) {
        NvRamItem_t* Node = NvRamGetNode(nvram_num);
        const NvRamConfig_t* Config = NvRamGetConfig(nvram_num);
        if(Node && Config) {
            res = sw_nvram_traversal_in_order( Node, Node->start_mem, entry_diag );
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}


bool sw_nvram_capacity(uint8_t nvram_num) {
    bool res = false;
    NvRamItem_t* Node = NvRamGetNode(nvram_num);
    if(Node) {
        uint32_t physical_address = sw_nvram_get_end(Node, Node->start_mem);
        uint32_t cur_page = Node->active_page;
        uint32_t total_size = Node->page[cur_page].size;
        uint32_t used_byte = physical_address - Node->page[cur_page].page_start;

        double used_precent = 100.0* ( (double)used_byte)/((double)total_size);
        double free_precent = 100.0* ( (double)(total_size-used_byte))/((double)total_size);

        LOG_WARNING(NVRAM,"CurPage %u", cur_page);
        LOG_WARNING(NVRAM,"Busy %u Size %u byte", used_byte, total_size);
        LOG_WARNING(NVRAM,"Busy %f %% Spare %f %%", used_precent, free_precent);

        res = nor_flash_usage(Node->nor_flash_num, 16*1024);
    }
    return res;
}

bool sw_nvram_final_diag(void){
    bool res = false;
    static const table_col_t cols[] = {
        {12, "AddrPhy"},
        {12, "AddrVirt"},
        {6, "Size"},
        {8, "crc16R"},
        {8, "crc16C"},
        {12, "left"},
        {12, "right"},
        {12, "Time"},
        {6, "state"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t nvram_cnt = sw_nvram_get_cnt();
    uint8_t nvram_num = 1; ;
    for(nvram_num = 1; nvram_num <= nvram_cnt; nvram_num++) {
        NvRamItem_t* Node = NvRamGetNode(nvram_num);
        const NvRamConfig_t* Config = NvRamGetConfig(nvram_num);
        if(Node && Config) {
            res = sw_nvram_traversal_in_order( Node, Node->start_mem, final_entry_diag );
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool SwNvramDiagPages(const NvRamPageConfig_t* const page){
    bool res = false;
    static const table_col_t cols[] = {
        {4, "num"},
        {12, "page_start"},
        {6, "size"},
        {12, "prefix"},
    };
    char line[80]="";
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t i = 2;
    for( i = 1; i <= 2; i++) {
        strcpy(line, TSEP);
        snprintf(line, sizeof(line), "%s 0x%1u " TSEP, line, page[i].num);
        snprintf(line, sizeof(line), "%s 0x%08x " TSEP, line, page[i].page_start);
        snprintf(line, sizeof(line), "%s %4u " TSEP, line, page[i].size);
        snprintf(line, sizeof(line), "%s 0x%08x " TSEP, line, page[i].prefix);
        cli_printf("%s" CRLF, line);
        res = true;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool SwNvramDiag(const NvRamConfig_t* const Config){
    bool res = false;

    LOG_INFO(NVRAM,"Num:%u,Name: %s, NorFlash:%u",
    		Config->num,
    		Config->name,
    		Config->nor_flash_num);
    res = SwNvramDiagPages(Config->page);

    return res;
}
