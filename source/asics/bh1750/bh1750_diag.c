#include "bh1750_diag.h"

#include <stdio.h>

#include "bh1750_config.h"
#include "bh1750_const.h"
#include "bh1750_drv.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log_utils.h"
#include "std_includes.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

#ifndef HAS_BH1750
#error "+HAS_BH1750"
#endif

bool bh1750_diag(char* key_word1, char* key_word2) {
    bool res = false;
    uint16_t num = 0;
    static const table_col_t cols[] = {{5, "No"},  {5, "I2c"},    {7, "I2cAdd"}, {8, "code"},
                                       {10, "lx"}, {10, "lxMin"}, {10, "lxMax"}, {14, "name"}};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint8_t i = 0;
    uint16_t cnt = bh1750_get_cnt();
    for(i = 0; i <= cnt; i++) {
        const Bh1750Config_t* Config = Bh1750GetConfig(i);
        if(Config) {
            Bh1750Handle_t* Node = Bh1750GetNode(i);
            if(Node) {
                char temp[120] = {0};
                strcpy(temp, TSEP);
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, num);
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, Node->i2c_num);
                snprintf(temp, sizeof(temp), "%s 0x%02x  " TSEP, temp, Node->chip_addr);
                snprintf(temp, sizeof(temp), "%s 0x%04x " TSEP, temp, Node->word);
                snprintf(temp, sizeof(temp), "%s %8.3f " TSEP, temp, Node->lx.cur);
                snprintf(temp, sizeof(temp), "%s %8.3f " TSEP, temp, Node->lx.min);
                snprintf(temp, sizeof(temp), "%s %8.3f " TSEP, temp, Node->lx.max);
                snprintf(temp, sizeof(temp), "%s %8.312s " TSEP, temp, Config->name);
                snprintf(temp, sizeof(temp), "%s %u " TSEP, temp, Node->err_cnt);

                res = is_contain(temp, key_word1, key_word2);
                if(res) {
                    cli_printf("%s" CRLF, temp);
                    num++;
                }
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
